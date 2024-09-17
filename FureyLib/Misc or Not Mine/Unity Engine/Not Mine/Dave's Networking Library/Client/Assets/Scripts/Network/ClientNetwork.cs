using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.Reflection;
using System;
using Lidgren.Network;


// Client networking class
public class ClientNetwork : UCNetwork
{

    // Lidgren connection
    NetClient client;

    // This is the current area this client is in
    List<int> areaIds = new List<int>();

    // List of networkIds that this client can use to create networked objects
    Queue<int> freeIds;

    // This object contains all of the audio souces for playing voice chat from non-local objects
    // As new objects chat remotely, audio sources for them will be added as child objects to this object
    public GameObject remoteVoiceChatContainerObject;
    // This is the prefab object we'll instantiate for playing remote audio. Make sure this has an audio source component and a VoiceChatPlayer component
    public GameObject remoteVoiceChatPrefab;

#if UNITY_EDITOR
    float lastRPCCallClearTime;
    int RPCCallWarningLevel = 20;
    Dictionary<string, int> recentRPCCalls = new Dictionary<string, int>();
#endif

    // Use this for initialization
    override protected void Awake()
    {
        base.Awake();
        freeIds = new Queue<int>();
        isServer = false;

        // Set up the client
        NetPeerConfiguration config = new NetPeerConfiguration("UpsilonCircuit");
        //config.SimulatedMinimumLatency = 0.2f;
        //config.SimulatedLoss = 0.1f;
        connection = new NetClient(config);
        connection.Start();

        client = connection as NetClient;
        

#if UNITY_EDITOR
        lastRPCCallClearTime = Time.realtimeSinceStartup;
#endif
    }

    // Update is called once per frame
    override public void Update()
    {
        base.Update();
    }

    // Connect to the Upsilon Circuit server
    // Username, Password, clientType, and uniqueId are all optional data that will be sent to the server
    public void Connect(string aServer, int aPort, string aUsername, string aPassword, string aClientType, ulong aUniqueId)
    {
        if (IsConnected())
        {
            Debug.LogError("Attempting to connect to a new server while already connected.");
            return;
        }

        NetOutgoingMessage sendMsg = client.CreateMessage();
        sendMsg.Write(aUsername);
        sendMsg.Write(aPassword);
        sendMsg.Write(aClientType);
        sendMsg.Write(aUniqueId);

        client.Connect(aServer, aPort, sendMsg);
    }

    public void Disconnect(string aReason)
    {
        client.Disconnect(aReason);
        DestroyNetworkObjects(true);
    }

    // Function called when we get a status changed message
    override protected void HandleMessage_StatusChanged(NetIncomingMessage aMsg)
    {
        base.HandleMessage_StatusChanged(aMsg);
    }

