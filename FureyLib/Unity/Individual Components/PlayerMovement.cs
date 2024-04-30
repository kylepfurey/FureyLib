
// Player Movement Template Script
// by Kyle Furey

using UnityEngine;
using UnityEngine.SceneManagement;

// Drop onto any object in a 3D Unity game to generate a Player.
public class PlayerMovement : MonoBehaviour
{
    [Header("Drop onto any object in a 3D Unity game to generate a Player.")]

    // Player Settings
    [Header("Third Person Variables")]
    [SerializeField] private bool thirdPerson = true;
    [SerializeField] private Vector3 thirdPersonCameraDistance = new Vector3(0, 0, -5);
    [SerializeField] private Vector3 firstPersonCameraDistance = new Vector3(0, 0.5f, 0);
    [SerializeField] private float cameraObstructedDistance = 0.1f;

    [Header("Rotation Variables")]
    [SerializeField] private bool playerRotatesToCamera = false;
    [SerializeField] private float playerRotateSpeed = 10;
    [SerializeField] private Vector2 firstPersonCameraClamp = new Vector2(-85, 85);
    [SerializeField] private Vector2 thirdPersonCameraClamp = new Vector2(0, 85);

    [Header("Camera Variables")]
    [SerializeField] private float bobHeight = 0.1f;
    [SerializeField] private float bobSpeed = 10;

    [Header("Mouse Sensitivity")]
    [SerializeField] private float mouseSensitivityX = 3;
    [SerializeField] private float mouseSensitivityY = 3;
    [SerializeField] private bool invertX = false;
    [SerializeField] private bool invertY = false;

    [Header("Player Speed")]
    [SerializeField] private float speed = 7.5f;
    [SerializeField] private float airControl = 0.5f;

    [Header("Jumping Variables")]
    [SerializeField] private bool canJump = true;
    [SerializeField] private float jumpForce = 5;
    [SerializeField] private float jumpCheckHeight = 0.5f;
    [SerializeField] private float jumpCheckWidth = 1;
    [SerializeField] private float jumpCheckDepth = 0.51f;
    [SerializeField] private Vector3 gravity = new Vector3(0, -9.8f, 0);

    [Header("Sprinting Variables")]
    [SerializeField] private bool canSprint = true;
    [SerializeField] private bool toggleSprint = false;
    [SerializeField] private float sprintModifer = 1.5f;
    [SerializeField] private float sprintAcceleration = 20;

    [Header("Crouching Variables")]
    [SerializeField] private bool canCrouch = true;
    [SerializeField] private bool toggleCrouch = false;
    [SerializeField] private float crouchModifier = 0.5f;
    [SerializeField] private float crouchSpeed = 0.75f;
    [SerializeField] private float crouchTime = 20;

    [Header("Other Settings")]
    [SerializeField] private bool canRestart = true;
    [SerializeField] private bool canExit = true;
    public bool active = true;

    // Variables
    private Rigidbody Rigidbody = null;
    private Camera Camera = null;
    private float currentSpeed = 0;
    private bool isGrounded = true;
    private Vector3 groundVelocity = Vector3.zero;
    private Vector2 mouseDelta = Vector2.zero;
    private bool isSprinting = false;
    private bool isCrouching = false;
    private float startingScale = 0;
    private float bobTime = 0;

    private void Start()
    {
        Initialize();
    }

    private void Update()
    {
        if (!thirdPerson)
        {
            CameraRotation();
        }

        CameraPosition();
        HeadBob();

        if (active)
        {
            CameraInput();
            Jumping();
            Sprinting();
            Crouching();
            Movement();
        }
        else
        {
            Rigidbody.velocity = new Vector3(0, Rigidbody.velocity.y, 0);
            Rigidbody.angularVelocity = Vector3.zero;
        }

        RestartAndExit();
    }

    private void FixedUpdate()
    {
        if (thirdPerson)
        {
            CameraRotation();
        }
    }

