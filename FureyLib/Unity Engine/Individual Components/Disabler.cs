
// Object Disabler Script
// by Kyle Furey

using System.Collections.Generic;
using UnityEngine;

// Disables an object or components of an object when the game starts.
public class Disabler : MonoBehaviour
{
    [Header("Disables an object or components of an object when the game starts.")]

    [Header("Whether to disable this script's object:")]
    public DisableState objectState = DisableState.Disable;

    [Header("Whether to disable this script's set objects:")]
    public DisableState gameObjectStates = DisableState.Disable;

    [Header("The disabled objects:")]
    public List<GameObject> disabledGameObjects = new List<GameObject>();

    [Header("Whether to disable this script's set components:")]
    public DisableState componentStates = DisableState.Disable;

    [Header("The disabled components:")]
    public List<MonoBehaviour> disabledComponents = new List<MonoBehaviour>();

    [Header("Whether to disable the renderers attached to this script's set objects and their children:")]
    public DisableState rendererStates = DisableState.Disable;

    [Header("The objects to disable their renderers:")]
    public List<GameObject> disabledRendererObjects = new List<GameObject>();

    [Header("Whether to destroy this script on activation:")]
    public bool destroyOnActivate = true;

    [Header("Whether to automatically activate this script:")]
    public bool autoActivate = true;

    [Header("The delay to activate this script when automatically activated:")]
    public float delay = 0;

    // Disable state enum
    public enum DisableState { Disable, Destroy, Enable, None };

    private void Awake()
    {
        if (autoActivate)
        {
            ActivateDelayed(delay);
        }
    }

    // Disables all the given objects
    public void Activate()
    {
        if (rendererStates != DisableState.None)
        {
            if (rendererStates == DisableState.Disable)
            {
                for (int i = 0; i < disabledRendererObjects.Count; i++)
                {
                    Renderer[] disabledRenderers = disabledRendererObjects[i].GetComponentsInChildren<Renderer>();

                    for (int j = 0; j < disabledRenderers.Length; j++)
                    {
                        disabledRenderers[j].enabled = false;
                    }
                }
            }
            else if (rendererStates == DisableState.Destroy)
            {
                for (int i = 0; i < disabledRendererObjects.Count; i++)
                {
                    Renderer[] disabledRenderers = disabledRendererObjects[i].GetComponentsInChildren<Renderer>();

                    for (int j = 0; j < disabledRenderers.Length; j++)
                    {
                        Destroy(disabledRenderers[j]);
                    }
                }
            }
            else if (rendererStates == DisableState.Enable)
            {
                for (int i = 0; i < disabledRendererObjects.Count; i++)
                {
                    Renderer[] disabledRenderers = disabledRendererObjects[i].GetComponentsInChildren<Renderer>();

                    for (int j = 0; j < disabledRenderers.Length; j++)
                    {
                        disabledRenderers[j].enabled = true;
                    }
                }
            }
        }

        if (componentStates != DisableState.None)
        {
            if (componentStates == DisableState.Disable)
            {
                for (int i = 0; i < disabledComponents.Count; i++)
                {
                    disabledComponents[i].enabled = false;
                }
            }
            else if (componentStates == DisableState.Destroy)
            {
                for (int i = 0; i < disabledComponents.Count; i++)
                {
                    Destroy(disabledComponents[i]);
                }
            }
            else if (componentStates == DisableState.Enable)
            {
                for (int i = 0; i < disabledComponents.Count; i++)
                {
                    disabledComponents[i].enabled = true;
                }
            }
        }

        if (gameObjectStates != DisableState.None)
        {
            if (gameObjectStates == DisableState.Disable)
            {
                for (int i = 0; i < disabledGameObjects.Count; i++)
                {
                    disabledGameObjects[i].SetActive(false);
                }
            }
            else if (gameObjectStates == DisableState.Destroy)
            {
                for (int i = 0; i < disabledGameObjects.Count; i++)
                {
                    Destroy(disabledGameObjects[i]);
                }
            }
            else if (gameObjectStates == DisableState.Enable)
            {
                for (int i = 0; i < disabledGameObjects.Count; i++)
                {
                    disabledGameObjects[i].SetActive(true);
                }
            }
        }

        if (objectState != DisableState.None)
        {
            if (objectState == DisableState.Disable)
            {
                gameObject.SetActive(false);

                if (destroyOnActivate)
                {
                    Destroy(this);
                }
            }
            else if (objectState == DisableState.Destroy)
            {
                Destroy(gameObject);
            }
            else
            {
                if (destroyOnActivate)
                {
                    Destroy(this);
                }
            }
        }
    }

    // Disables all the given objects
    public void ActivateDelayed(float delay)
    {
        Invoke("Activate", delay);
    }
}