    // Function called when we get a data message
    override protected void HandleMessage_Data(NetIncomingMessage aMsg)
    {
        // Data has just been sent from the server, what to do with it...
        MessageType type = (MessageType)aMsg.ReadInt32();
        if (type == MessageType.RPC)
        {
            ReceiveRPC(aMsg);
        }
        else if (type == MessageType.AddToArea)
        {
            int newAreaId = aMsg.ReadInt32();

            // Add this area id to the list of areas we are in
            areaIds.Add(newAreaId);
            SendMessage("OnChangeArea", SendMessageOptions.DontRequireReceiver);

        }
        else if (type == MessageType.RemoveFromArea)
        {
            int oldAreaId = aMsg.ReadInt32();

            // Remove the area id from the list of areas we are in
            areaIds.Remove(oldAreaId);
        }
        else if (type == MessageType.IdAllocation)
        {
            // Add the new id to our list of free ids
            int startId = aMsg.ReadInt32();
            int endId = aMsg.ReadInt32();
            //Debug.Log("Client adding ids " + startId.ToString() + " to " + endId.ToString() + " to its free ids");
            for (; startId < endId; startId++)
            {
                freeIds.Enqueue(startId);
            }

        }
        else if (type == MessageType.SyncUpdate || type == MessageType.LiteSyncUpdate)
        {
            aMsg.ReadInt32(); // Read the receiver value, which we don't care about here
            int networkId = aMsg.ReadInt32();
            Vector3 position = new Vector3();
            Quaternion orientation = new Quaternion();
            if (type == MessageType.SyncUpdate)
            {
                float x = aMsg.ReadFloat();
                float y = aMsg.ReadFloat();
                float z = aMsg.ReadFloat();
                position = new Vector3(x, y, z);

                x = aMsg.ReadFloat();
                y = aMsg.ReadFloat();
                z = aMsg.ReadFloat();
                float w = aMsg.ReadFloat();
                orientation = new Quaternion(x, y, z, w);
            }

            int byteDataLength = aMsg.ReadInt32();
            byte[] byteData = aMsg.ReadBytes(byteDataLength); // TODO: We could do some better checking here

            // Tell the NetworkSync component about the incoming data
            if (!netIdObjMap.ContainsKey(networkId))
            {
                Debug.LogWarning("Received a SyncUpdate for a networkId this client doesn't know about: " + networkId);
                return;
            }
            if (type == MessageType.SyncUpdate)
            {
                netIdObjMap[networkId].networkSync.ReceiveSyncData(byteData, position, orientation);
            }
            else if (type == MessageType.LiteSyncUpdate)
            {
                netIdObjMap[networkId].networkSync.ReceiveLiteSyncData(byteData);
            }
        }
        else if (type == MessageType.Instantiate)
        {
            int netId = aMsg.ReadInt32();
            string prefabName = aMsg.ReadString();

            float x = aMsg.ReadFloat();
            float y = aMsg.ReadFloat();
            float z = aMsg.ReadFloat();
            Vector3 position = new Vector3(x, y, z);

            x = aMsg.ReadFloat();
            y = aMsg.ReadFloat();
            z = aMsg.ReadFloat();
            float w = aMsg.ReadFloat();
            Quaternion orientation = new Quaternion(x, y, z, w);

            string json = aMsg.ReadString();
            // Create the object locally
            GameObject tempObj = CreateLocalObject(prefabName, position, orientation, netId);

            if(tempObj != null && !string.IsNullOrEmpty(json))
            {
                tempObj.SendMessage("ParseJson", json);
            }
        }
        else if (type == MessageType.ConnectNetworkSync)
        {
            float xPos = aMsg.ReadFloat();
            float yPos = aMsg.ReadFloat();
            float zPos = aMsg.ReadFloat();
            /*
            float xRot = aMsg.ReadFloat();
            float yRot = aMsg.ReadFloat();
            float zRot = aMsg.ReadFloat();
            float wRot = aMsg.ReadFloat();
            */
            // Read the rotation values
            aMsg.ReadFloat();
            aMsg.ReadFloat();
            aMsg.ReadFloat();
            aMsg.ReadFloat();
            //string name = aMsg.ReadString();
            aMsg.ReadString();
            int networkId = aMsg.ReadInt32();

            Vector3 position = new Vector3(xPos, yPos, zPos);

            // TODO: This just finds a network sync by position. We could find it by rotation as well.
            NetworkSync[] netSyncs = FindObjectsOfType<NetworkSync>();
            for (int i = 0; i < netSyncs.Length; i++)
            {
                if (netSyncs[i].position == position)
                {
                    Debug.Log("Assigning a network id for network sync " + netSyncs[i].GetInstanceID());
                    netSyncs[i].clientNet = this;
                    netSyncs[i].SetId(networkId);
                    return;
                }
            }
            Debug.LogError("ConnectNetworkSync received, but was unable to find an unconnected network sync.");
        }
        else if (type == MessageType.OwnershipGained)
        {
            // Gain ownership of a specific object
            int objectId = aMsg.ReadInt32();

            AddOwnedId(objectId);
        }
        else if (type == MessageType.OwnershipLost)
        {
            // Gain ownership of a specific object
            int objectId = aMsg.ReadInt32();

            RemoveOwnedId(objectId);
        }
        else if (type == MessageType.Destroy)
        {
            // Destroy the object with the given network id
            int objectId = aMsg.ReadInt32();

            DestroyNetworkObjects(objectId);
        }
        else if (type == MessageType.VoiceData)
        {
            //Speed back playback!

            int networkObjectId = aMsg.ReadInt32();

            /*VoiceChatPacket packet = new VoiceChatPacket();
            packet.Compression = (VoiceChatCompression)aMsg.ReadInt32();
            packet.NetworkId = aMsg.ReadInt32();
            VoiceChatChannel channel = (VoiceChatChannel)aMsg.ReadInt32();
            packet.Length = aMsg.ReadInt32();
            packet.Data = aMsg.ReadBytes(packet.Length);

            // Find out which object should be playing this audio, send it to them
            switch (channel)
            {
                case VoiceChatChannel.Radio:
                    // If this is an object that isn't in our area, or isn't a specific object at all, set up a new audio source to play from
                    if (!remoteVoiceChatPlayers.ContainsKey(networkObjectId))
                    {

                        GameObject newVoiceChatObj = Instantiate(remoteVoiceChatPrefab);
                        newVoiceChatObj.transform.SetParent(remoteVoiceChatContainerObject.transform, false);
                        newVoiceChatObj.name = "RemoteVoiceChat - " + networkObjectId.ToString();

                        VoiceChatPlayer vcp = newVoiceChatObj.GetComponent<VoiceChatPlayer>();
                        vcp.sourceNetId = networkObjectId;
                        vcp.isRadio = true;

                        remoteVoiceChatPlayers[networkObjectId] = vcp;

                    }
                    remoteVoiceChatPlayers[networkObjectId].OnNewSample(packet);
                    break;
                case VoiceChatChannel.Proximity:
                    if (netIdObjMap.ContainsKey(networkObjectId))
                    {
                        if (netIdObjMap[networkObjectId].voiceChatPlayer == null)
                        {
                            // If they dont have a voice chat player, set one up real quick (requires an AudioSource)
                            if (netIdObjMap[networkObjectId].gameObject.GetComponent<VoiceChatPlayer>() == null)
                            {
                                netIdObjMap[networkObjectId].voiceChatPlayer = netIdObjMap[networkObjectId].gameObject.AddComponent<VoiceChatPlayer>();
                            }
                        }
                        else
                        {
                            if (netIdObjMap[networkObjectId].gameObject.GetComponent<VoiceChatPlayer>() == null)
                            {
                                netIdObjMap[networkObjectId].voiceChatPlayer = netIdObjMap[networkObjectId].gameObject.AddComponent<VoiceChatPlayer>();
                            }
                        }

                        netIdObjMap[networkObjectId].voiceChatPlayer.OnNewSample(packet);
                    }
                    else
                    {
                        Debug.Log("Proximity VoiceData has been received by this client, but it doesn't have a network object with id " + networkObjectId);
                    }
                    break;
            }
            */
        }
        else
        {
            Debug.LogError("Unhandled message type sent to client " + type.ToString());
        }
    }