    private void Initialize()
    {
        if (!GetComponent<Collider>())
        {
            gameObject.AddComponent<CapsuleCollider>();
        }

        if (GetComponent<Rigidbody>())
        {
            Rigidbody = GetComponent<Rigidbody>();
        }
        else
        {
            Rigidbody = gameObject.AddComponent<Rigidbody>();
        }

        if (FindObjectOfType<Camera>())
        {
            Camera = FindObjectOfType<Camera>();
        }
        else
        {
            Camera = new GameObject().AddComponent<Camera>();
        }

        Rigidbody.constraints = ~RigidbodyConstraints.FreezeAll | RigidbodyConstraints.FreezeRotation;
        Rigidbody.collisionDetectionMode = CollisionDetectionMode.ContinuousSpeculative;
        Rigidbody.interpolation = RigidbodyInterpolation.Interpolate;

        if (!GetComponent<Collider>().material)
        {
            PhysicMaterial material = new PhysicMaterial();
            material.name = "Player Material";
            material.staticFriction = 0;
            material.dynamicFriction = 0;
            material.frictionCombine = PhysicMaterialCombine.Minimum;

            GetComponent<Collider>().material = material;
        }
        else if (GetComponent<Collider>().material.name == "")
        {
            PhysicMaterial material = new PhysicMaterial();
            material.name = "Player Material";
            material.staticFriction = 0;
            material.dynamicFriction = 0;
            material.frictionCombine = PhysicMaterialCombine.Minimum;

            GetComponent<Collider>().material = material;
        }


        name = "Player";
        tag = "Player";
        Camera.name = "Player Camera";
        Camera.tag = "MainCamera";
        Camera.nearClipPlane = 0.01f;

        currentSpeed = speed;
        startingScale = transform.localScale.y;

        Cursor.lockState = CursorLockMode.Locked;
    }

    private void Movement()
    {
        // Movement
        float fallingVelocity = Rigidbody.velocity.y;

        Vector2 movement = new Vector2(Input.GetAxis("Horizontal"), Input.GetAxis("Vertical"));

        if (isGrounded)
        {
            Rigidbody.velocity = transform.forward * currentSpeed * movement.y + transform.right * currentSpeed * movement.x;

            groundVelocity = Rigidbody.velocity;
        }
        else
        {
            Rigidbody.velocity = groundVelocity - groundVelocity * airControl;

            Rigidbody.velocity += transform.forward * currentSpeed * movement.y * airControl + transform.right * currentSpeed * movement.x * airControl;
        }

        Rigidbody.velocity = new Vector3(Rigidbody.velocity.x, fallingVelocity, Rigidbody.velocity.z);
        Rigidbody.angularVelocity = Vector3.zero;

        if (!thirdPerson || playerRotatesToCamera || Mathf.Abs(movement.magnitude) > 0)
        {
            RotatePlayer();
        }
    }

    private void RotatePlayer()
    {
        if (thirdPerson)
        {
            Vector3 playerRotation = transform.eulerAngles;
            Vector3 cameraRotation = Camera.transform.eulerAngles;

            transform.eulerAngles = new Vector3(0, transform.eulerAngles.y, 0);
            Camera.transform.eulerAngles = new Vector3(0, Camera.transform.eulerAngles.y, 0);

            transform.rotation = Quaternion.Lerp(transform.rotation, Camera.transform.rotation, playerRotateSpeed * Time.deltaTime);

            transform.eulerAngles = new Vector3(playerRotation.x, transform.eulerAngles.y, playerRotation.z);
            Camera.transform.eulerAngles = cameraRotation;
        }
        else
        {
            transform.eulerAngles = new Vector3(transform.eulerAngles.x, Camera.transform.eulerAngles.y, transform.eulerAngles.z);
        }
    }

    private void CameraInput()
    {
        // Camera Input
        if (!invertX)
        {
            mouseDelta += new Vector2(Input.GetAxis("Mouse X") * mouseSensitivityX, 0);
        }
        else
        {
            mouseDelta -= new Vector2(Input.GetAxis("Mouse X") * mouseSensitivityX, 0);
        }

        if (!invertY)
        {
            mouseDelta += new Vector2(0, -Input.GetAxis("Mouse Y") * mouseSensitivityY);
        }
        else
        {
            mouseDelta -= new Vector2(0, -Input.GetAxis("Mouse Y") * mouseSensitivityY);
        }

        if (!thirdPerson)
        {
            mouseDelta.y = Mathf.Clamp(mouseDelta.y, firstPersonCameraClamp.x, firstPersonCameraClamp.y);
        }
        else
        {
            mouseDelta.y = Mathf.Clamp(mouseDelta.y, thirdPersonCameraClamp.x, thirdPersonCameraClamp.y);
        }
    }

    private void CameraPosition()
    {
        // Camera Position
        if (!thirdPerson)
        {
            Camera.transform.parent = transform;
            Camera.transform.localPosition = firstPersonCameraDistance;
        }
        else
        {
            Camera.transform.parent = null;
            Camera.transform.position = transform.position;
            Camera.transform.Translate(thirdPersonCameraDistance);

            RaycastHit hit;

            Vector3 cameraRotation = Camera.transform.eulerAngles;
            Camera.transform.LookAt(transform.position);
            Vector3 direction = Camera.transform.forward;
            Camera.transform.eulerAngles = cameraRotation;

            if (Physics.Raycast(transform.position, -direction, out hit, Mathf.Abs(Vector3.Distance(Camera.transform.position, transform.position)), 1, QueryTriggerInteraction.Ignore))
            {
                Camera.transform.position = hit.point;
                Camera.transform.Translate(new Vector3(0, 0, cameraObstructedDistance));
            }
        }
    }

