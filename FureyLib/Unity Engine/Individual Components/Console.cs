
// Console Output Debugging Script
// by Kyle Furey

using System;
using System.IO;
using UnityEngine;
using TMPro;

// Include this heading to use the component's functions
using static Console;

/// <summary>
/// A simple component that provides functions to write text to a log in or out of builds.
/// </summary>
public class Console : MonoBehaviour
{
    [Header("A simple component that provides functions to write text to a log in or out of builds.")]

    [Header("\nCONFIGURATION")]

    [Header("The text used to display the current log:")]
    public TextMeshProUGUI UIText = null;
    public TextMeshPro worldText = null;

    [Header("The delay before clearing the current log:")]
    public bool clearLog = true;
    public float clearDelay = 3;

    [Header("The name and path to generate a file of the given output:")]
    public string outputFileName = "output.txt";
    public string outputPath = "C:\\Users\\";

    /// <summary>
    /// The current output of all the print logs.
    /// </summary>
    public static string output { get; private set; }

    /// <summary>
    /// The current instance of the console.
    /// </summary>
    public static Console instance = null;

    /// <summary>
    /// The timer used to clear the log.
    /// </summary>
    private static float timer = 0;


    // UNITY FUNCTIONS

    /// <summary>
    /// Marks the current instance of the console.
    /// </summary>
    private void Awake()
    {
        if (instance == null)
        {
            instance = this;

            print("OUTPUT - " + Application.productName + " - " + DateTime.Now.ToString() + "\n");

            if (instance.UIText != null)
            {
                instance.UIText.text = "";
            }

            if (instance.worldText != null)
            {
                instance.worldText.text = "";
            }
        }
        else
        {
            Destroy(instance);

            instance = this;
        }
    }

    /// <summary>
    /// Saves the current output.
    /// </summary>
    private void OnDestroy()
    {
        Save();
    }

    /// <summary>
    /// Clears the log after a certain time.
    /// </summary>
    private void Update()
    {
        if (clearLog)
        {
            if (timer >= clearDelay)
            {
                if (instance.UIText != null)
                {
                    instance.UIText.text = "";
                }

                if (instance.worldText != null)
                {
                    instance.worldText.text = "";
                }
            }

            timer += Time.deltaTime;
        }
    }


    // PRINT FUNCTIONS

    /// <summary>
    /// Writes to the console with a new line.
    /// </summary>
    public static void print(string log)
    {
        output += log + "\n";

        if (instance.UIText != null)
        {
            instance.UIText.text = log;
        }

        if (instance.worldText != null)
        {
            instance.worldText.text = log;
        }

        timer = 0;
    }

    /// <summary>
    /// Writes to the console with a new line.
    /// </summary>
    public static void WriteLine(string log)
    {
        output += log + "\n";

        if (instance.UIText != null)
        {
            instance.UIText.text = log;
        }

        if (instance.worldText != null)
        {
            instance.worldText.text = log;
        }

        timer = 0;
    }

    /// <summary>
    /// Writes to the console.
    /// </summary>
    public static void Write(string log)
    {
        output += log;

        if (instance.UIText != null)
        {
            instance.UIText.text += log;
        }

        if (instance.worldText != null)
        {
            instance.worldText.text += log;
        }

        timer = 0;
    }


    // CLEAR FUNCTION

    /// <summary>
    /// Clears the current output.
    /// </summary>
    public static void Clear()
    {
        output = "";

        print("OUTPUT - " + Application.productName + " - " + DateTime.Now.ToString() + "\n");

        if (instance.UIText != null)
        {
            instance.UIText.text = "";
        }

        if (instance.worldText != null)
        {
            instance.worldText.text = "";
        }
    }


    // SAVE FUNCTION

    /// <summary>
    /// Writes the output to a text file at the given output path.
    /// </summary>
    public static void Save()
    {
        if (!Directory.Exists(instance.outputPath))
        {
            return;
        }
        else
        {
            if (instance.outputPath[instance.outputPath.Length - 1] != '\\')
            {
                instance.outputPath += '\\';
            }

            if (!instance.outputFileName.Contains('.'))
            {
                instance.outputFileName += ".txt";
            }

            instance.outputPath += instance.outputFileName;

            FileStream file = File.Create(instance.outputPath);

            foreach (char letter in output.ToCharArray())
            {
                file.WriteByte((byte)letter);
            }

            file.Close();
        }
    }
}
