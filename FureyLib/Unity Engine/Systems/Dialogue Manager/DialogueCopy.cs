
// Dialogue Copying Script
// by Kyle Furey

using UnityEngine;

public class DialogueCopy : MonoBehaviour
{
    [SerializeField] private DialogueReader From;
    private DialogueReader To;

    private void Start()
    {
        To = GetComponent<DialogueReader>();
    }

    private void Update()
    {
        To.dialogueName = From.dialogueName;
        To.dialogueEnd = From.dialogueEnd;
        To.hasSpoken = From.hasSpoken;
        To.FindDialogue();
    }
}
