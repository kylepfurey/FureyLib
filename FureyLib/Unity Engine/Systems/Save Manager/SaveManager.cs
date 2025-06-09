// .cs
// Singleton Save Manager Class
// by Kyle Furey

#nullable enable
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using System.Text;
using UnityEngine;
using UnityEditor;
using Newtonsoft.Json;

/// <summary>
/// A singleton component used to manage saved data to and from save files.
/// </summary>
public class SaveManager : MonoBehaviour
{
    // CLASSES

    /// <summary>
    /// A wrapper for all save data stored within a file.
    /// </summary>
    public class SaveFile
    {
        // VARIABLES

        /// <summary>
        /// All loaded save data contained within this file by category name.
        /// </summary>
        private Dictionary<string, SaveData> categories = new Dictionary<string, SaveData>();


        // PROPERTIES

        /// <summary>
        /// The version number of this save file.
        /// </summary>
        public string version { get; private set; } = string.Empty;

        /// <summary>
        /// The path to this save file.
        /// </summary>
        public string filePath { get; private set; } = string.Empty;

        /// <summary>
        /// The directory where this save file is stored.
        /// </summary>
        public string fileDirectory => Path.GetDirectoryName(filePath);

        /// <summary>
        /// The name and extension of this save file.
        /// </summary>
        public string fileName => Path.GetFileName(filePath);

        /// <summary>
        /// The extension of this save file.
        /// </summary>
        public string fileExtension => Path.GetExtension(filePath);

        /// <summary>
        /// The name of this save file (no extension).
        /// </summary>
        public string saveName => Path.GetFileNameWithoutExtension(filePath);

        /// <summary>
        /// Whether this save file currently exists on the hard drive.
        /// </summary>
        public bool isSaved => File.Exists(filePath);


        // CONSTRUCTOR

        /// <summary>
        /// Constructs a save file from the given file path.
        /// </summary>
        public SaveFile(string path)
        {
            filePath = path;
            version = saveVersion;

            if (File.Exists(path))
            {
                try
                {
                    string[] lines = File.ReadAllLines(path);
                    if (lines == null || lines.Length == 0)
                    {
                        return;
                    }

                    version = lines[0].Trim();

                    string category = string.Empty;
                    for (int i = 1; i < lines.Length; ++i)
                    {
                        if (string.IsNullOrWhiteSpace(lines[i]))
                        {
                            if (category != string.Empty)
                            {
                                category = string.Empty;
                            }
                        }
                        else
                        {
                            if (category == string.Empty)
                            {
                                category = lines[i].Trim().ToUpper();
                                categories[category] = new SaveData();
                            }
                            else
                            {
                                string[] keyValue = lines[i].Split('=');
                                if (keyValue != null && keyValue.Length == 2)
                                {
                                    string key = keyValue[0].Trim();
                                    string value = keyValue[1].Trim();
                                    categories[category].AllProperties()[key] = value;
                                }
                            }
                        }
                    }
                }
                catch (Exception exception)
                {
                    Debug.LogError("SAVE ERROR: " + exception.Message);
                }
            }
            else
            {
                if (!Directory.Exists(fileDirectory))
                    Directory.CreateDirectory(fileDirectory);
            }
        }


        // METHODS

        /// <summary>
        /// Exports this save file to its set path, and returns whether it succeeded.
        /// </summary>
        public bool ExportFile() => ExportFile(filePath);

        /// <summary>
        /// Exports this save file to the given path, and returns whether it succeeded.
        /// </summary>
        public bool ExportFile(string path)
        {
            string directory = Path.GetDirectoryName(path);
            if (!Directory.Exists(directory))
                Directory.CreateDirectory(directory);

            try
            {
                File.WriteAllText(path, ToString());
                return true;
            }
            catch (Exception exception)
            {
                Debug.LogError("SAVE ERROR: " + exception.Message);
                return false;
            }
        }

        /// <summary>
        /// Returns all of this save file's categories.
        /// </summary>
        public Dictionary<string, SaveData> AllCategories() => categories;

        /// <summary>
        /// Creates new save data for the given category.<br/>
        /// Each category absolutely MUST be unique!
        /// </summary>
        public SaveData? NewCategory(string category)
        {
            if (string.IsNullOrWhiteSpace(category))
            {
                Debug.LogError("SAVE ERROR: Saving an invalid category!\n" +
                    "Category Name: " +
                    category);
                return null;
            }

            category = category.Trim().ToUpper();

            if (categories.ContainsKey(category))
            {
                Debug.LogError("SAVE ERROR: " +
                    category +
                    " already exists as a category!\n" +
                    "All save data categories MUST be unique!");
                return null;
            }

            SaveData saveData = new SaveData();
            categories[category] = saveData;

            return saveData;
        }

