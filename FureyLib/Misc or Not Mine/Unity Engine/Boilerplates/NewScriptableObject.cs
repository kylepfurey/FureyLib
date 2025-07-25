// .cs
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


	// PROPERTIES

	// New properties here


	// EVENTS

	/// <summary>
	/// Awake() is called when the script is loaded.
	/// </summary>
	private void Awake()
	{

	}

	/// <summary>
	/// Start() is called before the first frame update.
	/// </summary>
	private void Start()
	{

	}

	/// <summary>
	/// Update() is called once per frame.
	/// </summary>
	private void Update()
	{

	}

	/// <summary>
	/// FixedUpdate() is called once per physics tick.
	/// </summary>
	private void FixedUpdate()
	{

	}

	/// <summary>
	/// LateUpdate() is called once per frame after Update().
	/// </summary>
	private void LateUpdate()
	{

	}

	/// <summary>
	/// OnValidate() is called when one of this component's values are changed in the editor.
	/// </summary>
	private void OnValidate()
	{

	}


	// METHODS

	// New methods here
}
