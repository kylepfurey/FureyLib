
// Interactable VR Raygun Object Script
// by Kyle Furey

// REQUIREMENTS: HandTrackerVR.cs, HandGrabbableVR.cs

using System.Collections.Generic;
using System.Threading.Tasks;
using UnityEngine;
using UnityEngine.Events;
using TMPro;

/// <summary>
/// Creates a custom shootable raygun that fires laser beams in VR.
/// </summary>
public class RaygunVR : MonoBehaviour, IHandInteractableVR
{
    [Header("Creates a custom shootable raygun that fires laser beams in VR.")]
    [Header("Also provides an interface called IRaygunShootable that can detect when an object is hit with the raygun.")]

    [Header("\nCONFIGURATION")]

    [Header("Configures the raygun object's grab settings:")]
    [SerializeField] private HandGrabbableVR grabSettings = null;

    [Header("The muzzle object of this raygun (uses this object's forward direction for aiming):")]
    [SerializeField] private GameObject muzzle = null;

    [Header("The name of the raygun materials' color parameter:")]
    [SerializeField] private string raygunColorParameter = "_BaseColor";
    [SerializeField] private string raygunEmissiveColorParameter = "_EmissionColor";

    [Header("Renderers of separate parts of this raygun object that match the color of the ray that is fired:")]
    [SerializeField] private List<Renderer> coloredRaygunBodyParts = new List<Renderer>();

    [Header("The trigger's pivot object and its rotation clamps:")]
    [SerializeField] private GameObject triggerPivot = null;
    [SerializeField] private float triggerOutRotation = -45;
    [SerializeField] private float triggerInRotation = 45;

    [Header("The tag of held objects that are considered ammo for this raygun:")]
    [SerializeField] private string ammoTag = "Ammo";

    [Header("The slot to place ammo and the minimum distance from it to reload the raygun:")]
    [SerializeField] private GameObject ammoSlot = null;
    [SerializeField] private float ammoSlotDistance = 0.05f;

    [Header("The place to place ammo when it is loading in the raygun:")]
    [SerializeField] private GameObject ammoLocation = null;

    [Header("The raygun's current magazine and the prefab to eject when out of ammo:")]
    [SerializeField] private HandGrabbableVR currentMagazine = null;
    [SerializeField] private GameObject emptyMagazinePrefab = null;

    [Header("The renderer of the laser sight's ray (index 0) and any other colored laser sight parts:")]
    [SerializeField] private List<Renderer> laserSightParts = new List<Renderer>();

    [Header("The flashlight light object:")]
    [SerializeField] private Light flashlight = null;

    [Header("Text display of ammo:")]
    [SerializeField] private TextMeshPro ammoDisplay = null;

    [Header("\nRAYGUN SETTINGS")]

    [Header("Raygun beam settings:")]
    [SerializeField] private Color beamColor = Color.red;
    [SerializeField] private float beamIntensity = 5;
    [SerializeField] private float beamWidth = 0.01f;
    [SerializeField] private float beamLingerTime = 0.1f;

    [Header("The maximum range of this raygun:")]
    [SerializeField] private float beamRange = 100;

    [Header("Laser sight settings:")]
    [SerializeField] private bool laserSightOn = true;
    [SerializeField] private Color laserSightColor = new Color(1, 0, 0, 0.2f);
    [SerializeField] private float laserSightIntensity = 100;
    [SerializeField] private float laserSightWidth = 0.001f;

    [Header("Flashlight settings:")]
    [SerializeField] private bool flashlightOn = false;
    [SerializeField] private Color flashlightColor = Color.white;
    [SerializeField] private float flashlightIntensity = 2;
    [SerializeField] private float flashlightAngle = 45;
    [SerializeField] private float flashlightRange = 20;

    [Header("\nFIRING")]

    [Header("Whether the safety is on for this raygun:")]
    [SerializeField] private bool safety = false;

    [Header("The minimum percentage of the trigger to fire the raygun:")]
    [SerializeField] private float firePercent = 0.75f;

    [Header("Whether this raygun can be fired automatically:")]
    [SerializeField] private bool automatic = false;

    [Header("The fire rates of this raygun:")]
    [SerializeField] private float tapFireRate = 0;
    [SerializeField] private float fireRate = 0.3f;

    [Header("The number of shots fired from this raygun:")]
    [SerializeField] private int shotsFired = 1;

    [Header("First shot accuracy settings:")]
    [SerializeField] private bool firstShotAccuracy = true;
    [SerializeField] private float firstShotDelay = 1;

    [Header("Whether to use random spread and the spread in degrees:")]
    [SerializeField] private bool randomSpread = true;
    [SerializeField] private Vector2 spread = new Vector2(2.5f, 2.5f);

    [Header("The order of fixed angles of spread (repeats):")]
    [SerializeField] private List<Vector2> fixedSpreadPattern = new List<Vector2>();

    [Header("Whether this raygun fires in bursts and number of bursts fired from this raygun with their delay:")]
    [SerializeField] private bool burstFire = false;
    [SerializeField] private int burstsFired = 3;
    [SerializeField] private float burstRate = 0.1f;

    [Header("The ammo counts of this raygun:")]
    [SerializeField] private bool infiniteAmmo = false;
    [SerializeField] private int currentAmmo = 12;
    [SerializeField] private int maxAmmo = 12;
    [SerializeField] private bool autoEject = true;

    [Header("Sound effects:")]
    [SerializeField] private AudioClip fireSound = null;
    [SerializeField] private AudioClip emptySound = null;
    [SerializeField] private AudioClip ejectSound = null;
    [SerializeField] private AudioClip reloadSound = null;

