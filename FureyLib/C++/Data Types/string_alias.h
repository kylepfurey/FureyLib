
// String Alias Replacement Script
// by Kyle Furey

#pragma once
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdarg>

// Include this heading to use the class
#include "string_alias.h"

// Forward declaration of string_alias
class string_alias;

// Provides simple storage for string replacements.
class string_alias
{
private:

	// VARIABLES

	// The strings to locate for replacement
	std::vector<std::string> identifiers = std::vector<std::string>();

	// The strings to replace the identifier with
	std::vector<std::string> values = std::vector<std::string>();


	// FUNCTIONS

	// Returns the index of the given value in a vector.
	template <typename data_type> static int index_of(std::vector<data_type> vector, data_type element)
	{
		for (int i = 0; i < vector.size(); i++)
		{
			if (vector[i] == element)
			{
				return i;
			}
		}

		return -1;
	}

	// Replaces all character in a string with another character
	static std::string replace(std::string base, char find, char replace)
	{
		std::string replaced;

		for (int i = 0; i < base.length(); i++)
		{
			replaced += base[i] == find ? replace : base[i];
		}

		return replaced;
	}

public:

	// VARIABLES

	// Collection of globally used aliases
	static string_alias global_aliases;

	// Whitespace characters to ignore when parsing messages
	std::vector<char> whitespace_characters =
	{ '.', '?', '!', '+', '-', '*', '/', '=', '\n', '`', '~', '@', '#', '$', '%', '^', '&', '(', ')', '[', ']', '{', '}', '\\', ';', ':', '\'', ',', '<', '>', '"', '|' };


	// FUNCTIONS

	// Removes whitespace characters from the beginning and end of a string
	std::string remove_whitespace(std::string value)
	{
		if (value == " ")
		{
			return "";
		}

		for (int i = 0; i < whitespaceCharacters.size(); i++)
		{
			value = replace(value, whitespace_characters[i], ' ');
		}

		while (value[0] == ' ')
		{
			value = value.replace(0, 1, "");
		}

		while (value[value.length() - 1] == ' ')
		{
			value = value.replace(value.length() - 1, 1, "");
		}

		return value;
	}

	// Adds a new entry or replaces a entry in the list of aliases
	int add(std::string identifier, std::string value)
	{
		identifier = remove_whitespace(identifier);

		value = remove_whitespace(value);

		if (identifier == value || identifier == "" || value == "")
		{
			return -1;
		}

		int index = index_of(identifiers, identifier);

		if (index == -1)
		{
			identifiers.push_back(identifier);

			values.push_back(value);

			return identifiers.size() - 1;
		}
		else
		{
			values[index] = value;

			return index;
		}
	}

	// Removes the given identifier from the list of aliases and return the index
	int remove(std::string identifier)
	{
		identifier = remove_whitespace(identifier);

		int index = index_of(identifiers, identifier);

		if (index != -1)
		{
			identifiers.erase(identifiers.begin() + index);

			values.erase(identifiers.begin() + index);
		}

		return index;
	}

	// Removes the given index from the list of aliases
	bool remove_at(int index)
	{
		if (index >= 0 && index < identifiers.size())
		{
			identifiers.erase(identifiers.begin() + index);

			values.erase(identifiers.begin() + index);

			return true;
		}
		else
		{
			return false;
		}
	}

	// Clears the list of aliases
	int clear()
	{
		int count = identifiers.size();

		identifiers.clear();

		values.clear();

		return count;
	}

	// Replaces all aliases in the given message with their corresponding values in order of each alias.
	std::string replace_aliases(std::string message)
	{
		std::string temp_message = message;

		for (int i = 0; i < whitespace_characters.size(); i++)
		{
			temp_message = replace(temp_message, whitespace_characters[i], ' ');
		}

		for (int i = 0; i < identifiers.size(); i++)
		{
			if (message == identifiers[i])
			{
				message = values[i];

				continue;
			}

			std::string gap = "";

			for (int j = 0; j < values[i].length(); j++)
			{
				gap += " ";
			}

			int index = temp_message.find(" " + identifiers[i] + " ");

			if (index != -1)
			{
				message = message.erase(index + 1, identifiers[i].length());

				message = message.insert(index + 1, values[i]);

				temp_message = temp_message.erase(index + 1, identifiers[i].length());

				temp_message = temp_message.insert(index + 1, gap);

				i--;

				continue;
			}

			index = temp_message.find(identifiers[i] + " ");

			if (index == 0)
			{
				message = message.erase(index, identifiers[i].length());

				message = message.insert(index, values[i]);

				temp_message = temp_message.erase(index, identifiers[i].length());

				temp_message = temp_message.insert(index + 1, gap);

				i--;

				continue;
			}

			index = temp_message.find(" " + identifiers[i]);

			if (index == message.length() - identifiers[i].length() - 1)
			{
				message = message.erase(index + 1, identifiers[i].length());

				message = message.insert(index + 1, values[i]);

				temp_message = temp_message.erase(index + 1, identifiers[i].length());

				temp_message = temp_message.insert(index + 1, gap);

				i--;

				continue;
			}
		}

		return message;
	}

