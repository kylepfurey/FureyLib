
// Debugging Output Script
// by Kyle Furey

// SOURCE: https://docs.unity3d.com/ScriptReference/Debug.html

using System;
using System.IO;
using UnityEngine;
using TMPro;

// Include this heading to use the component's functions
using static Debug;

/// <summary>
/// A simple component that overrides the Debug functions to write text to a log file both in or out of builds.
/// </summary>
public class Debug : MonoBehaviour
{
    [Header("A simple component that overrides the Debug functions to write text to a log file both in or out of builds.")]

    [Header("\nTEXT LOG")]

    [Header("The text used to display the current text log:")]
    public TextMeshProUGUI UIText = null;
    public TextMeshPro worldText = null;

    [Header("The colors of different types of text logs:")]
    public bool colorizeMessages = true;
    public Color logColor = Color.white;
    public Color warningColor = Color.yellow;
    public Color errorColor = Color.red;

    [Header("Which type of logs to ignore in the text log:")]
    public bool ignoreLogs = false;
    public bool ignoreWarnings = false;
    public bool ignoreErrors = false;

    [Header("The delay before clearing the current text log:")]
    public bool clearLog = true;
    public float clearDelay = 3;

    [Header("\nOUTPUT FILE")]

    [Header("The name and path to generate a file of the given output:")]
    public string outputFileName = "output.txt";
    public string outputPath = "C:\\Users\\";

    /// <summary>
    /// The current instance of the console.
    /// </summary>
    public static Debug instance = null;

    /// <summary>
    /// The timer used to clear the log.
    /// </summary>
    private static float timer = 0;

    /// <summary>
    /// Returns true when called in any kind of built Player, or when called in the Editor in Play mode (Read Only).
    /// </summary>
    public static bool isPlaying { get => Application.isPlaying; }

    /// <summary>
    /// The current output of all the print logs.
    /// </summary>
    public static string output { get; private set; }


    // UNITY FUNCTIONS

