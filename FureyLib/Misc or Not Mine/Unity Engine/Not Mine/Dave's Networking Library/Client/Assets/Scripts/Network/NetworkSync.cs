using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine.SceneManagement;

// This class handles sync'ing data with a game object over the network
public class NetworkSync : MonoBehaviour
{

    // My network id, provided by the server
    [SerializeField]
    private int networkId = -1;

    // Is this networkSync owned by this client.
    [HideInInspector]
    public bool owned
    {
        get { return isOwned; }
    }
    private bool isOwned = false;
    [HideInInspector]
    public bool followsClient = false;

    // Component we should be sending updates about
    public UCNetwork.DeliveryMethod deliveryMethod = UCNetwork.DeliveryMethod.UnreliableSequenced;
    public float broadcastFrequency = 0.1f; // Ten times a second
    public bool inAreaOnly = true; // Should the broadcasts be sent to clients in other areas

    // This is a bit annoying to have to set these functions up in code
    [HideInInspector]
    public delegate void GetSyncData(ref System.IO.BinaryWriter aBinWriter);
    [HideInInspector]
    public delegate void SetSyncData(ref System.IO.BinaryReader aBinReader);

    // The functions we'll call to get/set data
    [HideInInspector]
    public GetSyncData getDataFunction = null;
    [HideInInspector]
    public SetSyncData setDataFunction = null;
    [HideInInspector]
    public Vector3 position;
    [HideInInspector]
    public Quaternion rotation;
    [HideInInspector]
    public string origScene;

    // Temporary storage for rotation and position logic
    private Vector3 tPosition;
    private Quaternion tRotation;

    // Temporary storage for the network sync byte array
    private int tDataLength;
    private byte[] tData;

    private List<int> areaIds = new List<int>();

    [HideInInspector]
    public ClientNetwork clientNet;

    // Counter for when to send a sync update
    float timeToSend = 0;
    
#if UNITY_EDITOR
    class PreviousPositionData
    {
        public Vector3 position;
        public Quaternion rotation;
        public float time;
        public Color color;
    }
    PreviousPositionData[] previousPostions = new PreviousPositionData[10];
    int previousPositionIndex = 0;
#endif 

    //////////////////
    // Network id functionality
    //////////////////
    // Set this objects network Id
    // Called from ClientNetwork when this object is instantiated
    public void SetId(int aNetworkId)
    {
        if (networkId != -1)
        {
            Debug.LogError("Changing a network id that has already been changed");
            clientNet.RemoveNetObject(aNetworkId);
        }
        else if (clientNet.AddNetObject(aNetworkId, this, gameObject))
        {
            networkId = aNetworkId;
        }
    }

    public int GetId()
    {
        return networkId;
    }

    void OnDestroy()
    {
        if (clientNet && networkId != -1)
        {
            clientNet.RemoveNetObject(networkId);
        }
    }

    // Callback happens on this object once the network is ready
    void NetworkInitialized()
    {

    }

    // Use this for initialization
    void Start()
    {
        position = transform.position;
        rotation = transform.rotation;
        origScene = gameObject.scene.name;

        // If our network id hasn't been set, ask the server to give us one
        if (networkId == -1)
        {
            ClientNetwork client = FindObjectOfType<ClientNetwork>();
            if (client == null)
            {
                Debug.LogError("NetworkId::Start() has been called without a ClientNetwork being available");
                this.enabled = false;
                return;
            }
            client.ConnectNetworkSync(this);
        }
        else
        {
            // Check if we own this object
            if (clientNet.isOwned(networkId))
            {
                isOwned = true;
            }
        }

#if UNITY_EDITOR
        for (int i = 0; i < previousPostions.Length; i++)
        {
            previousPostions[i] = new PreviousPositionData();
            previousPostions[i].color = new Color(0.0f, 0.0f, 0.0f, 0.0f);
        }
#endif

    }
     
    // Update is called once per frame
    void Update()
    {
        timeToSend -= Time.deltaTime;
        if (timeToSend <= 0)
        {
            timeToSend = broadcastFrequency;
            BroadcastSync();
        }
    }

    //////////////////
    // Ownership callbacks
    //////////////////
    public void OnGainOwnership()
    {
        isOwned = true;
    }
    public void OnLoseOwnership()
    {
        isOwned = false;
    }
    public void Destroy()
    {
        clientNet.Destroy(networkId);
    }
    public void SetFollowClient(bool aShouldFollow)
    {
        clientNet.CallRPC("SetFollowsClient", UCNetwork.MessageReceiver.ServerOnly, -1, networkId, aShouldFollow);
        followsClient = aShouldFollow;
    }

