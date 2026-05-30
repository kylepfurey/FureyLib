// .cs
// Importable Spreadsheet
// by Kyle Furey

using System;
using System.Collections.Generic;
using UnityEngine;
#if UNITY_EDITOR
using UnityEditor;
#endif

/// <summary>
/// A scriptable object for importing a spreadsheet.<br/>
/// The spreadsheet is assumed to be not empty and contains both valid rows and columns.<br/>
/// Two columns of the spreadsheet are combined to create an ID.<br/>
/// Each sheet should have matching column names and IDs.
/// </summary>
[CreateAssetMenu(fileName = "Spreadsheet", menuName = "Scriptable Objects/Spreadsheet")]
public class Spreadsheet : ScriptableObject
{
    // STRUCTS

    /// <summary>
    /// A sheet containing a name and list of rows.
    /// </summary>
    [Serializable]
    public struct Sheet
    {
        /// <summary>
        /// The name of this sheet.
        /// </summary>
        public string Name;

        /// <summary>
        /// Each row in this sheet.
        /// </summary>
        public List<Row> Rows;
    }

    /// <summary>
    /// A row of data indexed by its column name.
    /// </summary>
    [Serializable]
    public struct Row
    {
        /// <summary>
        /// Each column's data in this row..
        /// </summary>
        public List<string> Columns;
    }


    // FIELDS

    /// <summary>
    /// Each column name in this spreadsheet.
    /// </summary>
    public List<string> Columns;

    /// <summary>
    /// Each sheet in this spreadsheet.
    /// </summary>
    public List<Sheet> Sheets;

    /// <summary>
    /// Used to look up a column name to its index.
    /// </summary>
    Dictionary<string, int> columnToIndex;

    /// <summary>
    /// Used to look up a sheet name to its index.
    /// </summary>
    Dictionary<string, int> sheetToIndex;

    /// <summary>
    /// Used to enter a sheet and look up a row's ID to its index.
    /// </summary>
    List<Dictionary<string, int>> idToIndex;


    // CONSTANTS

    /// <summary>
    /// The index of the category column.
    /// </summary>
    public const int CATEGORY_COLUMN = 0;

    /// <summary>
    /// The index of the name column.
    /// </summary>
    public const int NAME_COLUMN = 1;

    /// <summary>
    /// A delimiter used to combine the first two columns into an ID.
    /// </summary>
    public const char ID_DELIMITER = '.';


    // EDITOR

#if UNITY_EDITOR
    /// <summary>
    /// Resets this spreadsheet.
    /// </summary>
    public void Reset()
    {
        Columns = new List<string>();
        Sheets = new List<Sheet>();
        columnToIndex = null;
        sheetToIndex = null;
        idToIndex = null;
    }

    /// <summary>
    /// Imports a spreadsheet with a name and rows with columns mapping to data.
    /// </summary>
    public void ImportSheet(string name, List<Dictionary<string, string>> rows)
    {
        if (Columns.Count == 0)
            foreach (var columns in rows[0].Keys)
                Columns.Add(columns);

        Sheet sheet = new()
        {
            Name = name,
            Rows = new List<Row>()
        };

        foreach (var columns in rows)
        {
            Row row = new()
            {
                Columns = new()
            };

            foreach (var value in columns.Values)
                row.Columns.Add(value);

            sheet.Rows.Add(row);
        }

        Sheets.Add(sheet);
    }

    /// <summary>
    /// Saves this scriptable object.
    /// </summary>
    public void Save()
    {
        EditorUtility.SetDirty(this);
        AssetDatabase.SaveAssets();
        AssetDatabase.Refresh();
    }
#endif

    // INITIALIZATION

    /// <summary>
    /// Initializes a sheet in this spreadsheet by its name.
    /// </summary>
    public void Init(string sheet)
    {
        if (idToIndex == null)
        {
            columnToIndex = new Dictionary<string, int>();
            for (int i = 0; i < Columns.Count; ++i)
                columnToIndex.Add(Columns[i], i);
            sheetToIndex = new Dictionary<string, int>();
            for (int i = 0; i < Sheets.Count; ++i)
                sheetToIndex.Add(Sheets[i].Name, i);
            idToIndex = new List<Dictionary<string, int>>();
            for (int i = 0; i < Sheets.Count; ++i)
                idToIndex.Add(null);
        }

        int sheetIndex = sheetToIndex[sheet];
        if (idToIndex[sheetIndex] != null)
            return;

        idToIndex[sheetIndex] = new Dictionary<string, int>();
        for (int i = 0; i < Sheets[sheetToIndex[sheet]].Rows.Count; ++i)
            idToIndex[sheetIndex].Add(
                MakeID(
                    Sheets[sheetToIndex[sheet]].Rows[i].Columns[CATEGORY_COLUMN],
                    Sheets[sheetToIndex[sheet]].Rows[i].Columns[NAME_COLUMN]
                ),
                i
            );
    }

    /// <summary>
    /// Initializes all sheets in this spreadsheet.
    /// </summary>
    public void InitAll()
    {
        foreach (var sheet in Sheets)
            Init(sheet.Name);
    }


    // LOOKUP

    /// <summary>
    /// Returns the data in a spreadsheet by looking up indices.
    /// </summary>
    public string Find(int sheet, int row, int column) => Sheets[sheet].Rows[row].Columns[column];

    /// <summary>
    /// Returns the data in a spreadsheet by looking up indices by sheet, row, and column name.
    /// </summary>
    public string Find(string sheet, string row, string column)
    {
        Init(sheet);
        int sheetIndex = sheetToIndex[sheet];
        int columnIndex = columnToIndex[column];
        int rowIndex = idToIndex[sheetIndex][row];
        return Sheets[sheetIndex].Rows[rowIndex].Columns[columnIndex];
    }


    // ID

    /// <summary>
    /// Creates an ID from a category and name.
    /// </summary>
    public static string MakeID(string category, string name) => category + ID_DELIMITER + name;
}
