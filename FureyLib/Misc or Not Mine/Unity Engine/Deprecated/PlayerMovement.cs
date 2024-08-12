
// Legacy Player Movement Script (Deprecated)
// by Kyle Furey

using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.SceneManagement;

/// <summary>
/// Complex movement settings for a shooter game's player character.
/// </summary>
public class Player : MonoBehaviour
{
    // References
    public PlayerInput Input = null;
    public Rigidbody Rigidbody = null;
    public Camera Camera = null;

    // Controls - CAPITALS are direct input values and behavior
    private Vector2 MOVE = Vector2.zero;

    private float LOOK_X = 0;
    private float LOOK_Y = 0;
    [HideInInspector] public float cameraRotationX = 0;
    [HideInInspector] public float cameraRotationY = 0;

    private bool JUMP = false;
    private bool JUMP_UP = true;
    [SerializeField] private float JUMP_COOLDOWN = 0.25f;
    [SerializeField] private float JUMP_COOLDOWN_RESET = 0.25f;
    private float JUMP_COOLDOWN_TIME = 0;

    private bool DODGE = false;
    private bool DODGE_UP = true;
    [SerializeField] private float DODGE_COOLDOWN = 0.75f;
    [SerializeField] private float DODGE_COOLDOWN_RESET = 0.75f;
    private float DODGE_COOLDOWN_TIME = 0;

    private bool CROUCH = false;
    private bool CROUCH_UP = true;
    [SerializeField] private float CROUCH_COOLDOWN = 0;
    [SerializeField] private float CROUCH_COOLDOWN_RESET = 0;
    private float CROUCH_COOLDOWN_TIME = 0;

    private bool SHOOT = false;
    private bool SHOOT_UP = true;
    [SerializeField] private float SHOOT_COOLDOWN = 0;
    [SerializeField] private float SHOOT_COOLDOWN_RESET = 0;
    private float SHOOT_COOLDOWN_TIME = 0;

    private bool AIM = false;
    private bool AIM_UP = true;
    [SerializeField] private float AIM_COOLDOWN = 0;
    [SerializeField] private float AIM_COOLDOWN_RESET = 0;
    private float AIM_COOLDOWN_TIME = 0;

    private bool RELOAD = false;
    private bool RELOAD_UP = true;
    [SerializeField] private float RELOAD_COOLDOWN = 0;
    [SerializeField] private float RELOAD_COOLDOWN_RESET = 0;
    private float RELOAD_COOLDOWN_TIME = 0;

    private bool FLASHLIGHT = false;
    private bool FLASHLIGHT_UP = true;

    private bool WEAPON_LEFT = false;
    private bool WEAPON_LEFT_UP = true;
    [SerializeField] private float WEAPON_LEFT_COOLDOWN = 0;
    [SerializeField] private float WEAPON_LEFT_COOLDOWN_RESET = 0;
    private float WEAPON_LEFT_COOLDOWN_TIME = 0;

    private bool WEAPON_RIGHT = false;
    private bool WEAPON_RIGHT_UP = true;
    [SerializeField] private float WEAPON_RIGHT_COOLDOWN = 0;
    [SerializeField] private float WEAPON_RIGHT_COOLDOWN_RESET = 0;
    private float WEAPON_RIGHT_COOLDOWN_TIME;

    private bool WEAPON_PREVIOUS = false;
    private bool WEAPON_PREVIOUS_UP = true;
    [SerializeField] private float WEAPON_PREVIOUS_COOLDOWN = 0;
    [SerializeField] private float WEAPON_PREVIOUS_COOLDOWN_RESET = 0;
    private float WEAPON_PREVIOUS_COOLDOWN_TIME = 0;

    private bool PRIMARY = false;
    private bool PRIMARY_UP = true;

    private bool SECONDARY = false;
    private bool SECONDARY_UP = true;

    private bool MELEE = false;
    private bool MELEE_UP = true;

    private bool SCOREBOARD = false;

    private bool RESTART = false;
    private bool EXIT = true;

