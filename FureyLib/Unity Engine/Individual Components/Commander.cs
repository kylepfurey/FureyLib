
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

    [Header("\nCOMMANDER SETTINGS")]

    [Header("Whether the commander is active:")]
    [SerializeField] private bool commanderActive = true;

    [Header("Whether to pause the game when the commander is open:")]
    [SerializeField] private bool pauseGame = false;

    /// <summary>
    /// The script currently sending commands
    /// </summary>
    public static MonoBehaviour instance = null;

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
    private static string currentCommand = "";

    /// <summary>
    /// A list of the current arguments that can be accessed by any of the command functions
    /// </summary>
    private static List<string> currentArguments = new List<string>();

    [Header("Test particle prefab:")]
    [SerializeField] private GameObject particlePrefab = null;


    // INITIALIZATION AND INPUT

    /// <summary>
    /// Initializes the commander
    /// </summary>
    private void Start()
    {
        // Set the commander object to itself is none is present
        if (instance == null)
        {
            instance = this;
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
                    SendCommand(inputField.text);
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
    /// Converts text into a command with arguments and sends the command to the commander
    /// </summary>
    /// <param name="text"></param>
    public void SendCommand(string text)
    {
        currentCommand = ConvertTextToCommand(text, out currentArguments);

        SendCommand(currentCommand, currentArguments);
    }

    /// <summary>
    /// Sends a command and its arguments to the commander
    /// </summary>
    /// <param name="command"></param>
    /// <param name="arguments"></param>
    public void SendCommand(string command, List<string> arguments)
    {
        currentCommand = command;

        currentArguments = arguments;

        if (instance == null)
        {
            instance = this;
        }

        instance.Invoke(command, 0);

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

        CloseCommander();
    }

    /// <summary>
    /// Convert a string into a command and arguments
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
        if (currentArguments.Count > 0)
        {
            SceneManager.LoadScene(currentArguments[0]);
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
        if (currentArguments.Count == 0)
        {
            Debug.LogWarning("No arguments were given to print!");

            return;
        }

        string log = "";

        foreach (string argument in currentArguments)
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
        if (currentArguments.Count == 0)
        {
            Debug.LogWarning("No arguments were given to print!");

            return;
        }

        string log = "";

        foreach (string argument in currentArguments)
        {
            log += argument + " ";
        }

        print(log);
    }


    // SUMMON PARTICLE COMMAND

    /// <summary>
    /// Summons a grabbable particle in front of the player
    /// </summary>
    private void particle()
    {
        Instantiate(particlePrefab, transform.position, transform.rotation);
    }

    /// <summary>
    /// Summons a grabbable particle in front of the player
    /// </summary>
    private void summon()
    {
        if (currentArguments.Count == 0)
        {
            Instantiate(particlePrefab, transform.position, transform.rotation);
        }
        else
        {
            switch (currentArguments[0])
            {
                default:

                    break;

                case "particle":

                    Instantiate(particlePrefab, transform.position, transform.rotation);

                    break;
            }
        }
    }
}
