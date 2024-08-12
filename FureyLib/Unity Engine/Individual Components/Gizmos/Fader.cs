
// Image Fader Script
// by Kyle Furey

using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.UI;

// Allows easy fading in or out of an image or images.
public class Fader : MonoBehaviour
{
    [Header("Allows easy fading in or out of an image or images.")]

    [Header("The images to fade in or out:")]
    public List<Graphic> images = new List<Graphic>();

    [Header("Whether fading has started:")]
    public bool start = false;

    [Header("The speed of the fade:")]
    public float speed = 1;

    [Header("Whether to use lerping to fade the images:")]
    public bool lerp = false;
    public float lerpForgiveness = 0.1f;

    [Header("What alpha values indicate the images have fully faded in and out:")]
    public float outAlpha = 0;
    public float inAlpha = 1;

    // The current alpha value
    private float currentAlpha = 0;

    [Header("What direction to fade the images in:")]
    public FadeDirection direction = FadeDirection.Default;

    // The current direction being faded
    private bool fadingIn = true;

    [Header("Whether to loop the fading:")]
    public bool loop = false;

    [Header("Whether to set the images' alphas to a given value on start:")]
    public bool setAlphaOnStart = true;
    public float startingAlpha = 0;

    [Header("Fading events:")]
    public UnityEvent startEvents = null;
    public UnityEvent fadingEvents = null;
    public UnityEvent stopEvents = null;
    public UnityEvent endEvents = null;
    public bool callStopEventsOnNewDirection = true;

    [Header("Debugging:")]
    [SerializeField] private bool testFade = false;

    // Fade direction enum
    public enum FadeDirection { Default, In, Out, InOut, OutIn };


    // UNITY FUNCTIONS

    private void Start()
    {
        if (setAlphaOnStart)
        {
            SetAlpha(startingAlpha);
        }

        if (start)
        {
            Fade();
        }
    }

    private void Update()
    {
        Fading();
    }

    private void OnValidate()
    {
        if (testFade)
        {
            testFade = false;

            if (!start)
            {
                Fade();
            }
            else
            {
                StopFade();
            }
        }
    }


    // FADE CONTROL

    // Fades the images
    public void Fade()
    {
        switch (direction)
        {
            case FadeDirection.Default:

                if (fadingIn)
                {
                    if (currentAlpha >= inAlpha)
                    {
                        RestartFade();
                    }
                    else
                    {
                        ResumeFade();
                    }
                }
                else
                {
                    if (currentAlpha <= outAlpha)
                    {
                        RestartFade();
                    }
                    else
                    {
                        ResumeFade();
                    }
                }

                break;

            case FadeDirection.In:

                if (currentAlpha >= inAlpha)
                {
                    RestartFade();
                }
                else
                {
                    ResumeFade();
                }

                break;

            case FadeDirection.Out:

                if (currentAlpha <= outAlpha)
                {
                    RestartFade();
                }
                else
                {
                    ResumeFade();
                }

                break;

            case FadeDirection.InOut:

                if (fadingIn)
                {
                    ResumeFade();
                }
                else
                {
                    if (currentAlpha <= outAlpha)
                    {
                        RestartFade();
                    }
                    else
                    {
                        ResumeFade();
                    }
                }

                break;

            case FadeDirection.OutIn:

                if (!fadingIn)
                {
                    ResumeFade();
                }
                else
                {
                    if (currentAlpha >= inAlpha)
                    {
                        RestartFade();
                    }
                    else
                    {
                        ResumeFade();
                    }
                }

                break;
        }
    }