    // Function called when we get a connection approval message
    override protected void HandleMessage_ConnectionApproval(NetIncomingMessage aMsg)
    {
        Debug.LogWarning("HandleMessage_ConnectionApproval is unimplemented");
    }

    // Function called when we get a latency updated message
    override protected void HandleMessage_ConnectionLatencyUpdated(NetIncomingMessage aMsg)
    {
        Debug.LogWarning("HandleMessage_ConnectionLatencyUpdated is unimplemented");
    }

    // Call a RPC on a single client
    override public void CallRPC(string aFunctionName, long aClientId, int aNetworkId, params object[] aParams)
    {
        Debug.Log("Calling a RPC to a single client from a client is currently unimmplemented");
        return;
    }

    override public void CallRPC(string aFunctionName, MessageReceiver aReceiver, int aNetworkId, params object[] aParams)
    {
        CallRPC(aFunctionName, aReceiver, aNetworkId, NetDeliveryMethod.ReliableOrdered, aParams);
    }

    // Call a RPC with a specific net delivery method
    public void CallRPC(string aFunctionName, MessageReceiver aReceiver, int aNetworkId, NetDeliveryMethod aDeliveryMethod, params object[] aParams)
    {
        if (!IsConnected())
        {
            Debug.LogWarning("Unable to call RPC while not connected to a server");
            return;
        }

        NetOutgoingMessage sendMsg = client.CreateMessage();
        sendMsg.Write((int)MessageType.RPC); // This is an rpc
        sendMsg.Write((int)aReceiver); // Which other clients this should be sent to
        sendMsg.Write(aNetworkId); // What network object on the clients this should be sent to
        sendMsg.Write(aFunctionName); // What network object on the clients this should be sent to

        // Write the RPC parameters
        WriteRPCParams(ref sendMsg, aParams);

        // Send the message
        client.SendMessage(sendMsg, aDeliveryMethod);

#if UNITY_EDITOR
        // If it's been longer than 1 second since we last cleared, clear now
        if (Time.realtimeSinceStartup - lastRPCCallClearTime > 1.0)
        {
            recentRPCCalls.Clear();
            lastRPCCallClearTime = Time.realtimeSinceStartup;
        }
        if (recentRPCCalls.ContainsKey(aFunctionName))
        {
            recentRPCCalls[aFunctionName] += 1;
        }
        else
        {
            recentRPCCalls[aFunctionName] = 1;
        }
        int totalRPCCalls = 0;
        string logString = "";
        foreach (KeyValuePair<string, int> element in recentRPCCalls)
        {
            totalRPCCalls += element.Value;
            logString += element.Key + ": " + element.Value + "\n";
        }
        if (totalRPCCalls > RPCCallWarningLevel)
        {
            Debug.LogWarning(totalRPCCalls + " RPC calls made in the last second. Types are: \n" + logString);
        }
#endif
    }