    // Camera Variables
    public bool thirdPerson = false;
    public Vector3 cameraStart = new Vector3(0, 0.8f, 0.25f);
    public Vector3 thirdPersonCameraDistance = new Vector3(0.75f, 0, -2);
    private float cameraYaw = 0;
    [SerializeField] private float firstPersonCameraClamp = 85;
    [SerializeField] private float thirdPersonCameraClamp = 65;
    private bool isMouse = false;
    [SerializeField] private bool forceController = false;
    [SerializeField] private float lookSpeedMouse = 0.25f;
    [SerializeField] private float lookSpeedX = 150;
    [SerializeField] private float lookSpeedY = 100;
    [SerializeField] private float lookSpeedModifier = 1;

    // Flick Stick
    [SerializeField] private bool flickStick = false;
    private float flickStickRotation = 0;
    [SerializeField] private float flickStickDeadzone = 0.25f;

    // Movement Variables
    [SerializeField] private float moveSpeed = 10;
    [SerializeField] private float moveSpeedModifier = 1;
    [SerializeField] private float moveLerpSpeed = 10;
    private Vector3 movement = Vector3.zero;
    private Vector3 lastStablePosition = Vector3.zero;

    // Jumping Variables
    private bool isGrounded = true;
    [SerializeField] private float jumpForce = 12;
    private float airTime = 0;
    [SerializeField] private float coyoteTime = 0.25f;
    [SerializeField] private bool canDoubleJump = false;
    private int currentJump = 0;
    private int maxJumps = 1;
    [SerializeField] private float jumpCheckHeight = 0.15f;
    [SerializeField] private float jumpCheckWidth = 0.9f;
    [SerializeField] private float jumpCheckDepth = 0.2f;

    // Air Control Variables
    [SerializeField] private float airControl = 0.4f;
    private Vector3 airVelocity = Vector3.zero;
    private Vector3 highestVelocity = Vector3.zero;
    [SerializeField] private bool rotateVelocity = true;
    [SerializeField] private float velocityRotationScale = 1;

    // Bunny Hop Variables
    [SerializeField] private bool canBunnyHop = true;
    private bool bunnyHopFrame = false;
    private Vector3 bunnyHopVelocity = Vector3.zero;
    [SerializeField] private float bunnyHopWindow = 0.1f;
    private bool isBunnyHopping = false;
    [SerializeField] private bool bunnyHopAcceleration = true;
    [SerializeField] private float bunnyHopModifier = 1.1f;
    [SerializeField] private float bunnyHopCap = 15;
    [SerializeField] private bool canAimBunnyHop = false;
    [SerializeField] private bool bunnyHopResetsJump = true;
    private float bunnyHopYaw = 0;

    // Dodging Variables
    [SerializeField] private bool canDodge = true;
    private bool isDodging = false;
    [SerializeField] private float dodgeForceGround = 5;
    [SerializeField] private float dodgeForceVertical = 8;
    [SerializeField] private float dodgeForceAir = 5;
    [SerializeField] private float dodgeCapHorizontal = 15;
    [SerializeField] private float dodgeCapVertical = 8;
    [SerializeField] private bool idleDodgeDive = true;
    [SerializeField] private bool movingDodgeDive = true;
    [SerializeField] private bool canDodgeIntoBunnyHop = false;
    [SerializeField] private bool canDodgeAfterBunnyHop = false;
    [SerializeField] private bool canLunge = true;
    [SerializeField] private float lungeCapHorizontal = 18;
    [SerializeField] private float lungeCapVertical = 10;

    // Flashlight
    [SerializeField] private Light flashlight = null;

    // Weapon Variables
    public int weapon = 0;

    // Debug
    [SerializeField] private bool debugVelocity = false;

    // Player Variables
    public int playerNumber = 1;
    public int team = 1;

    public bool play = true;

    private void Start()
    {
        Cursor.lockState = CursorLockMode.Locked;

        playerNumber = Input.playerIndex + 1;
    }

    private void Update()
    {
        if (play)
        {
            GetControls();
            CameraPosition();
            GroundCheck();
            Jumping();
            Dodging();
        }

        ExitGame();
    }

