
// Flow Data Text Visualization Script
// by Kyle Furey for NASA VR Project

// REQUIREMENTS: Flow Particle.cs

using System.Threading.Tasks;
using UnityEngine;
using TMPro;

/// <summary>
/// Configures a screen for flow particle data to be displayed.
/// </summary>
public class FlowMonitor : MonoBehaviour
{
    [Header("Configures a screen for flow particle data to be displayed.")]

    [Header("\nCONFIGURATION")]

    [Header("Text assets:")]
    [SerializeField] private TextMeshProUGUI positionText = null;
    [SerializeField] private TextMeshProUGUI velocityText = null;
    [SerializeField] private TextMeshProUGUI densityText = null;
    [SerializeField] private TextMeshProUGUI directionText = null;
    [SerializeField] private TextMeshProUGUI magneticText = null;

    [Header("The delay in seconds before updating the text:")]
    [SerializeField] private float updateDelay = 0;

    /// <summary>
    /// Automatically updates the text values
    /// </summary>
    private void Start()
    {
        UpdateText();
    }

    /// <summary>
    /// Updates the text assets
    /// </summary>
    public async Task UpdateText()
    {
        if (positionText != null)
        {
            positionText.text = "Position: { " +
            (int)FlowParticle.position.x + ", " +
            (int)FlowParticle.position.y + ", " +
            (int)FlowParticle.position.z + " }";
        }

        if (velocityText != null)
        {
            velocityText.text = "Velocity: { " +
            FlowParticle.velocity.x.ToString("F1") + ", " +
            FlowParticle.velocity.y.ToString("F1") + ", " +
            FlowParticle.velocity.z.ToString("F1") + " }";
        }

        if (densityText != null)
        {
            densityText.text = "Density: { " + FlowParticle.density.magnitude + " }";
        }

        if (directionText != null)
        {
            directionText.text = "Direction: { " +
            FlowParticle.direction.x.ToString("F1") + ", " +
            FlowParticle.direction.y.ToString("F1") + ", " +
            FlowParticle.direction.z.ToString("F1") + " }";
        }

        if (magneticText != null)
        {
            magneticText.text = "Magnetic: { " +
            FlowParticle.magnetic.x.ToString("F1") + ", " +
            FlowParticle.magnetic.y.ToString("F1") + ", " +
            FlowParticle.magnetic.z.ToString("F1") + " }";
        }

        await Task.Delay(updateDelay <= 0 ? 1 : (int)(updateDelay * 1000));

        UpdateText();
    }
}