    private void CameraRotation()
    {
        // Camera Rotation
        if (!thirdPerson)
        {
            transform.eulerAngles = new Vector3(transform.eulerAngles.x, mouseDelta.x, transform.eulerAngles.z);
            Camera.transform.eulerAngles = new Vector3(mouseDelta.y, transform.eulerAngles.y, Camera.transform.eulerAngles.z);
        }
        else
        {
            Camera.transform.eulerAngles = new Vector3(mouseDelta.y, mouseDelta.x, transform.eulerAngles.z);
        }
    }

    private void HeadBob()
    {
        if (!thirdPerson)
        {
            if (Rigidbody.velocity.x != 0 || Rigidbody.velocity.z != 0)
            {
                bobTime += Time.deltaTime;
                Camera.transform.localPosition += new Vector3(0, Mathf.Sin(bobTime * bobSpeed) * bobHeight, 0);
            }
        }
    }

    private void Jumping()
    {
        // Jumping
        Physics.gravity = gravity;

        isGrounded = Physics.BoxCast(new Vector3(transform.position.x, transform.position.y - transform.lossyScale.y / 2 + jumpCheckHeight, transform.position.z), new Vector3(transform.lossyScale.x / 2 * jumpCheckWidth, 0, transform.lossyScale.z / 2 * jumpCheckWidth), -Vector3.up, Quaternion.identity, jumpCheckHeight + jumpCheckDepth, 1, QueryTriggerInteraction.Ignore);

        if (Input.GetKeyDown(KeyCode.Space) && isGrounded && canJump)
        {
            Rigidbody.velocity = new Vector3(Rigidbody.velocity.x, 0, Rigidbody.velocity.z);
            Rigidbody.angularVelocity = Vector3.zero;
            Rigidbody.AddForce(new Vector3(0, jumpForce * Rigidbody.mass, 0), ForceMode.Impulse);
        }
    }

    private void Sprinting()
    {
        // Sprinting
        if (Input.GetKeyDown(KeyCode.LeftShift) && toggleSprint && canSprint)
        {
            isSprinting = !isSprinting;
        }
        else if (Input.GetKey(KeyCode.LeftShift) && !toggleSprint && canSprint)
        {
            isSprinting = true;
        }
        else if (!toggleSprint || !canSprint)
        {
            isSprinting = false;
        }

        if (isSprinting && canSprint && !isCrouching)
        {
            currentSpeed = Mathf.Lerp(currentSpeed, speed * sprintModifer, sprintAcceleration * Time.deltaTime);
        }
        else if (isCrouching)
        {
            currentSpeed = Mathf.Lerp(currentSpeed, speed * crouchSpeed, crouchTime * Time.deltaTime);
        }
        else
        {
            currentSpeed = Mathf.Lerp(currentSpeed, speed, sprintAcceleration * Time.deltaTime);
        }
    }

    private void Crouching()
    {
        // Crouching
        if (Input.GetKeyDown(KeyCode.LeftControl) && toggleCrouch && canCrouch)
        {
            isCrouching = !isCrouching;
        }
        else if (Input.GetKey(KeyCode.LeftControl) && !toggleCrouch && canCrouch)
        {
            isCrouching = true;
        }
        else if (!toggleCrouch || !canCrouch)
        {
            isCrouching = false;
        }

        if (isCrouching && canCrouch)
        {
            transform.localScale = new Vector3(transform.localScale.x, Mathf.Lerp(transform.localScale.y, startingScale * crouchModifier, crouchTime * Time.deltaTime), transform.localScale.z);
        }
        else
        {
            transform.localScale = new Vector3(transform.localScale.x, Mathf.Lerp(transform.localScale.y, startingScale, crouchTime * Time.deltaTime), transform.localScale.z);
        }
    }

    private void RestartAndExit()
    {
        // Restart and Exit
        if (Input.GetKeyDown(KeyCode.Backspace) && canRestart)
        {
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }

        if (Input.GetKeyDown(KeyCode.Escape) && canExit)
        {
            Application.Quit();
        }
    }

    public static bool Button(float input)
    {
        if (Mathf.Abs(input) > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    public static bool Button(float input, float threshold)
    {
        if (Mathf.Abs(input) >= Mathf.Abs(threshold))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    public static bool Trigger(float input, float threshold)
    {
        if (Mathf.Abs(input) >= Mathf.Abs(threshold))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
