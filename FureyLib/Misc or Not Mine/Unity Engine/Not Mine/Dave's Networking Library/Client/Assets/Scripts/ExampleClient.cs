using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class ExampleClient : MonoBehaviour
{
    public ClientNetwork clientNet;

    // Get the instance of the client
    static ExampleClient instance = null;
    
    // Are we in the process of logging into a server
    private bool loginInProcess = false;

    public GameObject loginScreen;

    public GameObject myPlayer;

    // Singleton support
    public static ExampleClient GetInstance()
    {
        if (instance == null)
        {
            Debug.LogError("ExampleClient is uninitialized");
            return null;
        }
        return instance;
    }

    // Use this for initialization
    void Awake()
    {
        // Make sure we have a ClientNetwork to use
        if (clientNet == null)
        {
            clientNet = GetComponent<ClientNetwork>();
        }
        if (clientNet == null)
        {
            clientNet = (ClientNetwork)gameObject.AddComponent(typeof(ClientNetwork));
        }
    }
    
    // Start the process to login to a server
    public void ConnectToServer(string aServerAddress, int aPort)
    {
        if (loginInProcess)
        {
            return;
        }
        loginInProcess = true;
        
        ClientNetwork.port = aPort;
        clientNet.Connect(aServerAddress, ClientNetwork.port, "", "", "", 0);
    }

    // Update is called once per frame
    void Update()
    {
        /*
        timeToSend -= Time.deltaTime;
        if (timeToSend <= 0)
        {
            clientNet.CallRPC("RequestMove", UCNetwork.MessageReceiver.ServerOnly, -1, 1, 1, "x");
            clientNet.CallRPC("Blah", UCNetwork.MessageReceiver.ServerOnly, -1, 1, 1, "x");
            timeToSend = 10;
        }
        */
    }

    public void UpdateState(int x, int y, string player)
    {
        // Update the visuals for the game
    }

    public void RPCTest(int aInt)
    {
        Debug.Log("RPC Test has been called with " + aInt);
    }

    public void NewClientConnected(long aClientId, string aValue)
    {
        Debug.Log("RPC NewClientConnected has been called with " + aClientId + " " + aValue);
    }

    // Networking callbacks
    // These are all the callbacks from the ClientNetwork
    void OnNetStatusNone()
    {
        Debug.Log("OnNetStatusNone called");
    }
    void OnNetStatusInitiatedConnect()
    {
        Debug.Log("OnNetStatusInitiatedConnect called");
    }
    void OnNetStatusReceivedInitiation()
    {
        Debug.Log("OnNetStatusReceivedInitiation called");
    }
    void OnNetStatusRespondedAwaitingApproval()
    {
        Debug.Log("OnNetStatusRespondedAwaitingApproval called");
    }
    void OnNetStatusRespondedConnect()
    {
        Debug.Log("OnNetStatusRespondedConnect called");
    }
    void OnNetStatusConnected()
    {
        loginScreen.SetActive(false);
        Debug.Log("OnNetStatusConnected called");

        clientNet.AddToArea(1);
    }

    void OnNetStatusDisconnecting()
    {
        Debug.Log("OnNetStatusDisconnecting called");

        if (myPlayer)
        {
            clientNet.Destroy(myPlayer.GetComponent<NetworkSync>().GetId());
        }
    }
    void OnNetStatusDisconnected()
    {
        Debug.Log("OnNetStatusDisconnected called");
        SceneManager.LoadScene("Client");
        
        loginInProcess = false;

        if (myPlayer)
        {
            clientNet.Destroy(myPlayer.GetComponent<NetworkSync>().GetId());
        }
    }
    public void OnChangeArea()
    {
        Debug.Log("OnChangeArea called");

        // Tell the server we are ready
        myPlayer = clientNet.Instantiate("Player", Vector3.zero, Quaternion.identity);
        myPlayer.GetComponent<NetworkSync>().AddToArea(1);
    }

    // RPC Called by the server once it has finished sending all area initization data for a new area
    public void AreaInitialized()
    {
        Debug.Log("AreaInitialized called");
    }
    
    void OnDestroy()
    {
        if (myPlayer)
        {
            clientNet.Destroy(myPlayer.GetComponent<NetworkSync>().GetId());
        }
        if (clientNet.IsConnected())
        {
            clientNet.Disconnect("Peace out");
        }
    }
}