    protected override void ReceiveRPC(NetIncomingMessage aMsg)
    {
        aMsg.ReadInt32(); // Read the receiver value, which we don't care about here
        int networkId = aMsg.ReadInt32();
        string functionName = aMsg.ReadString();
        //print("Got RPC: " + functionName);
        // Get the arguments
        List<object> args = new List<object>();
        ReadRPCParams(ref args, ref aMsg);

        // Find the object with this networkId
        GameObject targetObject;
        if (networkId == -1)
        {
            targetObject = this.gameObject;
        }
        else
        {
            if (!netIdObjMap.ContainsKey(networkId))
            {
                Debug.LogError(functionName + " was sent to unknown net object " + networkId.ToString());
                return;
            }
            targetObject = netIdObjMap[networkId].gameObject;
            if (targetObject == null)
            {
                Debug.LogError("Unable to get object from id map " + networkId.ToString());
                return;
            }
        }

        // Find the method to call
        // Loop through all the script components, finding a function
        bool rpcSent = false;
        MethodInfo theMethod = null;
        Component targetScript = null;
        Component[] scripts = targetObject.GetComponents(typeof(MonoBehaviour));
        for (int i = 0; i < scripts.Length; i++)
        {
            theMethod = null;
            // Debug.Log(scripts[i].GetType().ToString());
            theMethod = scripts[i].GetType().GetMethod(functionName);
            if (theMethod != null)
            {
                if (!rpcSent)
                    rpcSent = true;

                targetScript = scripts[i];

                try
                {
                    theMethod.Invoke(targetScript, args.ToArray());
                }
                catch (TargetParameterCountException exp)
                {
                    Debug.LogError(targetScript + "'s function " + theMethod + " has a parameter count exception.");
                    Debug.LogError(exp.ToString());
                }
                catch (TargetException e)
                {
                    Debug.Log(functionName);
                    Debug.LogError("Unable to call RPC method: " + e.ToString());
                }
                catch (Exception exp)
                {
                    Debug.LogError(targetScript + "'s function " + theMethod + " has an exception.");
                    Debug.LogError(exp.ToString());
                }
                //break;
            }
        }
        if (!rpcSent)
        {
            GameObject obj = GetGameObject(networkId);
            string objectInfo = " null object with net id " + networkId;
            if (obj != null)
            {
                objectInfo = obj.name;
            }
            Debug.LogWarning("Unhandled RPC call to function " + functionName + " for object " + objectInfo);
            return;
        }
    }

    // Send data about a sync'ed networked object to the server
    override public void SyncNetworkData(int aNetworkId, MessageReceiver aMessageReceiver, UCNetwork.DeliveryMethod aDeliveryMethod, byte[] aData, Vector3 aPosition, Quaternion aRotation)
    {
        if (!IsConnected())
        {
            return;
        }
        NetOutgoingMessage sendMsg = client.CreateMessage();
        sendMsg.Write((int)MessageType.SyncUpdate);
        sendMsg.Write((int)aMessageReceiver);
        sendMsg.Write(aNetworkId);
        sendMsg.Write(aPosition.x);
        sendMsg.Write(aPosition.y);
        sendMsg.Write(aPosition.z);
        sendMsg.Write(aRotation.x);
        sendMsg.Write(aRotation.y);
        sendMsg.Write(aRotation.z);
        sendMsg.Write(aRotation.w);
        sendMsg.Write(aData.Length);
        sendMsg.Write(aData);

        // Send the message to the server
        client.SendMessage(sendMsg, (NetDeliveryMethod)aDeliveryMethod, UCNetwork.SyncSequenceChannel);
    }

