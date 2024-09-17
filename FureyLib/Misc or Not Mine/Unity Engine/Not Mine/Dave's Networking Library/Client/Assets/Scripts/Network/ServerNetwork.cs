#if SERVER

using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using Lidgren.Network;
using System.Reflection;
using System.IO;


// Server networking class
public class ServerNetwork : UCNetwork {

    // Area change information
    public class AreaChangeInfo {
        public long id;
        public int oldAreaId;
        public int newAreaId;
    };

    // Network object initialization info
    // Used when a client changes areas, or connects
    public class InitializationInfo {
        public long clientId;
        public int netObjId;
    }

    // Used to pass data during the connection state
    public class ConnectionRequestInfo {
        public string username;
        public string password;
        public string clientType;
        public ulong uniqueId;
        public string ip;
        public long id;
        public NetConnection connection;
    };
    List<ConnectionRequestInfo> pendingConnections;

    // Alright, we need to store client data
    public class ClientData {
        public long networkIdentifier;  // Unique identifier
        public int areaId;              // What area is the client in
        public List<int> ownedObjects;  // Which objects does this client own
        public int numberOfIds;         // How many ids does the client have
        public NetConnection connection;// Lidgren connection to this client
        public string clientType;       // Type of client this is
        public ulong uniqueId;          // Some unique id sent from the client (could be used for a steam id)
    };
   List<ClientData> clientData = new List<ClientData>();

    // Lets store some data about instantiated objects
    public class NetworkObject {
        public string prefabName;
        public int areaId;
        public int networkId;
        public byte[] latestSyncData;
        public Vector3 position;
        public Quaternion rotation;
        public bool followsClient;  // Does this object follow the client from area to area
    };
    Dictionary<int, NetworkObject> networkObjects = new Dictionary<int, NetworkObject>();

    // List of network objects that need to be syned to the clients
    class ObjectSyncData {
        public MessageReceiver receiver;
        public int objectId;
        public long client;
    }
    Dictionary<int, ObjectSyncData> netObjsToSync = new Dictionary<int, ObjectSyncData>();

    // The last network id issued
    private int lastNetworkId = 0;
    private int issuedIdRange = 500; // How many ids do we issue to the clients

    // Lidgren connection
    NetServer server;

    // The lidgren NetPeer configuration
    protected NetPeerConfiguration config;
    public int maxConnections = 100;

    // Instance
    static public ServerNetwork instance;

    // VoIPManager
    VoIPManager voipManager;

    // StreamWriter for logging to a file, if enabled
    public string logFile = "MessageLog.txt";

    // Use this for initialization
    override protected void Awake() {
        EnableLogging(logFile);

        base.Awake();
        isServer = true;

        config = new NetPeerConfiguration("UpsilonCircuit");
        config.Port = port;
        config.MaximumConnections = maxConnections;
        config.EnableMessageType(NetIncomingMessageType.ConnectionApproval);

        // Start the server
        connection = new NetServer(config);
        connection.Start();
        LogText("Server Started");

        server = connection as NetServer;

        instance = this;

        pendingConnections = new List<ConnectionRequestInfo>();

        // Add the voip manager
        voipManager = (VoIPManager)gameObject.AddComponent(typeof(VoIPManager));
    }

    public void Start() {
        InvokeRepeating("SyncObjectsToClients", 5.0f, 0.1f);
    }

    void OnDestroy() {
        Debug.Log(connection.Statistics.ToString());
        
        if (connection.Status == NetPeerStatus.Running) {
            connection.Shutdown("Peace out");
            LogText("Server shutdown");
        }
    }

    // Update is called once per frame
    override public void Update() {
        base.Update();
    }

    // Function called when we get a status changed message
    override protected void HandleMessage_StatusChanged(NetIncomingMessage aMsg) {
        LogText(((NetConnectionStatus)aMsg.PeekByte()).ToString() + " " + aMsg.SenderConnection.RemoteUniqueIdentifier + " " + aMsg.SenderConnection.RemoteEndPoint.Address);

        NetConnectionStatus status = (NetConnectionStatus)aMsg.PeekByte();
        if (status == NetConnectionStatus.Connected) {
            // Add the client data with this connection
            ClientData data = new ClientData();
            data.networkIdentifier = aMsg.SenderConnection.RemoteUniqueIdentifier;
            data.areaId = -1;
            data.ownedObjects = new List<int>();
            data.numberOfIds = 0;
            data.connection = aMsg.SenderConnection;

            // Check if the client is in the pending connections
            for (int i = 0; i < pendingConnections.Count; i++) {
                if (pendingConnections[i].id == data.networkIdentifier) {
                    // Get any data from the pending connection we might need
                    data.clientType = pendingConnections[i].clientType;
                    data.uniqueId = pendingConnections[i].uniqueId;
                    pendingConnections.RemoveAt(i);
                }
            }

            clientData.Add(data);

            // Issue the client some network ids
            IssueNetworkIds(aMsg.SenderConnection);

            SendMessage("OnClientConnected", aMsg.SenderConnection.RemoteUniqueIdentifier, SendMessageOptions.DontRequireReceiver);
        } else if (status == NetConnectionStatus.Disconnected) {
            Debug.Log("Client " + aMsg.SenderConnection.RemoteUniqueIdentifier + " has disconnected.");
            // Find the data for this client
            for (int i = 0; i < clientData.Count; i++) {
                if (clientData[i].networkIdentifier == aMsg.SenderConnection.RemoteUniqueIdentifier) {
                    int areaId = clientData[i].areaId;
                    clientData[i].areaId = -1;
                    
                    // Transfer ownership of the objects that do not follow the client
                    FindNewOwners(clientData[i], areaId);

                    // Let the server know a client is going away
                    SendMessage("OnClientDisconnected", aMsg.SenderConnection.RemoteUniqueIdentifier, SendMessageOptions.DontRequireReceiver);

                    // Destroy any objects that are going away with this client
                    DestroyNetObject(clientData[i].ownedObjects);
                    
                    // Remove the client data with this connection
                    clientData.RemoveAt(i);
                    break;
                }
            }
        }
        base.HandleMessage_StatusChanged(aMsg);
    }

