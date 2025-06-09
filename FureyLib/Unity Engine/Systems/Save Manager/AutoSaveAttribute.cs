// .cs
// Automatic Saving Attribute
// by Kyle Furey

#nullable enable
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Metadata declaring that a field or property should automatically be saved and loaded.
/// </summary>
[AttributeUsage(AttributeTargets.Field | AttributeTargets.Property)]
public class AutoSaveAttribute : Attribute { }