    // Starts a new fade
    public void RestartFade()
    {
        start = true;

        switch (direction)
        {
            case FadeDirection.Default:

                if (currentAlpha <= outAlpha)
                {
                    start = true;

                    fadingIn = true;

                    SetAlpha(outAlpha);

                    currentAlpha = outAlpha;

                    startEvents.Invoke();
                }
                else if (currentAlpha >= inAlpha)
                {
                    start = true;

                    fadingIn = false;

                    SetAlpha(inAlpha);

                    currentAlpha = inAlpha;

                    startEvents.Invoke();
                }
                else
                {
                    if (inAlpha > outAlpha)
                    {
                        start = true;

                        fadingIn = true;

                        SetAlpha(outAlpha);

                        currentAlpha = outAlpha;

                        startEvents.Invoke();
                    }
                    else if (inAlpha < outAlpha)
                    {
                        start = true;

                        fadingIn = false;

                        SetAlpha(inAlpha);

                        currentAlpha = inAlpha;

                        startEvents.Invoke();
                    }
                    else
                    {
                        End();
                    }
                }

                break;

            case FadeDirection.In:

                FadeIn();

                break;

            case FadeDirection.Out:

                FadeOut();

                break;

            case FadeDirection.InOut:

                FadeInOut();

                break;

            case FadeDirection.OutIn:

                FadeOutIn();

                break;
        }

        startEvents.Invoke();
    }

    // Fades the images in
    public void FadeIn()
    {
        start = true;

        direction = FadeDirection.In;

        fadingIn = true;

        SetAlpha(outAlpha);

        currentAlpha = outAlpha;

        startEvents.Invoke();
    }

    // Fades the images out
    public void FadeOut()
    {
        start = true;

        direction = FadeDirection.Out;

        fadingIn = false;

        SetAlpha(inAlpha);

        currentAlpha = inAlpha;

        startEvents.Invoke();
    }

    // Fades the images in and then out
    public void FadeInOut()
    {
        start = true;

        direction = FadeDirection.InOut;

        fadingIn = true;

        SetAlpha(outAlpha);

        currentAlpha = outAlpha;

        startEvents.Invoke();
    }

    // Fades the images out and then in
    public void FadeOutIn()
    {
        start = true;

        direction = FadeDirection.OutIn;

        fadingIn = false;

        SetAlpha(inAlpha);

        currentAlpha = inAlpha;

        startEvents.Invoke();
    }

    // Resume the current fade
    public void ResumeFade()
    {
        start = true;

        startEvents.Invoke();

        switch (direction)
        {
            case FadeDirection.In:

                fadingIn = true;

                break;

            case FadeDirection.Out:

                fadingIn = false;

                break;
        }
    }

    // Stops the current fade
    public void StopFade()
    {
        start = false;

        stopEvents.Invoke();
    }


    // DURING FADE

    // Fading the images
    private void Fading()
    {
        if (start)
        {
            fadingEvents.Invoke();

            if (fadingIn)
            {
                if (lerp)
                {
                    currentAlpha = Mathf.Lerp(currentAlpha, inAlpha + lerpForgiveness, Time.deltaTime * speed);
                }
                else
                {
                    currentAlpha += Time.deltaTime * speed;
                }

                SetAlpha(currentAlpha);

                if (currentAlpha >= inAlpha)
                {
                    End();
                }
            }
            else
            {
                if (lerp)
                {
                    currentAlpha = Mathf.Lerp(currentAlpha, outAlpha - lerpForgiveness, Time.deltaTime * speed);
                }
                else
                {
                    currentAlpha -= Time.deltaTime * speed;
                }

                SetAlpha(currentAlpha);

                if (currentAlpha <= outAlpha)
                {
                    End();
                }
            }
        }
    }

    // When a fade reaches its end or changes direction
    private void End()
    {
        switch (direction)
        {
            case FadeDirection.Default:

                endEvents.Invoke();

                if (loop)
                {
                    if (callStopEventsOnNewDirection)
                    {
                        stopEvents.Invoke();
                    }

                    RestartFade();
                }
                else
                {
                    StopFade();
                }

                break;

            case FadeDirection.In:

                endEvents.Invoke();

                if (loop)
                {
                    RestartFade();
                }
                else
                {
                    StopFade();
                }

                break;

            case FadeDirection.Out:

                endEvents.Invoke();

                if (loop)
                {
                    RestartFade();
                }
                else
                {
                    StopFade();
                }

                break;

            case FadeDirection.InOut:

                if (fadingIn)
                {
                    if (callStopEventsOnNewDirection)
                    {
                        stopEvents.Invoke();
                    }

                    fadingIn = false;
                }
                else
                {
                    endEvents.Invoke();

                    if (loop)
                    {
                        RestartFade();
                    }
                    else
                    {
                        StopFade();
                    }
                }

                break;

            case FadeDirection.OutIn:

                if (!fadingIn)
                {
                    if (callStopEventsOnNewDirection)
                    {
                        stopEvents.Invoke();
                    }

                    fadingIn = true;
                }
                else
                {
                    endEvents.Invoke();

                    if (loop)
                    {
                        RestartFade();
                    }
                    else
                    {
                        StopFade();
                    }
                }

                break;
        }
    }


