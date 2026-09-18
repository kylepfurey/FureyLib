// .cs
// Spreadsheet Scriptable Object
// by Kyle Furey

#nullable enable
using System;
using System.Collections.Generic;
using Newtonsoft.Json;
using UnityEngine;
#if UNITY_EDITOR
using UnityEditor;
#endif

[CreateAssetMenu(fileName = "Spreadsheet", menuName = "Scriptable Objects/Spreadsheet")]
public class Spreadsheet : ScriptableObject
{
    [Serializable]
    public struct Row
    {
        [SerializeField] Dictionary<string, string> columns;

        public Row(Dictionary<string, string> columns)
        {
            this.columns = new Dictionary<string, string>();
            foreach (var pair in columns)
                this.columns[pair.Key.Trim().ToLower()] = pair.Value;
        }

        delegate bool Parser<T>(string s, out T result);
        readonly T GetAndParse<T>(string column, Parser<T> parser, T defaultValue)
        {
            if (!columns.TryGetValue(column.Trim().ToLower(), out var str))
                return defaultValue;
            if (!parser(str, out var result))
                return defaultValue;
            return result;
        }

        public readonly bool Bool(string column, bool defaultValue = false) => GetAndParse(column, bool.TryParse, defaultValue);
        public readonly int Int(string column, int defaultValue = 0) => GetAndParse(column, int.TryParse, defaultValue);
        public readonly float Float(string column, float defaultValue = 0.0f) => GetAndParse(column, float.TryParse, defaultValue);
        public readonly string String(string column, string defaultValue = "")
        {
            if (!columns.TryGetValue(column.Trim().ToLower(), out var result))
                return defaultValue;
            result = result.Trim();
            return result;
        }
        public readonly string[] Array(string column, string[] defaultValue = null!)
        {
            if (!columns.TryGetValue(column.Trim().ToLower(), out var str))
                return defaultValue ?? System.Array.Empty<string>();
            string[] result = str.Split(',');
            for (int i = 0; i < result.Length; ++i)
                result[i] = result[i].Trim();
            return result;
        }
    }

    [SerializeField] Dictionary<string, int> idToRow;
    [SerializeField] Row[] rows;

    public Row this[int row] { get => rows[row]; }
    public Row this[string id] { get => this[idToRow[id.Trim().ToLower()]]; }

#if UNITY_EDITOR
    public bool Deserialize(string json)
    {
        var rows = JsonConvert.DeserializeObject<Dictionary<string, string>[]>(json);
        if (rows == null)
            return false;
        this.rows = new Row[rows.Length];
        for (int i = 0; i < rows.Length; ++i)
        {
            idToRow[rows[i]["id"].Trim().ToLower()] = i;
            this.rows[i] = new Row(rows[i]);
        }
        EditorUtility.SetDirty(this);
        return true;
    }
#endif
}