    [Header("\nEVENTS")]

    [Header("Event called by the raygun:")]
    public UnityEvent onFire = null;
    public UnityEvent onReload = null;

    /// <summary>
    /// Whether the laser sight has been set
    /// </summary>
    private bool laserSightSet = false;

    /// <summary>
    /// The laser sight's starting local position
    /// </summary>
    private Vector3 laserSightLocalPosition = Vector3.zero;

    /// <summary>
    /// The current aimed target of the gun
    /// </summary>
    private RaycastHit hit = new RaycastHit();

    /// <summary>
    /// The current trigger percentage
    /// </summary>
    private float triggerPercent = 0;

    /// <summary>
    /// Whether the raygun is currently shooting its first shot
    /// </summary>
    private bool firstShot = false;

    /// <summary>
    /// The index of the raygun's current spread pattern
    /// </summary>
    private int currentSpread = 0;

    /// <summary>
    /// The delay timer used for reenabling shooting
    /// </summary>
    private float timer = 0;

    /// <summary>
    /// Whether the raygun is currently burst firing
    /// </summary>
    private bool burstFiring = false;

    /// <summary>
    /// Whether the raygun was just grabbed with the trigger down (prevents misfires)
    /// </summary>
    private bool triggerDownOnGrab = false;

    /// <summary>
    /// IHandInteractableVR Interface - Adds this object's implementation to the interface.
    /// </summary>
    private void Awake()
    {
        IHandInteractableVR.implementations.Add(this);

        if (IHandInteractableVR.handsSet)
        {
            OnSetHands();
        }
    }

    /// <summary>
    /// IHandInteractableVR Interface - Called when VR hands are successfully set.
    /// </summary>
    public void OnSetHands() { }

    /// <summary>
    /// IHandInteractableVR Interface - Removes the object's implementation to the interface.
    /// </summary>
    private void OnDestroy()
    {
        IHandInteractableVR.implementations.Remove(this);
    }

    /// <summary>
    /// Called when the raygun's settings are edited
    /// </summary>
    private void OnValidate()
    {
        if (Application.isPlaying)
        {
            Invoke("UpdateRaygun", 0);
        }
    }

    /// <summary>
    /// Initializes the raygun's settings
    /// </summary>
    private void Start()
    {
        if (grabSettings == null)
        {
            Debug.LogError("ERROR: RaygunVR " + gameObject.name + " does not have HandGrabbableVR configured!");

            Destroy(this);
        }

        if (coloredRaygunBodyParts != null && coloredRaygunBodyParts.Count != 0)
        {
            coloredRaygunBodyParts[0].sharedMaterial = new Material(coloredRaygunBodyParts[0].sharedMaterial);

            coloredRaygunBodyParts[0].sharedMaterial.EnableKeyword("_EMISSION");

            coloredRaygunBodyParts[0].sharedMaterial.SetColor(raygunColorParameter, beamColor);

            coloredRaygunBodyParts[0].sharedMaterial.SetColor(raygunEmissiveColorParameter, beamColor * beamIntensity);

            for (int i = 1; i < coloredRaygunBodyParts.Count; i++)
            {
                coloredRaygunBodyParts[i].sharedMaterial = coloredRaygunBodyParts[0].sharedMaterial;
            }
        }

        grabSettings.onGrab.AddListener(UpdateRaygun);

        grabSettings.onGrab.AddListener(() => { triggerDownOnGrab = true; });

        if (currentMagazine != null)
        {
            HandGrabbableVR magazine = currentMagazine;

            currentMagazine = null;

            InsertMagazine(magazine);
        }

        UpdateLaserSight();

        UpdateFlashlight();
    }

    /// <summary>
    /// Calculates the raygun's hit direction when held
    /// </summary>
    private void LateUpdate()
    {
        CheckRaygun();
    }


    // RAYGUN

    /// <summary>
    /// Checks, aims, and fires the raygun
    /// </summary>
    private void CheckRaygun()
    {
        laserSightParts[0].transform.localPosition = laserSightLocalPosition;

        if (grabSettings.IsGrabbed())
        {
            if (grabSettings.IsGrabbedRight())
            {
                triggerPercent = 1 - HandTrackerVR.rightHand.GetFinger(HandVR.Finger.Index);
            }
            else
            {
                triggerPercent = 1 - HandTrackerVR.leftHand.GetFinger(HandVR.Finger.Index);
            }

            float rotation = safety ? Mathf.Min(Value(triggerPercent, triggerOutRotation, triggerInRotation), Value(0.5f, triggerOutRotation, triggerInRotation)) : Value(triggerPercent, triggerOutRotation, triggerInRotation);

            triggerPivot.transform.localEulerAngles = new Vector3(rotation, triggerPivot.transform.localEulerAngles.y, triggerPivot.transform.localEulerAngles.z);

            if (laserSightSet && laserSightOn)
            {
                if (Physics.Raycast(laserSightParts[0].transform.position, muzzle.transform.forward, out hit, beamRange, ~(1 << 2), QueryTriggerInteraction.Ignore))
                {
                    laserSightParts[0].transform.position += (laserSightParts[0].transform.forward * (hit.distance / 2));

                    laserSightParts[0].transform.localScale = new Vector3(laserSightWidth, laserSightWidth, hit.distance / laserSightParts[0].transform.root.localScale.z);
                }
                else
                {
                    laserSightParts[0].transform.position += (laserSightParts[0].transform.forward * (beamRange / 2));

                    laserSightParts[0].transform.localScale = new Vector3(laserSightWidth, laserSightWidth, beamRange / laserSightParts[0].transform.root.localScale.z);
                }
            }

            if (currentAmmo <= 0 && autoEject)
            {
                EjectMagazine();
            }

            if (triggerPercent >= firePercent)
            {
                if (!triggerDownOnGrab)
                {
                    Shoot();
                }
            }
            else if (!burstFiring)
            {
                triggerDownOnGrab = false;

                firstShot = true;

                timer = Mathf.Min(timer, tapFireRate);
            }

            CheckReload();

            if (ammoDisplay != null)
            {
                ammoDisplay.text = infiniteAmmo ? "" : currentAmmo.ToString();

                ammoDisplay.color = Color.white;

                ammoDisplay.outlineColor = beamColor;
            }
        }
        else
        {
            triggerPivot.transform.localEulerAngles = new Vector3(Value(0.5f, triggerOutRotation, triggerInRotation), triggerPivot.transform.localEulerAngles.y, triggerPivot.transform.localEulerAngles.z);

            if (laserSightSet && laserSightOn)
            {
                laserSightParts[0].transform.localScale = new Vector3(laserSightWidth, laserSightWidth, laserSightWidth);

                laserSightParts[0].gameObject.active = false;
            }

            if (flashlight != null)
            {
                flashlight.gameObject.active = false;
            }

            if (!burstFiring)
            {
                firstShot = true;

                timer = Mathf.Min(timer, tapFireRate);
            }
        }

        timer -= Time.deltaTime;
    }

