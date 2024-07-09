
// VR Teleportation Fade Script
// by Kyle Furey

using UnityEngine;
using UnityEngine.UI;

/// <summary>
/// The fading of the screen when the player triggers a successful teleport.
/// </summary>
public class TeleportFadeVR : MonoBehaviour
{
    [Header("The fading of the screen when the player triggers a successful teleport.")]

    [Header("\nFADING IN / OUT")]

    [Header("The image we are fading in and out:")]
    [SerializeField] private Image fadeImage = null;

    [Header("The speed to fade in and out (scaled with delta time):")]
    [SerializeField] private float fadeSpeed = 300;

    /// <summary>
    /// Whether the screen is currently fading in or out
    /// </summary>
    private FadingState isFading = FadingState.NotFading;

    /// <summary>
    /// Fading state enum
    /// </summary>
    public enum FadingState { NotFading, FadingIn, FadingOut };

    /// <summary>
    /// Hide the image
    /// </summary>
    private void Start()
    {
        // Hide the fading image
        fadeImage.color = new Vector4(fadeImage.color.r, fadeImage.color.g, fadeImage.color.b, 0);
    }

    /// <summary>
    /// Fade the image in and out over time
    /// </summary>
    private void Update()
    {
        // Check if we are fading
        if (isFading != FadingState.NotFading)
        {
            // Fading in
            if (isFading == FadingState.FadingIn)
            {
                fadeImage.color = new Vector4(fadeImage.color.r, fadeImage.color.g, fadeImage.color.b, fadeImage.color.a + (fadeSpeed * Time.deltaTime / 255));

                if (fadeImage.color.a >= 1)
                {
                    isFading = FadingState.FadingOut;
                }
            }
            // Fading out
            else if (isFading == FadingState.FadingOut)
            {
                fadeImage.color = new Vector4(fadeImage.color.r, fadeImage.color.g, fadeImage.color.b, fadeImage.color.a - (fadeSpeed * Time.deltaTime / 255));

                if (fadeImage.color.a <= 0)
                {
                    isFading = FadingState.NotFading;
                }
            }
        }
    }

    /// <summary>
    /// Begin fading in and out the screen (trigger when teleporting)
    /// </summary>
    public void Fade()
    {
        isFading = FadingState.FadingIn;
    }
}
