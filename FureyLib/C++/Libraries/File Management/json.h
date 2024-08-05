
// Static Json Serialization Functions Script
// by Kyle Furey

// REQUIREMENT: Json Serializer or object.h

#pragma once
#include <string>
#include <fstream>
#include <cstdlib>
#include <sys/stat.h>
#include "object.h" // Serializer

// Include this heading to use the library.
#include "json.h"

// •  Serializes and deserializes data to and from Json files.
// •  Uses the virtual functions to_json() and read_json() from the serializer base class to serialize and deserialize derived objects.
class json
{
public:

	// SERIALIZATION

	// •  Converts the given data into a Json formatted string.
	// •  Returns the Json formatted string of the given data.
	static std::string serialize(object* data)
	{
		return data->to_json();
	}

	// •  Converts the given data into a Json formatted string.
	// •  Returns the Json formatted string of the given data.
	template <typename data_type> static std::string serialize(data_type& data)
	{
		return data.to_json();
	}

	// •  Reads the given Json formatted string as the given type.
	// •  Returns he deserialized Json string's corresponding values.
	template <typename data_type> static data_type deserialize(std::string json)
	{
		data_type obj = data_type();

		obj.read_json(json);

		return obj;
	}


	// IMPORT AND EXPORT

	// •  Reads a Json file at the given path and returns its data.
	// •  Returns the imported Json file's corresponding values.
	// •  Throws an exception if the file is not a valid Json file.
	template <typename data_type> static data_type load(std::string path)
	{
		if (to_lower(path).find(".json") == std::string::npos)
		{
			std::abort();
		}

		struct stat storage;

		if (stat(path.c_str(), &storage) != 0)
		{
			std::abort();
		}

		std::ifstream file = std::ifstream(path);

		std::string json = "";

		std::string current = "";

		while (std::getline(file, current))
		{
			json += current + "\n";
		}

		file.close();

		return deserialize<data_type>(json);
	}

	// •  Creates or overwrites a Json file of the given data to the given path.
	// •  Returns whether a Json file was overwritten.
	// •  Throws an exception if the destination is not a valid Json file.
	static bool save(object* data, std::string path)
	{
		if (to_lower(path).find(".json") == std::string::npos)
		{
			return false;
		}

		struct stat storage;

		bool overwrite = (stat(path.c_str(), &storage) == 0);

		std::ofstream file = std::ofstream(path);

		file << serialize(data) << std::endl;

		file.close();

		return overwrite;
	}

	// •  Creates or overwrites a Json file of the given data to the given path.
	// •  Returns whether a Json file was overwritten.
	// •  Throws an exception if the destination is not a valid Json file.
	template <typename data_type> static bool save(data_type& data, std::string path)
	{
		if (to_lower(path).find(".json") == std::string::npos)
		{
			std::abort();
		}

		struct stat storage;

		bool overwrite = (stat(path.c_str(), &storage) == 0);

		std::ofstream file = std::ofstream(path);

		file << serialize(data) << std::endl;

		file.close();

		return overwrite;
	}

	// •  Deletes the Json file at the given path.
	// •  Returns whether the file's deletion was successful.
	// •  Throws an exception if the file is not a valid Json file.
	static bool erase(std::string path)
	{
		if (to_lower(path).find(".json") == std::string::npos)
		{
			std::abort();
		}

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

	// Returns whether the given path leads to a Json file.
	static bool exists(std::string path)
	{
		if (to_lower(path).find(".json") == std::string::npos)
		{
			return false;
		}

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