    /// <summary>
    /// Attempts to shoot the raygun (as if the trigger was pulled)
    /// </summary>
    /// <returns></returns>
    public bool Shoot()
    {
        bool hasAmmo = currentAmmo > 0 || infiniteAmmo;

        bool success = timer <= 0 && (firstShot || automatic);

        if (success)
        {
            if (shotsFired > 1 || burstFire)
            {
                currentSpread = 0;
            }

            if (burstFire)
            {
                Burst(burstsFired);

                timer = burstRate * numberOfBursts + fireRate;
            }
            else
            {
                int count = infiniteAmmo ? shotsFired : Mathf.Min(shotsFired, currentAmmo);

                for (int i = 0; i < count; i++)
                {
                    Fire();
                }

                if (count == 0)
                {
                    Fire();
                }

                timer = fireRate;
            }
        }

        return hasAmmo && success;
    }

    /// <summary>
    /// Fires in a burst sequence
    /// </summary>
    /// <returns></returns>
    private async Task Burst(int numberOfBursts)
    {
        burstFiring = true;

        for (int i = 0; i < numberOfBursts; i++)
        {
            int count = infiniteAmmo ? shotsFired : Mathf.Min(shotsFired, currentAmmo);

            for (int j = 0; j < count; j++)
            {
                Fire();
            }

            if (count == 0)
            {
                Fire();
            }

            await Task.Delay((int)(burstRate * 1000));
        }

        burstFiring = false;
    }

    /// <summary>
    /// Fires one shot of the raygun
    /// </summary>
    /// <returns></returns>
    private RaycastHit Fire()
    {
        if ((infiniteAmmo || currentAmmo > 0) && !safety)
        {
            Vector3 direction = muzzle.transform.forward;

            if (!firstShot || !firstShotAccuracy || shotsFired > 1 || timer > -Mathf.Abs(firstShotDelay))
            {
                if (randomSpread)
                {
                    direction = Quaternion.Euler(Random.Range(-spread.y, spread.y), Random.Range(-spread.x, spread.x), 0) * direction;
                }
                else if (fixedSpreadPattern != null && fixedSpreadPattern.Count > 0)
                {
                    direction = Quaternion.Euler(new Vector3(-fixedSpreadPattern[currentSpread].y, fixedSpreadPattern[currentSpread].x, 0)) * direction;

                    currentSpread++;

                    currentSpread %= fixedSpreadPattern.Count;
                }
            }

            firstShot = false;

            Renderer ray = GameObject.CreatePrimitive(PrimitiveType.Cube).GetComponent<Renderer>();

            ray.gameObject.layer = 2;

            if (Application.isPlaying)
            {
                Destroy(ray.gameObject.GetComponent<Collider>());
            }
            else
            {
                DestroyImmediate(ray.gameObject.GetComponent<Collider>());
            }

            if (coloredRaygunBodyParts != null && coloredRaygunBodyParts.Count > 0)
            {
                ray.sharedMaterial = coloredRaygunBodyParts[0].sharedMaterial;
            }

            ray.sharedMaterial.EnableKeyword("_EMISSION");

            ray.sharedMaterial.SetColor(raygunColorParameter, beamColor);

            ray.sharedMaterial.SetColor(raygunEmissiveColorParameter, beamColor * beamIntensity);

            ray.transform.position = muzzle.transform.position;

            DestroyAfterSeconds(ray.gameObject, beamLingerTime);

            if (Physics.Raycast(muzzle.transform.position, direction, out hit, beamRange, ~(1 << 2), QueryTriggerInteraction.Ignore))
            {
                ray.transform.LookAt(hit.point);

                ray.transform.position += (ray.transform.forward * (hit.distance / 2));

                ray.transform.localScale = new Vector3(beamWidth, beamWidth, hit.distance);

                MonoBehaviour[] components = hit.collider.gameObject.GetComponents<MonoBehaviour>();

                for (int i = 0; i < components.Length; i++)
                {
                    if (components[i] is IRaygunShootable)
                    {
                        (components[i] as IRaygunShootable).OnRaygunHit(hit);
                    }
                }
            }
            else
            {
                ray.transform.rotation = Quaternion.LookRotation(direction);

                ray.transform.LookAt(ray.transform.position + ray.transform.forward * beamRange);

                ray.transform.position += (ray.transform.forward * (beamRange / 2));

                ray.transform.localScale = new Vector3(beamWidth, beamWidth, beamRange);
            }

            if (!infiniteAmmo)
            {
                currentAmmo--;
            }

            if (fireSound != null)
            {
                AudioSource.PlayClipAtPoint(fireSound, muzzle.transform.position);
            }

            onFire.Invoke();
        }
        else if (firstShot || automatic)
        {
            hit = new RaycastHit();

            firstShot = false;

            if (emptySound != null)
            {
                AudioSource.PlayClipAtPoint(emptySound, muzzle.transform.position);
            }
        }

        return hit;
    }

