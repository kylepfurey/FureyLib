
// Dialogue Manager Script
// by Kyle Furey

using TMPro;
using UnityEngine.Events;
using UnityEngine.UI;
using UnityEngine;

public class DialogueManager : MonoBehaviour
{
    [System.Serializable]
    public class LineOfDialogue
    {
        [Header("Dialogue Name")]
        // Name of Dialogue
        public string dialogueName = "None";

        [Header("Dialogue Settings")]
        // Line of Dialogue to Display
        public string lineOfDialogue = "";

        // Dialogue Sounds
        public string voiceClip = "";
        public string scrollSound = "Scroll";

        // Possible Dialogue Options
        public DialogueOption[] options;

        // Whether the Dialogue Sequence Ends There
        public bool breakPoint = false;

        [Header("Characters Looking at Other Characters")]
        // Look At Object
        public GameObject[] lookFromObject;
        public GameObject[] lookToObject;
        public float lookAtSpeed = 5;

        [Header("Text Settings")]
        // Speed Text Scrolls on Screen
        public float scrollTime = 0.05f;

        // Text Size on Screen
        public float textSize = 25;

        // Color of Text
        public Color textColor = Color.white;
        public Color boxColor = new Vector4(255, 107, 107, 255) / 255;
        public Color borderColor = Color.white;

        // Font
        public TMP_FontAsset font;

        [Header("Dialogue Unity Event")]
        // Dialogue Related Event
        public UnityEvent textEvent;
        public float eventTime;
    }

    [System.Serializable]
    public class DialogueOption
    {
        [Header("Dialogue Option Settings")]
        // Displayed Option
        public string displayedText;

        // Next Line of Dialogue to Start
        public string dialogueName;

        [Header("Button Settings")]
        // Text Size on Screen
        public float textSize = 40;

        // Color of Button
        public Color buttonColor = new Vector4(255, 107, 107, 255) / 255;
        public Color buttonColorHovered = new Vector4(255, 207, 107, 255) / 255;
        public Color buttonColorForeground = Color.white;

        [Header("Dialogue Unity Event")]
        // Dialogue Related Event
        public UnityEvent optionEvent;
        public float eventTime;
    }

    [System.Serializable]
    public class DialogueSequence
    {
        public string name = "New Dialogue Sequence";
        public LineOfDialogue[] dialogue;
    }

    public GameObject textBox;
    public TextMeshProUGUI text;
    public RawImage border;
    public RawImage box;
    public TMP_FontAsset defaultFont;
    [SerializeField] private Button[] OptionButtons;

    public DialogueSequence[] dialogueSequences;
    [HideInInspector] public LineOfDialogue[] linesOfDialogue;

    private Image[] OptionImages;
    private TextMeshProUGUI[] OptionText;

    [HideInInspector] public int currentDialogue;
    [HideInInspector] public string currentText;
    [HideInInspector] public int currentLetter;
    [HideInInspector] public bool input;
    [HideInInspector] public UnityEvent currentEvent;
    [HideInInspector] public string currentVoiceClip;
    private float scrollTimer;
    private bool playScrollSound;