    // Function called when we get a data message
    override protected void HandleMessage_Data(NetIncomingMessage aMsg) {
        // Data has just been sent from a client, what to do with it...
        // Check what kind of message this is
        List<NetConnection> clients;
        MessageType type = (MessageType)aMsg.ReadInt32();
        if (type == MessageType.RPC) {
            // Structure for a RPC:
            // Int - MessageType
            // Int - MessageReceiver
            // Int - Object Network Id
            // String - Function Name
            // String - Arguments contained in the rest of the message (ex. "iissf" - int, int, string, string, float)
            // [Int, String, Float] - Arguments

            LogRPC(aMsg);

            // Create the outgoing message
            NetOutgoingMessage sendMsg = server.CreateMessage();

            // Determine who it should go to
            MessageReceiver receiver = (MessageReceiver)aMsg.ReadUInt32();
            switch (receiver) {
                case MessageReceiver.AllClients:
                    sendMsg.Write(aMsg);
                    server.SendToAll(sendMsg, NetDeliveryMethod.ReliableOrdered);
                    break;

                case MessageReceiver.AllClientsInArea:
                    sendMsg.Write(aMsg);
                    clients = GetClientsInArea(aMsg.SenderConnection.RemoteUniqueIdentifier, true);
                    if (clients.Count > 0) {
                        server.SendMessage(sendMsg, clients, NetDeliveryMethod.ReliableOrdered, 0);
                    }
                    break;

                case MessageReceiver.OtherClients:
                    sendMsg.Write(aMsg);
                    server.SendToAll(sendMsg, aMsg.SenderConnection, NetDeliveryMethod.ReliableOrdered, 0);
                    break;

                case MessageReceiver.OtherClientsInArea:
                    sendMsg.Write(aMsg);
                    clients = GetClientsInArea(aMsg.SenderConnection.RemoteUniqueIdentifier, false);
                    if (clients.Count > 0) {
                        server.SendMessage(sendMsg, clients, NetDeliveryMethod.ReliableOrdered, 0);
                    }
                    break;

                case MessageReceiver.ServerOnly:
                    ReceiveRPC(aMsg);
                    break;

                default:
                    Debug.LogError("RPC call sent to unknown MessageReceiver type");
                    break;
            }

        }
        else if (type == MessageType.SyncUpdate || type == MessageType.LiteSyncUpdate)
        {
            if (type == MessageType.LiteSyncUpdate) {
                LogText("LiteSyncUpdate " + aMsg.SenderConnection.RemoteUniqueIdentifier + " " + aMsg.SenderConnection.RemoteEndPoint.Address);
                Debug.Log("LiteSyncUpdate");
            } else {
                LogText("SyncUpdate " + aMsg.SenderConnection.RemoteUniqueIdentifier + " " + aMsg.SenderConnection.RemoteEndPoint.Address);
            }

            // Structure for a Sync Update:
            // Int - MessageType
            // Int - MessageReceiver
            // Int - Object Network Id
            // 3 Floats - Vector3 - Position
            // 4 Floats - Quaternion - Rotation
            // Int - Length of the byte data
            // Byte[] - data

            MessageReceiver receiver = (MessageReceiver)aMsg.ReadUInt32();

            // Update our own record of the sync data
            int netId = aMsg.ReadInt32();

            NetOutgoingMessage sendMsg;
            // Get the client who sent this message
            foreach (ClientData data in clientData) {
                if (data.networkIdentifier == aMsg.SenderConnection.RemoteUniqueIdentifier) {
                    // Make sure the client owns the object
                    if (!data.ownedObjects.Contains(netId)) {
                        Debug.LogError("Getting sync data from client " + aMsg.SenderConnection.RemoteUniqueIdentifier + " for object " + netId + " which they don't own");

                        // Send the client a message saying they dont own the object
                        sendMsg = server.CreateMessage();
                        sendMsg.Write((int)MessageType.OwnershipLost);
                        sendMsg.Write(netId);
                        server.SendMessage(sendMsg, data.connection, NetDeliveryMethod.UnreliableSequenced, UCNetwork.SyncSequenceChannel);

                        return;
                    }
                }
            }
            Vector3 position = new Vector3();
            Quaternion orientation = new Quaternion();
            if (type == MessageType.SyncUpdate) {
                //Position and rotation received
                float x = aMsg.ReadFloat();
                float y = aMsg.ReadFloat();
                float z = aMsg.ReadFloat();
                position = new Vector3(x, y, z);
                
                networkObjects[netId].position = position;
                
                x = aMsg.ReadFloat();
                y = aMsg.ReadFloat();
                z = aMsg.ReadFloat();
                float w = aMsg.ReadFloat();
                orientation = new Quaternion(x, y, z, w);

                networkObjects[netId].rotation = orientation;
            }
            int byteLength = aMsg.ReadInt32();
            byte[] byteData = aMsg.ReadBytes(byteLength);

            if (!networkObjects.ContainsKey(netId)) {
                //Debug.LogError("Unable to update sync data for unknown object " + netId);
                return;
            }
            
            
            
            networkObjects[netId].latestSyncData = byteData;

            if (!netObjsToSync.ContainsKey(netId)) {
                ObjectSyncData data = new ObjectSyncData();
                data.objectId = netId;
                data.receiver = receiver;
                data.client = aMsg.SenderConnection.RemoteUniqueIdentifier;
                
                netObjsToSync[netId] = data;
            }
            /*
            // Send the sync data to the other clients
            sendMsg = server.CreateMessage();
            sendMsg.Write(aMsg);

            // Who should this update be sent to
            if (receiver == MessageReceiver.OtherClients) {
                server.SendToAll(sendMsg, aMsg.SenderConnection, NetDeliveryMethod.ReliableSequenced, 0);

            } else if (receiver == MessageReceiver.OtherClientsInArea) {
                clients = GetClientsInArea(aMsg.SenderConnection.RemoteUniqueIdentifier, false);
                if (clients.Count > 0) {
                    server.SendMessage(sendMsg, clients, NetDeliveryMethod.ReliableSequenced, 0);
                }
            } else {
                Debug.LogError("Unsupported MessageReceiver sent to SyncUpdate: " + receiver);
            }
            */
        } else if (type == MessageType.Instantiate) {
            // Structure for a Intantiate message:
            // Int - MessageType
            // Int - The network id
            // String - Prefab name
            // Float - Pos x
            // Float - Pos y
            // Float - Pos z
            // Float - Quaternion x
            // Float - Quaternion y
            // Float - Quaternion z
            // Float - Quaternion w

            int networkId = aMsg.ReadInt32();
            string prefabName = aMsg.ReadString();
            float posX = aMsg.ReadFloat();
            float posY = aMsg.ReadFloat();
            float posZ = aMsg.ReadFloat();
            float oriX = aMsg.ReadFloat();
            float oriY = aMsg.ReadFloat();
            float oriZ = aMsg.ReadFloat();
            float oriW = aMsg.ReadFloat();

            LogText("Instantiate " + aMsg.SenderConnection.RemoteUniqueIdentifier + " " + aMsg.SenderConnection.RemoteEndPoint.Address
                + "\n\tNetworkId: " + networkId.ToString()
                + "\n\tPrefab: " + prefabName
                + "\n\tLoc: " + posX.ToString() + ", " + posY.ToString() + ", " + posZ.ToString()
                + "\n\tOrientation: " + oriX.ToString() + ", " + oriY.ToString() + ", " + oriZ.ToString() + ", " + oriW.ToString()            
                );

            Vector3 position = new Vector3( posX, posY, posZ );
            Quaternion rotation = new Quaternion( oriX, oriY, oriZ, oriW );

            foreach (ClientData data in clientData) {
                if (data.networkIdentifier == aMsg.SenderConnection.RemoteUniqueIdentifier) {
                    data.numberOfIds--;
                    
                    // Should we issue more ids?
                    if (data.numberOfIds < issuedIdRange / 2) {
                        IssueNetworkIds(aMsg.SenderConnection);
                    }
                    break;
                }
            }

            InstantiateNetworkObject(prefabName, position, rotation, aMsg.SenderConnection.RemoteUniqueIdentifier, networkId, false);

        } else if (type == MessageType.AreaChange) {
            LogText("AreaChange " + aMsg.SenderConnection.RemoteUniqueIdentifier + " " + aMsg.SenderConnection.RemoteEndPoint.Address);

            // Structure for an area change:
            // Int - MessageType
            // Int - New area Id
            int newAreaId = aMsg.ReadInt32();
            ChangeArea(aMsg.SenderConnection.RemoteUniqueIdentifier, newAreaId);
        } else if (type == MessageType.Destroy) {
            LogText("Destroy " + aMsg.SenderConnection.RemoteUniqueIdentifier + " " + aMsg.SenderConnection.RemoteEndPoint.Address);

            int objectId = aMsg.ReadInt32();

            // Verify that the owner sent this message
            if (!networkObjects.ContainsKey(objectId)) {
                Debug.LogError("Server was asked to destroy unknown object " + objectId + " from client " + aMsg.SenderConnection.RemoteUniqueIdentifier);
                return;
            } else {
                Debug.Log("Request to destroy object " + objectId);
            }

            // Make sure only the owner can destroy
            foreach (ClientData data in clientData) {
                if (data.ownedObjects.Contains(objectId)) {
                    if (aMsg.SenderConnection.RemoteUniqueIdentifier != data.networkIdentifier) {
                        Debug.LogWarning("Client " + aMsg.SenderConnection.RemoteUniqueIdentifier + " requested to destroy object " + objectId + " which it does not own");
                    }
                    break;
                }
            }

            // Destroy the object
            DestroyNetObject(objectId);
        } else if (type == MessageType.VoiceData) {
            LogText("VoiceData " + aMsg.SenderConnection.RemoteUniqueIdentifier + " " + aMsg.SenderConnection.RemoteEndPoint.Address);

            // Structure for a voice data message
            // Int - MessageType
            // Int - Compression Type
            // Int - Data Length
            // byte[] - Data
            // Int - Voice Data Id (Unique id assigned by the VoIPManager)
            
            int networkObjectId = aMsg.ReadInt32();
            int compressionType = aMsg.ReadInt32();
            int voiceId = aMsg.ReadInt32();
            int channel = aMsg.ReadInt32();
            int length = aMsg.ReadInt32();
            byte[] data = aMsg.ReadBytes(length);

            NetOutgoingMessage sendMsg = server.CreateMessage();
            sendMsg.Write(aMsg);

            if (channel == (int)VoiceChatChannel.Proximity) {
                clients = GetClientsInArea(aMsg.SenderConnection.RemoteUniqueIdentifier, false);
                if (clients.Count > 0) {
                    server.SendMessage(sendMsg, clients, NetDeliveryMethod.ReliableOrdered, UCNetwork.VoiceSequenceChannel);
                }
            } else if (channel == (int)VoiceChatChannel.Radio) {
                //TODO: All this logic is probably really slow :(
                // should we cache which clients are on which teams somewhere? Maybe in voipManager?
                
                List<long> clientList = voipManager.GetClientsForRadio(networkObjectId, compressionType, length, data, voiceId, channel);

                // What area are we talking in
                int areaId = GetClientData(aMsg.SenderConnection.RemoteUniqueIdentifier).areaId;

                // List of clients for the proximity and radio messages
                List<NetConnection> proximityList = new List<NetConnection>();
                List<NetConnection> radioList = new List<NetConnection>();

                // Generate lists of who to broadcast to
                foreach (ClientData client in clientData) {
                    if (clientList.Contains(client.networkIdentifier)) {
                        radioList.Add(client.connection);
                        continue;
                    }
                    // If the client is in the same area, and it's not the client who sent it
                    if (client.areaId == areaId && client.networkIdentifier != aMsg.SenderConnection.RemoteUniqueIdentifier) {
                        proximityList.Add(client.connection);
                    }
                }
                
                // Broadcast
                if (proximityList.Count > 0) {
                    // Create a new message with the same data, except the channel should be proximity
                    NetOutgoingMessage proximityMessage = server.CreateMessage();
                    proximityMessage.Write((int)MessageType.VoiceData);
                    proximityMessage.Write(networkObjectId);
                    proximityMessage.Write(compressionType);
                    proximityMessage.Write(voiceId);
                    proximityMessage.Write((int)VoiceChatChannel.Proximity);
                    proximityMessage.Write(length);
                    proximityMessage.Write(data);

                    server.SendMessage(proximityMessage, proximityList, NetDeliveryMethod.ReliableOrdered, UCNetwork.VoiceSequenceChannel);
                }
                if (radioList.Count > 0) {
                    server.SendMessage(sendMsg, radioList, NetDeliveryMethod.ReliableOrdered, UCNetwork.VoiceSequenceChannel);
                }
            }

            
            /*
            // For now, send this data to all the clients
            NetOutgoingMessage sendMsg = server.CreateMessage();
            sendMsg.Write(aMsg);

            // Send the message to either all clients in the area, or to all clients
            clients = new List<NetConnection>();
            if (channel == (int)VoiceChatChannel.Proximity) {
                clients = GetClientsInArea(aMsg.SenderConnection.RemoteUniqueIdentifier, false);
                if (clients.Count > 0) {
                    server.SendMessage(sendMsg, clients, NetDeliveryMethod.ReliableOrdered, UCNetwork.VoiceSequenceChannel);
                }
            } else if (channel == (int)VoiceChatChannel.Radio) {
                server.SendToAll(sendMsg, aMsg.SenderConnection, NetDeliveryMethod.ReliableOrdered, UCNetwork.VoiceSequenceChannel);
            }
            */
        } else {
            LogText("UnknownMessageType " + aMsg.SenderConnection.RemoteUniqueIdentifier + " " + aMsg.SenderConnection.RemoteEndPoint.Address);

            Debug.LogError("Unhandled message type sent to server " + type.ToString());
        }
    }