    /// <summary>
    /// Destroys the given object after the given number of seconds
    /// </summary>
    /// <returns></returns>
    private static async Task DestroyAfterSeconds(GameObject gameObject, float seconds)
    {
        await Task.Delay((int)(seconds * 1000));

        if (Application.isPlaying)
        {
            Destroy(gameObject);
        }
        else
        {
            DestroyImmediate(gameObject);
        }
    }

    /// <summary>
    /// Checks if the player is holding ammo and is attempting to reload
    /// </summary>
    private void CheckReload()
    {
        if (currentAmmo <= 0 && !infiniteAmmo)
        {
            if (HandGrabbableVR.heldLeft != null && HandGrabbableVR.heldLeft.tag == ammoTag)
            {
                if (DistanceSquared(HandGrabbableVR.heldLeft.transform.position, ammoSlot.transform.position) <= ammoSlotDistance * ammoSlotDistance)
                {
                    Reload(HandGrabbableVR.heldLeft.GetComponent<HandGrabbableVR>());
                }
            }
            else if (HandGrabbableVR.heldRight != null && HandGrabbableVR.heldRight.tag == ammoTag)
            {
                if (DistanceSquared(HandGrabbableVR.heldRight.transform.position, ammoSlot.transform.position) <= ammoSlotDistance * ammoSlotDistance)
                {
                    Reload(HandGrabbableVR.heldRight.GetComponent<HandGrabbableVR>());
                }
            }
        }
    }

    /// <summary>
    /// Reloads the raygun to max ammo
    /// </summary>
    public void Reload(HandGrabbableVR magazine = null)
    {
        if (currentMagazine == null)
        {
            triggerDownOnGrab = true;

            currentAmmo = maxAmmo;

            InsertMagazine(magazine);

            if (reloadSound != null)
            {
                AudioSource.PlayClipAtPoint(reloadSound, ammoLocation.transform.position);
            }

            onReload.Invoke();
        }
    }

    /// <summary>
    /// Inserts the magazine
    /// </summary>
    /// <returns></returns>
    public bool InsertMagazine(HandGrabbableVR magazine)
    {
        if (magazine != null && currentMagazine == null)
        {
            magazine.tag = "Untagged";

            magazine.enabled = false;

            magazine.transform.parent = ammoLocation.transform;

            magazine.transform.localPosition = Vector3.zero;

            magazine.transform.localEulerAngles = Vector3.zero;

            magazine.GetComponentInChildren<Collider>().enabled = false;

            magazine.GetComponentInChildren<Rigidbody>().isKinematic = true;

            currentMagazine = magazine;

            return true;
        }

        return false;
    }

    /// <summary>
    /// Ejects the magazine
    /// </summary>
    /// <returns></returns>
    public bool EjectMagazine()
    {
        if (currentMagazine != null)
        {
            currentAmmo = 0;

            if (emptyMagazinePrefab != null)
            {
                GameObject magazine = Instantiate(emptyMagazinePrefab);

                magazine.transform.position = currentMagazine.transform.position;

                magazine.transform.eulerAngles = currentMagazine.transform.eulerAngles;
            }

            Destroy(currentMagazine.gameObject);

            currentMagazine = null;

            if (ejectSound != null)
            {
                AudioSource.PlayClipAtPoint(ejectSound, ammoLocation.transform.position);
            }

            return true;
        }

        return false;
    }

    /// <summary>
    /// Updates the raygun based on the current settings
    /// </summary>
    private void UpdateRaygun()
    {
        if (coloredRaygunBodyParts != null && coloredRaygunBodyParts.Count != 0)
        {
            coloredRaygunBodyParts[0].sharedMaterial.SetColor(raygunColorParameter, beamColor);

            coloredRaygunBodyParts[0].sharedMaterial.SetColor(raygunEmissiveColorParameter, beamColor * beamIntensity);
        }

        if (ammoDisplay != null)
        {
            ammoDisplay.text = infiniteAmmo ? "" : currentAmmo.ToString();

            ammoDisplay.color = Color.white;

            ammoDisplay.outlineColor = beamColor;
        }

        UpdateLaserSight();

        UpdateFlashlight();
    }

    /// <summary>
    /// Configures and updates the laser sight
    /// </summary>
    private void UpdateLaserSight()
    {
        if (!laserSightSet && laserSightParts != null && laserSightParts.Count > 0)
        {
            laserSightParts[0].sharedMaterial = new Material(laserSightParts[0].sharedMaterial);

            for (int i = 1; i < laserSightParts.Count; i++)
            {
                laserSightParts[i].sharedMaterial = laserSightParts[0].sharedMaterial;
            }

            laserSightLocalPosition = laserSightParts[0].transform.localPosition;

            laserSightSet = true;
        }

        if (laserSightSet)
        {
            laserSightParts[0].sharedMaterial.SetColor(raygunColorParameter, laserSightColor);

            laserSightParts[0].sharedMaterial.SetColor(raygunEmissiveColorParameter, laserSightColor * laserSightIntensity);

            laserSightParts[0].gameObject.active = laserSightOn;
        }
    }

