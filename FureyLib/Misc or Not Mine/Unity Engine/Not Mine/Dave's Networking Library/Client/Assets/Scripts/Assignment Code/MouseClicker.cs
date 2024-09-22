
// Mouse Clicking Script
// by Kyle Furey

using UnityEngine;
using UnityEngine.Events;

/// <summary>
/// Allows the main camera to fire events on clicked objects via IMouseClickable.
/// </summary>
public class MouseClicker : MonoBehaviour
{
    [Header("Allows the main camera to fire events on clicked objects via IMouseClickable.\n")]

    [Header("The camera used to cast the mouse towards an object for clicking functionality:")]
    [SerializeField] private Camera mainCamera = null;

    [Header("Event called when the mouse clicks or attempts to click an object:")]
    [SerializeField] private UnityEvent onClick = null;
    [SerializeField] private UnityEvent onSuccessfulClick = null;


    // UNITY FUNCTIONS

    /// <summary>
    /// Stores the main camera.
    /// </summary>
    private void Start()
    {
        if (mainCamera != null)
        {
            mainCamera = Camera.main;
        }
    }

    /// <summary>
    /// Checks for mouse input.
    /// </summary>
    private void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {
            onClick.Invoke();

            RaycastHit hit;

            Vector3 mouseDirection = mainCamera.ScreenPointToRay(new Vector3(Input.mousePosition.x, Input.mousePosition.y, 0)).direction;

            if (Physics.Raycast(mainCamera.transform.position, mouseDirection, out hit, Mathf.Infinity, ~(1 << 2), QueryTriggerInteraction.UseGlobal))
            {
                Component[] components = hit.transform.gameObject.GetComponents<Component>();

                foreach (Component component in components)
                {
                    if (component is IMouseClickable)
                    {
                        (component as IMouseClickable).OnMouseClick(mainCamera, hit);
                    }
                }

                Debug.DrawLine(mainCamera.transform.position, hit.point, Color.green, 1);

                onSuccessfulClick.Invoke();
            }
            else
            {
                Debug.DrawRay(mainCamera.transform.position, mouseDirection, Color.red, 1);
            }
        }
    }
}

/// <summary>
/// Contracts mouse clicking functionality.
/// </summary>
public interface IMouseClickable
{
    /// <summary>
    /// Called when this object is clicked on via a mouse.
    /// </summary>
    public abstract void OnMouseClick(Camera mainCamera, RaycastHit hitInfo);
}