    private void FixedUpdate()
    {
        if (play)
        {
            Movement();
            CameraRotation();
            RotateVelocity();
        }

        DebugVelocity();
    }

    private void OnTriggerEnter(Collider other)
    {
        // Falling Out of World
        if (other.tag == "Fall Boundary")
        {
            transform.position = lastStablePosition;

            Rigidbody.velocity = Vector3.zero;
            airVelocity = Vector3.zero;
        }
    }

    private void GetControls()
    {
        // Controls
        MOVE = Input.actions.FindAction("Move").ReadValue<Vector2>();
        JUMP = Button(Input.actions.FindAction("Jump").ReadValue<float>());
        DODGE = Button(Input.actions.FindAction("Dodge").ReadValue<float>());
        CROUCH = Button(Input.actions.FindAction("Crouch").ReadValue<float>());
        SHOOT = Button(Input.actions.FindAction("Shoot").ReadValue<float>());
        AIM = Button(Input.actions.FindAction("Aim").ReadValue<float>());
        RELOAD = Button(Input.actions.FindAction("Reload").ReadValue<float>());
        FLASHLIGHT = Button(Input.actions.FindAction("Flashlight").ReadValue<float>());
        WEAPON_LEFT = Button(Input.actions.FindAction("Weapon Left").ReadValue<float>());
        WEAPON_RIGHT = Button(Input.actions.FindAction("Weapon Right").ReadValue<float>());
        WEAPON_PREVIOUS = Button(Input.actions.FindAction("Previous Weapon").ReadValue<float>());
        PRIMARY = Button(Input.actions.FindAction("Primary").ReadValue<float>());
        SECONDARY = Button(Input.actions.FindAction("Secondary").ReadValue<float>());
        MELEE = Button(Input.actions.FindAction("Melee").ReadValue<float>());
        SCOREBOARD = Button(Input.actions.FindAction("Scoreboard").ReadValue<float>());


        // Button Behavior
        if (!JUMP)
        {
            JUMP_UP = true;
        }

        if (JUMP_COOLDOWN != 0)
        {
            if (JUMP_UP && JUMP_COOLDOWN_TIME > JUMP_COOLDOWN_RESET)
            {
                JUMP_COOLDOWN_TIME = JUMP_COOLDOWN_RESET;
            }

            if (JUMP_COOLDOWN_TIME > 0)
            {
                JUMP_COOLDOWN_TIME -= Time.deltaTime;
            }
            else
            {
                JUMP_COOLDOWN_TIME = 0;
            }
        }

        if (!DODGE)
        {
            DODGE_UP = true;
        }

        if (DODGE_COOLDOWN != 0)
        {
            if (DODGE_UP && DODGE_COOLDOWN_TIME > DODGE_COOLDOWN_RESET)
            {
                DODGE_COOLDOWN_TIME = DODGE_COOLDOWN_RESET;
            }

            if (DODGE_COOLDOWN_TIME > 0)
            {
                DODGE_COOLDOWN_TIME -= Time.deltaTime;
            }
            else
            {
                DODGE_COOLDOWN_TIME = 0;
            }
        }

        if (!CROUCH)
        {
            CROUCH_UP = true;
        }

        if (CROUCH_COOLDOWN != 0)
        {
            if (CROUCH_UP && CROUCH_COOLDOWN_TIME > CROUCH_COOLDOWN_RESET)
            {
                CROUCH_COOLDOWN_TIME = CROUCH_COOLDOWN_RESET;
            }

            if (CROUCH_COOLDOWN_TIME > 0)
            {
                CROUCH_COOLDOWN_TIME -= Time.deltaTime;
            }
            else
            {
                CROUCH_COOLDOWN_TIME = 0;
            }
        }

        if (!SHOOT)
        {
            SHOOT_UP = true;
        }

        if (SHOOT_COOLDOWN != 0)
        {
            if (SHOOT_UP && SHOOT_COOLDOWN_TIME > SHOOT_COOLDOWN_RESET)
            {
                SHOOT_COOLDOWN_TIME = SHOOT_COOLDOWN_RESET;
            }

            if (SHOOT_COOLDOWN_TIME > 0)
            {
                SHOOT_COOLDOWN_TIME -= Time.deltaTime;
            }
            else
            {
                SHOOT_COOLDOWN_TIME = 0;
            }
        }

        if (!AIM)
        {
            AIM_UP = true;
        }

        if (AIM_COOLDOWN != 0)
        {
            if (AIM_UP && AIM_COOLDOWN_TIME > AIM_COOLDOWN_RESET)
            {
                AIM_COOLDOWN_TIME = AIM_COOLDOWN_RESET;
            }

            if (AIM_COOLDOWN_TIME > 0)
            {
                AIM_COOLDOWN_TIME -= Time.deltaTime;
            }
            else
            {
                AIM_COOLDOWN_TIME = 0;
            }
        }

        if (!RELOAD)
        {
            RELOAD_UP = true;
        }

        if (RELOAD_COOLDOWN != 0)
        {
            if (RELOAD_UP && RELOAD_COOLDOWN_TIME > RELOAD_COOLDOWN_RESET)
            {
                RELOAD_COOLDOWN_TIME = RELOAD_COOLDOWN_RESET;
            }

            if (RELOAD_COOLDOWN_TIME > 0)
            {
                RELOAD_COOLDOWN_TIME -= Time.deltaTime;
            }
            else
            {
                RELOAD_COOLDOWN_TIME = 0;
            }
        }

        if (!FLASHLIGHT)
        {
            FLASHLIGHT_UP = true;
        }

        if (!WEAPON_LEFT)
        {
            WEAPON_LEFT_UP = true;
        }

        if (WEAPON_LEFT_COOLDOWN != 0)
        {
            if (WEAPON_LEFT_UP && WEAPON_LEFT_COOLDOWN_TIME > WEAPON_LEFT_COOLDOWN_RESET)
            {
                WEAPON_LEFT_COOLDOWN_TIME = WEAPON_LEFT_COOLDOWN_RESET;
            }

            if (WEAPON_LEFT_COOLDOWN_TIME > 0)
            {
                WEAPON_LEFT_COOLDOWN_TIME -= Time.deltaTime;
            }
            else
            {
                WEAPON_LEFT_COOLDOWN_TIME = 0;
            }
        }

        if (!WEAPON_RIGHT)
        {
            WEAPON_RIGHT_UP = true;
        }

        if (WEAPON_RIGHT_COOLDOWN != 0)
        {
            if (WEAPON_RIGHT_UP && WEAPON_RIGHT_COOLDOWN_TIME > WEAPON_RIGHT_COOLDOWN_RESET)
            {
                WEAPON_RIGHT_COOLDOWN_TIME = WEAPON_RIGHT_COOLDOWN_RESET;
            }

            if (WEAPON_RIGHT_COOLDOWN_TIME > 0)
            {
                WEAPON_RIGHT_COOLDOWN_TIME -= Time.deltaTime;
            }
            else
            {
                WEAPON_RIGHT_COOLDOWN_TIME = 0;
            }
        }

        if (!WEAPON_PREVIOUS)
        {
            WEAPON_PREVIOUS_UP = true;
        }

        if (WEAPON_PREVIOUS_COOLDOWN != 0)
        {
            if (WEAPON_PREVIOUS_UP && WEAPON_PREVIOUS_COOLDOWN_TIME > WEAPON_PREVIOUS_COOLDOWN_RESET)
            {
                WEAPON_PREVIOUS_COOLDOWN_TIME = WEAPON_PREVIOUS_COOLDOWN_RESET;
            }

            if (WEAPON_PREVIOUS_COOLDOWN_TIME > 0)
            {
                WEAPON_PREVIOUS_COOLDOWN_TIME -= Time.deltaTime;
            }
            else
            {
                WEAPON_PREVIOUS_COOLDOWN_TIME = 0;
            }
        }

        if (!PRIMARY)
        {
            PRIMARY_UP = true;
        }

        if (!SECONDARY)
        {
            SECONDARY_UP = true;
        }

        if (!MELEE)
        {
            MELEE_UP = true;
        }


        // Button Pressed

        // CROUCH_UP = false;
        // CROUCH_COOLDOWN_TIME = CROUCH_COOLDOWN;

        // SHOOT_UP = false;
        // SHOOT_COOLDOWN_TIME = SHOOT_COOLDOWN;

        // AIM_UP = false;
        // AIM_COOLDOWN_TIME = AIM_COOLDOWN;

        // WEAPON_LEFT_UP = false;
        // WEAPON_LEFT_COOLDOWN_TIME = WEAPON_RIGHT_COOLDOWN;

        // WEAPON_RIGHT_UP = false;
        // WEAPON_RIGHT_COOLDOWN_TIME = WEAPON_RIGHT_COOLDOWN;


        // Mouse and Controller Input
        if (Input.GetDevice<Mouse>() != null && !forceController)
        {
            isMouse = true;

            // Mouse
            LOOK_X = Input.actions.FindAction("Look X").ReadValue<float>() * lookSpeedMouse * lookSpeedModifier;
            LOOK_Y = Input.actions.FindAction("Look Y").ReadValue<float>() * lookSpeedMouse * lookSpeedModifier;
        }
        else
        {
            isMouse = false;

            if (!flickStick)
            {
                // Controller
                LOOK_X = Input.actions.FindAction("Look X").ReadValue<float>() * lookSpeedX * lookSpeedModifier * Time.deltaTime;
                LOOK_Y = Input.actions.FindAction("Look Y").ReadValue<float>() * lookSpeedY * lookSpeedModifier * Time.deltaTime;
            }
            else
            {
                // Controller (Flick Stick)
                LOOK_X = Input.actions.FindAction("Look X").ReadValue<float>();
                LOOK_Y = Input.actions.FindAction("Look Y").ReadValue<float>();
            }
        }

        // Flashlight
        if (FLASHLIGHT && FLASHLIGHT_UP)
        {
            FLASHLIGHT_UP = false;

            flashlight.enabled = !flashlight.enabled;
        }

        // Movement Input
        Vector3 forward = MOVE.y * transform.forward * moveSpeed * moveSpeedModifier;
        Vector3 right = MOVE.x * transform.right * moveSpeed * moveSpeedModifier;
        movement = forward + right;
    }

