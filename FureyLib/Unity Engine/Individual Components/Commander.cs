
// Function Commander Script
// by Kyle Furey

using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using TMPro;

/// <summary>
/// Allows communication and events between the game and the user through commands.
/// </summary>
public class Commander : MonoBehaviour
{
    [Header("Allows communication and events between the game and the user through commands.")]

    [Header("COMMANDER SETTINGS")]

    [Header("Whether the commander is active:")]
    [SerializeField] private bool commanderActive = true;

    [Header("Whether to pause the game when the commander is open:")]
    [SerializeField] private bool pauseGame = false;

    [Header("The script sending commands (defaults to this if no script is set):")]
    public static MonoBehaviour commanderScript = null;

    /// <summary>
    /// Whether the commander is currently open
    /// </summary>
    private bool commanderOpen = false;

    [Header("Commander keyboard settings:")]
    [SerializeField] private KeyCode open = KeyCode.Slash;
    [SerializeField] private KeyCode close = KeyCode.Slash;
    [SerializeField] private KeyCode send = KeyCode.Return;

    [Header("The commander's input field and components:")]
    [SerializeField] private TMP_InputField inputField = null;
    [SerializeField] private Image inputFieldImage = null;
    [SerializeField] private GameObject inputFieldTextArea = null;

    /// <summary>
    /// The current command that invokes the corresponding function by name
    /// </summary>
    private string command = "";

    /// <summary>
    /// A list of arguments that can be accessed by any of the command functions
    /// </summary>
    private List<string> arguments = new List<string>();


    // INITIALIZATION AND INPUT

    /// <summary>
    /// Initializes the commander
    /// </summary>
    private void Start()
    {
        // Set the commander object to itself is none is present
        if (commanderScript == null)
        {
            commanderScript = this;
        }

        // Close the commander
        CloseCommander();
    }

    /// <summary>
    /// Checks for input
    /// </summary>
    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            exit();
        }

        // Commander active
        if (commanderActive)
        {
            if (!commanderOpen)
            {
                // Opening commander
                if (Input.GetKeyDown(open))
                {
                    OpenCommander();
                }
            }
            else
            {
                // Closing commander
                if (Input.GetKeyDown(close))
                {
                    CloseCommander();
                }
                // Sending command
                else if (Input.GetKeyDown(send))
                {
                    command = ConvertTextToCommand(inputField.text, out arguments);

                    SendCommand(command, arguments);
                }
            }
        }
        // Commander inactive
        else if (commanderOpen)
        {
            CloseCommander();
        }
    }


    // COMMANDER FUNCTIONS

    /// <summary>
    /// Opening the commander
    /// </summary>
    public void OpenCommander()
    {
        commanderOpen = true;

        inputFieldImage.enabled = true;

        inputFieldTextArea.active = true;

        inputField.ActivateInputField();

        inputField.text = "";

        if (pauseGame)
        {
            Time.timeScale = 0;
        }
    }

    /// <summary>
    /// Closing the commander
    /// </summary>
    public void CloseCommander()
    {
        commanderOpen = false;

        inputFieldImage.enabled = false;

        inputFieldTextArea.active = false;

        inputField.DeactivateInputField();

        inputField.text = "";

        if (pauseGame)
        {
            Time.timeScale = 1;
        }
    }

    /// <summary>
    /// Convert a string to a command and arguments
    /// </summary>
    /// <param name="text"></param>
    /// <param name="arguments"></param>
    /// <returns></returns>
    public static string ConvertTextToCommand(string text, out List<string> arguments)
    {
        arguments = new List<string>();

        while (text.Length > 0)
        {
            string textCopy = text;

            string currentArgument = "";

            for (int i = 0; i < text.Length; i++)
            {
                if (text[i] == ' ')
                {
                    textCopy = text.Remove(i, 1);

                    break;
                }

                currentArgument += text[i];

                textCopy = text.Remove(i, 1);
            }

            currentArgument = currentArgument.Replace(" ", "");

            if (currentArgument != "")
            {
                arguments.Add(currentArgument);
            }

            if (text.Length > currentArgument.Length)
            {
                text = textCopy.Remove(0, currentArgument.Length);
            }
            else
            {
                break;
            }
        }

        string command = "";

        if (arguments.Count > 0)
        {
            command = arguments[0].ToLower();

            arguments.RemoveAt(0);
        }

        return command;
    }

    /// <summary>
    /// Sending a command
    /// </summary>
    /// <param name="command"></param>
    /// <param name="arguments"></param>
    public void SendCommand(string command, List<string> arguments)
    {
        string log = "Command: " + command;

        if (arguments.Count > 0)
        {
            log += " - Arguments:";

            foreach (string argument in arguments)
            {
                log += " " + argument + ",";
            }

            log = log.Remove(log.Length - 1, 1);
        }

        print(log);

        if (commanderScript == null)
        {
            commanderScript = this;
        }

        commanderScript.Invoke(command, 0);

        CloseCommander();
    }

    /// <summary>
    /// Sending a command through text
    /// </summary>
    /// <param name="text"></param>
    public void SendCommand(string text)
    {
        string command = ConvertTextToCommand(text, out List<string> arguments);

        SendCommand(command, arguments);
    }


    // ALL COMMAND FUNCTIONS
    // NOTE: THE NAME OF EACH FUNCTION MUST BE LOWERCASE


    // HELP COMMAND

    /// <summary>
    /// Help command
    /// </summary>
    private void help()
    {
        print("Please enter a command followed by any arguments for that command.");
    }


    // QUIT COMMANDS

    /// <summary>
    /// Quit game
    /// </summary>
    private void quit()
    {
        Application.Quit();
    }

    /// <summary>
    /// Quit game
    /// </summary>
    private void exit()
    {
        Application.Quit();
    }


    // RESTART COMMANDS

    /// <summary>
    /// Restart scene
    /// </summary>
    private void restart()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }

    /// <summary>
    /// Restart scene
    /// </summary>
    private void reload()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }

    /// <summary>
    /// Restart scene
    /// </summary>
    private void reset()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }


    // LOAD COMMAND

    /// <summary>
    /// Load a new scene (argument 0 is scene name)
    /// </summary>
    private void load()
    {
        if (arguments.Count > 0)
        {
            SceneManager.LoadScene(arguments[0]);
        }
        else
        {
            Debug.LogError("Could not load level, no level name argument was given.");
        }
    }


    // PRINT COMMANDS

    /// <summary>
    /// Print arguments
    /// </summary>
    private void print()
    {
        if (arguments.Count == 0)
        {
            Debug.LogWarning("No arguments were given to print!");

            return;
        }

        string log = "";

        foreach (string argument in arguments)
        {
            log += argument + " ";
        }

        print(log);
    }

    /// <summary>
    /// Print arguments
    /// </summary>
    private void log()
    {
        if (arguments.Count == 0)
        {
            Debug.LogWarning("No arguments were given to print!");

            return;
        }

        string log = "";

        foreach (string argument in arguments)
        {
            log += argument + " ";
        }

        print(log);
    }
}
