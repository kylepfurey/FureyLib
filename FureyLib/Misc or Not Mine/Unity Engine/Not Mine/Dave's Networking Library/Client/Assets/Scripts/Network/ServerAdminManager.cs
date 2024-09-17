#if SERVER

using UnityEngine;
using System.Collections;
using System.Collections.Generic;

// This class functions as a manager for any connected admin clients, keeping them updated with information from the server
public class ServerAdminManager : MonoBehaviour {

    /* What do we need to send to the admin clients:
    Connected clients:
        id
        areaId
        ownedObjects
        numberOfIds

    Network objects:
        prefabName
        areaId
        networkId
        latestSyncData?
        position
        rotation
        followsClient

    Current server stats:
        IP
        Port
        Uptime?
        Previous connections?
        Ids for previous networked objects?
        
    */

    // Server net
    ServerNetwork serverNet;
    public float updateFrequency = 1.0f;
    float updateTimer;

    // Keep a list of clients that are server admins
    List<long> adminClients;

	// Use this for initialization
	void Start () {
        adminClients = new List<long>();
        serverNet = GetComponent(typeof(ServerNetwork)) as ServerNetwork;

        updateTimer = updateFrequency;
	}

    IEnumerator TestStuff(long aClientId) {
        int numClients = 20;
        int numObjects = 45;

        // Create some other clients
        long[] clients = new long[numClients];
        int[] clientAreas = new int[numClients];
        for (int i = 0; i < numClients; i++) {
            clients[i] = UnityEngine.Random.Range(int.MaxValue, int.MinValue);
            clientAreas[i] = UnityEngine.Random.Range(0, 50);
            serverNet.CallRPC("UpdateClient", aClientId, -1, clients[i],
                "" + UnityEngine.Random.Range(0, 256) + "." + UnityEngine.Random.Range(0, 256) + "." + UnityEngine.Random.Range(0, 256) + "." + UnityEngine.Random.Range(0, 256),
                clientAreas[i],
                UnityEngine.Random.Range(400, 500),
                "client");
        }

        // Create some objects
        int[] objects = new int[numObjects];
        for (int i = 0; i < numObjects; i++) {
            objects[i] = UnityEngine.Random.Range(1, int.MaxValue);
            int clientNum = UnityEngine.Random.Range(0, numClients - 1);
            Vector3 initialPos = new Vector3(UnityEngine.Random.Range(-500.0f, 500.0f), UnityEngine.Random.Range(-500.0f, 500.0f));
            bool followsClient = (UnityEngine.Random.Range(0, 10) > 5);

            serverNet.CallRPC("UpdateNetObject", aClientId, -1, objects[i],
                clientAreas[clientNum],
                "Monsters/TestMonster/Blah",
                initialPos,
                new Quaternion(UnityEngine.Random.Range(-1000.0f, 1000.0f), UnityEngine.Random.Range(-1000.0f, 1000.0f), UnityEngine.Random.Range(-1000.0f, 1000.0f), UnityEngine.Random.Range(-1000.0f, 1000.0f)),
                followsClient,
                clients[clientNum]
                );

            StartCoroutine(UpdateObject(aClientId, objects[i], initialPos, clientAreas[clientNum], clients[clientNum], followsClient));
            yield return new WaitForSeconds(0.01f);
        }

        yield return null;
    }
    IEnumerator UpdateObject(long aClientId, int aId, Vector3 aPosition, int aAreaId, long aOwnerId, bool followsClient) {
        Vector3 velocity = new Vector3(UnityEngine.Random.Range(-1.0f, 0), UnityEngine.Random.Range(-1.0f, 0), 0);
        while (true) {
            yield return new WaitForSeconds(2.0f);
            // Get the object and update it's position
            aPosition += velocity;
            if (aPosition.x > 500) {
                velocity.x = UnityEngine.Random.Range(-1.0f, 0);
            }
            if (aPosition.x < -500) {
                velocity.x = UnityEngine.Random.Range(0, 1.0f);
            }
            if (aPosition.y > 500) {
                velocity.y = UnityEngine.Random.Range(-1.0f, 0);
            }
            if (aPosition.y < -500) {
                velocity.y = UnityEngine.Random.Range(0, 1.0f);
            }

            serverNet.CallRPC("UpdateNetObject", aClientId, -1, aId,
                aAreaId,
                "Monsters/TestMonster/Blah",
                aPosition,
                new Quaternion(UnityEngine.Random.Range(-1000.0f, 1000.0f), UnityEngine.Random.Range(-1000.0f, 1000.0f), UnityEngine.Random.Range(-1000.0f, 1000.0f), UnityEngine.Random.Range(-1000.0f, 1000.0f)),
                followsClient,
                aOwnerId
                );
        }
    }









	
	// Update is called once per frame
	void Update () {
	    // How often should we update to the admin clients?
        updateTimer -= Time.deltaTime;
        if (updateTimer <= 0) {
            updateTimer = updateFrequency;

            // Send down all the network objects
            Dictionary<int, ServerNetwork.NetworkObject> objects = serverNet.GetAllObjects();
            foreach (long clientId in adminClients) {
                foreach (KeyValuePair<int, ServerNetwork.NetworkObject> obj in objects) {
                    serverNet.CallRPC("UpdateNetObject", clientId, -1, obj.Value.networkId, obj.Value.areaId, obj.Value.prefabName, obj.Value.position, obj.Value.rotation, obj.Value.followsClient);
                }
            }
        }
	}

