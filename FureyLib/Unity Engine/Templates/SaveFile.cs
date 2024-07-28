
// Template Save Data and File Script
// by Kyle Furey

using System;
using System.IO;
using UnityEngine;

/// <summary>
/// A collection of variables that can be stored and loaded to resume progress in a game.
/// </summary>
[Serializable]
public struct SaveData
{
    // SAVED PROPERTIES

    /// <summary>
    /// The name of the file to save.
    /// </summary>
    public string fileName { get; set; }

    /// <summary>
    /// The file path to the save file.
    /// </summary>
    public string directory { get; set; }

    // New save data here


    // CONSTRUCTOR

    /// <summary>
    /// Default constructor.
    /// </summary>
    public SaveData(string fileName = "New Save File", string directory = "C:\\Users\\")
    {
        this.fileName = fileName;

        this.directory = directory;

        // Initialize save data properties here!
    }
}

/// <summary>
/// A container for a save data structure that allows easy saving and loading to and from text files in a game.
/// </summary>
public class SaveFile
{
    // SAVED DATA

    /// <summary>
    /// This save file's owned save data.
    /// </summary>
    protected SaveData saveData = new SaveData();


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor.
    /// </summary>
    public SaveFile()
    {
        saveData = new SaveData();
    }

    /// <summary>
    /// Save data constructor.
    /// </summary>
    public SaveFile(SaveData saveData)
    {
        this.saveData = saveData;
    }


    // GETTERS

    /// <summary>
    /// Returns a copy of the save file's variables.
    /// </summary>
    public SaveData Get()
    {
        return saveData;
    }

    /// <summary>
    /// Returns the file name of this save file.
    /// </summary>
    public string GetFileName()
    {
        return saveData.fileName;
    }

    /// <summary>
    /// Returns the directory string of this save file.
    /// </summary>
    public string GetDirectory()
    {
        return saveData.directory;
    }


    // SETTERS

    /// <summary>
    /// Overwrites the save file's variables with the given save data and returns the new save data.
    /// </summary>
    public SaveData Set(SaveData newData)
    {
        saveData = newData;

        return saveData;
    }

    /// <summary>
    /// Updates the file name of this save file.
    /// </summary>
    public string SetFileName(string newName)
    {
        saveData.fileName = newName;

        return saveData.fileName;
    }

    /// <summary>
    /// Updates the directory string of this save file.
    /// </summary>
    public string SetDirectory(string newDirectory)
    {
        saveData.directory = newDirectory;

        return saveData.directory;
    }


    // SERIALIZATION FUNCTIONS

    /// <summary>
    /// Serializes the given save data structure into a JSON string that can be saved to a text file.
    /// </summary>
    public static string SaveToJSON(SaveData saveData)
    {
        return JsonUtility.ToJson(saveData, true);
    }

    /// <summary>
    /// Serializes this save file's save data structure into a JSON string that can be saved to a text file.
    /// </summary>
    public string ToJSON()
    {
        return SaveToJSON(saveData);
    }

    /// <summary>
    /// Reads the given JSON string as a save data structure that can be loaded into a save file.
    /// </summary>
    public static SaveData JSONToSave(string saveDataJSON)
    {
        return JsonUtility.FromJson<SaveData>(saveDataJSON);
    }

    /// <summary>
    /// Reads the given JSON string as a save data structure and loads it into this save file.
    /// </summary>
    public SaveData ReadJSON(string saveDataJSON)
    {
        saveData = JSONToSave(saveDataJSON);

        return saveData;
    }


    // SAVE DATA FUNCTIONS

    /// <summary>
    /// Converts this save file into a text file and saves it to this save file's directory.
    /// </summary>
    public bool Save()
    {
        return Save(GetFileName(), GetDirectory());
    }

    /// <summary>
    /// Converts this save file into a text file and saves it to the given directory with the given name.
    /// </summary>
    public bool Save(string fileName, string directory)
    {
        if (!Directory.Exists(directory))
        {
            return false;
        }
        else
        {
            if (directory[directory.Length - 1] != '\\')
            {
                directory += '\\';
            }

            if (!fileName.Contains('.'))
            {
                fileName += ".json";
            }

            directory += fileName;

            FileStream file = File.Create(directory);

            saveData.fileName = fileName;

            saveData.directory = directory;

            string json = ToJSON();

            foreach (char letter in json)
            {
                file.WriteByte((byte)letter);
            }

            file.Close();

            return true;
        }
    }

    /// <summary>
    /// Converts the text file at this save file's directory into save data and loads it into this save file.
    /// </summary>
    public bool Load()
    {
        return Load(GetFileName(), GetDirectory());
    }

    /// <summary>
    /// Converts the text file at the given directory into save data and loads it into this save file.
    /// </summary>
    public bool Load(string fileName, string directory)
    {
        if (!Directory.Exists(directory))
        {
            return false;
        }
        else
        {
            if (directory[directory.Length - 1] != '\\')
            {
                directory += '\\';
            }

            if (!fileName.Contains('.'))
            {
                fileName += ".json";
            }

            directory += fileName;

            if (!File.Exists(directory))
            {
                return false;
            }

            FileStream file = File.OpenRead(directory);

            string json = "";

            int current = file.ReadByte();

            while (current != -1)
            {
                json += (char)current;

                current = file.ReadByte();
            }

            file.Close();

            saveData = JSONToSave(json);

            return true;
        }
    }

    /// <summary>
    /// Erases this save file's save data.
    /// </summary>
    public bool Delete()
    {
        return Delete(GetFileName(), GetDirectory());
    }

    /// <summary>
    /// Erases the given save file's save data.
    /// </summary>
    public bool Delete(string fileName, string directory)
    {
        if (!Directory.Exists(directory))
        {
            return false;
        }
        else
        {
            if (directory[directory.Length - 1] != '\\')
            {
                directory += '\\';
            }

            if (!fileName.Contains('.'))
            {
                fileName += ".json";
            }

            directory += fileName;

            if (!File.Exists(directory))
            {
                return false;
            }

            File.Delete(directory);

            return true;
        }
    }
}
