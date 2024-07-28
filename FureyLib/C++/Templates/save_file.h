
// Template Save Data and File Script
// by Kyle Furey

#pragma once
#include <string>
#include <fstream>
#include <sys/stat.h>

// Include this heading to use the class
#include "save_file.h"

// A collection of variables that can be stored and loaded to resume progress in a program.
struct save_data
{
public:

	// SAVED VARIABLES

	// The name of the file to save.
	std::string file_name;

	// The file path to the save file.
	std::string directory;

	// New save data here


	// CONSTRUCTOR

	// Default constructor.
	save_data(std::string file_name = "New Save File", std::string directory = "C:\\Users\\")
	{
		this->file_name = file_name;

		this->directory = directory;

		// Initialize save data variables here!
	}
};

// A container for a save data structure that allows easy saving and loading to and from text files in a program.
class save_file
{
protected:

	// SAVED DATA

	// This save file's owned save data.
	save_data data = save_data();

public:

	// CONSTRUCTORS

	// Default constructor.
	save_file()
	{
		data = save_data();
	}

	// Save data constructor.
	save_file(save_data save_data)
	{
		this->data = save_data;
	}


	// GETTERS

	// Returns a copy of the save file's variables.
	save_data get()
	{
		return data;
	}

	// Returns the file name of this save file.
	std::string get_file_name()
	{
		return data.file_name;
	}

	// Returns the directory std::string of this save file.
	std::string get_directory()
	{
		return data.directory;
	}


	// SETTERS

	// Overwrites the save file's variables with the given save data and returns the new save data.
	save_data set(save_data new_data)
	{
		data = new_data;

		return data;
	}

	// Updates the file name of this save file.
	std::string set_file_name(std::string new_name)
	{
		data.file_name = new_name;

		return data.file_name;
	}

	// Updates the directory string of this save file.
	std::string set_directory(std::string new_directory)
	{
		data.directory = new_directory;

		return data.directory;
	}


	// SERIALIZATION FUNCTIONS

	// Serializes the given save data structure into a string that can be saved to a text file.
	static std::string save_to_string(save_data save_data)
	{
		std::string text = "";

		// FILE NAME
		text += save_data.file_name;
		text += "\n";

		// DIRECTORY
		text += save_data.directory;
		text += "\n";

		// Serialize new variables here!

		return text;
	}

	// Serializes this save file's save data structure into a string that can be saved to a text file.
	std::string to_string()
	{
		return save_to_string(data);
	}

	// Reads the given string as a save data structure that can be loaded into a save file.
	static save_data string_to_save(std::string text)
	{
		save_data save = save_data();

		// FILE NAME
		int index = 0;
		std::string current = "";
		while (text[index] != '\n') { current += text[index]; index++; }
		save.file_name = current;

		// DIRECTORY
		index++;
		current = "";
		while (text[index] != '\n') { current += text[index]; index++; }
		save.directory = current;

		// Deserialize new variables here!

		return save;
	}

	// Reads the given string as a save data structure and loads it into this save file.
	save_data read_string(std::string text)
	{
		this->data = string_to_save(text);

		return this->data;
	}


	// SAVE DATA FUNCTIONS

	// Converts this save file into a text file and saves it to this save file's directory.
	bool save()
	{
		return save(get_file_name(), get_directory());
	}

	// Converts this save file into a text file and saves it to the given directory with the given name.
	bool save(std::string file_name, std::string directory)
	{
		struct stat storage;

		if (stat(directory.c_str(), &storage) != 0)
		{
			return false;
		}
		else
		{
			if (directory[directory.length() - 1] != '\\')
			{
				directory += '\\';
			}

			if (!file_name.find('.'))
			{
				file_name += ".txt";
			}

			directory += file_name;

			std::ofstream file = std::ofstream(directory);

			data.file_name = file_name;

			data.directory = directory;

			file << to_string() << std::endl;

			file.close();

			return true;
		}
	}

	// Converts the text file at this save file's directory into save data and loads it into this save file.
	bool load()
	{
		return load(get_file_name(), get_directory());
	}

	// Converts the text file at the given directory into save data and loads it into this save file.
	bool load(std::string file_name, std::string directory)
	{
		struct stat storage;

		if (stat(directory.c_str(), &storage) != 0)
		{
			return false;
		}
		else
		{
			if (directory[directory.length() - 1] != '\\')
			{
				directory += '\\';
			}

			if (!file_name.find('.'))
			{
				file_name += ".txt";
			}

			directory += file_name;

			if (stat(directory.c_str(), &storage) != 0 || (storage.st_mode & S_IFDIR))
			{
				return false;
			}

			std::ifstream file = std::ifstream(directory);

			std::string text = "";

			std::string current = "";

			while (std::getline(file, current))
			{
				text += current + "\n";
			}

			file.close();

			data = string_to_save(text);

			return true;
		}
	}

	// Erases this save file's save data.
	bool erase()
	{
		return erase(get_file_name(), get_directory());
	}

	// Erases the given save file's save data.
	bool erase(std::string file_name, std::string directory)
	{
		struct stat storage;

		if (stat(directory.c_str(), &storage) != 0)
		{
			return false;
		}
		else
		{
			if (directory[directory.length() - 1] != '\\')
			{
				directory += '\\';
			}

			if (!file_name.find('.'))
			{
				file_name += ".txt";
			}

			directory += file_name;

			if (stat(directory.c_str(), &storage) != 0 || (storage.st_mode & S_IFDIR))
			{
				return false;
			}

			std::remove(directory.c_str());

			return true;
		}
	}
};