    /// <summary>
    /// Updates the flashlight
    /// </summary>
    private void UpdateFlashlight()
    {
        if (flashlight != null)
        {
            flashlight.color = flashlightColor;

            flashlight.intensity = flashlightIntensity;

            flashlight.spotAngle = flashlightAngle;

            flashlight.range = flashlightRange;

            flashlight.gameObject.active = flashlightOn;
        }
    }


    // GETTERS

    /// <summary>
    /// Gets whether the safety is on
    /// </summary>
    /// <returns></returns>
    public bool IsSafetyOn()
    {
        return safety;
    }

    /// <summary>
    /// Gets the percentage of the trigger (1 = trigger pulled)
    /// </summary>
    /// <returns></returns>
    public float GetTriggerPercent()
    {
        return triggerPercent;
    }

    /// <summary>
    /// Gets whether the trigger is considered pulled
    /// </summary>
    /// <returns></returns>
    public bool IsTriggerPulled()
    {
        return triggerPercent >= firePercent;
    }

    /// <summary>
    /// Gets whether the raygun is currently shooting
    /// </summary>
    /// <returns></returns>
    public bool IsFiring()
    {
        return !firstShot;
    }

    /// <summary>
    /// Gets whether the raygun is currently in a burst fire
    /// </summary>
    /// <returns></returns>
    public bool IsBurstFiring()
    {
        return burstFiring;
    }

    /// <summary>
    /// Gets the beam color
    /// </summary>
    /// <returns></returns>
    public Color GetBeamColor()
    {
        return beamColor;
    }

    /// <summary>
    /// Gets the beam's emissive intensity
    /// </summary>
    /// <returns></returns>
    public float GetBeamIntensity()
    {
        return beamIntensity;
    }

    /// <summary>
    /// Gets the beam's width
    /// </summary>
    /// <returns></returns>
    public float GetBeamWidth()
    {
        return beamWidth;
    }

    /// <summary>
    /// Gets the beam's linger time
    /// </summary>
    /// <returns></returns>
    public float GetBeamLingerTime()
    {
        return beamLingerTime;
    }

    /// <summary>
    /// Gets the raygun's range
    /// </summary>
    /// <returns></returns>
    public float GetRange()
    {
        return beamRange;
    }

    /// <summary>
    /// Gets whether the magazine will auto eject when it is empty
    /// </summary>
    /// <returns></returns>
    public bool WillAutoEject()
    {
        return autoEject;
    }

    /// <summary>
    /// Gets the laser sight object
    /// </summary>
    /// <returns></returns>
    public Renderer GetLaserSight()
    {
        if (laserSightParts == null || laserSightParts.Count == 0)
        {
            return null;
        }

        return laserSightParts[0];
    }

    /// <summary>
    /// Gets whether the laser sight is on
    /// </summary>
    /// <returns></returns>
    public bool IsLaserSightOn()
    {
        return laserSightOn;
    }

    /// <summary>
    /// Gets the laser sight's color
    /// </summary>
    /// <returns></returns>
    public Color GetLaserSightColor()
    {
        return laserSightColor;
    }

    /// <summary>
    /// Gets the laser sight's emissive intensity
    /// </summary>
    /// <returns></returns>
    public float GetLaserSightIntensity()
    {
        return laserSightIntensity;
    }

    /// <summary>
    /// Gets the laser sight's width
    /// </summary>
    /// <returns></returns>
    public float GetLaserSightWidth()
    {
        return laserSightWidth;
    }

    /// <summary>
    /// Gets the flashlight object
    /// </summary>
    /// <returns></returns>
    public Light GetFlashlight()
    {
        return flashlight;
    }

    /// <summary>
    /// Gets whether the flashlight is on
    /// </summary>
    /// <returns></returns>
    public bool IsFlashlightOn()
    {
        return flashlightOn;
    }

    /// <summary>
    /// Gets the flashlight's color
    /// </summary>
    /// <returns></returns>
    public Color GetFlashlightColor()
    {
        return flashlightColor;
    }

    /// <summary>
    /// Gets the flashlight's intensity
    /// </summary>
    /// <returns></returns>
    public float GetFlashlightIntensity()
    {
        return flashlightIntensity;
    }

    /// <summary>
    /// Gets the flashlight's angle
    /// </summary>
    /// <returns></returns>
    public float GetFlashlightAngle()
    {
        return flashlightAngle;
    }

    /// <summary>
    /// Gets the flashlight's range
    /// </summary>
    /// <returns></returns>
    public float GetFlashlightRange()
    {
        return flashlightRange;
    }

    /// <summary>
    /// Gets whether the raygun is grabbed
    /// </summary>
    /// <returns></returns>
    public bool IsGrabbed()
    {
        return grabSettings.IsGrabbed();
    }

    /// <summary>
    /// Gets whether the raygun is grabbed in the left hand
    /// </summary>
    /// <returns></returns>
    public bool IsGrabbedLeft()
    {
        return grabSettings.IsGrabbedLeft();
    }

    /// <summary>
    /// Gets whether the raygun is grabbed in the right hand
    /// </summary>
    /// <returns></returns>
    public bool IsGrabbedRight()
    {
        return grabSettings.IsGrabbedRight();
    }

