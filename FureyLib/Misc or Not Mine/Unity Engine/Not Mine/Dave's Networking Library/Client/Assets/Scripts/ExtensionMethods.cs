using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public static class ExtensionMethods {

    // Shuffle a list
    public static void Shuffle<T>(this IList<T> aList) {
        int n = aList.Count;
        while (n > 1) {
            n--;
            int k = UnityEngine.Random.Range(0, n + 1);
            T value = aList[k];
            aList[k] = aList[n];
            aList[n] = value;
        }
    }


    // Get a value out of some JsonData
    public static float GetFloat(this LitJson.JsonData aJsonData, string aValue) {
        return (float)(double)aJsonData[aValue];
    }

    // Convert a float[] into a short[]
    public static void ToShortArray(this float[] input, short[] output) {
        if (output.Length < input.Length) {
            throw new System.ArgumentException("in: " + input.Length + ", out: " + output.Length);
        }

        for (int i = 0; i < input.Length; ++i) {
            output[i] = (short)Mathf.Clamp((int)(input[i] * 32767.0f), short.MinValue, short.MaxValue);
        }
    }

    // Convert a short[] into a float[]
    public static void ToFloatArray(this short[] input, float[] output, int length) {
        if (output.Length < length || input.Length < length) {
            throw new System.ArgumentException();
        }

        for (int i = 0; i < length; ++i) {
            output[i] = input[i] / (float)short.MaxValue;
        }
    }

    // Pretty print a vector
    public static string PrettyPrint(this Vector3 v) {
        return v.x + "," + v.y + "," + v.z;
    }

    // Returns true if the arrays are the same
    public static bool Compare(this byte[] a1, byte[] a2) {
        if (a2 == null) {
            return false;
        }

        if (a1.Length != a2.Length)
            return false;

        for (int i = 0; i < a1.Length; i++)
            if (a1[i] != a2[i])
                return false;

        return true;
    }

    // < operator for Vector3
    public static bool LessThan(this Vector3 v1, Vector3 v2) {
        float minDelta = 0.0001f;
        if (v1.x-v2.x > minDelta) {
            return true;
        }
        if (v1.y-v2.y > minDelta) {
            return true;
        }
        if (v1.z-v2.z > minDelta) {
            return true;
        }
        return false;
    }

    // Get a postion based on an angle and distance from a given transform
    public static Vector3 GetPositionFromAngle(this Transform aTransform, float aAngle, float aDistance)
    {
        return (aTransform.position + (Quaternion.Euler(0, aAngle, 0) * Vector3.forward) * aDistance);
    }
}
