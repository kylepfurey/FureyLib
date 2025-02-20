// .cs
// CSV Static Function Library
// by Kyle Furey

using System;
using System.Collections.Generic;
using System.IO;

// A collection of data that contains a map of a CSV’s rows to its columns to that row’s value at that column.
using CSV_Collection = System.Collections.Generic.Dictionary<string, System.Collections.Generic.Dictionary<string, string>>;

/// <summary>
/// Provides functions for converting comma separated values (.csv) files into a collection and back into a file.
/// </summary>
public static class CSV
{
    // TO / FROM STRING

    /// <summary>
    /// Converts the given .csv string to a CSV collection, if possible.
    /// </summary>
    /// <param name="csv"></param>
    /// <param name="ignoreQuotes"></param>
    /// <returns></returns>
    public static CSV_Collection FromCSV(string csv, bool ignoreQuotes = false)
    {
        if (csv == null)
        {
            return null;
        }

        var columns = new List<string>();

        string current = "";

        bool ignoreComma = false;

        int columnIndex = 0;

        foreach (char character in csv)
        {
            if (character == '\n')
            {
                columns.Add(current);

                current = "";

                break;
            }

            switch (character)
            {
                case '"':

                case '\'':

                    if (!ignoreQuotes)
                    {
                        ignoreComma = !ignoreComma;

                        current += character;
                    }

                    break;

                case ',':

                case ';':

                    if (ignoreComma)
                    {
                        current += character;
                    }
                    else
                    {
                        columns.Add(current);

                        current = "";
                    }

                    break;

                default:

                    current += character;

                    break;

            }

            ++columnIndex;
        }

        if (columns.Count == 0)
        {
            return null;
        }

        var collection = new CSV_Collection();

        current = "";

        ignoreComma = false;

        string row = "";

        int i = columnIndex + 1;

        columnIndex = 0;

        for (; i < csv.Length; i++)
        {
            switch (csv[i])
            {
                case '\n':

                    if (columnIndex < columns.Count && collection.ContainsKey(row))
                    {
                        collection[row][columns[columnIndex]] = current;
                    }

                    current = "";

                    columnIndex = 0;

                    row = "";

                    break;

                case '"':

                case '\'':

                    if (!ignoreQuotes)
                    {
                        ignoreComma = !ignoreComma;

                        current += csv[i];
                    }

                    break;

                case ',':

                case ';':

                    if (!ignoreComma)
                    {
                        current += csv[i];
                    }
                    else
                    {
                        if (columnIndex == 0)
                        {
                            row = current;

                            collection[row] = new Dictionary<string, string>();
                        }

                        if (columnIndex < columns.Count)
                        {
                            collection[row][columns[columnIndex]] = current;
                        }

                        ++columnIndex;

                        current = "";
                    }

                    break;

                default:

                    current += csv[i];

                    break;
            }
        }

        return collection;
    }

    /// <summary>
    /// Converts the given CSV collection to a .csv string, if possible.
    /// </summary>
    /// <param name="csv"></param>
    /// <param name="addQuotes"></param>
    /// <returns></returns>
    public static string ToCSV(this CSV_Collection collection, bool addQuotes = false)
    {
        if (collection == null)
        {
            return "";
        }

        string csv = "";

        foreach (var row in collection)
        {
            if (csv.Length == 0)
            {
                foreach (var column in row.Value)
                {
                    if (addQuotes)
                    {
                        csv += '"' + column.Key + "\",";
                    }
                    else
                    {
                        csv += column.Key + ',';
                    }
                }

                csv = csv.Remove(csv.Length - 1, 1) + '\n';
            }

            foreach (var column in row.Value)
            {
                if (addQuotes)
                {
                    csv += '"' + collection[row.Key][column.Key] + "\",";
                }
                else
                {
                    csv += collection[row.Key][column.Key] + ',';
                }
            }

            csv = csv.Remove(csv.Length - 1, 1) + '\n';
        }

        return csv;
    }


    // IMPORT / EXPORT

    /// <summary>
    /// Imports and returns a CSV collection from the .csv file at the give path, if possible.
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    public static CSV_Collection ImportCSV(string path, bool ignoreQuotes = false)
    {
        if (!path.Contains('.'))
        {
            path += ".csv";
        }

        try
        {
            path = File.ReadAllText(path);
        }
        catch
        {
            return null;
        }

        return FromCSV(path, ignoreQuotes);
    }

    /// <summary>
    /// Saves the given CSV collection to the given path, and returns whether it was successful.
    /// </summary>
    /// <param name="collection"></param>
    /// <param name="path"></param>
    /// <returns></returns>
    public static bool ExportCSV(this CSV_Collection collection, string path, bool addQuotes = false)
    {
        if (!path.Contains('.'))
        {
            path += ".csv";
        }

        try
        {
            File.WriteAllText(path, ToCSV(collection, addQuotes));
        }
        catch
        {
            return false;
        }

        return File.Exists(path);
    }


    // EXTENSION METHODS

    /// <summary>
    /// Returns the comma separated value at the given row and column of this CSV collection.
    /// </summary>
    /// <param name="row"></param>
    /// <param name="column"></param>
    /// <returns></returns>
    public static string GetValue(this CSV_Collection collection, string row, string column)
    {
        if (collection.ContainsKey(row))
        {
            if (collection[row].ContainsKey(column))
            {
                return collection[row][column];
            }
        }

        return "";
    }

    /// <summary>
    /// Returns a list of this CSV collection's columns.
    /// </summary>
    /// <returns></returns>
    public static List<string> GetColumns(this CSV_Collection collection)
    {
        var columns = new List<string>();

        foreach (var row in collection)
        {
            foreach (var column in row.Value)
            {
                columns.Add(column.Key);
            }

            return columns;
        }

        return columns;
    }

    /// <summary>
    /// Returns a list of this CSV collection's rows.
    /// </summary>
    /// <returns></returns>
    public static List<string> GetRows(this CSV_Collection collection)
    {
        return new List<string>(collection.Keys);
    }
}
