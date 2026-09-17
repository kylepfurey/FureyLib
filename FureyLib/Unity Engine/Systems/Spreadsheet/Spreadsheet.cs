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

        delegate bool Parser<T>(string s, out T result) where T : struct;
        readonly T? Get<T>(string column, Parser<T> parser) where T : struct
        {
            if (!parser(columns[column.Trim().ToLower()], out var result))
                return null;
            return result;
        }

        public readonly bool? Bool(string column) => Get<bool>(column, bool.TryParse);
        public readonly int? Int(string column) => Get<int>(column, int.TryParse);
        public readonly float? Float(string column) => Get<float>(column, float.TryParse);
        public readonly string String(string column)
        {
            if (!columns.TryGetValue(column.Trim().ToLower(), out var result))
                return string.Empty;
            result = result.Trim();
            return result;
        }
        public readonly string[] Array(string column)
        {
            if (!columns.TryGetValue(column.Trim().ToLower(), out var str))
                return System.Array.Empty<string>();
            string[] result = str.Split(',');
            for (int i = 0; i < result.Length; ++i)
                result[i] = result[i].Trim();
            return result;
        }
    }

    [SerializeField] Dictionary<string, int> idToRow;
    [SerializeField] Row[] rows;

    public Row this[int row] { get => rows[row]; }
    public Row this[string id] { get => rows[idToRow[id.Trim().ToLower()]]; }

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