    // ALPHA AND COLOR FUNCTIONS

    // Updates the alpha of an image
    public static Graphic SetAlpha(Graphic image, float newAlpha)
    {
        image.color = new Vector4(image.color.r, image.color.b, image.color.g, Mathf.Clamp(newAlpha, 0, 1));

        return image;
    }

    // Updates the alphas of images
    public static Graphic[] SetAlpha(Graphic[] images, float newAlpha)
    {
        for (int i = 0; i < images.Length; i++)
        {
            SetAlpha(images[i], newAlpha);
        }

        return images;
    }

    // Updates the color of an image
    public static Graphic SetColor(Graphic image, Color newColor)
    {
        image.color = new Vector4(Mathf.Clamp(newColor.r, 0, 1), Mathf.Clamp(newColor.g, 0, 1), Mathf.Clamp(newColor.b, 0, 1), Mathf.Clamp(newColor.a, 0, 1));

        return image;
    }

    // Updates the colors of images
    public static Graphic[] SetColor(Graphic[] images, Color newColor)
    {
        for (int i = 0; i < images.Length; i++)
        {
            SetColor(images[i], newColor);
        }

        return images;
    }

    // Updates the color of an image
    public static Graphic SetColor(Graphic image, Vector4 newColor)
    {
        image.color = new Vector4(Mathf.Clamp(newColor.x, 0, 1), Mathf.Clamp(newColor.y, 0, 1), Mathf.Clamp(newColor.z, 0, 1), Mathf.Clamp(newColor.w, 0, 1));

        return image;
    }

    // Updates the colors of images
    public static Graphic[] SetColor(Graphic[] images, Vector4 newColor)
    {
        for (int i = 0; i < images.Length; i++)
        {
            SetColor(images[i], newColor);
        }

        return images;
    }

    // Updates the color of an image
    public static Graphic SetColor(Graphic image, float newRed, float newBlue, float newGreen, float newAlpha)
    {
        image.color = new Vector4(Mathf.Clamp(newRed, 0, 1), Mathf.Clamp(newBlue, 0, 1), Mathf.Clamp(newGreen, 0, 1), Mathf.Clamp(newAlpha, 0, 1));

        return image;
    }

    // Updates the colors of images
    public static Graphic[] SetColor(Graphic[] images, float newRed, float newBlue, float newGreen, float newAlpha)
    {
        for (int i = 0; i < images.Length; i++)
        {
            SetColor(images[i], newRed, newBlue, newGreen, newAlpha);
        }

        return images;
    }

    // Updates the alphas of this fader's images
    public List<Graphic> SetAlpha(float newAlpha)
    {
        for (int i = 0; i < images.Count; i++)
        {
            SetAlpha(images[i], newAlpha);
        }

        return images;
    }

    // Updates the colors of this fader's images
    public List<Graphic> SetColor(Color newColor)
    {
        for (int i = 0; i < images.Count; i++)
        {
            SetColor(images[i], newColor);
        }

        return images;
    }

    // Updates the colors of this fader's images
    public List<Graphic> SetColor(Vector4 newColor)
    {
        for (int i = 0; i < images.Count; i++)
        {
            SetColor(images[i], newColor);
        }

        return images;
    }

    // Updates the colors of this fader's images
    public List<Graphic> SetColor(float newRed, float newBlue, float newGreen, float newAlpha)
    {
        for (int i = 0; i < images.Count; i++)
        {
            SetColor(images[i], newRed, newBlue, newGreen, newAlpha);
        }

        return images;
    }


    // EXTRA FUNCTIONS

    // Destroy this script
    public void Destroy()
    {
        Destroy(this);
    }

    // Destroy this object
    public void DestroyObject()
    {
        Destroy(gameObject);
    }

    // Flip the fading direction
    public void Flip()
    {
        fadingIn = !fadingIn;
    }
}
