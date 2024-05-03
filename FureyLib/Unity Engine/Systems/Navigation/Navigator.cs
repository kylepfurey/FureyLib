
// Navigation Entity Script
// by Kyle Furey

namespace Navigation
{
    using System.Collections.Generic;
    using UnityEngine;
    using UnityEngine.Events;

    using static Pathfinding;

    // A base AI controller and settings for a game object that will move across generated navigation meshes.
    public class Navigator : MonoBehaviour
    {
        [Header("A base AI controller and settings for a game object that will move across generated Navigation Meshes.")]

        [Header("\nNAVIGATOR MOVING ENABLED:")]
        public bool canMove = true;

        [Header("\nSPEED AND ROTATION")]

        [Header("The speed this object will move across baked navigation meshes:")]
        public float movementSpeed = 15;

        [Header("The directions to move when moving towards the target:")]
        public bool moveX = true;
        public bool moveY = false;
        public bool moveZ = true;

        [Header("The lerp speed for this object's rotation towards its current target:")]
        public float rotationSpeed = 10;

        [Header("The rotated axis when rotating towards the target:")]
        public bool rotateX = false;
        public bool rotateY = true;
        public bool rotateZ = false;

        [Header("\nTARGET POSITION")]

        [Header("The search algorithm to use for this object's pathfinding:")]
        public Algorithm pathfindingAlgorithm = Algorithm.AStar;

        [Header("The heuristic scale used for A Star pathfinding:")]
        public float heuristicScale = 1;

        // The remaining target positions for this Navigator to go towards
        private List<Vector3> targetPositions = new List<Vector3>();

        [Header("The max distance to the current target position before it moves to the next target position:")]
        public float minTargetPositionDistance = 1;

        [Header("The max distance to the final target position before it has reached the target position:")]
        public float minGoalDistance = 3;

        [Header("Whether to shortcut to the goal when it is closer than the next target position:")]
        public bool shortcut = true;

        [Header("\nFOLLOWING OBJECT")]

        [Header("Whether to follow the target object:")]
        public bool followObject = true;

        [Header("The target object for this Navigator to follow:")]
        public GameObject followedObject = null;

        [Header("Whether to dynamically update the follow update time based on distance:")]
        public bool dynamicFollow = true;

        [Header("The maximum time in seconds before updating the target position to the followed object's position:")]
        public float followUpdateTime = 1;

        [Header("The maximum distance used to calculate how much time remains before updating the target position to the followed object's position:")]
        public float followUpdateDistance = 75;

        [Header("The maximum distance the followed object must travel to consider recalculating:")]
        public float followUpdateMovement = 1;

        // The following timer
        private float followTimer = 0;

        // The following position to check for distance
        private Vector3 followPosition = Vector3.zero;

        [Header("Whether to stop following an object when it is reached:")]
        public bool stopFollowingOnReachedTarget = false;

        [Header("Whether to stop following an object when it is out of range:")]
        public bool stopFollowingWhenOutOfRange = false;

        [Header("The maximum range before stopping following an object:")]
        public float followRange = 20;

        [Header("\nHOME OBJECT")]

        [Header("The home object for this Navigator to go to when no follow object is set:")]
        public GameObject homeObject = null;

        [Header("Whether to go to the home object's position when no follow object is set:")]
        public bool goHomeWhenNoTargetIsSet = false;

        [Header("Whether to stop following the target and return to the home object's position when out of range of the target:")]
        public bool returnHomeWhenOutOfRange = false;

        [Header("The maximum range before returning home:")]
        public float homeRange = 20;

        [Header("The delay in seconds before having this object go home when no follow object is set:")]
        public float homeDelay = 2;

        [Header("\nUNITY EVENTS")]
        public UnityEvent beginNavigationEvents = null;
        public UnityEvent whileNavigatingEvents = null;
        public UnityEvent reachedTargetEvents = null;
        public UnityEvent stopEvents = null;


        // MOVEMENT

        // Move the object to the next position and check navigation settings
        private void Update()
        {
            // Check if we can move
            if (canMove)
            {
                // Update the followed object's path
                UpdateFollow();

                // Check if we have not reached the target
                if (targetPositions.Count > 0)
                {
                    // Check if we made it to the target position
                    GoalCheck();
                }
            }
        }

        // Update the followed object's path
        private void UpdateFollow()
        {
            // Check if we are following a target object
            if (followObject && followedObject != null)
            {
                // Check if we are in range of the home object
                if (!returnHomeWhenOutOfRange || homeObject == null || DistanceSquared(transform.position, homeObject.transform.position) <= homeRange * homeRange)
                {
                    // Check that we are in range of the target object
                    if (!stopFollowingWhenOutOfRange || DistanceSquared(transform.position, followedObject.transform.position) <= followRange * followRange)
                    {
                        // Decrement the timer
                        followTimer -= Time.deltaTime;

                        // Check if it is time to update our path to the target
                        if (followTimer <= 0 && DistanceSquared(followPosition, followedObject.transform.position) > followUpdateMovement * followUpdateMovement)
                        {
                            // Pathfind to the followed object
                            Navigate(followedObject.transform.position);
                        }
                    }
                    else
                    {
                        // Stop following when out of range
                        StopFollowing();
                    }
                }
                else
                {
                    // Return home when out of range
                    StopFollowing();
                }
            }
            else
            {
                // Stop trying to follow if we are not able to follow
                followObject = false;

                // Go home if we have no target set
                if (goHomeWhenNoTargetIsSet && homeObject != null)
                {
                    Invoke("GoHome", homeDelay);
                }
            }
        }