    // Add a client to the list of admin clients
    void AddAdminClient(long aClientId) {
        adminClients.Add(aClientId);

        // Send initial data to the admin client
        SendInitialData(aClientId);


        // TOOD: This is just for testing
        StartCoroutine(TestStuff(aClientId));
    }

    // Remove a client from the list of admin client
    void RemoveAdminClient(long aClientId) {
        adminClients.Remove(aClientId);
    }

    // Send down initial data the admin client will need
    public void SendInitialData(long aClientId) {
        // Send a bunch of data to the admin client
        List<ServerNetwork.ClientData> clients = serverNet.GetAllClients();
        foreach (ServerNetwork.ClientData client in clients) {
            serverNet.CallRPC("UpdateClient", aClientId, -1, client.networkIdentifier, client.connection.RemoteEndPoint.Address.ToString(), client.areaId, client.numberOfIds, client.clientType);
        }

        // Send down all the network objects
        Dictionary<int, ServerNetwork.NetworkObject> objects = serverNet.GetAllObjects();
        foreach (KeyValuePair<int, ServerNetwork.NetworkObject> obj in objects) {
            //public void AddObject(int aId, int aAreaId, string aPrefabName, Vector3 aPosition, Quaternion aRotation, bool aFollowsClient) {
            serverNet.CallRPC("UpdateNetObject", aClientId, -1, obj.Value.networkId, obj.Value.areaId, obj.Value.prefabName, obj.Value.position, obj.Value.rotation, obj.Value.followsClient);
        }
    }

    // These contain all the SendMessage's that ServerNetwork does, and sends data to any admin clients
    public void OnClientConnected(long aClientId) {
        ServerNetwork.ClientData client = serverNet.GetClientData(aClientId);

        // Send data about this client to all the current admin clients
        foreach (long adminClientId in adminClients) {
            serverNet.CallRPC("UpdateClient", aClientId, -1, client.networkIdentifier, client.connection.RemoteEndPoint.Address.ToString(), client.areaId, client.numberOfIds, client.clientType);
        }

        // If this new client is a admin, add them
        if (client.clientType == "admin") {
            AddAdminClient(aClientId);
        }
    }
    public void OnClientDisconnected(long aClientId) {
        ServerNetwork.ClientData clientData = serverNet.GetClientData(aClientId);
        
        // If this was an admin, remove them
        if (clientData.clientType == "admin") {
            RemoveAdminClient(clientData.networkIdentifier);
        }

        // Update the admin clients
        foreach (long adminClientId in adminClients) {
            serverNet.CallRPC("RemoveClient", adminClientId, -1, aClientId);
        }
    }
    public void OnAreaChange(ServerNetwork.AreaChangeInfo info) {
        ServerNetwork.ClientData clientData = serverNet.GetClientData(info.id);
        foreach (long adminClientId in adminClients) {
            serverNet.CallRPC("ClientChangeArea", adminClientId, -1, info.id, info.newAreaId, info.oldAreaId);
        }
    }
    public void OnIntantiateNetworkObject(int aNetworkId) {
        ServerNetwork.NetworkObject netObj = serverNet.GetNetObjById(aNetworkId);
        foreach (long adminClientId in adminClients) {
            serverNet.CallRPC("UpdateNetObject", adminClientId, -1, netObj.networkId, netObj.areaId, netObj.prefabName, netObj.position, netObj.rotation, netObj.followsClient);
        }
    }
    public void OnDestroyNetworkObject(int aNetworkId) {
        ServerNetwork.NetworkObject netObj = serverNet.GetNetObjById(aNetworkId);
        foreach (long adminClientId in adminClients) {
            serverNet.CallRPC("RemoveNetObject", adminClientId, -1, aNetworkId);
        }
    }
    public void ConnectionRequest(ServerNetwork.ConnectionRequestInfo info) {
        // A client is requesting to connect to the game
    }

    //////////////////////////
    // RPCs from the admin client
    //////////////////////////
    public void ClientKick(long aClientId) {
        serverNet.Kick(aClientId);
    }
    public void DestroyObject(int aObjectId) {
        serverNet.Destroy(aObjectId);
    }
    public void Instantiate(string aPrefab, Vector3 aPosition, Quaternion aRotation, int aAreaId) {
        serverNet.InstantiateNetworkObject(aPrefab, aPosition, aRotation, aAreaId);
    }
    public void SetPosition(int aObjectId, Vector3 aPosition, Quaternion aRotation, int aAreaId) {
        // Send a message to the given game object asking it to change its position
        ServerNetwork.NetworkObject obj = serverNet.GetNetObjById(aObjectId);
        long aClientId = serverNet.GetOwnerClientId(aObjectId);

        // Send the message to the client
        serverNet.CallRPC("SetPositionFromServer", aClientId, aObjectId, aPosition, aRotation, aAreaId);
    }
}

#endif