    /// <summary>
    /// Marks the current instance of the console.
    /// </summary>
    private void Awake()
    {
        if (instance == null)
        {
            instance = this;

            Log("OUTPUT - " + Application.productName + " - " + DateTime.Now.ToString() + "\n");

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
        SaveLog();
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


    // PROPERTIES

    /// <summary>
    /// Allows you to enable or disable the developer console.
    /// </summary>
    public static bool developerConsoleEnabled { get => UnityEngine.Debug.developerConsoleEnabled; set => UnityEngine.Debug.developerConsoleEnabled = value; }

    /// <summary>
    /// Controls whether the development console is visible.
    /// </summary>
    public static bool developerConsoleVisible { get => UnityEngine.Debug.developerConsoleVisible; set => UnityEngine.Debug.developerConsoleVisible = value; }

    /// <summary>
    /// In the Build Settings dialog there is a check box called "Development Build".
    /// </summary>
    public static bool isDebugBuild { get => UnityEngine.Debug.isDebugBuild; }

    /// <summary>
    /// Get default debug logger.
    /// </summary>
    public static ILogger unityLogger { get => UnityEngine.Debug.unityLogger; }


    // ASSERT FUNCTIONS

    /// <summary>
    /// Assert a condition and logs an error message to the Unity console on failure.
    /// </summary>
    public static void Assert(bool condition, UnityEngine.Object context = null)
    {
        if (instance != null)
        {
            string log = context == null ? "ASSERTION" : "ASSERTION - " + context.name;

            output += log + "\n";

            if (!instance.ignoreErrors)
            {
                if (instance.UIText != null)
                {
                    instance.UIText.text = log;

                    if (instance.colorizeMessages)
                    {
                        instance.UIText.color = instance.errorColor;
                    }
                }

                if (instance.worldText != null)
                {
                    instance.worldText.text = log;

                    if (instance.colorizeMessages)
                    {
                        instance.worldText.color = instance.errorColor;
                    }
                }

                timer = 0;
            }
        }

        UnityEngine.Debug.Assert(condition, context);
    }

    /// <summary>
    /// Assert a condition and logs an error message to the Unity console on failure.
    /// </summary>
    public static void Assert(bool condition, object message, UnityEngine.Object context = null)
    {
        if (instance != null)
        {
            string log = context == null ? "ASSERTION - " + message.ToString() : "ASSERTION - " + context.name + " - " + message.ToString();

            output += log + "\n";

            if (!instance.ignoreErrors)
            {
                if (instance.UIText != null)
                {
                    instance.UIText.text = log;

                    if (instance.colorizeMessages)
                    {
                        instance.UIText.color = instance.errorColor;
                    }
                }

                if (instance.worldText != null)
                {
                    instance.worldText.text = log;

                    if (instance.colorizeMessages)
                    {
                        instance.worldText.color = instance.errorColor;
                    }
                }

                timer = 0;
            }
        }

        UnityEngine.Debug.Assert(condition, message, context);
    }


    // BREAK FUNCTION

    /// <summary>
    /// Pauses the editor.
    /// </summary>
    public static void Break()
    {
        UnityEngine.Debug.Break();
    }


    // CLEAR FUNCTIONS

    /// <summary>
    /// Clears errors from the developer console.
    /// </summary>
    public static void Clear()
    {
        if (instance != null)
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

        UnityEngine.Debug.ClearDeveloperConsole();
    }

    /// <summary>
    /// Clears errors from the developer console.
    /// </summary>
    public static void ClearDeveloperConsole()
    {
        if (instance != null)
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

        UnityEngine.Debug.ClearDeveloperConsole();
    }


    // DRAW FUNCTIONS

    /// <summary>
    /// Draws a line between specified start and end points.
    /// </summary>
    public static void DrawLine(Vector3 start, Vector3 end)
    {
        UnityEngine.Debug.DrawLine(start, end);
    }

    /// <summary>
    /// Draws a line between specified start and end points.
    /// </summary>
    public static void DrawLine(Vector3 start, Vector3 end, Color color, float duration = 0.0f, bool depthTest = true)
    {
        UnityEngine.Debug.DrawLine(start, end, color, duration, depthTest);
    }

    /// <summary>
    /// Draws a line from start to start + dir in world coordinates.
    /// </summary>
    public static void DrawRay(Vector3 start, Vector3 dir)
    {
        UnityEngine.Debug.DrawRay(start, dir);
    }

    /// <summary>
    /// Draws a line from start to start + dir in world coordinates.
    /// </summary>
    public static void DrawRay(Vector3 start, Vector3 dir, Color color, float duration = 0.0f, bool depthTest = true)
    {
        UnityEngine.Debug.DrawRay(start, dir, color, duration, depthTest);
    }


    // LOG FUNCTIONS

    /// <summary>
    /// Logs a message to the Unity Console.
    /// </summary>
    public static void print(object log, UnityEngine.Object context = null)
    {
        if (instance != null)
        {
            string message = context == null ? log.ToString() : context.name + " - " + log.ToString();

            output += message + "\n";

            if (!instance.ignoreLogs)
            {
                if (instance.UIText != null)
                {
                    instance.UIText.text = message;

                    if (instance.colorizeMessages)
                    {
                        instance.UIText.color = instance.logColor;
                    }
                }

                if (instance.worldText != null)
                {
                    instance.worldText.text = message;

                    if (instance.colorizeMessages)
                    {
                        instance.worldText.color = instance.logColor;
                    }
                }

                timer = 0;
            }
        }

        UnityEngine.Debug.Log(log, context);
    }

    /// <summary>
    /// Logs a message to the Unity Console.
    /// </summary>
    public static void Log(object log, UnityEngine.Object context = null)
    {
        if (instance != null)
        {
            string message = context == null ? log.ToString() : context.name + " - " + log.ToString();

            output += message + "\n";

            if (!instance.ignoreLogs)
            {
                if (instance.UIText != null)
                {
                    instance.UIText.text = message;

                    if (instance.colorizeMessages)
                    {
                        instance.UIText.color = instance.logColor;
                    }
                }

                if (instance.worldText != null)
                {
                    instance.worldText.text = message;

                    if (instance.colorizeMessages)
                    {
                        instance.worldText.color = instance.logColor;
                    }
                }

                timer = 0;
            }
        }

        UnityEngine.Debug.Log(log, context);
    }

    /// <summary>
    /// A variant of Debug.Log() that logs a warning message to the console.
    /// </summary>
    public static void LogWarning(object log, UnityEngine.Object context = null)
    {
        if (instance != null)
        {
            string message = context == null ? "WARNING - " + log.ToString() : "WARNING - " + context.name + " - " + log.ToString();

            output += message + "\n";

            if (!instance.ignoreWarnings)
            {
                if (instance.UIText != null)
                {
                    instance.UIText.text = message;

                    if (instance.colorizeMessages)
                    {
                        instance.UIText.color = instance.warningColor;
                    }
                }

                if (instance.worldText != null)
                {
                    instance.worldText.text = message;

                    if (instance.colorizeMessages)
                    {
                        instance.worldText.color = instance.warningColor;
                    }
                }

                timer = 0;
            }
        }

        UnityEngine.Debug.LogWarning(log, context);
    }

    /// <summary>
    /// A variant of Debug.Log() that logs an error message to the console.
    /// </summary>
    public static void LogError(object log, UnityEngine.Object context = null)
    {
        if (instance != null)
        {
            string message = context == null ? "ERROR - " + log.ToString() : "ERROR - " + context.name + " - " + log.ToString();

            output += message + "\n";

            if (!instance.ignoreErrors)
            {
                if (instance.UIText != null)
                {
                    instance.UIText.text = message;

                    if (instance.colorizeMessages)
                    {
                        instance.UIText.color = instance.errorColor;
                    }
                }

                if (instance.worldText != null)
                {
                    instance.worldText.text = message;

                    if (instance.colorizeMessages)
                    {
                        instance.worldText.color = instance.errorColor;
                    }
                }

                timer = 0;
            }
        }

        UnityEngine.Debug.LogError(log, context);
    }

    /// <summary>
    /// A variant of Debug.Log() that logs an error message from an exception to the console.
    /// </summary>
    public static void LogException(Exception exception, UnityEngine.Object context = null)
    {
        if (instance != null)
        {
            string message = context == null ? "EXCEPTION - " + exception.Message : "EXCEPTION - " + context.name + " - " + exception.Message;

            output += message + "\n";

            if (!instance.ignoreErrors)
            {
                if (instance.UIText != null)
                {
                    instance.UIText.text = message;

                    if (instance.colorizeMessages)
                    {
                        instance.UIText.color = instance.errorColor;
                    }
                }

                if (instance.worldText != null)
                {
                    instance.worldText.text = message;

                    if (instance.colorizeMessages)
                    {
                        instance.worldText.color = instance.errorColor;
                    }
                }

                timer = 0;
            }
        }

        UnityEngine.Debug.LogException(exception, context);
    }


    // SAVE FUNCTION

    /// <summary>
    /// Writes the output to a text file at the given output path.
    /// </summary>
    public static void SaveLog()
    {
        if (instance != null)
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
}