    private void Start()
    {
        OptionImages = new Image[OptionButtons.Length];
        OptionText = new TextMeshProUGUI[OptionButtons.Length];

        playScrollSound = true;

        for (int i = 0; i < OptionButtons.Length; i++)
        {
            OptionImages[i] = OptionButtons[i].transform.GetChild(0).GetComponent<Image>();
            OptionText[i] = OptionButtons[i].transform.GetChild(1).GetComponent<TextMeshProUGUI>();
        }

        // Cumulate Lines of Dialogue in One Array
        List<LineOfDialogue> list = new List<LineOfDialogue>();

        foreach (DialogueSequence sequence in dialogueSequences)
        {
            foreach (LineOfDialogue dialogue in sequence.dialogue)
            {
                list.Add(dialogue);
            }
        }

        linesOfDialogue = list.ToArray();

        list.Clear();

        // Setting Default Look At Objects
        for (int i = 0; i < linesOfDialogue.Length; i++)
        {
            if (linesOfDialogue[i].lookFromObject.Length > linesOfDialogue[i].lookToObject.Length)
            {
                GameObject[] array = new GameObject[linesOfDialogue[i].lookToObject.Length];

                linesOfDialogue[i].lookToObject.CopyTo(array, 0);

                linesOfDialogue[i].lookToObject = new GameObject[linesOfDialogue[i].lookFromObject.Length];

                int index = 0;
                foreach (GameObject Object in array)
                {
                    linesOfDialogue[i].lookToObject[index] = Object;
                    index++;
                }
            }
        }
    }

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.T))
        {
            playScrollSound = !playScrollSound;
        }

        if (currentDialogue != 0 && (Input.GetKeyDown(KeyCode.E) || Input.GetKeyDown(KeyCode.Mouse0)) && !input)
        {
            input = true;

            if (linesOfDialogue[currentDialogue - 1].lineOfDialogue == currentText)
            {
                if (linesOfDialogue[currentDialogue - 1].breakPoint)
                {
                    textBox.SetActive(false);

                    foreach (Button button in OptionButtons)
                    {
                        button.gameObject.SetActive(false);
                    }

                    currentDialogue = 0;
                    text.text = "";
                    currentText = "";
                    currentLetter = -1;
                    GameManager.Player.active = true;

                    Cursor.lockState = CursorLockMode.Locked;
                }
                else if (linesOfDialogue[currentDialogue - 1].options.Length == 0)
                {
                    currentDialogue++;
                    text.text = "";
                    currentText = "";
                    currentLetter = -1;

                    if (linesOfDialogue[currentDialogue - 1].textEvent != null)
                    {
                        currentEvent = linesOfDialogue[currentDialogue - 1].textEvent;
                        Invoke("InvokeEvent", linesOfDialogue[currentDialogue - 1].eventTime);
                    }

                    GameManager.Audio.Stop(currentVoiceClip);
                    GameManager.Audio.PlayOnce("Next");
                    GameManager.Audio.Play(linesOfDialogue[currentDialogue - 1].voiceClip);
                    currentVoiceClip = linesOfDialogue[currentDialogue - 1].voiceClip;

                    text.fontSize = linesOfDialogue[currentDialogue - 1].textSize;
                    text.color = linesOfDialogue[currentDialogue - 1].textColor;

                    if (linesOfDialogue[currentDialogue - 1].font)
                    {
                        text.font = linesOfDialogue[currentDialogue - 1].font;
                    }
                    else
                    {
                        text.font = defaultFont;
                    }

                    box.color = linesOfDialogue[currentDialogue - 1].boxColor;
                    border.color = linesOfDialogue[currentDialogue - 1].borderColor;

                    UpdateButtonColor(false);
                }
            }
            else
            {
                currentText = linesOfDialogue[currentDialogue - 1].lineOfDialogue;
                text.text = currentText;

                if (linesOfDialogue[currentDialogue - 1].scrollSound == "")
                {
                    linesOfDialogue[currentDialogue - 1].scrollSound = "Scroll";
                }

                if (playScrollSound)
                {
                    GameManager.Audio.PlayOnce(linesOfDialogue[currentDialogue - 1].scrollSound);
                }

                GameManager.Audio.Stop(currentVoiceClip);
            }
        }

        if (currentDialogue != 0)
        {
            textBox.SetActive(true);
            GameManager.Player.active = false;
            GameManager.Player.Rigidbody.velocity = new Vector3(0, GameManager.Player.Rigidbody.velocity.y, 0);

            if (linesOfDialogue[currentDialogue - 1].lineOfDialogue != currentText)
            {
                foreach (Button button in OptionButtons)
                {
                    button.gameObject.SetActive(false);
                }

                if (scrollTimer >= linesOfDialogue[currentDialogue - 1].scrollTime)
                {
                    scrollTimer -= linesOfDialogue[currentDialogue - 1].scrollTime;

                    if (currentLetter >= 0)
                    {
                        currentText += linesOfDialogue[currentDialogue - 1].lineOfDialogue[currentLetter];

                        if (linesOfDialogue[currentDialogue - 1].lineOfDialogue[currentLetter] != ' ' && linesOfDialogue[currentDialogue - 1].lineOfDialogue[currentLetter] != '.')
                        {
                            if (linesOfDialogue[currentDialogue - 1].scrollSound == "")
                            {
                                linesOfDialogue[currentDialogue - 1].scrollSound = "Scroll";
                            }

                            if (playScrollSound)
                            {
                                GameManager.Audio.PlayOnce(linesOfDialogue[currentDialogue - 1].scrollSound);
                            }
                        }
                    }

                    currentLetter++;

                    text.text = currentText;
                }
                else
                {
                    scrollTimer += Time.deltaTime;
                }
            }
            else
            {
                UpdateButtonColor(true);
            }

            for (int i = 0; i < OptionButtons.Length; i++)
            {
                OptionText[i].color = OptionButtons[i].targetGraphic.canvasRenderer.GetColor();
            }

            int index = 0;
            foreach (GameObject Object in linesOfDialogue[currentDialogue - 1].lookFromObject)
            {
                Vector3 rotation = Object.transform.eulerAngles;
                Object.transform.eulerAngles = new Vector3(0, Object.transform.eulerAngles.y, 0);

                if (linesOfDialogue[currentDialogue - 1].lookToObject[index])
                {
                    Object.transform.LookAt(linesOfDialogue[currentDialogue - 1].lookToObject[index].transform.position);
                }
                else
                {
                    Object.transform.LookAt(GameManager.Player.transform.position);
                }

                Object.transform.eulerAngles = new Vector3(0, Object.transform.eulerAngles.y, 0);
                Quaternion lookAtRotation = Object.transform.rotation;
                Object.transform.eulerAngles = rotation;

                Object.transform.rotation = Quaternion.Lerp(Object.transform.rotation, lookAtRotation, linesOfDialogue[currentDialogue - 1].lookAtSpeed * Time.deltaTime);
                Object.transform.eulerAngles = new Vector3(rotation.x, Object.transform.eulerAngles.y, rotation.z);

                index++;
            }
        }
        else if (textBox.activeSelf)
        {
            textBox.SetActive(false);

            foreach (Button button in OptionButtons)
            {
                button.gameObject.SetActive(false);
            }

            currentDialogue = 0;
            text.text = "";
            currentText = "";
            currentLetter = -1;
            GameManager.Player.active = true;

            Cursor.lockState = CursorLockMode.Locked;
        }

        if (!Input.GetKey(KeyCode.E) && !Input.GetKey(KeyCode.Mouse0))
        {
            input = false;
        }
    }

    public void OptionClick(int option)
    {
        int index = 0;
        foreach (LineOfDialogue dialogue in linesOfDialogue)
        {
            if (dialogue.dialogueName.ToLower() == linesOfDialogue[currentDialogue - 1].options[option - 1].dialogueName.ToLower())
            {
                if (linesOfDialogue[currentDialogue - 1].options[option - 1].optionEvent != null)
                {
                    currentEvent = linesOfDialogue[currentDialogue - 1].options[option - 1].optionEvent;
                    Invoke("InvokeEvent", linesOfDialogue[currentDialogue - 1].options[option - 1].eventTime);
                }

                currentDialogue = index + 1;
                break;
            }

            index++;
        }

        if (linesOfDialogue[currentDialogue - 1].textEvent != null)
        {
            currentEvent = linesOfDialogue[currentDialogue - 1].textEvent;
            Invoke("InvokeEvent", linesOfDialogue[currentDialogue - 1].eventTime);
        }

        text.text = "";
        currentText = "";
        currentLetter = -1;

        GameManager.Audio.Stop(currentVoiceClip);
        GameManager.Audio.PlayOnce("Click");
        GameManager.Audio.Play(linesOfDialogue[currentDialogue - 1].voiceClip);
        currentVoiceClip = linesOfDialogue[currentDialogue - 1].voiceClip;

        text.fontSize = linesOfDialogue[currentDialogue - 1].textSize;
        text.color = linesOfDialogue[currentDialogue - 1].textColor;

        if (linesOfDialogue[currentDialogue - 1].font)
        {
            text.font = linesOfDialogue[currentDialogue - 1].font;
        }
        else
        {
            text.font = defaultFont;
        }

        box.color = linesOfDialogue[currentDialogue - 1].boxColor;
        border.color = linesOfDialogue[currentDialogue - 1].borderColor;

        UpdateButtonColor(false);
    }

    public void OptionHover()
    {
        GameManager.Audio.PlayOnce("Hover");
    }

    public void UpdateButtonColor(bool setActive)
    {
        if (linesOfDialogue[currentDialogue - 1].options.Length > 0 && !OptionButtons[0].gameObject.activeSelf)
        {
            for (int i = 0; i < linesOfDialogue[currentDialogue - 1].options.Length; i++)
            {
                if (setActive)
                {
                    OptionButtons[i].gameObject.SetActive(true);
                }

                ColorBlock colors = OptionButtons[i].colors;
                colors.normalColor = linesOfDialogue[currentDialogue - 1].options[i].buttonColor;
                colors.highlightedColor = linesOfDialogue[currentDialogue - 1].options[i].buttonColorHovered;
                colors.pressedColor = linesOfDialogue[currentDialogue - 1].options[i].buttonColorHovered;
                colors.selectedColor = linesOfDialogue[currentDialogue - 1].options[i].buttonColorHovered;
                colors.disabledColor = linesOfDialogue[currentDialogue - 1].options[i].buttonColor;

                OptionButtons[i].colors = colors;

                OptionText[i].text = linesOfDialogue[currentDialogue - 1].options[i].displayedText;
                OptionText[i].fontSize = linesOfDialogue[currentDialogue - 1].options[i].textSize;
                OptionImages[i].color = linesOfDialogue[currentDialogue - 1].options[i].buttonColorForeground;
            }

            if (setActive)
            {
                Cursor.lockState = CursorLockMode.None;
            }
        }
    }

    private void InvokeEvent()
    {
        currentEvent.Invoke();
    }

    public void TestEvent()
    {
        print("Event was successful!");
    }
}
