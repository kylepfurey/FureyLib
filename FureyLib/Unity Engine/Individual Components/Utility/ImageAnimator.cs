
// UI Image Animator Script
// by Kyle Furey

using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

/// <summary>
/// Animates an image through a set of textures.
/// </summary>
public class ImageAnimator : MonoBehaviour
{
    [Header("Animates an image through a set of textures.\n")]

    [Header("The image to animate:")]
    [SerializeField] private RawImage image = null;

    [Header("The textures to loop through:")]
    [SerializeField] private List<Texture> textures = new List<Texture>();

    [Header("The speed to iterate through the textures:")]
    [SerializeField] private float speed = 30;

    [Header("Whether to animate the textures:")]
    public bool animate = true;

    /// <summary>
    /// The current index of the textures.
    /// </summary>
    private float index = 0;

    /// <summary>
    /// Initializes the animation.
    /// </summary>
    private void Start()
    {
        image.texture = textures[0];
    }

    /// <summary>
    /// Animates the texture.
    /// </summary>
    private void Update()
    {
        image.texture = textures[((int)index) % textures.Count];

        index += Time.deltaTime * speed;
    }
}
