
// Static File Functions Script
// by Kyle Furey

using System;
using System.IO;

// Include this heading to use the library.
using static File;

/// <summary>
/// Provides easy to use read and write file management functions.
/// </summary>
public static class File
{
    // FILES

    /// <summary>
    /// Reads a file at the given path and returns its content.
    /// </summary>
    /// <returns>The imported file's text. Throws an exception if the file is not valid.</returns>
    public static string Import(string path)
    {
        if (!System.IO.File.Exists(path))
        {
            throw new FileNotFoundException("The given file does not exist at path \"" + path + "\".");
        }

        FileStream file = System.IO.File.OpenRead(path);

        string text = "";

        int current = file.ReadByte();

        while (current != -1)
        {
            text += (char)current;

            current = file.ReadByte();
        }

        file.Close();

        return text;
    }

    /// <summary>
    /// Creates or overwrites a file of the given text to the given path.
    /// </summary>
    /// <returns>Whether a file was overwritten.</returns>
    public static bool Export(string text, string path)
    {
        bool overwrite = System.IO.File.Exists(path);

        FileStream file = System.IO.File.Create(path);

        foreach (char letter in text)
        {
            file.WriteByte((byte)letter);
        }

        file.Close();

        return overwrite;
    }

    /// <summary>
    /// Deletes the file at the given path.
    /// </summary>
    /// <returns>Whether the file's deletion was successful. Throws an exception if the file is not valid.</returns>
    public static bool Delete(string path)
    {
        if (!System.IO.File.Exists(path))
        {
            throw new FileNotFoundException("The given file does not exist at path \"" + path + "\".");
        }
        else
        {
            System.IO.File.Delete(path);

            return true;
        }
    }

    /// <summary>
    /// Returns whether the given path leads to a file.
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    public static bool Exists(string path)
    {
        return System.IO.File.Exists(path);
    }
}
