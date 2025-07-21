// .cs
// Generic Movement Component
// by Kyle Furey

using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Provides generic movement capabilities for a game object.
/// </summary>
public sealed class GenericMove : MonoBehaviour
{
    // CLASSES

    /// <summary>
    /// A node within a generic move component's path.
    /// </summary>
    [Serializable]
    public class GenericMoveNode
    {
        public float delay = 0.0f;
        public GameObject target = null;
        public float speed = 1.0f;
        public float smoothTime = 1.0f;
        public bool followPosition = true;
        public bool followRotation = true;
        public bool followScale = false;
        [NonSerialized]
        public float currentDelay = 0.0f;
    }


    // VARIABLES

    /// <summary>
    /// An optional rigidbody for generic physics movement.
    /// </summary>
    private new Rigidbody rigidbody = null;

    [Header("Constant motion:")]
    [SerializeField]
    private Vector3 constantSpeed = Vector3.zero;
    [SerializeField]
    private Vector3 constantRotation = Vector3.zero;
    [SerializeField]
    private Vector3 constantScale = Vector3.zero;

    [Header("\nDestruction:")]
    [SerializeField]
    private float destroyAfterSeconds = 0.0f;

    [Header("\nPath:")]
    [SerializeField]
    private float pathSpeedMultiplier = 1.0f;
    [SerializeField]
    private bool loopPath = true;
    [SerializeField]
    private List<GenericMoveNode> path = new List<GenericMoveNode>();
    private int pathIndex = 0;
    private Vector3 positionVelocity = Vector3.zero;
    private Vector3 scaleVelocity = Vector3.zero;
    [SerializeField]
    private float minDistance = 0.05f;
    [SerializeField]
    private float minDegrees = 2.0f;
    [SerializeField]
    private float minScale = 0.05f;

    /// <summary>
    /// Nodes that need to be cleaned up.
    /// </summary>
    private List<GameObject> ownedNodes = new List<GameObject>();


    // EVENTS

    /// <summary>
    /// Optionally destroys this game object after a set amount of time.
    /// </summary>
    private IEnumerator Start()
    {
        // Set rigidbody
        rigidbody = GetComponent<Rigidbody>();

        // Initialize path
        for (int i = 0; i < path.Count; ++i)
        {
            GenericMoveNode node = path[i];
            if (node.target == null)
            {
                path.RemoveAt(i);
                --i;
                continue;
            }
            node.currentDelay = node.delay;
            if (node.target.transform.IsChildOf(transform))
            {
                node.target.transform.parent = transform.parent; // Prevents child targets from constantly moving away
                ownedNodes.Add(node.target);
            }
        }

        // Destruction
        if (destroyAfterSeconds > 0.0f)
        {
            yield return new WaitForSeconds(destroyAfterSeconds);
            if (this != null)
            {
                Destroy(gameObject);
            }
        }
    }

    /// <summary>
    /// Destroys owned path nodes.
    /// </summary>
    private void OnDestroy()
    {
        foreach (var node in ownedNodes)
        {
            if (node != null)
            {
                Destroy(node);
            }
        }
    }

    /// <summary>
    /// Called each game tick.
    /// </summary>
    private void Update()
    {
        if (rigidbody == null)
        {
            Vector3 position = transform.position;
            Quaternion rotation = transform.rotation;
            Vector3 scale = transform.localScale;

            // Constant motion
            position += constantSpeed * Time.deltaTime;
            rotation *= Quaternion.Euler(constantRotation * Time.deltaTime);
            scale += constantScale * Time.deltaTime;

            // Path
            if (path != null && path.Count > 0)
            {
                if (loopPath && pathIndex >= path.Count)
                {
                    pathIndex = 0;
                }
                if (pathIndex < path.Count)
                {
                    GenericMoveNode node = path[pathIndex];
                    float delta = node.speed * pathSpeedMultiplier * Time.deltaTime;
                    if (node.currentDelay <= 0.0f)
                    {
                        bool nextNode = true;
                        if (node.followPosition)
                        {
                            position = node.smoothTime <= 0.0 ?
                                Vector3.MoveTowards(position, node.target.transform.position, delta) :
                                Vector3.SmoothDamp(position, node.target.transform.position, ref positionVelocity, node.smoothTime, node.speed * pathSpeedMultiplier, Time.deltaTime);
                            if ((node.target.transform.position - position).sqrMagnitude > minDistance * minDistance)
                            {
                                nextNode = false;
                            }
                            else
                            {
                                positionVelocity = Vector3.zero;
                                position = node.target.transform.position;
                            }
                        }
                        if (node.followRotation)
                        {
                            rotation = node.smoothTime <= 0.0 ?
                                Quaternion.RotateTowards(rotation, node.target.transform.rotation, delta) :
                                Quaternion.Slerp(rotation, node.target.transform.rotation, delta * node.smoothTime);
                            if (Quaternion.Angle(rotation, node.target.transform.rotation) > minDegrees)
                            {
                                nextNode = false;
                            }
                            else
                            {
                                rotation = node.target.transform.rotation;
                            }
                        }
                        if (node.followScale)
                        {
                            scale = node.smoothTime <= 0.0 ?
                                Vector3.MoveTowards(scale, node.target.transform.localScale, delta) :
                                Vector3.SmoothDamp(scale, node.target.transform.localScale, ref scaleVelocity, node.smoothTime, node.speed * pathSpeedMultiplier, Time.deltaTime);
                            if ((node.target.transform.localScale - scale).sqrMagnitude > minScale * minScale)
                            {
                                nextNode = false;
                            }
                            else
                            {
                                scaleVelocity = Vector3.zero;
                                scale = node.target.transform.localScale;
                            }
                        }
                        if (nextNode)
                        {
                            node.currentDelay = node.delay;
                            ++pathIndex;
                        }
                    }
                    else
                    {
                        node.currentDelay -= Time.deltaTime;
                    }
                }
            }

            transform.localScale = scale;
            transform.rotation = rotation;
            transform.position = position;
        }
    }