    private void CameraPosition()
    {
        // Camera Position
        Camera.transform.position = transform.position + (transform.right * cameraStart.x + Vector3.up * cameraStart.y + transform.forward * cameraStart.z);

        if (thirdPerson)
        {
            Camera.transform.Translate(thirdPersonCameraDistance);

            RaycastHit hit;

            Vector3 cameraRotation = Camera.transform.eulerAngles;
            Camera.transform.LookAt(transform.position);
            Vector3 direction = Camera.transform.forward;
            Camera.transform.eulerAngles = cameraRotation;

            if (Physics.Raycast(transform.position, -direction, out hit, Mathf.Abs(Vector3.Distance(Camera.transform.position, transform.position)), 1, QueryTriggerInteraction.Ignore))
            {
                Camera.transform.position = hit.point;
            }
        }


        // Camera Clamp
        cameraRotationX += LOOK_X;
        cameraRotationY -= LOOK_Y;

        if (!thirdPerson)
        {
            cameraRotationY = Mathf.Clamp(cameraRotationY, -firstPersonCameraClamp, firstPersonCameraClamp);
        }
        else
        {
            cameraRotationY = Mathf.Clamp(cameraRotationY, -thirdPersonCameraClamp, thirdPersonCameraClamp);
        }
    }

    private void CameraRotation()
    {
        // Camera Rotation
        if (!flickStick)
        {
            cameraYaw = Camera.transform.eulerAngles.y;
            Camera.transform.rotation = Quaternion.Euler(cameraRotationY, cameraRotationX, 0);
        }
        else
        {
            // Flick Stick
            if (Mathf.Abs(LOOK_X) >= flickStickDeadzone || Mathf.Abs(LOOK_Y) >= flickStickDeadzone)
            {
                Camera.transform.eulerAngles = new Vector3(0, flickStickRotation + Mathf.Atan2(LOOK_X, LOOK_Y) * Mathf.Rad2Deg, 0);
            }
            else
            {
                flickStickRotation = Camera.transform.eulerAngles.y;
            }
        }
    }