    // Send updated sync data to the clients
    void SyncObjectsToClients() {
        // Structure for a Sync Update:
        // Int - MessageType
        // Int - MessageReceiver
        // Int - Object Network Id
        // 3 Floats - Vector3 - Position
        // 4 Floats - Quaternion - Rotation
        // Int - Length of the byte data
        // Byte[] - data
        NetOutgoingMessage sendMsg;
        foreach (KeyValuePair<int, ObjectSyncData> objectSync in netObjsToSync) {
            // Send the sync data to the other clients
            sendMsg = server.CreateMessage();
            sendMsg.Write((int)MessageType.SyncUpdate);
            sendMsg.Write((int)objectSync.Value.receiver);
            sendMsg.Write(objectSync.Value.objectId);

            // If the object isn't around anymore don't sync it
            if (!networkObjects.ContainsKey(objectSync.Value.objectId)) {
                continue;
            }
            sendMsg.Write(networkObjects[objectSync.Value.objectId].position.x);
            sendMsg.Write(networkObjects[objectSync.Value.objectId].position.y);
            sendMsg.Write(networkObjects[objectSync.Value.objectId].position.z);
            sendMsg.Write(networkObjects[objectSync.Value.objectId].rotation.x);
            sendMsg.Write(networkObjects[objectSync.Value.objectId].rotation.y);
            sendMsg.Write(networkObjects[objectSync.Value.objectId].rotation.z);
            sendMsg.Write(networkObjects[objectSync.Value.objectId].rotation.w);
            sendMsg.Write(networkObjects[objectSync.Value.objectId].latestSyncData.Length);
            sendMsg.Write(networkObjects[objectSync.Value.objectId].latestSyncData);

            // Who should this update be sent to
            if (objectSync.Value.receiver == MessageReceiver.OtherClients) {
                server.SendToAll(sendMsg, GetClientData(objectSync.Value.client).connection, NetDeliveryMethod.ReliableSequenced, 0);

            } else if (objectSync.Value.receiver == MessageReceiver.OtherClientsInArea) {
                List<NetConnection> clients = GetClientsInArea(objectSync.Value.client, false);
                if (clients.Count > 0) {
                    server.SendMessage(sendMsg, clients, NetDeliveryMethod.ReliableSequenced, 0);
                }
            } else {
                Debug.LogError("Unsupported MessageReceiver sent to SyncUpdate: " + objectSync.Value.receiver);
            }
        }
        netObjsToSync.Clear();
    }

