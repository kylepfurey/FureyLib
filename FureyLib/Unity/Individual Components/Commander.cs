
// Function Commander Script
// by Kyle Furey

using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;
using TMPro;
using UnityEngine.SceneManagement;

// Allows communication and events between the game and the user through commands.
public class Commander : MonoBehaviour
{
    [Header("Allows communication and events between the game and the user through commands.")]

    [Header("COMMANDER SETTINGS")]

    [Header("Whether the commander is active:")]
    [SerializeField] private bool commanderActive = true;

    [Header("Whether to pause the game when the commander is open:")]
    [SerializeField] private bool pauseGame = false;

    [Header("The script sending commands (defaults to this if no script is set):")]
    public MonoBehaviour commanderScript = null;

    // Whether the commander is currently open
    private bool commanderOpen = false;

    [Header("Commander keyboard settings:")]
    [SerializeField] private KeyCode open = KeyCode.Slash;
    [SerializeField] private KeyCode close = KeyCode.Escape;
    [SerializeField] private KeyCode send = KeyCode.Return;

    [Header("The commander's input field and components:")]
    [SerializeField] private TMP_InputField inputField = null;
    [SerializeField] private Image inputFieldImage = null;
    [SerializeField] private GameObject inputFieldTextArea = null;

    // The current command that invokes the corresponding function by name
    private string command = "";

    // A list of arguments that can be accessed by any of the command functions
    private List<string> arguments = new List<string>();

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

    private void Update()
    {
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

    // Opening the commander
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

    // Closing the commander
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

    // Convert a string to a command and arguments
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

    // Sending a command
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

    // Sending a command through text
    public void SendCommand(string text)
    {
        string command = ConvertTextToCommand(text, out List<string> arguments);

        SendCommand(command, arguments);
    }


    // ALL COMMAND FUNCTIONS
    // NOTE: THE NAME OF EACH FUNCTION MUST BE LOWERCASE

    // Help command
    private void help()
    {
        print("Please enter a command followed by any arguments for that command.");
    }

    // Quit game
    private void quit()
    {
        Application.Quit();
    }

    private void exit()
    {
        Application.Quit();
    }


    // Restart scene
    private void restart()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }

    // Load a new scene (argument 0 is scene name)
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

    // Print arguments
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
}