    private void Movement()
    {
        // Movement
        float fallingSpeed = Rigidbody.velocity.y;

        if (isGrounded && !bunnyHopFrame)
        {
            // Ground Movement
            Rigidbody.velocity = Vector3.Lerp(Rigidbody.velocity, movement, moveLerpSpeed * Time.deltaTime);
        }
        else
        {
            // Air Movement
            Rigidbody.velocity = airVelocity - airVelocity * airControl;

            Rigidbody.velocity += movement * airControl;
        }

        Rigidbody.velocity = new Vector3(Rigidbody.velocity.x, fallingSpeed, Rigidbody.velocity.z);
    }

    private void GroundCheck()
    {
        if (isGrounded && Physics.BoxCast(new Vector3(transform.position.x, transform.position.y - transform.lossyScale.y / 2 + jumpCheckHeight, transform.position.z), new Vector3(transform.lossyScale.x / 2 * jumpCheckWidth, 0, transform.lossyScale.z / 2 * jumpCheckWidth), -Vector3.up, Quaternion.identity, jumpCheckHeight + jumpCheckDepth, 1, QueryTriggerInteraction.Ignore))
        {
            // On Ground
            isGrounded = true;

            lastStablePosition = new Vector3(transform.position.x, transform.position.y + cameraStart.y * 2, transform.position.z);

            if (!bunnyHopFrame)
            {
                isBunnyHopping = false;
            }
        }
        else if (!isGrounded && !Physics.BoxCast(new Vector3(transform.position.x, transform.position.y - transform.lossyScale.y / 2 + jumpCheckHeight, transform.position.z), new Vector3(transform.lossyScale.x / 2 * jumpCheckWidth, 0, transform.lossyScale.z / 2 * jumpCheckWidth), -Vector3.up, Quaternion.identity, jumpCheckHeight + jumpCheckDepth))
        {
            // Off Ground
        }
        else if (!isGrounded && Physics.BoxCast(new Vector3(transform.position.x, transform.position.y - transform.lossyScale.y / 2 + jumpCheckHeight, transform.position.z), new Vector3(transform.lossyScale.x / 2 * jumpCheckWidth, 0, transform.lossyScale.z / 2 * jumpCheckWidth), -Vector3.up, Quaternion.identity, jumpCheckHeight + jumpCheckDepth))
        {
            // Entering Ground
            isGrounded = true;

            lastStablePosition = new Vector3(transform.position.x, transform.position.y + cameraStart.y * 2, transform.position.z);

            if (bunnyHopResetsJump)
            {
                currentJump = 0;
            }
            else
            {
                currentJump = maxJumps;
            }

            JUMP_COOLDOWN_TIME = JUMP_COOLDOWN;

            airTime = 0;

            bunnyHopFrame = true;

            Invoke("BunnyHopFrame", bunnyHopWindow);

            if (canDodgeIntoBunnyHop)
            {
                isDodging = false;
            }
        }
        else if (isGrounded && !Physics.BoxCast(new Vector3(transform.position.x, transform.position.y - transform.lossyScale.y / 2 + jumpCheckHeight, transform.position.z), new Vector3(transform.lossyScale.x / 2 * jumpCheckWidth, 0, transform.lossyScale.z / 2 * jumpCheckWidth), -Vector3.up, Quaternion.identity, jumpCheckHeight + jumpCheckDepth))
        {
            // Leaving Ground
            isGrounded = false;

            airVelocity = Rigidbody.velocity;
        }
    }

