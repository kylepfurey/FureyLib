using UnityEngine;
using System.Collections;
using System;

public class NetworkTest : MonoBehaviour {

#if SERVER
    public ServerNetwork serverNet;
#endif
#if CLIENT
    public ClientNetwork clientNet;
#endif

    // Bunch of variables for sending test data through the UI
    string rpcValue = "RPC Value";
    string rpcName = "TestRPC";
    int networkId = 1;
    int areaId = 0;
    string server = "127.0.0.1";
    int port = 456;
    string username = "username";
    string password = "password";
    string prefabName = "Cube";
    void OnGUI() {

#if SERVER
        if (serverNet == null) {
            serverNet = ServerNetwork.instance as ServerNetwork;
        }
#endif
#if CLIENT
        if (clientNet == null) {
            clientNet = clientNet as ClientNetwork;
        }
#endif

#if SERVER
        if (serverNet != null) {
            GUI.Label(new Rect(10, 60, 180, 20), "Running as Server");
            GUI.Label(new Rect(10, 90, 180, 20), "Address: " + serverNet.GetAddress());
            GUI.Label(new Rect(10, 120, 180, 20), "Port: " + serverNet.GetPort());

            GUI.TextArea(new Rect(10, 150, 1000, 800 - 150), serverNet.GetStatsText());
            return;
        }
#endif

#if CLIENT
        int temp = 0;

        GUI.Label(new Rect(120, 10, 50, 20), "Address:");
        GUI.Label(new Rect(120, 35, 50, 20), "Port:");

        if (clientNet.IsConnected()) {
            // Disconnect
            GUI.Label(new Rect(180, 10, 100, 20), server);
            GUI.Label(new Rect(180, 35, 100, 20), port.ToString());
            if (GUI.Button(new Rect(10, 10, 100, 40), "Disconnect")) {
                clientNet.Disconnect("Peace out sucka!");
            }
        } else {
            // Connect
            GUI.Label(new Rect(120, 10, 50, 20), "Address:");
            server = GUI.TextField(new Rect(180, 10, 100, 20), server);
            GUI.Label(new Rect(120, 35, 50, 20), "Port:");
            string tempPort = GUI.TextField(new Rect(180, 35, 100, 20), port.ToString());
            if (int.TryParse(tempPort, out temp)) {
                port = temp;
            }
            if (GUI.Button(new Rect(10, 10, 100, 40), "Connect")) {
                clientNet.Connect(server, port, username, password, "networkTest", 0);
            }
        }

        // The rest we should only do if connected
        if (!clientNet.IsConnected()) {
            return;
        }

        // Testing RPC
        GUI.Label(new Rect(10, 60, 70, 20), "RPC Name");
        rpcName = GUI.TextField(new Rect(80, 60, 200, 20), rpcName, 25);
        GUI.Label(new Rect(10, 90, 70, 20), "RPC Value");
        rpcValue = GUI.TextField(new Rect(80, 90, 200, 20), rpcValue, 25);
        GUI.Label(new Rect(10, 120, 70, 20), "NetworkId");
        string tmpNetworkId = GUI.TextField(new Rect(80, 120, 200, 20), networkId.ToString(), 25);
        if (int.TryParse(tmpNetworkId, out temp)) {
            networkId = temp;
        }
        if (GUI.Button(new Rect(10, 150, 100, 40), "Test RPC")) {
            clientNet.CallRPC(rpcName, UCNetwork.MessageReceiver.AllClients, networkId, 0, 0.0f, rpcValue);
        }

        // Test switching areas
        //GUI.Label(new Rect(10, 220, 70, 20), "AreaId: " + clientNet.GetArea().ToString());
        string tmpAreaId = GUI.TextField(new Rect(80, 220, 200, 20), areaId.ToString(), 25);
        temp = 0;
        if (int.TryParse(tmpAreaId, out temp)) {
            areaId = temp;
        }
        if (GUI.Button(new Rect(10, 250, 100, 40), "Change Area")) {
          //  clientNet.ChangeArea(areaId);
        }

        // Test instantiate
        GUI.Label(new Rect(10, 320, 70, 20), "Prefab Name");
        prefabName = GUI.TextField(new Rect(80, 320, 200, 20), prefabName, 25);
        if (GUI.Button(new Rect(10, 350, 100, 40), "Instantiate")) {
            clientNet.Instantiate(prefabName, new Vector3(), new Quaternion());
        }
#endif
    }

    void Start() {

    }


    // These are all the callbacks from the network
    void OnNetStatusNone() {
        Debug.Log("OnNetStatusNone called");
    }
    void OnNetStatusInitiatedConnect() {
        Debug.Log("OnNetStatusInitiatedConnect called");
    }
    void OnNetStatusReceivedInitiation() {
        Debug.Log("OnNetStatusReceivedInitiation called");
    }
    void OnNetStatusRespondedAwaitingApproval() {
        Debug.Log("OnNetStatusRespondedAwaitingApproval called");
    }
    void OnNetStatusRespondedConnect() {
        Debug.Log("OnNetStatusRespondedConnect called");
    }
    void OnNetStatusConnected() {
        Debug.Log("OnNetStatusConnected called");
#if CLIENT
      //  clientNet.ChangeArea(1);
#endif
    }
    void OnNetStatusDisconnecting() {
        Debug.Log("OnNetStatusDisconnecting called");
    }
    void OnNetStatusDisconnected() {
        Debug.Log("OnNetStatusDisconnected called");
    }
    void OnChangeArea() {
        // This is where we should do logic for changing level/whatever in the game
        Debug.Log("Area changed called");
    }


    // Test receiving a RPC
    void testRPC(string aString) {
        Debug.Log("RPC Received with value " + aString);
    }
}
