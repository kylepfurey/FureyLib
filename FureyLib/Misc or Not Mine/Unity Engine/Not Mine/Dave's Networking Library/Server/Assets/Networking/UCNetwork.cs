using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using Lidgren.Network;

// The base networking class for Upsilon Circuit
public abstract class UCNetwork : MonoBehaviour
{
    // Is this running as a server
    [HideInInspector]
    public bool isServer;

    // Port
    public static int port = 603;

    // Sequence channel id for sync data
    protected static int SyncSequenceChannel = 10;
    protected static int VoiceSequenceChannel = 11;

    // This network connection (could be a NetServer, or NetClient)
    protected NetPeer connection = null;

    // List of ids this owns
    List<int> ownedIds;

    // Maps networkIds to their gameobject and networkId component
    protected class NetIdMapData
    {
        public GameObject gameObject;
        //public NetworkSync networkSync;
    };
    protected Dictionary<int, NetIdMapData> netIdObjMap;

    // Delivery methods
    public enum DeliveryMethod
    {
        ReliableOrdered = NetDeliveryMethod.ReliableOrdered,
        UnreliableSequenced = NetDeliveryMethod.UnreliableSequenced
    };

    // Receiver type
    public enum MessageReceiver
    {
        ServerOnly = 1,
        AllClients = 2,
        OtherClients = 4,
        AllClientsInArea = 8,
        OtherClientsInArea = 16,
        SingleClient = 32
    };

    // The types of messages we'll be sending between the server/clients
    protected enum MessageType
    {
        SyncUpdate = 1,
        Instantiate = 2,
        AddToArea = 3,
        RemoveFromArea = 4,
        RPC = 5,
        IdAllocation = 6,
        OwnershipGained = 7,
        OwnershipLost = 8,
        Destroy = 9,
        VoiceData = 10,
        LiteSyncUpdate = 11,
        ConnectNetworkSync = 12,
        AddObjectToArea = 13,
        RemoveObjectFromArea = 14
    };

    // Initialize the static instance
    virtual protected void Awake()
    {
        ownedIds = new List<int>();
        netIdObjMap = new Dictionary<int, NetIdMapData>();
    }

    public void RemoveNetObject(int aNetworkId)
    {
        if (!netIdObjMap.ContainsKey(aNetworkId))
            Debug.LogError("RemoveNetObject called with a key that doesn't exist");
        else
            netIdObjMap.Remove(aNetworkId);
    }

    /*public void AddNetObject(int aNetworkId, NetworkSync aNetworkSync, GameObject gameObject)
    {
        if (netIdObjMap.ContainsKey(aNetworkId))
        {
            Debug.LogError("AddNetObject called with a key that already exists: " + aNetworkId);
            return;
        }
        NetIdMapData mapData = new NetIdMapData();
        mapData.gameObject = gameObject;
        mapData.networkSync = aNetworkSync;
        mapData.voiceChatPlayer = null;

        netIdObjMap[aNetworkId] = mapData;
    }*/

