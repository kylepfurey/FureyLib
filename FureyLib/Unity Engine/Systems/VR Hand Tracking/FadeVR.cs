
// VR Screen Fading Script
// by Kyle Furey

using UnityEngine;
using UnityEngine.UI;

/// <summary>
/// Used to quickly fade the screen in VR.
/// </summary>
public class FadeVR : MonoBehaviour
{
    [Header("Used to quickly fade the screen in VR")]

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
    /// Begin fading in and out the screen.
    /// </summary>
    public void Fade()
    {
        isFading = FadingState.FadingIn;
    }

    /// <summary>
    /// Attempts to fade the player's screen.
    /// </summary>
    public static bool TryFade()
    {
        FadeVR instance = VRUser.instance.GetComponentInChildren<FadeVR>();

        if (instance != null)
        {
            instance.Fade();

            return true;
        }

        return false;
    }
}