        /// <summary>
        /// Returns the save data from the given category or null if it is not found.
        /// </summary>
        public SaveData? GetCategory(string category)
        {
            if (categories.TryGetValue(category.Trim().ToUpper(), out SaveData saveData))
            {
                return saveData;
            }

            return null;
        }

        /// <summary>
        /// Removes the given category and all its data from this save file.
        /// </summary>
        public bool EraseCategory(string category) => categories.Remove(category.Trim().ToUpper());

        /// <summary>
        /// Returns whether this save file has data for the given category.
        /// </summary>
        public bool HasCategory(string category) => categories.ContainsKey(category.Trim().ToUpper());

        /// <summary>
        /// Clears all save data within this save file.
        /// </summary>
        public void ClearCategories() => categories.Clear();

        /// <summary>
        /// Returns the total number of categories for this save file.
        /// </summary>
        public int CategoryCount() => categories.Count;

        /// <summary>
        /// Serializes this save file and its categories into a parsable string.
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            StringBuilder str = new StringBuilder();
            str.AppendLine(saveVersion);
            foreach (var pair in categories)
            {
                str.AppendLine(pair.Key.Trim().ToUpper());
                str.AppendLine(pair.Value.ToString());
            }
            return str.ToString();
        }
    }

    /// <summary>
    /// A collection of save data specific to an element of the game.
    /// </summary>
    public class SaveData
    {
        // VARIABLES

        /// <summary>
        /// All of this category's stored properties stored as strings.
        /// </summary>
        private Dictionary<string, string> properties = new Dictionary<string, string>();


        // METHODS

        /// <summary>
        /// Returns all of this category's properties.
        /// </summary>
        public Dictionary<string, string> AllProperties() => properties;

        /// <summary>
        /// Saves the given property to this category and returns whether a property was overwritten.
        /// </summary>
        public bool SaveProperty<Type>(string property, Type value)
        {
            property = property.Trim();

            if (string.IsNullOrWhiteSpace(property))
            {
                Debug.LogError("SAVE ERROR: Saving an invalid property!\n" +
                    "Property Name: " +
                    property);
                return false;
            }

            bool exists = properties.ContainsKey(property);
            properties[property] = JsonConvert.SerializeObject(value, Formatting.None);
            return exists;
        }

        /// <summary>
        /// Loads the given property from this category if it was found and returns whether the property was found.
        /// </summary>
        public bool LoadProperty<Type>(string property, ref Type value)
        {
            property = property.Trim();

            if (properties.ContainsKey(property))
            {
                value = JsonConvert.DeserializeObject<Type>(properties[property])!;
                return true;
            }

            return false;
        }

        /// <summary>
        /// Erases a property from this category and returns whether the property was successfully erased.
        /// </summary>
        public bool EraseProperty(string property) => properties.Remove(property.Trim());

        /// <summary>
        /// Returns whether the given property is saved within this category.
        /// </summary>
        public bool HasProperty(string property) => properties.ContainsKey(property.Trim());

        /// <summary>
        /// Clears all properties within this category.
        /// </summary>
        public void ClearProperties() => properties.Clear();

        /// <summary>
        /// Returns the total number of stored properties.
        /// </summary>
        public int PropertyCount() => properties.Count;

        /// <summary>
        /// Serializes this category's save data into a list of all properties and their values.
        /// </summary>
        public override string ToString()
        {
            StringBuilder result = new StringBuilder();
            foreach (var pair in properties)
            {
                result.Append(pair.Key);
                result.Append('=');
                result.AppendLine(pair.Value);
            }
            return result.ToString();
        }
    }


    // VARIABLES

    /// <summary>
    /// Each saved object and its category.
    /// </summary>
    private Dictionary<ISaveData, string> savedObjects = new Dictionary<ISaveData, string>();


    // PROPERTIES

    /// <summary>
    /// Singleton reference to the SaveManager component.
    /// </summary>
    public static SaveManager instance { get; private set; } = null!;

    /// <summary>
    /// The instance of the current save file.
    /// </summary>
    public static SaveFile currentSave { get; private set; } = null!;

    /// <summary>
    /// The version number to save each save file with.
    /// </summary>
    public static string saveVersion => Application.version;

    /// <summary>
    /// The name of the folder where save files are stored.
    /// </summary>
    public static string saveFolder => "Save Files";

    /// <summary>
    /// The directory of where to save each save file.
    /// </summary>
    public static string saveDirectory => Path.Combine(Application.persistentDataPath, saveFolder);

    /// <summary>
    /// The extension to save each save file with.
    /// </summary>
    public static string saveExtension => ".sav";


    // EVENTS

    /// <summary>
    /// Initializes this singleton component and loads the default save file.
    /// </summary>
    private void Awake()
    {
        if (instance == null)
        {
            instance = this;
        }
        else
        {
            Debug.LogError("SINGLETON ERROR: A SaveManager component already exists on " +
                instance.gameObject.name +
                "!");
            Destroy(this);
            return;
        }

        currentSave = new SaveFile(MakePath("MyGame_SaveFile"));
    }

    /// <summary>
    /// Loads the current save data.
    /// </summary>
    private IEnumerator Start()
    {
        yield return null;
        LoadAll();
    }

    /// <summary>
    /// Cleans up the singleton component and saves all save data to disk.
    /// </summary>
    private void OnDestroy()
    {
        if (instance == this)
        {
            SaveAll();
            instance = null!;
            currentSave = null!;
        }
    }


    // METHODS

    /// <summary>
    /// Generates a path from the name of the given save file.
    /// </summary>
    private static string MakePath(string saveName) => Path.Combine(saveDirectory, saveName + saveExtension);

    /// <summary>
    /// Imports a save file from the given name and returns it or null if it failed.
    /// </summary>
    public SaveFile? ImportFile(string saveName)
    {
        string path = MakePath(saveName);

        if (File.Exists(path))
        {
            return new SaveFile(path);
        }

        return null;
    }

    /// <summary>
    /// Deletes a save file from the given name and returns whether it was successful.
    /// </summary>
    public bool DeleteFile(string saveName)
    {
        string path = MakePath(saveName);

        if (File.Exists(path))
        {
            File.Delete(path);
            return true;
        }

        return false;
    }

    /// <summary>
    /// Returns whether the given save file by name is present on the hard drive.
    /// </summary>
    public bool HasFile(string saveName) => File.Exists(MakePath(saveName));

    /// <summary>
    /// Sets the current save file to the given save file.<br/>
    /// NOTE: The current save file's memory may be deleted if it is not saved to disk!
    /// </summary>
    public bool SetCurrentSave(SaveFile saveFile)
    {
        if (saveFile != null)
        {
            currentSave = saveFile;
            LoadAll();

            return true;
        }

        return false;
    }

    /// <summary>
    /// Binds the given save data to the given category for save callbacks.
    /// </summary>
    public bool BindObject(ISaveData savedObject, string category)
    {
        if (savedObject == null || string.IsNullOrWhiteSpace(category) || savedObjects.ContainsKey(savedObject))
            return false;

        savedObjects.Add(savedObject, category);

        if (!currentSave.HasCategory(category))
            currentSave.NewCategory(category);

        return true;
    }

    /// <summary>
    /// Unbinds the given save data from receiving save callbacks.
    /// </summary>
    public bool UnbindObject(ISaveData savedObject) => savedObjects.Remove(savedObject);

    /// <summary>
    /// Returns whether the given saved object is bound.
    /// </summary>
    public bool IsObjectBound(ISaveData savedObject) => savedObjects.ContainsKey(savedObject);

    /// <summary>
    /// The current total number of saved objects.
    /// </summary>
    public int TotalObjects() => savedObjects.Count;

    /// <summary>
    /// Updates all the data in the given save data's category.
    /// </summary>
    public bool Save(ISaveData savedObject)
    {
        if (!savedObjects.ContainsKey(savedObject))
        {
            Debug.LogError("SAVE ERROR: Saving an object " +
                savedObject.ToString() +
                " when it was not bound with SaveManager.BindObject()!");
            return false;
        }

        SaveData? category = currentSave.GetCategory(savedObjects[savedObject]);
        if (category == null)
        {
            Debug.LogError("SAVE ERROR: Saving an object with an invalid category!\n" +
                "Category Name: " +
                savedObjects[savedObject]);
            return false;
        }

        savedObject.OnSave(category);

        bool success = true;
        Type type = savedObject.GetType();
        foreach (var field in type.GetFields(BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance))
        {
            if (field.GetCustomAttribute<AutoSaveAttribute>() != null)
            {
                try
                {
                    MethodInfo saveMethod = category.GetType().GetMethod("SaveProperty");
                    MethodInfo genericSave = saveMethod.MakeGenericMethod(field.FieldType);
                    genericSave.Invoke(category, new object[] { field.Name, field.GetValue(savedObject) });
                }
                catch
                {
                    Debug.LogError("SAVE ERROR: Could not save property from field " +
                        field.Name +
                        " in object " +
                        savedObject.ToString() +
                        "!");
                    success = false;
                }
            }
        }

        foreach (var property in type.GetProperties(BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance))
        {
            if (property.GetCustomAttribute<AutoSaveAttribute>() != null)
            {
                try
                {
                    MethodInfo saveMethod = category.GetType().GetMethod("SaveProperty");
                    MethodInfo genericSave = saveMethod.MakeGenericMethod(property.PropertyType);
                    genericSave.Invoke(category, new object[] { property.Name, property.GetValue(savedObject) });
                }
                catch
                {
                    Debug.LogError("SAVE ERROR: Could not save property from property " +
                        property.Name +
                        " in object " +
                        savedObject.ToString() +
                        "!");
                    success = false;
                }
            }
        }

        return success;
    }

    /// <summary>
    /// Updates all the data in the given save data's category.
    /// </summary>
    public bool Load(ISaveData savedObject)
    {
        if (!savedObjects.ContainsKey(savedObject))
        {
            Debug.LogError("SAVE ERROR: Loading an object " +
                savedObject.ToString() +
                " when it was not bound with SaveManager.BindObject()!");
            return false;
        }

        SaveData? category = currentSave.GetCategory(savedObjects[savedObject]);
        if (category == null)
        {
            Debug.LogError("SAVE ERROR: Loading an object with an invalid category!\n" +
                "Category Name: " +
                savedObjects[savedObject]);
            return false;
        }

        bool success = true;
        Type type = savedObject.GetType();
        foreach (var field in type.GetFields(BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance))
        {
            if (field.GetCustomAttribute<AutoSaveAttribute>() != null)
            {
                try
                {
                    MethodInfo loadMethod = category.GetType().GetMethod("LoadProperty");
                    MethodInfo genericLoad = loadMethod.MakeGenericMethod(field.FieldType);
                    object[] args = new object[] { field.Name, null! };
                    genericLoad.Invoke(category, args);
                    field.SetValue(savedObject, args[1]);
                }
                catch
                {
                    Debug.LogError("SAVE ERROR: Could not load property from field " +
                        field.Name +
                        " in object " +
                        savedObject.ToString() +
                        "!");
                    success = false;
                }
            }
        }

        foreach (var property in type.GetProperties(BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance))
        {
            if (property.GetCustomAttribute<AutoSaveAttribute>() != null)
            {
                try
                {
                    MethodInfo loadMethod = category.GetType().GetMethod("LoadProperty");
                    MethodInfo genericLoad = loadMethod.MakeGenericMethod(property.PropertyType);
                    object[] args = new object[] { property.Name, null! };
                    genericLoad.Invoke(category, args);
                    property.SetValue(savedObject, args[1]);
                }
                catch
                {

                    Debug.LogError("SAVE ERROR: Could not load property from property " +
                        property.Name +
                        " in object " +
                        savedObject.ToString() +
                        "!");
                    success = false;
                }
            }
        }

        savedObject.OnLoad(category);

        return success;
    }

    /// <summary>
    /// Saves all data currently bound to the current save file and writes the save file to disk.
    /// </summary>
    public bool SaveAll()
    {
        bool success = true;
        foreach (var pair in savedObjects)
        {
            if (pair.Key == null)
            {
                Debug.LogError("SAVE ERROR: A destroyed save object was not unbound before saving!\n" +
                    "Category Name: " +
                    pair.Value);
                success = false;
                continue;
            }

            if (!Save(pair.Key))
            {
                success = false;
            }
        }

        if (success)
        {
            currentSave.ExportFile();
        }

        return success;
    }

    /// <summary>
    /// Loads all save data currently bound from the current save file.
    /// </summary>
    public bool LoadAll()
    {
        bool success = true;
        foreach (var pair in savedObjects)
        {
            if (pair.Key == null)
            {
                Debug.LogError("SAVE ERROR: A destroyed save object was not unbound before loading!\n" +
                    "Category Name: " + pair.Value);
                success = false;
                continue;
            }

            if (!Load(pair.Key))
            {
                success = false;
            }
        }

        return success;
    }

    /// <summary>
    /// Opens the folder where save files are stored.
    /// </summary>
    [MenuItem("My Game/Open Save Files Folder", false, int.MaxValue)]
    public static void OpenSaveFilesFolder()
    {
        if (!Directory.Exists(saveDirectory))
            Directory.CreateDirectory(saveDirectory);
            
        EditorUtility.RevealInFinder(Path.Combine(saveDirectory, saveExtension));
    }
}