    /// <summary>
    /// Gets whether the raygun is being grabbed by the given hand
    /// </summary>
    /// <returns></returns>
    public bool IsGrabbed(bool isRight)
    {
        return isRight ? grabSettings.IsGrabbedRight() : grabSettings.IsGrabbedLeft();
    }

    /// <summary>
    /// Gets whether the raygun fires automatically
    /// </summary>
    /// <returns></returns>
    public bool IsAutomatic()
    {
        return automatic;
    }

    /// <summary>
    /// Gets the fire rate of the first shot
    /// </summary>
    /// <returns></returns>
    public float GetTapFireRate()
    {
        return tapFireRate;
    }

    /// <summary>
    /// Gets the fire rate
    /// </summary>
    /// <returns></returns>
    public float GetFireRate()
    {
        return fireRate;
    }

    /// <summary>
    /// Gets the total number of shots fired at a time
    /// </summary>
    /// <returns></returns>
    public int GetShotsFired()
    {
        return shotsFired;
    }

    /// <summary>
    /// Gets whether first shot accuracy is enabled
    /// </summary>
    /// <returns></returns>
    public bool HasFirstShotAccuracy()
    {
        return firstShotAccuracy;
    }

    /// <summary>
    /// Gets whether spread is random
    /// </summary>
    /// <returns></returns>
    public bool IsSpreadRandom()
    {
        return randomSpread;
    }

    /// <summary>
    /// Gets the angle of the random spread
    /// </summary>
    /// <returns></returns>
    public Vector2 GetRandomSpread()
    {
        return spread;
    }

    /// <summary>
    /// Gets the fixed spread pattern
    /// </summary>
    /// <returns></returns>
    public List<Vector2> GetFixedSpreadPattern()
    {
        return fixedSpreadPattern;
    }

    /// <summary>
    /// Gets whether this raygun fires in bursts
    /// </summary>
    /// <returns></returns>
    public bool IsBurst()
    {
        return burstFire;
    }

    /// <summary>
    /// Gets the total number of bursts
    /// </summary>
    /// <returns></returns>
    public int GetBursts()
    {
        return burstsFired;
    }

    /// <summary>
    /// Gets the burst time
    /// </summary>
    /// <returns></returns>
    public float GetBurstTime()
    {
        return burstRate;
    }

    /// <summary>
    /// Gets whether ammo is infinite
    /// </summary>
    /// <returns></returns>
    public bool IsAmmoInfinite()
    {
        return infiniteAmmo;
    }

    /// <summary>
    /// Gets the ammo count
    /// </summary>
    /// <returns></returns>
    public int GetCurrentAmmo()
    {
        return currentAmmo;
    }

    /// <summary>
    /// Gets the maximum ammo count
    /// </summary>
    /// <returns></returns>
    public int GetMaxAmmo()
    {
        return maxAmmo;
    }

    /// <summary>
    /// Gets the magazine object
    /// </summary>
    /// <returns></returns>
    public HandGrabbableVR GetMagazine()
    {
        return currentMagazine;
    }

    /// <summary>
    /// Gets the empty magazine prefab object
    /// </summary>
    /// <returns></returns>
    public GameObject GetEmptyMagazinePrefab()
    {
        return emptyMagazinePrefab;
    }

    /// <summary>
    /// Gets the firing sound
    /// </summary>
    /// <returns></returns>
    public AudioClip GetFireSound()
    {
        return fireSound;
    }

    /// <summary>
    /// Gets the reloading sound
    /// </summary>
    /// <returns></returns>
    public AudioClip GetReloadSound()
    {
        return reloadSound;
    }

    /// <summary>
    /// Gets the firing empty sound
    /// </summary>
    /// <returns></returns>
    public AudioClip GetEmptySound()
    {
        return emptySound;
    }

    /// <summary>
    /// Gets the magazine eject sound
    /// </summary>
    /// <returns></returns>
    public AudioClip GetEjectSound()
    {
        return ejectSound;
    }

    /// <summary>
    /// Gets the ammo display text
    /// </summary>
    /// <returns></returns>
    public TextMeshPro GetAmmoDisplay()
    {
        return ammoDisplay;
    }


    // SETTERS

    /// <summary>
    /// Sets whether the safety is on
    /// </summary>
    /// <returns></returns>
    public bool SetSafety(bool newSafety)
    {
        safety = newSafety;

        return newSafety;
    }

    /// <summary>
    /// Toggles the safety of this raygun
    /// </summary>
    /// <returns></returns>
    public bool ToggleSafety()
    {
        safety = !safety;

        return safety;
    }

    /// <summary>
    /// Sets the beam color
    /// </summary>
    /// <returns></returns>
    public Color SetBeamColor(Color newColor)
    {
        beamColor = newColor;

        UpdateRaygun();

        return newColor;
    }

    /// <summary>
    /// Sets the beam's emissive intensity
    /// </summary>
    /// <returns></returns>
    public float SetBeamIntensity(float newIntensity)
    {
        beamIntensity = newIntensity;

        UpdateRaygun();

        return newIntensity;
    }

    /// <summary>
    /// Sets the beam's width
    /// </summary>
    /// <returns></returns>
    public float SetBeamWidth(float newWidth)
    {
        beamWidth = newWidth;

        return newWidth;
    }

    /// <summary>
    /// Sets the beam's linger time
    /// </summary>
    /// <returns></returns>
    public float SetBeamLingerTime(float newTime)
    {
        beamLingerTime = newTime;

        return newTime;
    }

    /// <summary>
    /// Sets the raygun's range
    /// </summary>
    /// <returns></returns>
    public float SetRange(float newRange)
    {
        beamRange = newRange;

        return newRange;
    }

