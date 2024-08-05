
// Static File Functions Script
// by Kyle Furey

#pragma once
#include <string>
#include <fstream>
#include <cstdlib>
#include <sys/stat.h>

// Include this heading to use the library.
#include "file.h"

// Provides easy to use read and write file management functions.
class file
{
public:

	// FILES

	// •  Reads a file at the given path and returns its content.
	// •  Returns the imported file's text.
	// •  Throws an exception if the file is not valid.
	static std::string load(std::string path)
	{
		struct stat storage;

		if (stat(path.c_str(), &storage) != 0)
		{
			std::abort();
		}

		std::ifstream file = std::ifstream(path);

		std::string text = "";

		std::string current = "";

		while (std::getline(file, current))
		{
			text += current + "\n";
		}

		file.close();

		return text;
	}

	// •  Creates or overwrites a file of the given text to the given path.
	// •  Returns whether a file was overwritten.
	static bool save(std::string text, std::string path)
	{
		struct stat storage;

		bool overwrite = (stat(path.c_str(), &storage) == 0);

		std::ofstream file = std::ofstream(path);

		file << text << std::endl;

		file.close();

		return overwrite;
	}

	// •  Deletes the file at the given path.
	// •  Returns whether the file's deletion was successful.
	// •  Throws an exception if the file is not valid.
	static bool erase(std::string path)
	{
		struct stat storage;

		if (stat(path.c_str(), &storage) != 0)
		{
			std::abort();
		}
		else
		{
			std::remove(path.c_str());

			return true;
		}
	}

	// Returns whether the given path leads to a file.
	static bool exists(std::string path)
	{
		struct stat storage;

		return stat(path.c_str(), &storage) == 0;
	}

private:

	// TO LOWER

	// Converts the given string to lowercase.
	static std::string to_lower(std::string string)
	{
		std::string lower = "";

		for (char letter : string)
		{
			lower += tolower(letter);
		}

		return lower;
	}
};