       //Lite SyncUpdate
       void LiteSyncObjectsToClients() {
        // Structure for a Sync Update (minus rotation and position):
        // Int - MessageType
        // Int - MessageReceiver
        // Int - Object Network Id
        // Int - Length of the byte data
        // Byte[] - data
        NetOutgoingMessage sendMsg;
        foreach (KeyValuePair<int, ObjectSyncData> objectSync in netObjsToSync) {
            // Send the sync data to the other clients
            sendMsg = server.CreateMessage();
            sendMsg.Write((int)MessageType.LiteSyncUpdate);
            sendMsg.Write((int)objectSync.Value.receiver);
            sendMsg.Write(objectSync.Value.objectId);

            // If the object isn't around anymore don't sync it
            if (!networkObjects.ContainsKey(objectSync.Value.objectId)) {
                continue;
            }
            sendMsg.Write(networkObjects[objectSync.Value.objectId].latestSyncData.Length);
            sendMsg.Write(networkObjects[objectSync.Value.objectId].latestSyncData);

            // Who should this update be sent to
            if (objectSync.Value.receiver == MessageReceiver.OtherClients) {
                server.SendToAll(sendMsg, GetClientData(objectSync.Value.client).connection, NetDeliveryMethod.ReliableSequenced, 0);

            } else if (objectSync.Value.receiver == MessageReceiver.OtherClientsInArea) {
                List<NetConnection> clients = GetClientsInArea(objectSync.Value.client, false);
                if (clients.Count > 0) {
                    server.SendMessage(sendMsg, clients, NetDeliveryMethod.ReliableSequenced, 0);
                }
            } else {
                Debug.LogError("Unsupported MessageReceiver sent to LiteSyncUpdate: " + objectSync.Value.receiver);
            }
        }
    }   


    // Change the area of a client
    public void ChangeArea(long aClientId, int aNewAreaId) {
        List<NetConnection> clients;        
        bool found = false;
        for (int i = 0; i < clientData.Count; i++) {
            if (clientData[i].networkIdentifier == aClientId) {
                found = true;
                int oldAreaId = clientData[i].areaId;

                if (oldAreaId == aNewAreaId) {
                    // Do nothing in this case
                    Debug.LogWarning("Client is trying to change to the same area id");
                    return;
                }

                // Update the client's area id
                clientData[i].areaId = aNewAreaId;

                // Find new owners for these objects
                FindNewOwners(clientData[i], oldAreaId);

                NetOutgoingMessage sendMsg;

                // Send a message back confirming the area change
                sendMsg = server.CreateMessage();
                sendMsg.Write((int)MessageType.AreaChange);
                sendMsg.Write(aNewAreaId);
                server.SendMessage(sendMsg, clientData[i].connection, NetDeliveryMethod.ReliableOrdered);

                // Send intialization data to this client about the area
                SendInitializationData(clientData[i].connection, aNewAreaId);

                // Go through the list of remianing objects
                // Tell the clients in the old area they are being destroyed
                // Tell the clients in the new area they are being instantiated
                for (int x = 0; x < clientData[i].ownedObjects.Count; x++) {

                    // Tell the clients in the old area that we are destroying this game object
                    sendMsg = server.CreateMessage();
                    sendMsg.Write((int)MessageType.Destroy);
                    sendMsg.Write(clientData[i].ownedObjects[x]);
                    clients = GetClientsInArea(oldAreaId, false);
                    if (clients.Count > 0) {
                        server.SendMessage(sendMsg, clients, NetDeliveryMethod.ReliableOrdered, 0);
                    }

                    // Instantiate for the clients in the new area
                    if (!networkObjects.ContainsKey(clientData[i].ownedObjects[x])) {
                        Debug.LogError("Trying to instantiate unknown network object when moving areas " + clientData[i].ownedObjects[x]);
                        continue;
                    }
                    NetworkObject obj = networkObjects[clientData[i].ownedObjects[x]];
                    obj.areaId = aNewAreaId;

                    // obj.areaId = aNewAreaId;
                    sendMsg = server.CreateMessage();
                    sendMsg.Write((int)MessageType.Instantiate);
                    sendMsg.Write(obj.networkId);
                    sendMsg.Write(obj.prefabName);
                    sendMsg.Write(obj.position.x);
                    sendMsg.Write(obj.position.y);
                    sendMsg.Write(obj.position.z);
                    sendMsg.Write(obj.rotation.x);
                    sendMsg.Write(obj.rotation.y);
                    sendMsg.Write(obj.rotation.z);
                    sendMsg.Write(obj.rotation.w);


                    clients = GetClientsInArea(aClientId, false);
                    if (clients.Count > 0) {
                        server.SendMessage(sendMsg, clients, NetDeliveryMethod.ReliableOrdered, 0);
                    }
                }

                // Give any game logic a chance to send stuff to the client before objects are intialized
                AreaChangeInfo info = new AreaChangeInfo();
                info.id = aClientId;
                info.newAreaId = aNewAreaId;
                info.oldAreaId = oldAreaId;
                SendMessage("OnAreaChange", info, SendMessageOptions.DontRequireReceiver);

                //Debug.Log("Change area from " + oldAreaId + " to " + newAreaId);

                break;
            }
        }
        if (!found) {
            Debug.LogError("Unknown client " + aClientId + " is trying to change area to " + aNewAreaId);
            return;
        }

    }

    override public GameObject Instantiate(string prefabName, Vector3 aPostion, Quaternion aOrientation) {
        Debug.LogError("The server cannot instantiate objects directly");
        return null;
    }

