
// Name
// Creator

using System;
using System.Collections;
using System.Collections.Generic;

using UnityEngine;

/// <summary>
/// Template Unity scriptable object.
/// </summary>
[CreateAssetMenu(fileName = "New Scriptable Object", menuName = "Scriptable Objects", order = 0)]
public class NewScriptableObject : ScriptableObject
{
    [Header("Template Unity scriptable object.")]

    [Header("\nCONFIGURATION")]

    [Header("Example setting:")]
    [SerializeField] private bool setting = false;

    // New variables here


    // CONSTRUCTORS AND DECONSTRUCTOR

    /// <summary>
    /// Default constructor
    /// </summary>
    public NewScriptableObject()
    {

    }

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="copied"></param>
    public NewScriptableObject(NewScriptableObject copied)
    {

    }

    // New constructors here


    // FUNCTIONS

    /// <summary>
    /// Awake() is called when the script is loaded
    /// </summary>
    private void Awake()
    {

    }

    /// <summary>
    /// Start() is called before the first frame update
    /// </summary>
    private void Start()
    {

    }

    /// <summary>
    /// Update() is called once per frame
    /// </summary>
    private void Update()
    {

    }

    /// <summary>
    /// FixedUpdate() is called once per physics tick
    /// </summary>
    private void FixedUpdate()
    {

    }

    /// <summary>
    /// LateUpdate() is called once per frame after Update
    /// </summary>
    private void LateUpdate()
    {

    }

    // New functions here
}