    /// <summary>
    /// Sets whether the magazine will auto eject when it is empty
    /// </summary>
    /// <returns></returns>
    public bool SetAutoEject(bool autoEject)
    {
        this.autoEject = autoEject;

        return autoEject;
    }

    /// <summary>
    /// Toggles whether the magazine will auto eject when it is empty
    /// </summary>
    /// <returns></returns>
    public bool ToggleAutoEject()
    {
        autoEject = !autoEject;

        return autoEject;
    }

    /// <summary>
    /// Sets whether the laser sight is on
    /// </summary>
    /// <returns></returns>
    public bool SetLaserSightOn(bool on)
    {
        laserSightOn = on;

        UpdateLaserSight();

        return on;
    }

    /// <summary>
    /// Toggles the laser sight
    /// </summary>
    /// <returns></returns>
    public bool ToggleLaserSight()
    {
        laserSightOn = !laserSightOn;

        UpdateLaserSight();

        return laserSightOn;
    }

    /// <summary>
    /// Sets the laser sight's color
    /// </summary>
    /// <returns></returns>
    public Color SetLaserSightColor(Color newColor)
    {
        laserSightColor = newColor;

        UpdateLaserSight();

        return newColor;
    }

    /// <summary>
    /// Sets the laser sight's emissive intensity
    /// </summary>
    /// <returns></returns>
    public float SetLaserSightIntensity(float newIntensity)
    {
        laserSightIntensity = newIntensity;

        UpdateRaygun();

        return newIntensity;
    }

    /// <summary>
    /// Sets the laser sight's width
    /// </summary>
    /// <returns></returns>
    public float SetLaserSightWidth(float newWidth)
    {
        laserSightWidth = newWidth;

        return newWidth;
    }

    /// <summary>
    /// Resets the laser sight
    /// </summary>
    public void ResetLaserSight(Vector3 newLocalPosition)
    {
        if (laserSightSet)
        {
            laserSightSet = false;

            laserSightParts[0].transform.localPosition = newLocalPosition;

            UpdateLaserSight();
        }
    }

    /// <summary>
    /// Set whether the flashlight is on
    /// </summary>
    /// <returns></returns>
    public bool SetFlashlightOn(bool on)
    {
        flashlightOn = on;

        UpdateFlashlight();

        return on;
    }

    /// <summary>
    /// Toggles the flashlight
    /// </summary>
    /// <returns></returns>
    public bool ToggleFlashlight()
    {
        flashlightOn = !flashlightOn;

        UpdateFlashlight();

        return flashlightOn;
    }

    /// <summary>
    /// Sets the flashlight's color
    /// </summary>
    /// <returns></returns>
    public Color SetFlashlightColor(Color newColor)
    {
        flashlightColor = newColor;

        UpdateFlashlight();

        return newColor;
    }

    /// <summary>
    /// Sets the flashlight's intensity
    /// </summary>
    /// <returns></returns>
    public float SetFlashlightIntensity(float newIntensity)
    {
        flashlightIntensity = newIntensity;

        UpdateFlashlight();

        return newIntensity;
    }

    /// <summary>
    /// Sets the flashlight's angle
    /// </summary>
    /// <returns></returns>
    public float SetFlashlightAngle(float newAngle)
    {
        flashlightAngle = newAngle;

        UpdateFlashlight();

        return newAngle;
    }

    /// <summary>
    /// Sets the flashlight's range
    /// </summary>
    /// <returns></returns>
    public float SetFlashlightRange(float newRange)
    {
        flashlightRange = newRange;

        UpdateFlashlight();

        return newRange;
    }

    /// <summary>
    /// Sets whether the raygun fires automatically
    /// </summary>
    /// <returns></returns>
    public bool SetAutomatic(bool automatic)
    {
        this.automatic = automatic;

        return automatic;
    }

    /// <summary>
    /// Toggles whether the raygun fires automatically
    /// </summary>
    /// <returns></returns>
    public bool ToggleAutomatic()
    {
        automatic = !automatic;

        return automatic;
    }

    /// <summary>
    /// Sets the fire rate of the first shot
    /// </summary>
    /// <returns></returns>
    public float SetTapFireRate(float newFireRate)
    {
        tapFireRate = newFireRate;

        return newFireRate;
    }

    /// <summary>
    /// Sets the fire rate
    /// </summary>
    /// <returns></returns>
    public float SetFireRate(float newFireRate)
    {
        fireRate = newFireRate;

        return newFireRate;
    }

    /// <summary>
    /// Sets the total number of shots fired
    /// </summary>
    /// <returns></returns>
    public int SetShotsFired(int newShotsFired)
    {
        shotsFired = newShotsFired;

        return newShotsFired;
    }

    /// <summary>
    /// Sets whether first shot accuracy is enabled
    /// </summary>
    /// <returns></returns>
    public bool HasFirstShotAccuracy(bool hasFirstShotAccuracy)
    {
        firstShotAccuracy = hasFirstShotAccuracy;

        return hasFirstShotAccuracy;
    }

    /// <summary>
    /// Toggles whether first shot accuracy is enabled
    /// </summary>
    /// <returns></returns>
    public bool ToggleFirstShotAccuracy()
    {
        firstShotAccuracy = !firstShotAccuracy;

        return firstShotAccuracy;
    }

    /// <summary>
    /// Sets whether spread is random
    /// </summary>
    /// <returns></returns>
    public bool SetRandomSpread(bool randomSpread)
    {
        this.randomSpread = randomSpread;

        return randomSpread;
    }

