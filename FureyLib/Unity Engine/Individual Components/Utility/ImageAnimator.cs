// .cs
// 2D Image Animator Component
// by Kyle Furey

using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using UnityEngine;
using UnityEngine.UI;

/// <summary>
/// Plays a sequence of images over time to make an image animate.
/// </summary>
[RequireComponent(typeof(Image))]
public sealed class ImageAnimator : MonoBehaviour
{
    [Header("Plays a sequence of images over time to make an image animate.\n")]

    [Header("The managed image used to create animations:")]
    public Image image = null;

    [Header("The animation to start playing on start:")]
    [SerializeField] private string startAnim = "Idle";

    [Header("The number of animation frames to play per second:")]
    [SerializeField] private float frameRate = 30;

    [Header("Each animation by name:")]
    [SerializeField] private List<ImageAnimation> animations = new List<ImageAnimation>();


    // FIELDS

    /// <summary>
    /// The current index of the current animation.
    /// </summary>
    private int animIndex = 0;

    /// <summary>
    /// The current animation being played.
    /// </summary>
    private ImageAnimation currentAnim = null;

    /// <summary>
    /// The number of times the animation has changed.
    /// </summary>
    private int animCount = 0;


    // PROPERTIES

    /// <summary>
    /// Returns the name of the current animation or sets the current animation by name.<br/>
    /// This property does not overwrite the same playing animation.
    /// </summary>
    public string Animation
    {
        get
        {
            return currentAnim.name;
        }

        set
        {
            if (value.ToLower() != currentAnim.name.ToLower())
            {
                SetAnimation(value);
            }
        }
    }


    // UNITY EVENTS

    /// <summary>
    /// Awake() is called before Start().
    /// </summary>
    private void Awake()
    {
        if (image == null)
        {
            image = GetComponent<Image>();

            if (image == null)
            {
                Debug.LogError("ERROR: No image was found for the ImageAnimator on \"" + gameObject.name + "\"!");

                Destroy(this);
            }
        }
    }

    /// <summary>
    /// Start() is called before the first frame update.
    /// </summary>
    private void Start()
    {
        SetAnimation(startAnim);
    }


    // METHODS

    /// <summary>
    /// Animates the image over time using async.
    /// </summary>
    private async void Animate()
    {
        int animIndex = animCount;

        while (true)
        {
            await Task.Delay((int)(1000 * (1 / frameRate)));

            if (this == null || animIndex != animCount)
            {
                return;
            }

            ++this.animIndex;

            this.animIndex %= currentAnim.frames.Count;

            image.sprite = currentAnim.frames[this.animIndex];
        }
    }

    /// <summary>
    /// Sets the current animation to the given animation by name.
    /// </summary>
    public void SetAnimation(string animName, int frame = 0)
    {
        animName = animName.ToLower();

        animIndex = 0;

        currentAnim = null;

        foreach (var anim in animations)
        {
            if (animName == anim.name.ToLower())
            {
                currentAnim = anim;

                break;
            }
        }

        if (currentAnim != null)
        {
            image.sprite = currentAnim.frames[frame % currentAnim.frames.Count];

            ++animCount;

            Animate();
        }
        else
        {
            Debug.LogError("ERROR: Animation \"" + animName + "\" was not found in the PlayerAnimaton component attached to " + gameObject.name + "!");

            Destroy(this);
        }
    }
}

/// <summary>
/// A series of sprites used to create an animation on an image.
/// </summary>
[Serializable]
public sealed class ImageAnimation
{
    [Header("A series of sprites used to create an animation on an image.\n")]

    [Header("The name of this animation:")]
    public string name = "New Animation";

    [Header("Each sprite frame in this animation:")]
    public List<Sprite> frames = new List<Sprite>();
}