    //////////////////
    // RPC functionality
    //////////////////
    // Call an RPC on this object
    public void CallRPC(string aFunctionName, UCNetwork.MessageReceiver aReceiver, params object[] aParams)
    {
        /*
        int sendingNetworkId = networkId;
        if (aReceiver == UCNetwork.MessageReceiver.ServerOnly) {
            sendingNetworkId = -1;
        }
        */
        if (networkId == -1)
        {
            Debug.LogWarning("NetworkSync::CallRPC - Net sync does not have a valid network id yet");
        }
        if (clientNet)
        {
            clientNet.CallRPC(aFunctionName, aReceiver, networkId, aParams);
        }
    }


    //////////////////
    // Synchonization functionality
    //////////////////
    // Receive a sync
    public void ReceiveSyncData(byte[] aData, Vector3 aPosition, Quaternion aRotation)
    {
#if UNITY_EDITOR
        previousPostions[previousPositionIndex] = new PreviousPositionData();
        previousPostions[previousPositionIndex].position = aPosition;
        previousPostions[previousPositionIndex].rotation = aRotation;
        previousPostions[previousPositionIndex].time = Time.time;
        previousPostions[previousPositionIndex].color = new Color(Random.Range(0.0f, 1.0f), Random.Range(0.0f, 1.0f), Random.Range(0.0f, 1.0f));
        previousPositionIndex++;
        if (previousPositionIndex > previousPostions.Length - 1)
        {
            previousPositionIndex = 0;
        }
#endif
        if (owned)
            return;

        position = aPosition;
        rotation = aRotation;

        
        transform.localPosition = aPosition;
        transform.localRotation = aRotation;
    
        MemoryStream stream = new MemoryStream(aData);
        BinaryReader binReader = new BinaryReader(stream);
        if (setDataFunction != null)
        {
            setDataFunction(ref binReader);
        }
    }

    //Receive a (lite) sync
    public void ReceiveLiteSyncData(byte[] aData)
    {
        MemoryStream stream = new MemoryStream(aData);
        BinaryReader binReader = new BinaryReader(stream);
        if (setDataFunction != null)
        {
            setDataFunction(ref binReader);
        }
    }

    // Broadcast sync data
    void BroadcastSync()
    {
        if (!owned)
        {
            return;
        }
        MemoryStream stream = new MemoryStream();
        BinaryWriter binWriter = new BinaryWriter(stream);

        // Get the data
        if (getDataFunction != null)
        {
            getDataFunction(ref binWriter);
        }

        // Send this data to all of the other objects with my network id
        byte[] dataArray = stream.ToArray();
        bool arrayDataChanged = !dataArray.Compare(tData);

        position = transform.localPosition;
        rotation = transform.localRotation;

        // If the position has changed, do a full update
        if (position != tPosition || rotation != tRotation)
        {
            tPosition = position;
            tRotation = rotation;
            if (inAreaOnly)
            {
                clientNet.SyncNetworkData(networkId, UCNetwork.MessageReceiver.OtherClientsInArea, deliveryMethod, dataArray, position, rotation);
            }
            else
            {
                clientNet.SyncNetworkData(networkId, UCNetwork.MessageReceiver.OtherClients, deliveryMethod, dataArray, position, rotation);
            }
            // If the data has changed, and the position hasn't, do a lite update.
        }
        else if (arrayDataChanged)
        {
            tData = dataArray;
            if (inAreaOnly)
            {
                clientNet.LiteSyncNetworkData(networkId, UCNetwork.MessageReceiver.OtherClientsInArea, deliveryMethod, dataArray);
            }
            else
            {
                clientNet.LiteSyncNetworkData(networkId, UCNetwork.MessageReceiver.OtherClients, deliveryMethod, dataArray);
            }
        }
        else
        {
            //Debug.Log("Sending no update with positions: " + position + " " + tPosition);
        }
        // If nothing has changed, don't send any updates
    }

    // Add this object to an area
    public void AddToArea(int aAreaId)
    {
        clientNet.AddObjectToArea(networkId, aAreaId);
        if(!areaIds.Contains(aAreaId))
        {
            areaIds.Add(aAreaId);
        }
    }

    // Remove this object from an area
    public void RemoveFromArea(int aAreaId)
    {
        clientNet.RemoveObjectFromArea(networkId, aAreaId);
        if (areaIds.Contains(aAreaId))
        {
            areaIds.Remove(aAreaId);
        }
    }

#if UNITY_EDITOR
    public void OnDrawGizmos()
    {
        if (Application.isEditor && Application.isPlaying)
        {
            if (owned)
            {
                Gizmos.color = Color.green;
                Gizmos.DrawSphere(position, 0.5f);
            }
            else
            {
                foreach (PreviousPositionData data in previousPostions)
                {
                    Gizmos.color = data.color;
                    Gizmos.DrawSphere(data.position, 0.5f);
                }
            }
        }
    }
#endif
}