    private void Jumping()
    {
        // Double Jump
        if (canDoubleJump)
        {
            maxJumps = 2;
        }
        else
        {
            maxJumps = 1;
        }

        // Jumping
        if (JUMP && JUMP_UP && (isGrounded || (airTime < coyoteTime && currentJump == 0) || (currentJump < maxJumps)) && (JUMP_COOLDOWN_TIME <= 0 || (canBunnyHop && bunnyHopFrame)) && (canDodgeIntoBunnyHop || !isDodging))
        {
            JUMP_UP = false;

            // Bunny Hopping
            if (canBunnyHop && bunnyHopFrame && (canDodgeIntoBunnyHop || !isDodging))
            {
                isBunnyHopping = true;

                Rigidbody.velocity = new Vector3(bunnyHopVelocity.x, Rigidbody.velocity.y, bunnyHopVelocity.z);

                if (canAimBunnyHop)
                {
                    Rigidbody.velocity = Quaternion.Euler(0, (Camera.transform.eulerAngles.y - bunnyHopYaw), 0) * Rigidbody.velocity;
                }
            }
            else
            {
                Rigidbody.velocity = new Vector3(movement.x, 0, movement.z);
            }

            Rigidbody.AddForce(new Vector3(0, jumpForce * Rigidbody.mass, 0), ForceMode.Impulse);

            airTime = 0;

            currentJump += 1;

            // Bunny Hop Acceleration
            if (bunnyHopAcceleration && isBunnyHopping)
            {
                if (Mathf.Abs(Rigidbody.velocity.x) < bunnyHopCap * moveSpeedModifier && Mathf.Abs(Rigidbody.velocity.z) < bunnyHopCap * moveSpeedModifier)
                {
                    Rigidbody.velocity = new Vector3(Mathf.Clamp(Rigidbody.velocity.x * bunnyHopModifier, -bunnyHopCap * moveSpeedModifier, bunnyHopCap * moveSpeedModifier), Rigidbody.velocity.y, Mathf.Clamp(Rigidbody.velocity.z * bunnyHopModifier, -bunnyHopCap, bunnyHopCap));
                }
            }

            bunnyHopVelocity = Rigidbody.velocity;
            bunnyHopYaw = Camera.transform.eulerAngles.y;
        }
        else if (JUMP && JUMP_UP)
        {
            JUMP_UP = false;
        }

        // Airtime
        if (!isGrounded)
        {
            airTime += Time.deltaTime;

            if (coyoteTime < airTime && currentJump < 1)
            {
                currentJump++;
            }
        }
    }

