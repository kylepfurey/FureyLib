
// Networked Chat Box Script
// by Kyle Furey

using System.Collections.Generic;
using System.Threading.Tasks;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.Events;

/// <summary>
/// A component used to send and display networked chat messages.
/// </summary>
public class NetChatBox : MonoBehaviour
{
    [Header("A component used to send and display networked chat messages.\n")]

    [Header("OUTGOING MESSAGES")]

    [Header("The text box that displays and edits the current outgoing message:")]
    [SerializeField] private InputField outgoingText = null;

    [Header("The button that sends an outgoing chat:")]
    [SerializeField] private Button sendButton = null;

    [Header("Events to call when a message is sent:\nNote: This is automatically bound to the send chat button.")]
    public UnityEvent<string> onSendChat = null;

    [Header("INCOMING MESSAGES")]

    [Header("The text box(s) that displays current received messages:")]
    [SerializeField] private List<Text> incomingText = new List<Text>();

    [Header("The time in seconds before clearing a message:")]
    [SerializeField] private float clearTime = 5;

    [Header("MESSAGE SETTINGS")]

    [Header("The maximum number of displayed messages:")]
    [SerializeField] private int maxMessages = 9;

    [Header("The maximum number of characters in a message:")]
    [SerializeField] private int characterLimit = 40;

    /// <summary>
    /// Each received message in order.
    /// </summary>
    private Queue<string> messages = new Queue<string>();


    // UNITY FUNCTIONS

    /// <summary>
    /// Binds the chat button to sending an outgoing message.
    /// </summary>
    private void Start()
    {
        sendButton.onClick.AddListener(() =>
        {
            SendMessage(outgoingText.text);

            outgoingText.text = "";
        });

        outgoingText.text = "";

        foreach (Text textBox in incomingText)
        {
            textBox.text = "";
        }
    }

    /// <summary>
    /// Sends messages when the outgoing chat box is highlighted.
    /// </summary>
    private async void Update()
    {
        if (outgoingText.text != "" && Input.GetKeyDown(KeyCode.Return))
        {
            SendMessage(outgoingText.text);

            outgoingText.text = "";

            outgoingText.interactable = false;

            await Task.Delay(1);

            outgoingText.interactable = true;
        }
        else if (Input.GetKeyDown(KeyCode.Slash))
        {
            outgoingText.ActivateInputField();
        }
    }


    // MESSAGES

    /// <summary>
    /// Sends the given message from the chat box.
    /// </summary>
    /// <param name="outgoingMessage"></param>
    public void SendMessage(string outgoingMessage)
    {
        if (outgoingMessage != "" && outgoingMessage.Replace(" ", "") != "" && outgoingMessage.Replace("\n", "") != "" && outgoingMessage.Replace("\t", "") != "")
        {
            onSendChat.Invoke(outgoingMessage);
        }
    }

    /// <summary>
    /// Adds the given message to the chat.<br/>
    /// Call this function when receiving an incoming message.
    /// </summary>
    public async void ReceiveMessage(string incomingMessage)
    {
        if (incomingMessage != "" && incomingMessage.Replace(" ", "") != "" && incomingMessage.Replace("\n", "") != "" && incomingMessage.Replace("\t", "") != "")
        {
            incomingMessage = incomingMessage.Replace("\n", " ");

            incomingMessage = incomingMessage.Replace("\t", " ");

            if (incomingMessage.Length > characterLimit)
            {
                incomingMessage = incomingMessage.Remove(characterLimit, incomingMessage.Length - characterLimit);
            }

            incomingMessage += "\n";

            messages.Enqueue(incomingMessage);

            foreach (Text textBox in incomingText)
            {
                textBox.text += incomingMessage;
            }

            if (messages.Count > maxMessages)
            {
                string removedMessage = messages.Dequeue();

                foreach (Text textBox in incomingText)
                {
                    textBox.text = textBox.text.Remove(0, removedMessage.Length >= textBox.text.Length ? textBox.text.Length : removedMessage.Length);
                }
            }

            await Task.Delay((int)(clearTime * 1000));

            if (messages.Count > 0 && messages.Peek() == incomingMessage)
            {
                string removedMessage = messages.Dequeue();

                foreach (Text textBox in incomingText)
                {
                    textBox.text = textBox.text.Remove(0, removedMessage.Length >= textBox.text.Length ? textBox.text.Length : removedMessage.Length);
                }
            }
        }
    }

    /// <summary>
    /// Returns the current messages in the chat in order.
    /// </summary>
    /// <returns></returns>
    public Queue<string> GetMessages()
    {
        return new Queue<string>(messages);
    }

    /// <summary>
    /// Returns the current number of messages in the chat.
    /// </summary>
    /// <returns></returns>
    public int NumberOfMessages()
    {
        return messages.Count;
    }

    /// <summary>
    /// Returns the most recent message in the chat, if any.
    /// </summary>
    /// <returns></returns>
    public string NewestMessage()
    {
        return messages.Count > 0 ? messages.Peek() : "";
    }

    /// <summary>
    /// Returns the oldest message in the chat, if any.
    /// </summary>
    /// <returns></returns>
    public string OldestMessage()
    {
        return messages.Count > 0 ? messages.ToArray()[messages.Count - 1] : "";
    }


    // ENABLE / DISABLE

    /// <summary>
    /// Enables or disables the chat box.
    /// </summary>
    /// <param name="enabled"></param>
    public void Enable(bool enabled = true)
    {
        outgoingText.gameObject.SetActive(enabled);

        sendButton.gameObject.SetActive(enabled);

        foreach (Text textBox in incomingText)
        {
            textBox.gameObject.SetActive(enabled);
        }
    }

    /// <summary>
    /// Disables the chat box
    /// </summary>
    public void Disable()
    {
        Enable(false);
    }

    /// <summary>
    /// Returns whether the chat box is fully enabled.
    /// </summary>
    /// <returns></returns>
    public bool IsEnabled()
    {
        bool success = true;

        foreach (Text textBox in incomingText)
        {
            if (!textBox.gameObject.activeSelf)
            {
                success = false;

                break;
            }
        }

        return success && outgoingText.gameObject.activeSelf && sendButton.gameObject.activeSelf;
    }
}
