// .cs
// Save Data Interface
// by Kyle Furey

#nullable enable
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Enables a class to save and load data from a file within itself.
/// </summary>
public interface ISaveData
{
    // INTERFACE
	
    /// <summary>
    /// Called when this object is requested to save its data to a save file.
    /// </summary>
    /// <param name="saveData">The save data category that is storing this object's properties.</param>
    public void OnSave(SaveManager.SaveFile.SaveData saveData);

    /// <summary>
    /// Called when this object is requested to load its data from a save file.
    /// </summary>
    /// <param name="saveData">The save data category that is storing this object's properties.</param>
    public void OnLoad(SaveManager.SaveFile.SaveData saveData);
}