    // Update is called once per frame
    virtual public void Update()
    {
        // See if the network connection has been created
        if (connection == null)
        {
            return;
        }
        float initialTime = Time.realtimeSinceStartup;
        double netTime = GetTime();

        int statusMessages = 0;
        int dataMessages = 0;
        int connectionMessages = 0;
        int debugMessage = 0;
        int warningMessages = 0;
        int errorMessages = 0;
        int otherMessages = 0;

        // Read any new messages from the network
        List<NetIncomingMessage> msg = new List<NetIncomingMessage>();
        int msgCount = connection.ReadMessages(msg);
        for (int i = 0; i < msgCount; i++)
        {
            switch (msg[i].MessageType)
            {
                // See https://code.google.com/p/lidgren-network-gen3/wiki/IncomingMessageTypes
                case NetIncomingMessageType.StatusChanged:
                    statusMessages++;
                    HandleMessage_StatusChanged(msg[i]);
                    break;
                case NetIncomingMessageType.Data:
                    dataMessages++;
                    HandleMessage_Data(msg[i]);
                    break;
                case NetIncomingMessageType.ConnectionApproval:
                    connectionMessages++;
                    HandleMessage_ConnectionApproval(msg[i]);
                    break;
                case NetIncomingMessageType.ConnectionLatencyUpdated:
                    connectionMessages++;
                    HandleMessage_ConnectionLatencyUpdated(msg[i]);
                    break;

                // Error/Warning messages
                case NetIncomingMessageType.DebugMessage:
                    debugMessage++;
                    HandleMessage_DebugMessage(msg[i]);
                    break;
                case NetIncomingMessageType.VerboseDebugMessage:
                    debugMessage++;
                    HandleMessage_VerboseDebugMessage(msg[i]);
                    break;
                case NetIncomingMessageType.WarningMessage:
                    warningMessages++;
                    HandleMessage_WarningMessage(msg[i]);
                    break;
                case NetIncomingMessageType.ErrorMessage:
                    errorMessages++;
                    HandleMessage_ErrorMessage(msg[i]);
                    break;

                // Messages types we shouldn't have to deal with
                case NetIncomingMessageType.Error:
                case NetIncomingMessageType.UnconnectedData:
                case NetIncomingMessageType.DiscoveryRequest:
                case NetIncomingMessageType.DiscoveryResponse:
                case NetIncomingMessageType.NatIntroductionSuccess:
                case NetIncomingMessageType.Receipt:
                default:
                    otherMessages++;
                    Debug.LogError("Unhandled network message type: " + msg[i].MessageType);
                    break;
            }
            connection.Recycle(msg[i]);
        }

        float deltaTime = (Time.realtimeSinceStartup - initialTime);
        int messagesProcessed = statusMessages + dataMessages + connectionMessages + debugMessage + warningMessages + errorMessages + otherMessages;
        if (messagesProcessed >= 100 || deltaTime > 1.0f)
        {
            Debug.Log(GetTime() + ": NetTime:" + netTime + " " + messagesProcessed + " network messages proccessed in " + (Time.realtimeSinceStartup - initialTime).ToString() + " seconds" +
                "\n\t statusMessages: " + statusMessages +
                "\n\t dataMessages: " + dataMessages +
                "\n\t connectionMessages: " + connectionMessages +
                "\n\t debugMessage: " + debugMessage +
                "\n\t warningMessages: " + warningMessages +
                "\n\t errorMessages: " + errorMessages +
                "\n\t otherMessages: " + otherMessages
                );
        }
    }

