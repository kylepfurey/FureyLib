using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public static class ExtensionMethods
{

    // Shuffle a list
    public static void Shuffle<T>(this IList<T> aList)
    {
        int n = aList.Count;
        while (n > 1)
        {
            n--;
            int k = UnityEngine.Random.Range(0, n + 1);
            T value = aList[k];
            aList[k] = aList[n];
            aList[n] = value;
        }
    }


    // Get a value out of some JsonData
    public static float GetFloat(this LitJson.JsonData aJsonData, string aValue)
    {
        return (float)(double)aJsonData[aValue];
    }

    // Convert a float[] into a short[]
    public static void ToShortArray(this float[] input, short[] output)
    {
        if (output.Length < input.Length)
        {
            throw new System.ArgumentException("in: " + input.Length + ", out: " + output.Length);
        }

        for (int i = 0; i < input.Length; ++i)
        {
            output[i] = (short)Mathf.Clamp((int)(input[i] * 32767.0f), short.MinValue, short.MaxValue);
        }
    }

    // Convert a short[] into a float[]
    public static void ToFloatArray(this short[] input, float[] output, int length)
    {
        if (output.Length < length || input.Length < length)
        {
            throw new System.ArgumentException();
        }

        for (int i = 0; i < length; ++i)
        {
            output[i] = input[i] / (float)short.MaxValue;
        }
    }

    // Pretty print a vector
    public static string PrettyPrint(this Vector3 v)
    {
        return v.x + "," + v.y + "," + v.z;
    }

    // Find the intersection between these two lists
    public static List<T> Intersect<T>(this List<T> aList, List<T> aSecondList) where T : System.IComparable<T>
    {
        List<T> intersection = new List<T>();
        for (int i = 0; i < aList.Count; i++)
        {
            for (int j = 0; j < aSecondList.Count; j++)
            {
                if (aList[i].CompareTo(aSecondList[j]) == 0)
                {
                    intersection.Add(aList[i]);
                }
            }
        }
        return intersection;
    }

    static bool ByteArrayCompare(byte[] a1, byte[] a2)
    {
        if (a1.Length != a2.Length)
            return false;

        for (int i = 0; i < a1.Length; i++)
            if (a1[i] != a2[i])
                return false;

        return true;
    }
}