    // Instantiate a new network object
    // aPrefabName - Prebab to instantiate
    // aPosition - Position of the network object
    // aOrientation - Orientation of the network object
    // aClientIdentifier - Which client will own this object
    // aNetworkId - The new network id for this object (this should be unique - use ServerNetwork::GetNewNetworkId() )
    // aSpawnedByServer - If this object has been spawned by the server
    NetworkObject InstantiateNetworkObject(string aPrefabName, Vector3 aPostion, Quaternion aOrientation, long aClientIdentifier, int aNetworkId, bool aSpawnedByServer) {
        Debug.Log("Instantiate for client - " + aClientIdentifier
                + "\n\tNetworkId: " + aNetworkId
                + "\n\tPrefab: " + aPrefabName
                + "\n\tLoc: " + aPostion.ToString()
                + "\n\tOrientation: " + aOrientation.eulerAngles.ToString()
                );

        // Create the message that will be sent to the clients
        NetOutgoingMessage sendMsg = server.CreateMessage();
        sendMsg.Write((int)MessageType.Instantiate);
        sendMsg.Write(aNetworkId);
        sendMsg.Write(aPrefabName);
        sendMsg.Write(aPostion.x);
        sendMsg.Write(aPostion.y);
        sendMsg.Write(aPostion.z);
        sendMsg.Write(aOrientation.x);
        sendMsg.Write(aOrientation.y);
        sendMsg.Write(aOrientation.z);
        sendMsg.Write(aOrientation.w);

        // Get the clients in the area
        // If aSpawnedByServer == true, sending the data to the owner client == true
        List<NetConnection> clients = GetClientsInArea(aClientIdentifier, aSpawnedByServer);
        if (clients.Count > 0) {
            server.SendMessage(sendMsg, clients, NetDeliveryMethod.ReliableOrdered, 0);
        }

        // Tell the owner client that they own it, if it was created by the server
        if (aSpawnedByServer) {
            foreach (ClientData client in clientData) {
                if (client.networkIdentifier == aClientIdentifier) {
                    sendMsg = server.CreateMessage();
                    sendMsg.Write((int)MessageType.OwnershipGained);
                    sendMsg.Write(aNetworkId);
                    server.SendMessage(sendMsg, client.connection, NetDeliveryMethod.ReliableOrdered);
                    break;
                }
            }
        }

        int areaId = -1;
        // Set up our own logic for tracking which clients own which objects
        foreach (ClientData data in clientData) {
            if (data.networkIdentifier == aClientIdentifier) {
                data.ownedObjects.Add(aNetworkId);
                
                // Remember the clients areaId, this is where the object is as well
                areaId = data.areaId;
                break;
            }
        }
        if (areaId == -1) {
            Debug.LogError("Unable to get valid area id for new " + aPrefabName + " object. Does the client have a valid area? Does client exist?");
        }

        // Store the object in our NetworkObject list
        NetworkObject newObject = new NetworkObject();
        newObject.prefabName = aPrefabName;
        newObject.areaId = areaId;
        newObject.networkId = aNetworkId;
        newObject.position = aPostion;
        newObject.rotation = aOrientation;
        newObject.followsClient = false;
        newObject.latestSyncData = new byte[0];
        if (networkObjects.ContainsKey(aNetworkId)) {
            Debug.LogError("Network id collision when adding " + aPrefabName + " for client " + aClientIdentifier + " with id " + aNetworkId);
            return null;
        }
        networkObjects[aNetworkId] = newObject;

        // Let any other scripts on this object know we're adding the object
        SendMessage("OnIntantiateNetworkObject", aNetworkId);
        //Debug.Log("Instantiate: " + newObject.prefabName + " in " + newObject.areaId + " with id " + newObject.networkId);
        
        return networkObjects[aNetworkId];
    }

    // Instantiate a new network object, and give ownership to a specific client
    public NetworkObject InstantiateNetworkObject(string aPrefabName, Vector3 aPostion, Quaternion aOrientation, long aClientIdentifier) {
        // Make sure the client exists
        ClientData client = null;
        foreach (ClientData data in clientData) {
            if (data.networkIdentifier == aClientIdentifier) {
                client = data;
                break;
            }
        }
        if (client == null) {
            Debug.LogWarning("Unable to instantiate for unknown client with id " + aClientIdentifier);
            return null;
        }

        // Create the object
        return InstantiateNetworkObject(aPrefabName, aPostion, aOrientation, aClientIdentifier, GetNewNetworkId(), true);
    }
    
    // Instantiate a new network object in the given area, give ownership to a non-specific client
    public NetworkObject InstantiateNetworkObject(string aPrefabName, Vector3 aPostion, Quaternion aOrientation, int aAreaId) {
        // Find a client in the given area
        ClientData client = null;
        foreach (ClientData data in clientData) {
            if (data.areaId == aAreaId) {
                client = data;
                break;
            }
        }
        if (client == null) {
            print("No CLients");
        }
        return InstantiateNetworkObject(aPrefabName, aPostion, aOrientation, client.networkIdentifier, GetNewNetworkId(), true);        
    }

    // Function called when we get a connection approval message
    override protected void HandleMessage_ConnectionApproval(NetIncomingMessage aMsg) {
        // Check if we will allow this connection
        string username = aMsg.ReadString();
        string password = aMsg.ReadString();
        string clientType = aMsg.ReadString();
        ulong uniqueId = (ulong)aMsg.ReadInt64();

        // Ask the game logic if this client should be able to connect
        ConnectionRequestInfo data = new ConnectionRequestInfo();
        data.username = username;
        data.password = password;
        data.clientType = clientType;
        data.uniqueId = uniqueId;
        data.ip = aMsg.SenderConnection.RemoteEndPoint.Address.ToString();
        data.id = aMsg.SenderConnection.RemoteUniqueIdentifier;
        data.connection = aMsg.SenderConnection;

        pendingConnections.Add(data);

        Debug.Log("ConnectionRequest for " + data.id + ": " + data.ip);
        SendMessage("ConnectionRequest", data, SendMessageOptions.RequireReceiver);
    }

    // ConnectionApproved and ConnectionDenied need to be called by the game logic.
    // These tell the server if a pending connection should be allowed to connect
    public void ConnectionApproved(long aClientId) {
        Debug.Log("ConnectionApproved for " + aClientId);
        // Don't remove the pending connection data here, we'll do that in the connection callback
        for (int i = 0; i < pendingConnections.Count; i++) {
            if (pendingConnections[i].id == aClientId) {
                pendingConnections[i].connection.Approve();
                return;
            }
        }
        Debug.LogWarning("ConnectionApproved called with unknown client " + aClientId);
    }
    public void ConnectionDenied(long aClientId) {
        Debug.Log("ConnectionDenied for " + aClientId);
        for (int i = 0; i < pendingConnections.Count; i++) {
            if (pendingConnections[i].id == aClientId) {
                pendingConnections[i].connection.Deny();
                pendingConnections.RemoveAt(i);
                return;
            }
        }
        Debug.LogWarning("ConnectionDenied called with unknown client " + aClientId);
    }

    // Function called when we get a latency update message
    override protected void HandleMessage_ConnectionLatencyUpdated(NetIncomingMessage aMsg) {
        Debug.LogWarning("HandleMessage_ConnectionLatencyUpdated is unimplemented");
    }

    // Kick a client from the server
    public void Kick(long aClientId) {
        ClientData data = GetClientData(aClientId);
        data.connection.Disconnect("Server kick");
    }

    // Issue a set of free ids to this client
    void IssueNetworkIds(NetConnection aClient) {
        // Give the client a range of ids
        int startIdRange = ++lastNetworkId;
        lastNetworkId += issuedIdRange;
        int endIdRange = lastNetworkId;

        //Debug.Log("Issuing ids " + startIdRange + " through " + endIdRange + " to client " + aClient.RemoteUniqueIdentifier);

        // Keep track of how many ids the client has remaining
        foreach (ClientData data in clientData) {
            if (data.networkIdentifier == aClient.RemoteUniqueIdentifier) {
                data.numberOfIds += issuedIdRange;
                break;
            }
        }

        // Send the message to the client telling them which ids they can use
        NetOutgoingMessage sendMsg = server.CreateMessage();
        sendMsg.Write((int)MessageType.IdRequest);
        sendMsg.Write(startIdRange);
        sendMsg.Write(endIdRange);
        server.SendMessage(sendMsg, aClient, NetDeliveryMethod.ReliableOrdered);
    }

    // Get a single new network id
    public int GetNewNetworkId() {
        return ++lastNetworkId;
    }