    // Call a RPC
    abstract public void CallRPC(string aFunctionName, long aClientId, int aNetworkId, params object[] aParams);
    abstract public void CallRPC(string aFunctionName, MessageReceiver aReceiver, int aNetworkId, params object[] aParams);
    abstract protected void ReceiveRPC(NetIncomingMessage aMsg);
    protected void WriteRPCParams(ref NetOutgoingMessage aMsg, params object[] aParams)
    {
        // Build all the arguments up for the RPC
        string typeString = "";
        foreach (object arg in aParams)
        {
            if (arg is long)
            {
                typeString += "l";
            }
            else if (arg is ulong)
            {
                typeString += "u";
            }
            else if (arg is int)
            {
                typeString += "i";
            }
            else if (arg is float)
            {
                typeString += "f";
            }
            else if (arg is string)
            {
                typeString += "s";
            }
            else if (arg is bool)
            {
                typeString += "b";
            }
            else if (arg is Vector3)
            {
                typeString += "v";
            }
            else if (arg is Quaternion)
            {
                typeString += "q";
            }
            else if (arg is int[])
            {
                typeString += "a";
            }
            else {
                Debug.LogError("Unimplemented RPC parameter type " + arg.GetType());
                return;
            }
        }
        aMsg.Write(typeString);

        // Write all the parameters
        foreach (object arg in aParams)
        {
            if (arg is long)
            {
                aMsg.Write((long)arg);
            }
            else if (arg is ulong)
            {
                aMsg.Write((ulong)arg);
            }
            else if (arg is int)
            {
                aMsg.Write((int)arg);
            }
            else if (arg is float)
            {
                aMsg.Write((float)arg);
            }
            else if (arg is string)
            {
                aMsg.Write((string)arg);
            }
            else if (arg is bool)
            {
                aMsg.Write((bool)arg);
            }
            else if (arg is Vector3)
            {
                Vector3 vec = (Vector3)arg;
                aMsg.Write(vec.x);
                aMsg.Write(vec.y);
                aMsg.Write(vec.z);
            }
            else if (arg is Quaternion)
            {
                Quaternion quat = (Quaternion)arg;
                aMsg.Write(quat.x);
                aMsg.Write(quat.y);
                aMsg.Write(quat.z);
                aMsg.Write(quat.w);
            }
            else if (arg is int[])
            {
                int[] temp = (int[])arg;
                aMsg.Write(temp.Length);
                foreach(int a in temp)
                {
                    aMsg.Write(a);
                }
            }
        }
    }
    protected void ReadRPCParams(ref List<object> aArgs, ref NetIncomingMessage aMsg)
    {
        string argDef = aMsg.ReadString();
        foreach (char c in argDef)
        {
            if (c == 'l')
            {
                aArgs.Add(aMsg.ReadInt64());
            }
            else if (c == 'u')
            {
                aArgs.Add(aMsg.ReadUInt64());
            }
            else if (c == 'i')
            {
                aArgs.Add(aMsg.ReadInt32());
            }
            else if (c == 'f')
            {
                aArgs.Add(aMsg.ReadFloat());
            }
            else if (c == 's')
            {
                aArgs.Add(aMsg.ReadString());
            }
            else if (c == 'b')
            {
                aArgs.Add(aMsg.ReadBoolean());
            }
            else if (c == 'v')
            {
                float x = aMsg.ReadFloat();
                float y = aMsg.ReadFloat();
                float z = aMsg.ReadFloat();
                aArgs.Add(new Vector3(x, y, z));
            }
            else if (c == 'q')
            {
                float x = aMsg.ReadFloat();
                float y = aMsg.ReadFloat();
                float z = aMsg.ReadFloat();
                float w = aMsg.ReadFloat();
                aArgs.Add(new Quaternion(x, y, z, w));
            }
            else if (c == 'a')
            {
                int length = aMsg.ReadInt32();
                int[] temp = new int[length];
                for(int i=0; i<length; i++)
                {
                    temp[i] = aMsg.ReadInt32();
                }
                aArgs.Add(temp);
            }
            else {
                Debug.LogError("Unhandled RPC parameter type " + c);
            }
        }
    }

    // Instantiate an object
    abstract public GameObject Instantiate(string prefabName, Vector3 aPostion, Quaternion aOrientation);

    // Sync network data
    abstract public void SyncNetworkData(int aNetworkId, MessageReceiver aMessageReceiver, DeliveryMethod aDeliveryMethod, byte[] aData, Vector3 aPosition, Quaternion aRotation);

    // Lite Sync netword data
    abstract public void LiteSyncNetworkData(int aNetworkId, MessageReceiver aMessageReceiver, DeliveryMethod aDeliveryMethod, byte[] aData);

    // Destroy a network object
    abstract public void Destroy(int aObjectId);

    // Are we currently connected to another machine
    public bool IsConnected()
    {
        return connection.ConnectionsCount != 0;
    }

    // These methods should be overridden by the server/client classes
    abstract protected void HandleMessage_Data(NetIncomingMessage aMsg);
    abstract protected void HandleMessage_ConnectionApproval(NetIncomingMessage aMsg);
    abstract protected void HandleMessage_ConnectionLatencyUpdated(NetIncomingMessage aMsg);