    // Send data about a sync'ed network object to server that has not changed it's position or rotation
    override public void LiteSyncNetworkData(int aNetworkId, MessageReceiver aMessageReceiver, UCNetwork.DeliveryMethod aDeliveryMethod, byte[] aData)
    {
        if (!IsConnected())
        {
            return;
        }
        NetOutgoingMessage sendMsg = client.CreateMessage();
        sendMsg.Write((int)MessageType.LiteSyncUpdate);
        sendMsg.Write((int)aMessageReceiver);
        sendMsg.Write(aNetworkId);
        sendMsg.Write(aData.Length);
        sendMsg.Write(aData);

        // Send the message to the server
        client.SendMessage(sendMsg, (NetDeliveryMethod)aDeliveryMethod, UCNetwork.SyncSequenceChannel);
    }

    // Get the current area id
    public List<int> GetAreas()
    {
        return areaIds;
    }

    // Change the area this client is in
    public void AddToArea(int aNewAreaId)
    {
        //Debug.Log("AddToArea request: " + aNewAreaId);
        if (areaIds.Contains(aNewAreaId))
        {
            return;
        }

        // Send a message to the server letting it know we want to go to a new area
        NetOutgoingMessage sendMsg = client.CreateMessage();
        sendMsg.Write((int)MessageType.AddToArea);
        sendMsg.Write(aNewAreaId);
        // Send the message
        client.SendMessage(sendMsg, NetDeliveryMethod.ReliableOrdered);
    }

    public void RemoveFromArea(int aOldAreaId)
    {
        //Debug.Log("RemoveFromArea request: " + aOldAreaId);
        if (!areaIds.Contains(aOldAreaId))
        {
            return;
        }

        // Send a message to the server letting it know we want to go to a new area
        NetOutgoingMessage sendMsg = client.CreateMessage();
        sendMsg.Write((int)MessageType.RemoveFromArea);
        sendMsg.Write(aOldAreaId);
        // Send the message
        client.SendMessage(sendMsg, NetDeliveryMethod.ReliableOrdered);
    }

    public void AddObjectToArea(int aObjectId, int aNewAreaId)
    {
        //Debug.Log("AddObjectToArea request: " + aNewAreaId);

        // Send a message to the server letting it know we want to go to a new area
        NetOutgoingMessage sendMsg = client.CreateMessage();
        sendMsg.Write((int)MessageType.AddObjectToArea);
        sendMsg.Write(aObjectId);
        sendMsg.Write(aNewAreaId);
        // Send the message
        client.SendMessage(sendMsg, NetDeliveryMethod.ReliableOrdered);
    }

    public void RemoveObjectFromArea(int aObjectId, int aOldAreaId)
    {
        //Debug.Log("RemoveObjectFromArea request: " + aOldAreaId);

        // Send a message to the server letting it know we want to go to a new area
        NetOutgoingMessage sendMsg = client.CreateMessage();
        sendMsg.Write((int)MessageType.RemoveObjectFromArea);
        sendMsg.Write(aObjectId);
        sendMsg.Write(aOldAreaId);
        // Send the message
        client.SendMessage(sendMsg, NetDeliveryMethod.ReliableOrdered);
    }

    // Instantiate a new object over the network
    override public GameObject Instantiate(string prefabName, Vector3 aPostion, Quaternion aOrientation)
    {
        if (!IsConnected())
        {
            Debug.Log("ClientNetwork::Instantiate called while not connected to a server");
            return null;
        }
        // Get a free id
        if (freeIds.Count <= 0)
        {
            Debug.LogError("ClientNetwork::Instantiate, no more network ids available");
            return null;
        }
        int newId = freeIds.Dequeue();

        Debug.Log("ClientNetwork::Instantiate - Creating new obj with id " + newId + "(" + prefabName + ")");

        // Create the object locally
        GameObject newObj = CreateLocalObject(prefabName, aPostion, aOrientation, newId);

        if (newObj == null)
        {
            freeIds.Enqueue(newId); // Put the id back
            return null;
        }

        // Let the server know about the new object
        NetOutgoingMessage sendMsg = client.CreateMessage();
        sendMsg.Write((int)MessageType.Instantiate);
        sendMsg.Write(newId);
        sendMsg.Write(prefabName);
        sendMsg.Write(aPostion.x);
        sendMsg.Write(aPostion.y);
        sendMsg.Write(aPostion.z);
        sendMsg.Write(aOrientation.x);
        sendMsg.Write(aOrientation.y);
        sendMsg.Write(aOrientation.z);
        sendMsg.Write(aOrientation.w);
        client.SendMessage(sendMsg, NetDeliveryMethod.ReliableOrdered);

        // Make sure we know we own this object
        AddOwnedId(newId);

        // Return the new local object
        return newObj;
    }