    /// <summary>
    /// Toggle whether spread is random
    /// </summary>
    /// <returns></returns>
    public bool ToggleRandomSpread()
    {
        randomSpread = !randomSpread;

        return randomSpread;
    }

    /// <summary>
    /// Sets the angle of the random spread
    /// </summary>
    /// <returns></returns>
    public Vector2 SetSpread(Vector2 newSpread)
    {
        spread = newSpread;

        return newSpread;
    }

    /// <summary>
    /// Sets the fixed spread pattern
    /// </summary>
    /// <returns></returns>
    public List<Vector2> SetFixedSpreadPattern(params Vector2[] pattern)
    {
        fixedSpreadPattern.Clear();

        for (int i = 0; i < pattern.Length; i++)
        {
            fixedSpreadPattern.Add(pattern[i]);
        }

        return fixedSpreadPattern;
    }

    /// <summary>
    /// Sets whether this raygun fires in bursts
    /// </summary>
    /// <returns></returns>
    public bool SetBurst(bool burst)
    {
        this.burstFire = burst;

        return burst;
    }

    /// <summary>
    /// Toggles whether this raygun fires in bursts
    /// </summary>
    /// <returns></returns>
    public bool ToggleBurst()
    {
        burstFire = !burstFire;

        return burstFire;
    }

    /// <summary>
    /// Sets the total number of bursts
    /// </summary>
    /// <returns></returns>
    public int SetBurstCount(int newCount)
    {
        burstsFired = newCount;

        return newCount;
    }

    /// <summary>
    /// Sets the burst time
    /// </summary>
    /// <returns></returns>
    public float SetBurstTime(float newTime)
    {
        burstRate = newTime;

        return newTime;
    }

    /// <summary>
    /// Sets whether ammo is infinite
    /// </summary>
    /// <returns></returns>
    public bool SetInfiniteAmmo(bool infinite)
    {
        infiniteAmmo = infinite;

        return infinite;
    }

    /// <summary>
    /// Toggles whether ammo is infinite
    /// </summary>
    /// <returns></returns>
    public bool ToggleInfiniteAmmo()
    {
        infiniteAmmo = !infiniteAmmo;

        return infiniteAmmo;
    }

    /// <summary>
    /// Sets the ammo count
    /// </summary>
    /// <returns></returns>
    public int SetCurrentAmmo(int newAmmo)
    {
        currentAmmo = newAmmo;

        return newAmmo;
    }

    /// <summary>
    /// Sets the maximum ammo count
    /// </summary>
    /// <returns></returns>
    public int SetMaxAmmo(int newMax)
    {
        maxAmmo = newMax;

        return newMax;
    }

    /// <summary>
    /// Sets the magazine object
    /// </summary>
    /// <returns></returns>
    public HandGrabbableVR SetMagazine(HandGrabbableVR newMagazine, bool destroy = true)
    {
        if (currentMagazine != null && destroy)
        {
            Destroy(currentMagazine.gameObject);
        }

        currentMagazine = newMagazine;

        return newMagazine;
    }

    /// <summary>
    /// Sets the empty magazing prefab
    /// </summary>
    /// <returns></returns>
    public GameObject SetEmptyMagazinePrefab(GameObject newPrefab)
    {
        emptyMagazinePrefab = newPrefab;

        return newPrefab;
    }

    /// <summary>
    /// Sets the firing sound
    /// </summary>
    /// <returns></returns>
    public AudioClip SetFireSound(AudioClip newSound)
    {
        fireSound = newSound;

        return newSound;
    }

    /// <summary>
    /// Sets the reloading sound
    /// </summary>
    /// <returns></returns>
    public AudioClip SetReloadSound(AudioClip newSound)
    {
        reloadSound = newSound;

        return newSound;
    }

    /// <summary>
    /// Sets the empty firing sound
    /// </summary>
    /// <returns></returns>
    public AudioClip SetEmptySound(AudioClip newSound)
    {
        emptySound = newSound;

        return newSound;
    }

    /// <summary>
    /// Sets the magazine eject sound
    /// </summary>
    /// <returns></returns>
    public AudioClip SetEjectSound(AudioClip newSound)
    {
        ejectSound = newSound;

        return newSound;
    }

    /// <summary>
    /// Sets the ammo display text
    /// </summary>
    /// <returns></returns>
    public TextMeshPro SetAmmoDisplay(TextMeshPro newDisplay)
    {
        ammoDisplay = newDisplay;

        UpdateRaygun();

        return newDisplay;
    }


    // HELPER FUNCTIONS

    /// <summary>
    /// Returns a value relative to a percentage of a minimum and maximum
    /// </summary>
    /// <param name="percentage"></param>
    /// <param name="min"></param>
    /// <param name="max"></param>
    /// <returns></returns>
    private static float Value(float percentage, float min, float max)
    {
        return (max - min) * percentage + min;
    }

    /// <summary>
    /// Returns the squared distance between two vector 3s
    /// </summary>
    /// <param name="pointA"></param>
    /// <param name="pointB"></param>
    /// <returns></returns>
    private static float DistanceSquared(Vector3 pointA, Vector3 pointB)
    {
        float xDistance = pointA.x - pointB.x;
        float yDistance = pointA.y - pointB.y;
        float zDistance = pointA.z - pointB.z;

        return xDistance * xDistance + yDistance * yDistance + zDistance * zDistance;
    }
}

/// <summary>
/// Interface that contracts a function for when a raygun shoots it.
/// </summary>
public interface IRaygunShootable
{
    /// <summary>
    /// Called when a raygun shoots this object.
    /// </summary>
    /// <param name="hit"></param>
    public abstract void OnRaygunHit(RaycastHit hit);
}