    // Send down all the initialization data for a given area
    void SendInitializationData(NetConnection aConnection, int newAreaId) {
        // Alright, we need to send down initialization calls to the client first, then any current data about the objects
        NetOutgoingMessage sendMsg;
        foreach (KeyValuePair<int, NetworkObject> data in networkObjects) {
            if (data.Value.areaId != newAreaId) {
                continue;
            }
            // Let the client know about the new object
            sendMsg = server.CreateMessage();
            sendMsg.Write((int)MessageType.Instantiate);
            sendMsg.Write(data.Value.networkId);
            sendMsg.Write(data.Value.prefabName);
            sendMsg.Write(data.Value.position.x);
            sendMsg.Write(data.Value.position.y);
            sendMsg.Write(data.Value.position.z);
            sendMsg.Write(data.Value.rotation.x);
            sendMsg.Write(data.Value.rotation.y);
            sendMsg.Write(data.Value.rotation.z);
            sendMsg.Write(data.Value.rotation.w);
            server.SendMessage(sendMsg, aConnection, NetDeliveryMethod.ReliableOrdered);

            // Send updated information about that object
            // Int - MessageType
            // Int - MessageReceiver
            // Int - Object Network Id
            // Int - Length of the byte data
            // Byte[] - data
            sendMsg = server.CreateMessage();
            sendMsg.Write((int)MessageType.SyncUpdate);
            sendMsg.Write((int)MessageReceiver.OtherClientsInArea); // This is ignored by the recieving client
            sendMsg.Write(data.Value.networkId);
            sendMsg.Write(data.Value.position.x);
            sendMsg.Write(data.Value.position.y);
            sendMsg.Write(data.Value.position.z);
            sendMsg.Write(data.Value.rotation.x);
            sendMsg.Write(data.Value.rotation.y);
            sendMsg.Write(data.Value.rotation.z);
            sendMsg.Write(data.Value.rotation.w);
            sendMsg.Write(data.Value.latestSyncData.Length);
            sendMsg.Write(data.Value.latestSyncData);
            server.SendMessage(sendMsg, aConnection, NetDeliveryMethod.ReliableOrdered);

            // Tell the game server that we're initializing an object for this client
            InitializationInfo info = new InitializationInfo();
            info.clientId = aConnection.RemoteUniqueIdentifier;
            info.netObjId = data.Value.networkId;
            SendMessage("InitializeNetworkObject", info);
        }

        // TODO: Do we want to wrap this with rpcs saying that we're initializing a level?
        CallRPC("AreaInitialized", aConnection.RemoteUniqueIdentifier, -1);
    }

    // Gather the connections for all the clients in a given area
    List<NetConnection> GetClientsInArea(long aRemoteUniqueIdentifier, bool aOwnClient) {
        List<NetConnection> clients = new List<NetConnection>();
        // First get the area id of this client
        int areaId = -1;
        foreach (ClientData data in clientData) {
            if (data.networkIdentifier == aRemoteUniqueIdentifier) {
                areaId = data.areaId;
                break;
            }
        }

        // Make sure we found an area
        if (areaId == -1) {
            Debug.LogWarning("Unable to gather clients without a valid areaId");
            return clients;
        }

        // Build the list of clients in the area
        // TODO: This lookup is painful
        foreach (ClientData data in clientData) {
            if (data.networkIdentifier == aRemoteUniqueIdentifier && !aOwnClient) {
                continue;
            }
            if (data.areaId == areaId) {
                foreach (NetConnection con in server.Connections) {
                    if (con.RemoteUniqueIdentifier == data.networkIdentifier) {
                        clients.Add(con);
                        break;
                    }
                }
            }
        }
        return clients;
    }

    List<NetConnection> GetClientsInArea(int aAreaId, bool aOwnClient) {
        List<NetConnection> clients = new List<NetConnection>();
        // First get the area id of this client
        int areaId = aAreaId;

        // Make sure we found an area
        if (areaId == -1) {
            Debug.LogWarning("Unable to gather clients without a valid areaId");
            return clients;
        }

        // Build the list of clients in the area
        // TODO: This lookup is painful
        foreach (ClientData data in clientData) {
            if (data.areaId == areaId) {
                foreach (NetConnection con in server.Connections) {
                    if (con.RemoteUniqueIdentifier == data.networkIdentifier) {
                        clients.Add(con);
                        break;
                    }
                }
            }
        }
        return clients;
    }

    // Find new owners for the given object ids. Find owners in the given area
    // This takes a ClientData object and removes the ids from the ownedObjects list that it gives to new clients
    // Note: Any objects that use followClient will remain with the client
    public void FindNewOwners(ClientData aClient, int aAreaId) {
        if (aClient == null) {
            return;
        }
        if (aClient.ownedObjects.Count == 0) {
            //Debug.Log("No objects need to change owners");
            return;
        }

        // Start by finding potential owners
        List<ClientData> clients = new List<ClientData>();
        foreach (ClientData client in clientData) {
            if (client.areaId == aAreaId && (client.networkIdentifier != aClient.networkIdentifier) && client.clientType == "client") {
                clients.Add(client);
            }
        }

        // Build a list of objects ids, removing any that we're taking away
        List<int> objIds = new List<int>();
        for (int i = aClient.ownedObjects.Count - 1; i >= 0; i--) {
            if (!networkObjects.ContainsKey(aClient.ownedObjects[i])) {
                Debug.LogError("Trying to find objects to change ownership and client " + aClient.networkIdentifier + " has invalid object id " + aClient.ownedObjects[i]);
                continue;
            }

            // Should this transfer ownership
            if (!networkObjects[aClient.ownedObjects[i]].followsClient) {
                objIds.Add(aClient.ownedObjects[i]);

                // Send a message to the client saying they lost ownership
                NetOutgoingMessage sendMsg = server.CreateMessage();
                sendMsg.Write((int)MessageType.OwnershipLost);
                sendMsg.Write(aClient.ownedObjects[i]);
                server.SendMessage(sendMsg, aClient.connection, NetDeliveryMethod.ReliableOrdered);

                // Remove the object from this clients list of owned objects
                aClient.ownedObjects.RemoveAt(i);
            }
        }

        // Check if there are any other clients to own these objects
        if (clients.Count == 0) {
            Debug.LogError("No clients available to take ownership of objects in area " + aAreaId + " and database persistence is unimplemented - destroying them");
            DestroyNetObject(objIds);
            return;
        }

        // Find new owners
        foreach (int objId in objIds) {
            if (!networkObjects.ContainsKey(objId)) {
                Debug.LogError("Unable to transfer ownership of unknown game object " + objId);
                continue;
            }

            if (networkObjects[objId].followsClient) {
                Debug.LogWarning("Changing ownership of an object that should follow a client: " + objId + " " + networkObjects[objId].prefabName);
            }

            // Pick a new client and give them ownership
            int rand = Random.Range(0, clients.Count);
            clients[rand].ownedObjects.Add(objId);

            // Send a message to the client telling them they are now the owner
            NetOutgoingMessage sendMsg = server.CreateMessage();
            sendMsg.Write((int)MessageType.OwnershipGained);
            sendMsg.Write(objId);
            server.SendMessage(sendMsg, clients[rand].connection, NetDeliveryMethod.ReliableOrdered);
        }
    }

    // Destroy a network object
    override public void Destroy(int aObjectId) {
        DestroyNetObject(aObjectId);
    }

    // Destroy the server representation of some objects
    void DestroyNetObject(List<int> aDestroyObjectIds) {
        List<int> newList = new List<int>(aDestroyObjectIds);
        foreach (int objId in newList) {
            DestroyNetObject(objId);
        }
    }

