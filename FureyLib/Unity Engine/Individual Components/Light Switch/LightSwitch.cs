
// Light Switch Script
// by Kyle Furey

using System.Collections.Generic;
using UnityEngine;

// An interactable light switch object.
public class LightSwitch : MonoBehaviour
{
    [Header("An interactable light switch object.")]

    [Header("Whether the light switch is currently on:")]
    [SerializeField] private bool on = true;

    [Header("The rotations of the switch being up or down:")]
    [SerializeField] private float upRotation = 160;
    [SerializeField] private float downRotation = 20;

    [Header("The flip speed of the switch:")]
    [SerializeField] private float speed = 8;

    [Header("The input settings of interacting with this light:")]
    [SerializeField] private bool useMouseButton = true;
    [SerializeField] private bool useKey = true;
    [SerializeField] private KeyCode key = KeyCode.E;

    [Header("The light switch pivot:")]
    [SerializeField] private GameObject switchPivot = null;

    [Header("The switches this light is connected to:")]
    [SerializeField] private List<SwitchedLights> lights = new List<SwitchedLights>();

    [Header("Whether to delay the fading of each light:")]
    [SerializeField] private bool delayLights = false;

    [Header("The delay between fading all of the lights:")]
    [SerializeField] private float delay = 0.25f;

    [Header("Whether to start fading the lights instantly or after the switch is fully down:")]
    [SerializeField] private bool instant = false;

    [Header("Whether to destroy the script on completion:")]
    [SerializeField] private bool destroy = false;

    // Whether the player is in range of the switch
    private bool inRange = false;

    // The current percentage of the switch
    private float percentage = 1;

    // Whether the switch is currently being flipped
    private bool go = false;

    private void Awake()
    {
        if (switchPivot == null)
        {
            switchPivot = transform.GetChild(1).gameObject;
        }

        switchPivot.transform.localEulerAngles = new Vector3(on ? downRotation : upRotation, 0, 0);

        percentage = on ? 1 : 0;

        for (int j = 0; j < lights.Count; j++)
        {
            for (int i = 0; i < lights[j].lights.Count; i++)
            {
                lights[j].lights[i].Invoke(on ? "TurnOnInstantly" : "TurnOffInstantly", 0);
            }
        }
    }

    private void Update()
    {
        if (go)
        {
            if (!on)
            {
                percentage = Mathf.MoveTowards(percentage, 0, speed * Time.deltaTime);

                switchPivot.transform.localEulerAngles = new Vector3(Value(percentage, upRotation, downRotation), 0, 0);

                if (percentage <= 0)
                {
                    go = false;

                    if (!instant)
                    {
                        for (int j = 0; j < lights.Count; j++)
                        {
                            for (int i = 0; i < lights[j].lights.Count; i++)
                            {
                                lights[j].lights[i].Invoke("TurnOff", delayLights ? i * delay : 0);
                            }
                        }
                    }

                    if (destroy)
                    {
                        Destroy(this);
                    }
                }
            }
            else
            {
                percentage = Mathf.MoveTowards(percentage, 1, speed * Time.deltaTime);

                switchPivot.transform.localEulerAngles = new Vector3(Value(percentage, upRotation, downRotation), 0, 0);

                if (percentage >= 1)
                {
                    go = false;

                    if (!instant)
                    {
                        for (int j = 0; j < lights.Count; j++)
                        {
                            for (int i = 0; i < lights[j].lights.Count; i++)
                            {
                                lights[j].lights[i].Invoke("TurnOn", delayLights ? i * delay : 0);
                            }
                        }
                    }

                    if (destroy)
                    {
                        Destroy(this);
                    }
                }
            }
        }
        // Light being switched
        else if (inRange)
        {
            if ((useMouseButton && Input.GetMouseButtonDown(0)) || (useKey && Input.GetKeyDown(key)))
            {
                on = !on;

                go = true;

                if (instant)
                {
                    for (int j = 0; j < lights.Count; j++)
                    {
                        for (int i = 0; i < lights[j].lights.Count; i++)
                        {
                            lights[j].lights[i].Invoke(on ? "TurnOn" : "TurnOff", delayLights ? i * delay : 0);
                        }
                    }
                }
            }
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Player")
        {
            inRange = true;
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.tag == "Player")
        {
            inRange = false;
        }
    }

    // Returns a value relative to a percentage of a minimum and maximum
    private static float Value(float percentage, float min, float max)
    {
        return (max - min) * percentage + min;
    }
}