    private void BunnyHopFrame()
    {
        if (isGrounded || currentJump < maxJumps)
        {
            bunnyHopFrame = false;

            if (!canDodgeIntoBunnyHop)
            {
                isDodging = false;
            }

            if (!bunnyHopResetsJump)
            {
                currentJump = 0;
            }
        }
    }

    private void Dodging()
    {
        if (canDodge && DODGE && DODGE_UP && DODGE_COOLDOWN_TIME <= 0 && !isDodging && (canDodgeAfterBunnyHop || !isBunnyHopping))
        {
            DODGE_UP = false;

            DODGE_COOLDOWN_TIME = DODGE_COOLDOWN;

            isDodging = true;

            if (isGrounded)
            {
                // Dodging on Ground
                Rigidbody.velocity = new Vector3(Rigidbody.velocity.x, 0, Rigidbody.velocity.z);
                transform.Translate(0, .1f, 0);

                if (Mathf.Abs(movement.x) > 0 || Mathf.Abs(movement.z) > 0)
                {
                    Rigidbody.velocity += new Vector3(movement.x * dodgeForceGround / moveSpeed, dodgeForceVertical, movement.z * dodgeForceGround / moveSpeed);
                }
                else
                {
                    Rigidbody.velocity += transform.forward * (dodgeForceGround + moveSpeed * moveSpeedModifier);
                    Rigidbody.velocity += new Vector3(0, dodgeForceVertical, 0);
                }
            }
            else
            {
                // Dodging in Air
                if (Mathf.Abs(movement.x) > 0 || Mathf.Abs(movement.z) > 0)
                {
                    if (movingDodgeDive)
                    {
                        Rigidbody.velocity = Vector3.zero;
                    }
                    else
                    {
                        Rigidbody.velocity = new Vector3(0, Rigidbody.velocity.y, 0);
                    }

                    Rigidbody.velocity += new Vector3(movement.x * dodgeForceAir / moveSpeed, 0, movement.z * dodgeForceAir / moveSpeed) * 4;
                }
                else
                {
                    if (idleDodgeDive)
                    {
                        Rigidbody.velocity = Vector3.zero;
                    }
                    else
                    {
                        Rigidbody.velocity = new Vector3(0, Rigidbody.velocity.y, 0);
                    }

                    Rigidbody.velocity += transform.forward * (dodgeForceAir + moveSpeed * moveSpeedModifier);
                }

                airVelocity = Rigidbody.velocity;
            }
        }

        // Dodge and Lunge Control
        if (isDodging)
        {
            if (canLunge)
            {
                Rigidbody.velocity = new Vector3(Mathf.Clamp(Rigidbody.velocity.x, -lungeCapHorizontal, lungeCapHorizontal), Mathf.Clamp(Rigidbody.velocity.y, Rigidbody.velocity.y, lungeCapVertical), Mathf.Clamp(Rigidbody.velocity.z, -lungeCapHorizontal, lungeCapHorizontal));
            }
            else
            {
                Rigidbody.velocity = new Vector3(Mathf.Clamp(Rigidbody.velocity.x, -dodgeCapHorizontal, dodgeCapHorizontal), Mathf.Clamp(Rigidbody.velocity.y, Rigidbody.velocity.y, dodgeCapVertical), Mathf.Clamp(Rigidbody.velocity.z, -dodgeCapHorizontal, dodgeCapHorizontal));
            }

            bunnyHopVelocity = Rigidbody.velocity;
            bunnyHopYaw = Camera.transform.eulerAngles.y;
        }
    }

