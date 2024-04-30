
// Switchable Light Script
// by Kyle Furey

using System.Collections.Generic;
using UnityEngine;

// Allows a light to be easily turned on and off.
public class SwitchedLight : MonoBehaviour
{
    [Header("Allows a light to be easily turned on and off.")]

    [Header("Whether the light is currently on:")]
    [SerializeField] private bool on = true;

    [Header("The max intensity of the light:")]
    [SerializeField] private float intensity = 150;

    [Header("The fade speed of the light:")]
    [SerializeField] private float speed = 2;

    [Header("Whether to destroy the script on completion:")]
    [SerializeField] private bool destroy = false;

    // The light we are using
    private Light light = null;

    // The current percentage of the light
    private float percentage = 1;

    // Whether the light is currently changing
    private bool go = false;

    private void Awake()
    {
        light = GetComponent<Light>();

        light.intensity = on ? intensity : 0;

        percentage = on ? 1 : 0;
    }

    private void Update()
    {
        if (go)
        {
            if (!on)
            {
                percentage = Mathf.MoveTowards(percentage, 0, speed * Time.deltaTime);

                light.intensity = Value(percentage, 0, intensity);

                if (percentage <= 0)
                {
                    light.intensity = 0;

                    percentage = 0;

                    go = false;

                    if (destroy)
                    {
                        Destroy(this);
                    }
                }
            }
            else
            {
                percentage = Mathf.MoveTowards(percentage, 1, speed * Time.deltaTime);

                light.intensity = Value(percentage, 0, intensity);

                if (percentage >= 1)
                {
                    light.intensity = intensity;

                    percentage = 1;

                    go = false;

                    if (destroy)
                    {
                        Destroy(this);
                    }
                }
            }
        }
    }

    // Turns the light off
    public void TurnOff()
    {
        on = false;

        go = true;
    }

    // Turns the light on
    public void TurnOn()
    {
        on = true;

        go = true;
    }

    // Turns the light off instantly
    public void TurnOffInstantly()
    {
        on = false;

        intensity = 0;
    }

    // Turns the light on instantly
    public void TurnOnInstantly()
    {
        on = true;

        light.intensity = intensity;
    }

    // Returns a value relative to a percentage of a minimum and maximum
    private static float Value(float percentage, float min, float max)
    {
        return (max - min) * percentage + min;
    }
}

// Group of lights
[System.Serializable]
public class SwitchedLights
{
    public string name = "New Group of Lights";
    public List<SwitchedLight> lights = new List<SwitchedLight>();

    // Turns all the lights off
    public void TurnOff()
    {
        for (int i = 0; i < lights.Count; i++)
        {
            lights[i].TurnOff();
        }
    }

    // Turns all the lights on
    public void TurnOn()
    {
        for (int i = 0; i < lights.Count; i++)
        {
            lights[i].TurnOn();
        }
    }

    // Turns all the lights instantly
    public void TurnOffInstantly()
    {
        for (int i = 0; i < lights.Count; i++)
        {
            lights[i].TurnOffInstantly();
        }
    }

    // Turns all the lights instantly
    public void TurnOnInstantly()
    {
        for (int i = 0; i < lights.Count; i++)
        {
            lights[i].TurnOnInstantly();
        }
    }
}