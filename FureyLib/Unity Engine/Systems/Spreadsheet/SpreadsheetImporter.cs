// .cs
// Spreadsheet Scriptable Object Importer
// by Kyle Furey

// Place in Assets/Editor folder

#nullable enable
using System.IO;
using UnityEditor;

public static class SpreadsheetImporter
{
    [MenuItem("Utility/Update Spreadsheets")]
    public static void UpdateSpreadsheets()
    {
        GSpreadSheetsToJson google = new();
        google.Init();                                                          // Field <spreadSheetKey> needs to be initialized
        google.DownloadToJson();                                                // DownloadToJson() method needs to be public
        EditorUtility.ClearProgressBar();
        foreach (var sheetName in google.ranges)                                // Local variable <ranges> needs to be exposed as a public field
        {
            string path = google.outputDir + sheetName;
            string objFile = path + ".asset";                                   // Field <outputDir> needs to be initialized and public
            string jsonFile = path + ".txt";                                    // Field <outputDir> needs to be initialized and public
            var sheet = AssetDatabase.LoadAssetAtPath<Spreadsheet>(objFile);
            sheet.Deserialize(File.ReadAllText(jsonFile));
            File.Delete(jsonFile);
        }
        AssetDatabase.Refresh();
    }
}
