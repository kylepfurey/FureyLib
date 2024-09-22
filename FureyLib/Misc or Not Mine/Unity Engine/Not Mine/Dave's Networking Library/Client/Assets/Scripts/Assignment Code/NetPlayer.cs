
// Example Networked Player Script
// by Kyle Furey

// REQUIREMENT: UCNetwork Library, MouseClicker.cs

using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Example networked player.
/// </summary>
public class NetPlayer : MonoBehaviour, IMouseClickable
{
    [Header("Example networked player.\n")]

    [Header("The player's speed:")]
    [SerializeField] private float movementSpeed = 5;

    [Header("The player's materials (changed on click):")]
    [SerializeField] private List<Material> clickedMaterials = new List<Material>();

    /// <summary>
    /// This object's network sync object.
    /// </summary>
    private NetworkSync networkSync = null;

    /// <summary>
    /// This object's renderer.
    /// </summary>
    private Renderer renderer = null;


    // UNITY FUNCTIONS

    /// <summary>
    /// Gets the network sync object and renderer.
    /// </summary>
    private void Start()
    {
        networkSync = GetComponent<NetworkSync>();

        renderer = GetComponent<Renderer>();

        if (networkSync != null && !networkSync.owned)
        {
            // Requests each client to update its player object for this client.
            networkSync.CallRPC("RPC_UpdateMyObject", UCNetwork.MessageReceiver.OtherClients);
        }
    }

    /// <summary>
    /// Update is called once per frame
    /// </summary>
    private void Update()
    {
        if (networkSync != null && networkSync.owned)
        {
            Vector3 movement = new Vector3(Input.GetAxis("Horizontal") * movementSpeed * Time.deltaTime, Input.GetAxis("Vertical") * movementSpeed * Time.deltaTime, 0);

            transform.position += movement;
        }
    }


    // IMOUSECLICKABLE

    /// <summary>
    /// Called when this object is clicked on.
    /// </summary>
    /// <param name="mainCamera"></param>
    /// <param name="hitInfo"></param>
    public void OnMouseClick(Camera mainCamera, RaycastHit hitInfo)
    {
        if (renderer != null && clickedMaterials.Count > 0)
        {
            Material oldMaterial = renderer.material;

            renderer.sharedMaterial = clickedMaterials[Random.Range(0, clickedMaterials.Count)];

            // Send a message to each other client informing them I changed my player's material!
            networkSync.CallRPC("RPC_ChangeMaterial", UCNetwork.MessageReceiver.OtherClientsInArea, oldMaterial.name, renderer.sharedMaterial.name);
        }
    }


    // RPC FUNCTIONS

    /// <summary>
    /// Refreshes this object for a new client.
    /// </summary>
    public void RPC_UpdateMyObject()
    {
        // Update this player's material for the new client's corresponding player object.
        networkSync.CallRPC("RPC_ChangeMaterial", UCNetwork.MessageReceiver.OtherClients, renderer.sharedMaterial.name, renderer.sharedMaterial.name);
    }

    /// <summary>
    /// Changes this object's material and updates this object on other's clients.<br/>
    /// The payload includes the old material in the event the RPC is denied.
    /// </summary>
    public void RPC_ChangeMaterial(string oldMaterial, string newMaterial)
    {
        newMaterial = newMaterial.Replace("(Instance)", "");

        newMaterial = newMaterial.Trim();

        Material material = (Material)Resources.Load("Materials/" + newMaterial);

        if (renderer != null && newMaterial != null)
        {
            renderer.sharedMaterial = material;
        }
    }
}