    void DestroyNetObject(int aObjectId) {
        if (!networkObjects.ContainsKey(aObjectId)) {
            Debug.LogError("Unable to destroy unknown networked object " + aObjectId);
            return;
        }

        // Tell the clients we're destroying this network object
        NetOutgoingMessage sendMsg = server.CreateMessage();
        sendMsg.Write((int)MessageType.Destroy);
        sendMsg.Write(aObjectId);
        List<NetConnection> clients = GetClientsInArea(networkObjects[aObjectId].areaId, false);
        if (clients.Count > 0) {
            server.SendMessage(sendMsg, clients, NetDeliveryMethod.ReliableOrdered, 0);
        }

        // Let any other scripts on this object know we're removing the object
        SendMessage("OnDestroyNetworkObject", aObjectId);

        // Remove the object from the list of owned objects the client has
        foreach (ClientData client in clientData) {
            if (client.ownedObjects.Contains(aObjectId)) {
                client.ownedObjects.Remove(aObjectId);
                break;
            }
        }

        networkObjects.Remove(aObjectId);
    }

    public string GetStatsText() {
        string text;
        text = "Connections: " + server.ConnectionsCount + " / " + server.Configuration.MaximumConnections + "\n";
        foreach (ClientData client in clientData) {
            text += "\tID: " + client.connection.RemoteUniqueIdentifier + "\tAddr: " + client.connection.RemoteEndPoint.Address.ToString() + "\tAreaId: " + client.areaId + "\t#Ids: " + client.numberOfIds + "\t#Owned Objs: " + client.ownedObjects.Count + "\n";
            if (client.ownedObjects.Count > 0) {
                text += "\t\tOwned objects: ";
                foreach (int id in client.ownedObjects) {
                    text += id + ",";
                }
                text += "\n";
            }
        }
        text += "\n";
        text += "\n";
        text += networkObjects.Count + " total Networked objects: \n";
        foreach (KeyValuePair<int, NetworkObject> netObj in networkObjects) {
            text += "\tNetId: " + netObj.Value.networkId + "\tArea: " + netObj.Value.areaId + "\tPrefab: " + netObj.Value.prefabName + " Pos: (" + netObj.Value.position.x + ", " + netObj.Value.position.y + ", " + netObj.Value.position.z + ") \n";
        }

        return text;
    }

    public override void SyncNetworkData(int aNetworkId, UCNetwork.MessageReceiver aMessageReceiver, DeliveryMethod aDeliveryMethod, byte[] aData, Vector3 aPosition, Quaternion aRotation) {
        Debug.LogError("ServerNetwork::SyncNetworkData is not implemented!");
    }
    
    //Lite
    public override void LiteSyncNetworkData(int aNetworkId, UCNetwork.MessageReceiver aMessageReceiver, DeliveryMethod aDeliveryMethod, byte[] aData) {
        Debug.LogError("ServerNetwork::LiteSyncNetworkData is not implemented!");
    }


    // Used to call RPCs to clients, regardless of area
    public override void CallRPC(string aFunctionName, UCNetwork.MessageReceiver aReceiver, int aNetworkId, params object[] aParams) {
        CallRPCToArea(aFunctionName, aReceiver, -1, aNetworkId, aParams);
    }

    // Used to call RPCs to an area
    public void CallRPCToArea(string aFunctionName, UCNetwork.MessageReceiver aReceiver, int aAreaId, int aNetworkId, params object[] aParams) {
        NetOutgoingMessage sendMsg = server.CreateMessage();
        sendMsg.Write((int)MessageType.RPC); // This is an rpc
        sendMsg.Write((int)MessageReceiver.SingleClient); // Which other clients this should be sent to
        sendMsg.Write(aNetworkId); // What network object on the clients this should be sent to
        sendMsg.Write(aFunctionName); // What network object on the clients this should be sent to

        WriteRPCParams(ref sendMsg, aParams);

        List<NetConnection> clients;

        LogRPC(sendMsg, aReceiver);

        switch (aReceiver) {
            case MessageReceiver.AllClients:
                server.SendToAll(sendMsg, NetDeliveryMethod.ReliableOrdered);
                break;

            case MessageReceiver.AllClientsInArea:
                if (aAreaId == -1) {
                    Debug.LogError("ServerNetwork::CallRPCToArea - MessageReceiver.AllClientsInArea: No area id specified.");
                    return;
                }
                clients = GetClientsInArea(aAreaId, true);
                if (clients.Count > 0) {
                    server.SendMessage(sendMsg, clients, NetDeliveryMethod.ReliableOrdered, 0);
                }
                break;

            case MessageReceiver.OtherClients:
                Debug.LogError("ServerNetwork::CallRPCToArea - MessageReceiver.OtherClients: Sending to OtherClients on server. Use AllClients instead.");
                break;

            case MessageReceiver.OtherClientsInArea:
                if (aAreaId == -1) {
                    Debug.LogError("ServerNetwork::CallRPCToArea - MessageReceiver.OtherClientsInArea: No area id specified.");
                    return;
                }
                clients = GetClientsInArea(aAreaId, false);
                if (clients.Count > 0) {
                    server.SendMessage(sendMsg, clients, NetDeliveryMethod.ReliableOrdered, 0);
                }
                break;

            case MessageReceiver.ServerOnly:
                Debug.LogError("ServerNetwork::CallRPCToArea - MessageReceiver.ServerOnly: Sending a RPC to the server from the server is unimplemented.");
                break;

            default:
                Debug.LogError("CallRPCToArea call sent to unknown MessageReceiver type");
                break;
        }
    }

    public override void CallRPC(string aFunctionName, long aClientId, int aNetworkId, params object[] aParams) {
        NetOutgoingMessage sendMsg = server.CreateMessage();
        sendMsg.Write((int)MessageType.RPC); // This is an rpc
        sendMsg.Write((int)MessageReceiver.SingleClient); // Which other clients this should be sent to
        sendMsg.Write(aNetworkId); // What network object on the clients this should be sent to
        sendMsg.Write(aFunctionName); // What network object on the clients this should be sent to

        WriteRPCParams(ref sendMsg, aParams);

        LogRPC(sendMsg, MessageReceiver.SingleClient);

        // Find the client we want to send to
        for (int i = 0; i < clientData.Count; i++) {
            if (clientData[i].networkIdentifier == aClientId) {
                // Send it to the client
                //Debug.Log("Server RPC: " + aFunctionName);
                server.SendMessage(sendMsg, clientData[i].connection, NetDeliveryMethod.ReliableOrdered);
                return;
            }
        }

        Debug.LogWarning("Unable to send RPC to a single client. Client not found: " + aClientId);
    }

