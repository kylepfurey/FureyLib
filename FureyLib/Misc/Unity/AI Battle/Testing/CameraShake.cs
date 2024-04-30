using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraShake : MonoBehaviour
{
    float timeRemaining = 0f;
    float maxTime = 0f;
    float amplitude = 0.5f;
    Vector3 originalPos;

    void Update()
    {
        if (timeRemaining > 0)
        {
            transform.localPosition = originalPos + Random.insideUnitSphere * (timeRemaining / maxTime) * amplitude;
            timeRemaining -= Time.deltaTime;
        }
        else
        {
            timeRemaining = 0f;
            transform.localPosition = originalPos;
        }
    }

    public void SetPosition(Vector3 aPostion)
    {
        originalPos = aPostion;
    }

    public void AddShake(float aTime, float aAmplitude)
    {
        if (timeRemaining < aTime)
        {
            timeRemaining = aTime;
            maxTime = timeRemaining;
        }

        if (amplitude < aAmplitude)
            amplitude = aAmplitude;
    }
}