    // Make callbacks on this game object when the network status has changed
    virtual protected void HandleMessage_StatusChanged(NetIncomingMessage aMsg)
    {
        NetConnectionStatus status = (NetConnectionStatus)aMsg.ReadByte();
        switch (status)
        {
            case NetConnectionStatus.None:
                SendMessage("OnNetStatusNone", SendMessageOptions.DontRequireReceiver);
                break;
            case NetConnectionStatus.InitiatedConnect:
                SendMessage("OnNetStatusInitiatedConnect", SendMessageOptions.DontRequireReceiver);
                break;
            case NetConnectionStatus.ReceivedInitiation:
                SendMessage("OnNetStatusReceivedInitiation", SendMessageOptions.DontRequireReceiver);
                break;
            case NetConnectionStatus.RespondedAwaitingApproval:
                SendMessage("OnNetStatusRespondedAwaitingApproval", SendMessageOptions.DontRequireReceiver);
                break;
            case NetConnectionStatus.RespondedConnect:
                SendMessage("OnNetStatusRespondedConnect", SendMessageOptions.DontRequireReceiver);
                break;
            case NetConnectionStatus.Connected:
                SendMessage("OnNetStatusConnected", SendMessageOptions.DontRequireReceiver);
                break;
            case NetConnectionStatus.Disconnecting:
                SendMessage("OnNetStatusDisconnecting", SendMessageOptions.DontRequireReceiver);
                break;
            case NetConnectionStatus.Disconnected:
                SendMessage("OnNetStatusDisconnected", SendMessageOptions.DontRequireReceiver);
                break;
            default:
                break;
        }
    }

    // Message handling functions for the error/warning messages
    virtual protected void HandleMessage_DebugMessage(NetIncomingMessage aMsg)
    {
        Debug.Log("Network debug message: " + aMsg.ReadString());
    }
    virtual protected void HandleMessage_VerboseDebugMessage(NetIncomingMessage aMsg)
    {
        Debug.Log("Network verbose debug message: " + aMsg.ReadString());
    }
    virtual protected void HandleMessage_WarningMessage(NetIncomingMessage aMsg)
    {
        Debug.LogWarning("Network warning message: " + aMsg.ReadString());
    }
    virtual protected void HandleMessage_ErrorMessage(NetIncomingMessage aMsg)
    {
        Debug.LogError("Network error message: " + aMsg.ReadString());
    }

    // Add an ID to the list that I own
    protected void AddOwnedId(int aId)
    {
        // Tell the object that we are now the owner
        if (!netIdObjMap.ContainsKey(aId))
        {
            Debug.LogError("Client doesn't know about object " + aId + " which it is supposed to now own");
            return;
        }

        ownedIds.Add(aId);
        netIdObjMap[aId].gameObject.SendMessage("OnGainOwnership");
    }
    protected void RemoveOwnedId(int aId)
    {
        // Tell the object that we just lost ownership
        if (!netIdObjMap.ContainsKey(aId))
        {
            Debug.LogError("Client doesn't know about object " + aId + " which it is supposed to lose ownership of");
            return;
        }

        ownedIds.Remove(aId);
        netIdObjMap[aId].gameObject.SendMessage("OnLoseOwnership");
    }
    /*protected void RemoveAllOwnedIds()
    {
        List<int> remainingIds = new List<int>();
        foreach (int objId in ownedIds)
        {
            if (!netIdObjMap.ContainsKey(objId))
            {
                Debug.LogError("Client doesn't know about object " + objId + " which it is supposed to lose ownership of");
                return;
            }

            if (netIdObjMap[objId].networkSync.followsClient)
            {
                remainingIds.Add(objId);
                continue;
            }

            netIdObjMap[objId].gameObject.SendMessage("OnLoseOwnership");
        }

        ownedIds = new List<int>(remainingIds);
    }*/
    public bool isOwned(int aId)
    {
        return ownedIds.Contains(aId);
    }

    public string GetAddress()
    {
        System.Net.IPAddress addr;
        System.Net.IPAddress mask;
        addr = NetUtility.GetMyAddress(out mask);
        if (addr == null)
        {
            return "";
        }
        return addr.ToString();
    }

    public int GetPort()
    {
        return connection.Configuration.Port;
    }

    public double GetTime()
    {
        // Lidgren.Network.NetTime.Now
        return NetTime.Now;
    }

    // Return the game object with the given network sync id
    public GameObject GetGameObject(int aNetworkId)
    {
        if (netIdObjMap.ContainsKey(aNetworkId))
        {
            return netIdObjMap[aNetworkId].gameObject;
        }
        return null;
    }
}
