
// Static Math Functions Script
// by Kyle Furey

using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UIElements;

// Include this heading to use the class
using static Math;

/// <summary>
/// New math functions.
/// </summary>
public static class Math
{
    // VECTOR

    /// <summary>
    /// Returns the squared distance between two vectors
    /// </summary>
    /// <param name="pointA"></param>
    /// <param name="pointB"></param>
    /// <returns></returns>
    public static float DistanceSquared(Vector3 pointA, Vector3 pointB)
    {
        float xDistance = pointA.x - pointB.x;
        float yDistance = pointA.y - pointB.y;
        float zDistance = pointA.z - pointB.z;

        return xDistance * xDistance + yDistance * yDistance + zDistance * zDistance;
    }

    /// <summary>
    /// Returns an offset vector based on the relative transform and given offset vector
    /// </summary>
    /// <param name="transform"></param>
    /// <param name="offset"></param>
    /// <returns></returns>
    public static Vector3 TranslateRelative(Transform transform, Vector3 offset)
    {
        Vector3 directionX = transform.right * offset.x;
        Vector3 directionY = transform.up * offset.y;
        Vector3 directionZ = transform.forward * offset.z;

        return transform.position + directionX + directionY + directionZ;
    }

    /// <summary>
    /// Returns the direction between two vectors
    /// </summary>
    /// <param name="pointA"></param>
    /// <param name="pointB"></param>
    /// <returns></returns>
    public static Vector3 Direction(Vector3 pointA, Vector3 pointB)
    {
        return pointB - pointA;
    }

    /// <summary>
    /// Get a direction relative to the given rotation from the given euler rotation
    /// </summary>
    /// <param name="rotation"></param>
    /// <param name="eulerRotation"></param>
    /// <returns></returns>
    public static Vector3 Direction(Quaternion rotation, Vector3 eulerRotation)
    {
        return rotation * eulerRotation;
    }

    /// <summary>
    /// Returns the cross product of a vector
    /// </summary>
    /// <param name="pointA"></param>
    /// <param name="pointB"></param>
    /// <param name="pointC"></param>
    /// <param name="useY"></param>
    /// <returns></returns>
    public static float CrossProduct(Vector3 pointA, Vector3 pointB, Vector3 pointC, bool useY = false)
    {
        return (pointB.x - pointA.x) * (useY ? (pointC.y - pointA.y) : (pointC.z - pointA.z)) - (pointC.x - pointA.x) * (useY ? (pointB.y - pointA.y) : (pointB.z - pointA.z));
    }

    /// <summary>
    /// Rotate a direction by a euler rotation
    /// </summary>
    /// <param name="direction"></param>
    /// <param name="rotation"></param>
    /// <returns></returns>
    public static Vector3 Rotate(Vector3 direction, Vector3 rotation)
    {
        return Quaternion.Euler(rotation) * direction;
    }

    /// <summary>
    /// Rotate a direction by a quaternion rotation
    /// </summary>
    /// <param name="direction"></param>
    /// <param name="rotation"></param>
    /// <returns></returns>
    public static Vector3 Rotate(Vector3 direction, Quaternion rotation)
    {
        return rotation * direction;
    }

    /// <summary>
    /// Gets the bezier interpolation of two points based on a third point
    /// </summary>
    /// <param name="start"></param>
    /// <param name="end"></param>
    /// <param name="curve"></param>
    /// <param name="alpha"></param>
    /// <returns></returns>
    public static Vector3 Bezier(Vector3 start, Vector3 end, Vector3 curve, float alpha)
    {
        return Vector3.Lerp(Vector3.Lerp(start, curve, alpha), Vector3.Lerp(curve, end, alpha), alpha);
    }

    /// <summary>
    /// Returns a list of vectors representing a bezier curve
    /// </summary>
    /// <param name="start"></param>
    /// <param name="end"></param>
    /// <param name="curve"></param>
    /// <param name="resolution"></param>
    /// <returns></returns>
    public static List<Vector3[]> BezierCurve(Vector3 start, Vector3 end, Vector3 curve, int resolution)
    {
        List<Vector3[]> result = new List<Vector3[]>(resolution);

        Vector3 previous = start;

        for (int i = 0; i < resolution; i++)
        {
            float alpha = (i + 1) / resolution;

            Vector3 next = Bezier(start, end, curve, alpha);

            Vector3[] line = new Vector3[2]
            {
                previous, next
            };

            result.Add(line);

            previous = next;
        }

        return result;
    }

    /// <summary>
    /// Returns the corresponding local position of the given world position relative to the given transform
    /// </summary>
    /// <param name="position"></param>
    /// <param name="transform"></param>
    /// <returns></returns>
    public static Vector3 GetLocalPosition(Vector3 position, Transform transform)
    {
        position -= Quaternion.Euler(-transform.eulerAngles.x, -transform.eulerAngles.y, -transform.eulerAngles.z) * transform.position;

        position = new Vector3(position.x / transform.lossyScale.x, position.y / transform.lossyScale.y, position.z / transform.lossyScale.z);

        return position;
    }

    /// <summary>
    /// Returns the corresponding world position of the given local position relative to the given transform
    /// </summary>
    /// <param name="position"></param>
    /// <param name="transform"></param>
    /// <returns></returns>
    public static Vector3 GetWorldPosition(Vector3 position, Transform transform)
    {
        position = new Vector3(position.x * transform.lossyScale.x, position.y * transform.lossyScale.y, position.z * transform.lossyScale.z);

        position = transform.rotation * position;

        position += transform.position;

        return position;
    }


    // FLOAT

    /// <summary>
    /// Returns a percentage relative to a value of a minimum and maximum
    /// </summary>
    /// <param name="value"></param>
    /// <param name="min"></param>
    /// <param name="max"></param>
    /// <returns></returns>
    public static float Percentage(float value, float min, float max)
    {
        return (value - min) / (max - min);
    }

    /// <summary>
    /// Returns a value relative to a percentage of a minimum and maximum
    /// </summary>
    /// <param name="percentage"></param>
    /// <param name="min"></param>
    /// <param name="max"></param>
    /// <returns></returns>
    public static float Value(float percentage, float min, float max)
    {
        return (max - min) * percentage + min;
    }

    /// <summary>
    /// Moves a value towards another value by a percentage of the distance to the destination (and reaches the target after a certain distance is met)
    /// </summary>
    /// <param name="start"></param>
    /// <param name="end"></param>
    /// <param name="alpha"></param>
    /// <param name="minimumDistance"></param>
    /// <returns></returns>
    public static float SmartLerp(float start, float end, float alpha, float minimumDistance = 0.005f)
    {
        return (Mathf.Abs(end - start) <= minimumDistance) ? (end) : (start + ((end - start) * alpha));
    }


    // PRINT

    /// <summary>
    /// Prints a message to the console
    /// </summary>
    /// <param name="message"></param>
    public static string print(object message)
    {
        message = message.ToString();

        Debug.Log(message);

        return (string)message;
    }

    /// <summary>
    /// Prints messages to the console
    /// </summary>
    /// <param name="messages"></param>
    public static string print(params object[] messages)
    {
        string message = "";

        for (int i = 0; i < messages.Length; i++)
        {
            message += messages[i].ToString() + " ";
        }

        Debug.Log(message);

        return message;
    }
}