    private void RotateVelocity()
    {
        // Rotate Velocity
        if (rotateVelocity && !isGrounded && (!isBunnyHopping || canAimBunnyHop))
        {
            Rigidbody.velocity = Quaternion.Euler(0, (Camera.transform.eulerAngles.y - cameraYaw) * velocityRotationScale, 0) * Rigidbody.velocity;
            airVelocity = Quaternion.Euler(0, (Camera.transform.eulerAngles.y - cameraYaw) * velocityRotationScale, 0) * airVelocity;
        }
    }

    private void ExitGame()
    {
        // Restart and Exit
        RESTART = Button(Input.actions.FindAction("Restart").ReadValue<float>());
        EXIT = Button(Input.actions.FindAction("Exit").ReadValue<float>());

        if (EXIT)
        {
            Application.Quit();
        }
        else if (RESTART && play)
        {
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }
    }

    private void DebugVelocity()
    {
        if (debugVelocity)
        {
            // Record the Greatest Velocity and Print It
            if (Mathf.Abs(Rigidbody.velocity.x) > highestVelocity.x)
            {
                highestVelocity = new Vector3(Mathf.Abs(Rigidbody.velocity.x), highestVelocity.y, highestVelocity.z);
                print("Player " + playerNumber + "'s Highest Velocity: " + highestVelocity);
            }

            if (Mathf.Abs(Rigidbody.velocity.y) > highestVelocity.y)
            {
                highestVelocity = new Vector3(highestVelocity.x, Mathf.Abs(Rigidbody.velocity.y), highestVelocity.z);
                print("Player " + playerNumber + "'s Highest Velocity: " + highestVelocity);
            }

            if (Mathf.Abs(Rigidbody.velocity.z) > highestVelocity.z)
            {
                highestVelocity = new Vector3(highestVelocity.x, highestVelocity.y, Mathf.Abs(Rigidbody.velocity.z));
                print("Player " + playerNumber + "'s Highest Velocity: " + highestVelocity);
            }
        }
    }

    private bool Button(float input)
    {
        if (input > 0)
        {
            return true;
        }

        return false;
    }

    private bool Button(float input, float threshold)
    {
        if (input > threshold)
        {
            return true;
        }

        return false;
    }

    private bool Trigger(float input, float threshold)
    {
        if (input > threshold)
        {
            return true;
        }

        return false;
    }
}