	// Replaces all of the given aliases in the given message with their corresponding values in order of each alias.
	std::string replace_aliases(std::string message, int count, std::string identifiers[])
	{
		for (int i = 0; i < count; i++)
		{
			identifiers[i] = remove_whitespace(identifiers[i]);
		}

		std::string temp_message = message;

		for (int i = 0; i < whitespace_characters.size(); i++)
		{
			temp_message = replace(temp_message, whitespace_characters[i], ' ');
		}

		for (int j = 0; j < count; j++)
		{
			int i = index_of(this->identifiers, identifiers[j]);

			if (message == this->identifiers[i])
			{
				message = values[i];

				continue;
			}

			std::string gap = "";

			for (int j = 0; j < values[i].length(); j++)
			{
				gap += " ";
			}

			int index = temp_message.find(" " + this->identifiers[i] + " ");

			if (index != -1)
			{
				message = message.erase(index + 1, this->identifiers[i].length());

				message = message.insert(index + 1, values[i]);

				temp_message = temp_message.erase(index + 1, this->identifiers[i].length());

				temp_message = temp_message.insert(index + 1, gap);

				j--;

				continue;
			}

			index = temp_message.find(this->identifiers[i] + " ");

			if (index == 0)
			{
				message = message.erase(index, this->identifiers[i].length());

				message = message.insert(index, values[i]);

				temp_message = temp_message.erase(index, this->identifiers[i].length());

				temp_message = temp_message.insert(index + 1, gap);

				j--;

				continue;
			}

			index = temp_message.find(" " + this->identifiers[i]);

			if (index == message.length() - this->identifiers[i].length() - 1)
			{
				message = message.erase(index + 1, this->identifiers[i].length());

				message = message.insert(index + 1, values[i]);

				temp_message = temp_message.erase(index + 1, this->identifiers[i].length());

				temp_message = temp_message.insert(index + 1, gap);

				j--;

				continue;
			}
		}

		return message;
	}

	// Replaces all of the given aliases in the given message with their corresponding values in order of each alias.
	std::string replace_aliases(std::string message, int count, std::string strings...)
	{
		std::string* identifiers = new std::string[count];

		va_list list;

		va_start(list, count);

		for (int i = 0; i < count; i++)
		{
			identifiers[i] = strings;

			identifiers[i] = remove_whitespace(identifiers[i]);

			strings = va_arg(list, std::string);
		}

		va_end(list);

		std::string temp_message = message;

		for (int i = 0; i < whitespace_characters.size(); i++)
		{
			temp_message = replace(temp_message, whitespace_characters[i], ' ');
		}

		for (int j = 0; j < count; j++)
		{
			int i = index_of(this->identifiers, identifiers[j]);

			if (message == this->identifiers[i])
			{
				message = values[i];

				continue;
			}

			std::string gap = "";

			for (int j = 0; j < values[i].length(); j++)
			{
				gap += " ";
			}

			int index = temp_message.find(" " + this->identifiers[i] + " ");

			if (index != -1)
			{
				message = message.erase(index + 1, this->identifiers[i].length());

				message = message.insert(index + 1, values[i]);

				temp_message = temp_message.erase(index + 1, this->identifiers[i].length());

				temp_message = temp_message.insert(index + 1, gap);

				j--;

				continue;
			}

			index = temp_message.find(this->identifiers[i] + " ");

			if (index == 0)
			{
				message = message.erase(index, this->identifiers[i].length());

				message = message.insert(index, values[i]);

				temp_message = temp_message.erase(index, this->identifiers[i].length());

				temp_message = temp_message.insert(index + 1, gap);

				j--;

				continue;
			}

			index = temp_message.find(" " + this->identifiers[i]);

			if (index == message.length() - this->identifiers[i].length() - 1)
			{
				message = message.erase(index + 1, this->identifiers[i].length());

				message = message.insert(index + 1, values[i]);

				temp_message = temp_message.erase(index + 1, this->identifiers[i].length());

				temp_message = temp_message.insert(index + 1, gap);

				j--;

				continue;
			}
		}

		delete[] identifiers;

		return message;
	}

	// Returns whether the list of aliases contains the given identifier
	bool contains(std::string identifier)
	{
		identifier = remove_whitespace(identifier);

		return index_of(identifiers, identifier) != -1;
	}

	// Returns the index of the given identifier
	int find(std::string identifier)
	{
		identifier = remove_whitespace(identifier);

		return index_of(identifiers, identifier);
	}

	// Returns the total number of aliases
	int count()
	{
		return identifiers.size();
	}

	// Returns the corresponding value of the given index
	std::string get_value(int index)
	{
		if (index >= 0 && index < values.size())
		{
			return values[index];
		}
		else
		{
			return "";
		}
	}

	// Returns the corresponding identifier of the given index
	std::string get_identifier(int index)
	{
		if (index >= 0 && index < identifiers.size())
		{
			return identifiers[index];
		}
		else
		{
			return "";
		}
	}

	// Returns the corresponding value of the given identifier
	std::string get_value(std::string identifier)
	{
		identifier = remove_whitespace(identifier);

		int index = index_of(values, identifier);

		if (index != -1)
		{
			return values[index];
		}
		else
		{
			return "";
		}
	}

	// Returns the corresponding identifier of the given value
	std::string get_identifier(std::string value)
	{
		value = remove_whitespace(value);

		int index = index_of(identifiers, value);

		if (index != -1)
		{
			return identifiers[index];
		}
		else
		{
			return "";
		}
	}

	// Returns a vector of the identifiers
	std::vector<std::string> get_identifiers()
	{
		return identifiers;
	}

	// Returns a vector of the values
	std::vector<std::string> get_values()
	{
		return values;
	}

	// Returns a map of identifiers to values
	std::map<std::string, std::string> get_map()
	{
		std::map<std::string, std::string> map = std::map<std::string, std::string>();

		for (int i = 0; i < identifiers.size(); i++)
		{
			map[identifiers[i]] = values[i];
		}

		return map;
	}
};

// Static variable initialization
string_alias string_alias::global_aliases = string_alias();
