
// Dialogue Reader Script
// by Kyle Furey

using UnityEngine;

public class DialogueReader : MonoBehaviour
{
    public string dialogueName = "No dialogue set";
    public string dialogueEnd = "No dialogue set";
    private DialogueManager Dialogue;
    private int dialogueIndex;
    private int dialogueIndexEnd;
    private bool interactable;
    [HideInInspector] public bool hasSpoken;
    private bool load;

    private void Start()
    {
        Dialogue = GameManager.Dialogue;
    }

    public void FindDialogue()
    {
        int index = 0;
        foreach (DialogueManager.LineOfDialogue dialogue in Dialogue.linesOfDialogue)
        {
            if (dialogue.dialogueName.ToLower() == dialogueName.ToLower())
            {
                dialogueIndex = index + 1;
            }

            if (dialogue.dialogueName.ToLower() == dialogueEnd.ToLower())
            {
                dialogueIndexEnd = index + 1;
            }

            index++;
        }
    }

    private void Update()
    {
        if (!load)
        {
            load = true;

            FindDialogue();
        }
        else
        {
            if (Dialogue.currentDialogue == 0 && interactable && (Input.GetKeyDown(KeyCode.E) || Input.GetKeyDown(KeyCode.Mouse0)) && !Dialogue.input)
            {
                Dialogue.input = true;

                if (!hasSpoken)
                {
                    Dialogue.currentDialogue = dialogueIndex;
                }
                else
                {
                    Dialogue.currentDialogue = dialogueIndexEnd;
                }

                Dialogue.text.text = "";
                Dialogue.currentText = "";
                Dialogue.currentLetter = -1;

                if (Dialogue.linesOfDialogue[Dialogue.currentDialogue - 1].textEvent != null)
                {
                    Dialogue.currentEvent = Dialogue.linesOfDialogue[Dialogue.currentDialogue - 1].textEvent;
                    Dialogue.Invoke("InvokeEvent", Dialogue.linesOfDialogue[Dialogue.currentDialogue - 1].eventTime);
                }

                GameManager.Audio.Stop(Dialogue.currentVoiceClip);
                GameManager.Audio.Play(Dialogue.linesOfDialogue[Dialogue.currentDialogue - 1].voiceClip);
                Dialogue.currentVoiceClip = Dialogue.linesOfDialogue[Dialogue.currentDialogue - 1].voiceClip;

                Dialogue.text.fontSize = Dialogue.linesOfDialogue[Dialogue.currentDialogue - 1].textSize;
                Dialogue.text.color = Dialogue.linesOfDialogue[Dialogue.currentDialogue - 1].textColor;

                if (Dialogue.linesOfDialogue[Dialogue.currentDialogue - 1].font)
                {
                    Dialogue.text.font = Dialogue.linesOfDialogue[Dialogue.currentDialogue - 1].font;
                }
                else
                {
                    Dialogue.text.font = Dialogue.defaultFont;
                }

                Dialogue.box.color = Dialogue.linesOfDialogue[Dialogue.currentDialogue - 1].boxColor;
                Dialogue.border.color = Dialogue.linesOfDialogue[Dialogue.currentDialogue - 1].borderColor;

                Dialogue.UpdateButtonColor(false);

                hasSpoken = true;

                Cursor.lockState = CursorLockMode.None;
            }
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Player")
        {
            interactable = true;
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.tag == "Player")
        {
            interactable = false;
        }
    }

    public void SetLastDialogue()
    {
        // Call to set what is last said as the last line of dialogue.
        dialogueEnd = Dialogue.linesOfDialogue[Dialogue.currentDialogue].dialogueName;
    }
}