    protected override void ReceiveRPC(NetIncomingMessage aMsg) {
        int networkId = aMsg.ReadInt32();
        string functionName = aMsg.ReadString();

        // Get the arguments
        List<object> args = new List<object>();
        ReadRPCParams(ref args, ref aMsg);

        // For server RPCs, we're always going to call the RPC on this game object
        networkId = -1;
        // Find the object with this networkId
        GameObject targetObject;
        if (networkId == -1) {
            targetObject = this.gameObject;
        } else {
            if (!netIdObjMap.ContainsKey(networkId)) {
                Debug.LogError("RPC was sent to unknown net object " + networkId.ToString() + " " + functionName);
                return;
            }
            targetObject = netIdObjMap[networkId].gameObject;
            if (targetObject == null) {
                Debug.LogError("Unable to get object from id map " + networkId.ToString() + " " + functionName);
                return;
            }
        }

        // Find the method to call
        // Loop through all the script components, finding a function
        MethodInfo theMethod = null;
        Component targetScript = null;
        Component[] scripts = targetObject.GetComponents(typeof(MonoBehaviour));
        for (int i = 0; i < scripts.Length; i++) {
            theMethod = scripts[i].GetType().GetMethod(functionName);
            if (theMethod != null) {
                targetScript = scripts[i];
                break;
            }
        }
        if (theMethod == null) {
            Debug.LogWarning("Unhandled RPC call to function " + functionName);
            return;
        }

        // Call the method
        try {
            theMethod.Invoke(targetScript, args.ToArray());
        } catch (TargetException e) {
            Debug.LogError("Unable to call RPC method: " + e.ToString());
        }
    }

    // Set a network object to follow a client when it changes areas or disconnects
    public void SetFollowsClient(int aNetworkId, bool aShouldFollow) {
        // Find the object, set it to follow the client
        if (!networkObjects.ContainsKey(aNetworkId)) {
            Debug.LogWarning("Attempted to set unknown network object " + aNetworkId + " to follow the client.");
            return;
        }
        networkObjects[aNetworkId].followsClient = aShouldFollow;
    }

    // Get network objects by various methods
    public NetworkObject GetNetObjById(int aNetworkId) {
        if (!networkObjects.ContainsKey(aNetworkId)) {
            return null;
        }
        return networkObjects[aNetworkId];
    }
    public List<NetworkObject> GetNetObjsByPrefab(string aPrefabName) {
        List<NetworkObject> objs = new List<NetworkObject>();
        for (int i = 0; i < networkObjects.Count; i++) {
            if (networkObjects[i].prefabName == aPrefabName) {
                objs.Add(networkObjects[i]);
            }
        }
        return objs;
    }

    // Get the client that owns a specific network object
    public long GetOwnerClientId(int aNetworkId) {
        if (!networkObjects.ContainsKey(aNetworkId)) {
            Debug.LogWarning("Unable to return client that owns unknown object " + aNetworkId);
            return -1;
        }

        foreach (ClientData client in clientData) {
            if (client.ownedObjects.Contains(aNetworkId)) {
                return client.networkIdentifier;
            }
        }

        Debug.LogError("Unable to find the owner of object " + aNetworkId);
        return -1;
    }

    // Return a client based on the unique id
    public ClientData GetClientData(long aClientId) {
        foreach (ClientData client in clientData) {
            if (client.networkIdentifier == aClientId) {
                return client;
            }
        }
        return null;
    }

    // Return all of the clients
    public List<ClientData> GetAllClients() {
        return clientData;
    }

    // Return all of the network object data
    public Dictionary<int, NetworkObject> GetAllObjects() {
        return networkObjects;
    }

    //////////////////////////////////
    // Logging functions
    //////////////////////////////////
    
    // Enable logging the network traffic
    public void EnableLogging(string aLogFile) {
        logFile = aLogFile;
        using (StreamWriter w = new StreamWriter(File.Create(logFile))) {
            w.Write("...Logging started...\r\n");
            w.Close();
        }
    }

    // Disable logging
    public void DisableLogging() {
        logFile = "";
    }

    // Log some text
    void LogText(string aLogEntry) {
        if (logFile == "") {
            return;
        }

        StreamWriter logFileWriter = new StreamWriter(logFile, true);
        logFileWriter.Write(GetTime() + ": " + aLogEntry + "\r\n");
        logFileWriter.Close();
    }

    // Log an outgoing RPC
    void LogRPC(NetOutgoingMessage aMsg, UCNetwork.MessageReceiver aReceiver) {
        if (logFile == "") {
            return;
        }

        long originalPosition = aMsg.Position;

        aMsg.Position = 0;

        // RPC Receiver Id:id Function:SomeFunc( arg, arg, arg, arg )
        string logMessage = "=> Outgoing " + (MessageType)aMsg.ReadInt32() + " Sent to: " + aReceiver + " as " + (MessageReceiver)aMsg.ReadUInt32();
        logMessage += " NetSyncId: " + aMsg.ReadInt32();
        string temp = "";
        aMsg.ReadString(out temp);

        logMessage += " Function: " + temp + "( ";

        string argDef = aMsg.ReadString();
        foreach (char c in argDef) {
            if (c == 'l') {
                logMessage += aMsg.ReadInt64();
            } else if (c == 'i') {
                logMessage += aMsg.ReadInt32();
            } else if (c == 'f') {
                logMessage += aMsg.ReadFloat();
            } else if (c == 's') {
                logMessage += aMsg.ReadString();
            } else if (c == 'b') {
                logMessage += aMsg.ReadBoolean();
            } else if (c == 'v') {
                float x = aMsg.ReadFloat();
                float y = aMsg.ReadFloat();
                float z = aMsg.ReadFloat();
                logMessage += new Vector3(x, y, z);
            } else if (c == 'q') {
                float x = aMsg.ReadFloat();
                float y = aMsg.ReadFloat();
                float z = aMsg.ReadFloat();
                float w = aMsg.ReadFloat();
                logMessage += new Quaternion(x, y, z, w);
            } else {
                Debug.LogError("Unhandled RPC parameter type " + c);
            }
            logMessage += ", ";
        }

        // Remove the last ", "
        if (argDef.Length > 0) {
            logMessage = logMessage.Substring(0, logMessage.Length - 2);
        }

        logMessage += " )\r\n";
        LogText(logMessage);

        aMsg.Position = originalPosition;
    }

    // Log an RPC
    void LogRPC(NetIncomingMessage aMsg) {
        if (logFile == "") {
            return;
        }

        long originalPosition = aMsg.Position;

        // RPC Receiver Id:id Function:SomeFunc( arg, arg, arg, arg )
        string logMessage = "RPC " + (MessageReceiver)aMsg.ReadUInt32();
        logMessage += " NetSyncId: " + aMsg.ReadInt32();
        string temp = "";
        aMsg.ReadString(out temp);

        logMessage += " Function: " + temp + "( ";

        string argDef = aMsg.ReadString();
        foreach (char c in argDef) {
            if (c == 'l') {
                logMessage += aMsg.ReadInt64();
            } else if (c == 'i') {
                logMessage += aMsg.ReadInt32();
            } else if (c == 'f') {
                logMessage += aMsg.ReadFloat();
            } else if (c == 's') {
                logMessage += aMsg.ReadString();
            } else if (c == 'b') {
                logMessage += aMsg.ReadBoolean();
            } else if (c == 'v') {
                float x = aMsg.ReadFloat();
                float y = aMsg.ReadFloat();
                float z = aMsg.ReadFloat();
                logMessage += new Vector3(x, y, z);
            } else if (c == 'q') {
                float x = aMsg.ReadFloat();
                float y = aMsg.ReadFloat();
                float z = aMsg.ReadFloat();
                float w = aMsg.ReadFloat();
                logMessage += new Quaternion(x, y, z, w);
            } else {
                Debug.LogError("Unhandled RPC parameter type " + c);
            }
            logMessage += ", ";
        }

        // Remove the last ", "
        if (argDef.Length > 0) {
            logMessage = logMessage.Substring(0, logMessage.Length - 2);
        }

        logMessage += " )\r\n";
        LogText(logMessage);

        aMsg.Position = originalPosition;
    }
}


#endif