        // Check if we made it to the target position
        private void GoalCheck()
        {
            // Check if we made it to the target position
            if (targetPositions.Count > 1 && DistanceSquared(transform.position, targetPositions[0]) <= minTargetPositionDistance * minTargetPositionDistance)
            {
                // Remove the current target position
                targetPositions.RemoveAt(0);

                // Check if the goal is closer than the next target position
                if (shortcut && targetPositions.Count > 1 && DistanceSquared(transform.position, targetPositions[targetPositions.Count - 1]) <= DistanceSquared(transform.position, targetPositions[0]))
                {
                    Vector3 target = targetPositions[targetPositions.Count - 1];

                    targetPositions.Clear();

                    targetPositions.Add(target);
                }
            }
            // Check if we made it to the goal
            else if (targetPositions.Count == 1 && DistanceSquared(transform.position, targetPositions[0]) <= minGoalDistance * minGoalDistance)
            {
                // Call reached target events
                reachedTargetEvents.Invoke();

                // Check if we are following an object
                if (followObject && followedObject != null)
                {
                    // Check if we stop following when we reach our target object
                    if (stopFollowingOnReachedTarget)
                    {
                        StopFollowing();
                    }
                    else
                    {
                        // Pathfind to the followed object
                        Navigate(followedObject.transform.position);
                    }
                }
            }
            // Move, rotate, and call events
            else
            {
                // Move towards the target using lerp or move towards
                Move();

                // Rotate towards the target using lerp or rotate towards
                Rotate();

                // Call navigating events
                whileNavigatingEvents.Invoke();
            }
        }

        // Move towards the target using lerp or move towards
        private void Move()
        {
            // Store current position
            float xPosition = transform.position.x;
            float yPosition = transform.position.y;
            float zPosition = transform.position.z;

            // Move towards the target using move towards
            transform.position = Vector3.MoveTowards(transform.position, targetPositions[0], movementSpeed * Time.deltaTime);

            // Move the unmoved directions back
            transform.position = new Vector3(moveX ? transform.position.x : xPosition, moveY ? transform.position.y : yPosition, moveZ ? transform.position.z : zPosition);
        }

        // Rotate towards the target using lerp or rotate towards
        private void Rotate()
        {
            // Store current rotation
            float xRotation = transform.eulerAngles.x;
            float yRotation = transform.eulerAngles.y;
            float zRotation = transform.eulerAngles.z;

            // Rotate towards the target using lerp
            transform.rotation = Quaternion.Lerp(transform.rotation, Quaternion.LookRotation(targetPositions[0] - transform.position), rotationSpeed * Time.deltaTime);

            // Unrotate any unrotated axis
            transform.eulerAngles = new Vector3(rotateX ? transform.eulerAngles.x : xRotation, rotateY ? transform.eulerAngles.y : yRotation, rotateZ ? transform.eulerAngles.z : zRotation);
        }


        // NAVIGATION METHODS

        // Navigate towards the given position
        public void Navigate(Vector3 targetPosition)
        {
            // Set the next target positions
            targetPositions = NavigationManager.Navigate(transform.position, targetPosition, pathfindingAlgorithm, heuristicScale);

            // Call navigation start events
            beginNavigationEvents.Invoke();

            // Update the time before the next path to the target
            followTimer = dynamicFollow ? Mathf.Min(Percentage(DistanceSquared(transform.position, followedObject.transform.position), 0, followUpdateDistance * followUpdateDistance), 1) * followUpdateTime : followUpdateTime;

            // Update the current following position
            followPosition = targetPosition;
        }

        // Stop navigating
        public void Stop()
        {
            // Clear the target positions
            targetPositions.Clear();

            // Call navigation stop events
            stopEvents.Invoke();
        }

        // Follow the given object
        public void Follow(GameObject objectToFollow = null)
        {
            // Check if the new followed object is set
            if (objectToFollow != null)
            {
                // Begin following
                followObject = true;

                // Update the current followed object
                followedObject = objectToFollow;

                // Pathfind to the followed object
                Navigate(followedObject.transform.position);
            }
            // Check if the current followed object is set
            else if (followedObject != null)
            {
                // Begin following
                followObject = true;

                // Pathfind to the followed object
                Navigate(followedObject.transform.position);
            }
            else
            {
                // Throw an error
                Debug.LogError("Navigator " + gameObject.name + " cannot follow! No followed object is set!");
            }
        }

        // Stop following the followed object
        public void StopFollowing()
        {
            // Stop following
            followObject = false;

            // Clear the target positions
            targetPositions.Clear();

            // Call navigation stop events
            stopEvents.Invoke();

            // Go home if we have no target set
            if (goHomeWhenNoTargetIsSet && homeObject != null)
            {
                Invoke("GoHome", homeDelay);
            }
        }

        // Set the home object
        public void SetHome(GameObject newHome)
        {
            // Update the home object
            homeObject = newHome;
        }

        // Navigate to the home object
        public void GoHome()
        {
            // Check if the home object is set
            if (homeObject != null)
            {
                // Pathfind to the home object
                Navigate(homeObject.transform.position);
            }
            else
            {
                // Throw an error
                Debug.LogError("Navigator " + gameObject.name + " cannot go home! No home is set!");
            }
        }


        // OTHER FUNCTIONS

        // Returns the squared distance between two vector 3s
        private static float DistanceSquared(Vector3 pointA, Vector3 pointB)
        {
            float xDistance = pointA.x - pointB.x;
            float yDistance = pointA.y - pointB.y;
            float zDistance = pointA.z - pointB.z;

            return xDistance * xDistance + yDistance * yDistance + zDistance * zDistance;
        }

        // Returns a percentage relative to a value of a minimum and maximum
        private static float Percentage(float value, float min, float max)
        {
            return (value - min) / (max - min);
        }
    }
}