    private GameObject CreateLocalObject(string aPrefabName, Vector3 aPosition, Quaternion aOrientation, int aNetId)
    {
        // Create the object locally
        GameObject newObj = Instantiate(Resources.Load(aPrefabName), aPosition, aOrientation) as GameObject;
        if (newObj == null)
        {
            Debug.LogError("ClientNetwork.CreateLocalObject can't instantiate unknown prefab " + aPrefabName);
            return null;
        }

        // Set the id on the NetworkId script
        NetworkSync netSync = newObj.GetComponent(typeof(NetworkSync)) as NetworkSync;
        if (netSync != null)
        {
            netSync.clientNet = this;
            netSync.SetId(aNetId);

        }
        else
        {
            Debug.LogWarning("Instantiating object " + gameObject.name + " over the network without a NetworkSync");
        }

        // Tell the object everything for the network has been initialized
        newObj.SendMessage("NetworkInitialized", SendMessageOptions.DontRequireReceiver);


        return newObj;
    }

    // A network sync wants to be assigned a network id
    public void ConnectNetworkSync(NetworkSync aNetworkSync)
    {
        // Id's requested from a network sync that this client hasn't instantiated, and the server hasn't created, need to the requested from the server
        // This handles the case where a NetworkSync is assigned to an object inside of a scene

        Debug.Log("ClientNetwork::RequestNetworkId - Requesting a network id for network sync " + aNetworkSync.GetInstanceID());

        // Let the server know about the new object
        NetOutgoingMessage sendMsg = client.CreateMessage();
        sendMsg.Write((int)MessageType.ConnectNetworkSync);
        sendMsg.Write(aNetworkSync.position.x);
        sendMsg.Write(aNetworkSync.position.y);
        sendMsg.Write(aNetworkSync.position.z);
        sendMsg.Write(aNetworkSync.rotation.x);
        sendMsg.Write(aNetworkSync.rotation.y);
        sendMsg.Write(aNetworkSync.rotation.z);
        sendMsg.Write(aNetworkSync.rotation.w);
        sendMsg.Write(aNetworkSync.gameObject.name);

        client.SendMessage(sendMsg, NetDeliveryMethod.ReliableOrdered);
    }

    // Destroy a network object
    override public void Destroy(int aObjectId)
    {
        if (!netIdObjMap.ContainsKey(aObjectId))
        {
            Debug.LogWarning("Unable to destroy unknown object " + aObjectId);
            return;
        }

        // Make a request to the server to delete the object
        NetOutgoingMessage sendMsg = client.CreateMessage();
        sendMsg.Write((int)MessageType.Destroy);
        sendMsg.Write(aObjectId);
        client.SendMessage(sendMsg, NetDeliveryMethod.ReliableOrdered);
    }

    private void DestroyNetworkObjects(int aObjectId)
    {
        if (!netIdObjMap.ContainsKey(aObjectId))
        {
            Debug.LogWarning("Unable to destroy unknown object " + aObjectId);
            return;
        }

        Destroy(netIdObjMap[aObjectId].gameObject);
    }

    // Destroy all the network objects, except for ones that follow the client
    private void DestroyNetworkObjects(bool aDestroyFollowedByClient)
    {
        foreach (KeyValuePair<int, NetIdMapData> data in netIdObjMap)
        {
            if (data.Value.networkSync.followsClient && !aDestroyFollowedByClient)
            {
                continue;
            }
            Destroy(data.Value.gameObject);
        }
    }

    // Send voice data to the server
    public void SendVoiceData(int aNetObjId, int aCompressionType, int aDataLength, byte[] aData, int aVoiceDataId, int aChannel = 1)
    {
        // Send the data to the server
        NetOutgoingMessage sendMsg = client.CreateMessage();
        sendMsg.Write((int)MessageType.VoiceData);
        sendMsg.Write(aNetObjId);
        sendMsg.Write(aCompressionType);
        sendMsg.Write(aVoiceDataId);
        sendMsg.Write((int)aChannel);
        sendMsg.Write(aDataLength);
        sendMsg.Write(aData);

        client.SendMessage(sendMsg, NetDeliveryMethod.ReliableSequenced);
    }

    // Get the remote voice chat player for a given network object
    public AudioSource GetRemoteVoiceChatPlayer(int aNetworkId)
    {
        return null;
    }
}