    /// <summary>
    /// Called each physics tick.
    /// </summary>
    private void FixedUpdate()
    {
        if (rigidbody != null)
        {
            Vector3 position = transform.position;
            Quaternion rotation = transform.rotation;
            Vector3 scale = transform.localScale;

            // Constant motion
            position += constantSpeed * Time.fixedDeltaTime;
            rotation *= Quaternion.Euler(constantRotation * Time.fixedDeltaTime);
            scale += constantScale * Time.fixedDeltaTime;

            // Path
            if (path != null && path.Count > 0)
            {
                if (loopPath && pathIndex >= path.Count)
                {
                    pathIndex = 0;
                }
                if (pathIndex < path.Count)
                {
                    GenericMoveNode node = path[pathIndex];
                    float delta = node.speed * pathSpeedMultiplier * Time.fixedDeltaTime;
                    if (node.currentDelay <= 0.0f)
                    {
                        bool nextNode = true;
                        if (node.followPosition)
                        {
                            position = node.smoothTime <= 0.0 ?
                                Vector3.MoveTowards(position, node.target.transform.position, delta) :
                                Vector3.SmoothDamp(position, node.target.transform.position, ref positionVelocity, node.smoothTime, node.speed * pathSpeedMultiplier, Time.fixedDeltaTime);
                            if ((node.target.transform.position - position).sqrMagnitude > minDistance * minDistance)
                            {
                                nextNode = false;
                            }
                            else
                            {
                                positionVelocity = Vector3.zero;
                                position = node.target.transform.position;
                            }
                        }
                        if (node.followRotation)
                        {
                            rotation = node.smoothTime <= 0.0 ?
                                Quaternion.RotateTowards(rotation, node.target.transform.rotation, delta) :
                                Quaternion.Slerp(rotation, node.target.transform.rotation, delta * node.smoothTime);
                            if (Quaternion.Angle(rotation, node.target.transform.rotation) > minDegrees)
                            {
                                nextNode = false;
                            }
                            else
                            {
                                rotation = node.target.transform.rotation;
                            }
                        }
                        if (node.followScale)
                        {
                            scale = node.smoothTime <= 0.0 ?
                                Vector3.MoveTowards(scale, node.target.transform.localScale, delta) :
                                Vector3.SmoothDamp(scale, node.target.transform.localScale, ref scaleVelocity, node.smoothTime, node.speed * pathSpeedMultiplier, Time.fixedDeltaTime);
                            if ((node.target.transform.localScale - scale).sqrMagnitude > minScale * minScale)
                            {
                                nextNode = false;
                            }
                            else
                            {
                                scaleVelocity = Vector3.zero;
                                scale = node.target.transform.localScale;
                            }
                        }
                        if (nextNode)
                        {
                            node.currentDelay = node.delay;
                            ++pathIndex;
                        }
                    }
                    else
                    {
                        node.currentDelay -= Time.fixedDeltaTime;
                    }
                }
            }

            transform.localScale = scale;
            rigidbody.rotation = rotation; // rigidbody.position and rigidbody.rotation enables physics teleportation:
            rigidbody.position = position; // the rigidbody wont get stuck on collision unlike rigidbody.Move()
        }
    }
}
