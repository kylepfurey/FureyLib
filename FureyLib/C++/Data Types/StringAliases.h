
// String Alias Replacement Script
// by Kyle Furey

#pragma once
#include <string>
#include <vector>
#include <map>
#include <algorithm>

// Include this heading to use the class
#include "StringAliases.h"

// Forward declaration of string_aliases
class string_aliases;

// Provides simple storage for string replacements.
class string_aliases
{
private:

	// VARIABLES

	// The strings to locate for replacement
	std::vector<std::string> identifiers = std::vector<std::string>();

	// The strings to replace the identifier with
	std::vector<std::string> values = std::vector<std::string>();


	// FUNCTIONS

	// Returns the index of the given value in a vector.
	template <typename DataType> static int index_of(std::vector<DataType> vector, DataType element)
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

public:

	// VARIABLES

	// Collection of globally used aliases
	static string_aliases global_aliases;


	// FUNCTIONS

	// Removes whitespace characters from the beginning and end of a string
	static std::string remove_whitespace(std::string value, bool lower = false)
	{
		if (value == " ")
		{
			return "";
		}

		for (int i = 0; i < value.length(); i++)
		{
			if (value[i] == '\n')
			{
				value.replace(i, 1, "");

				i--;
			}
		}

		while (value[0] == ' ')
		{
			value = value.replace(0, 1, "");
		}

		while (value[value.length() - 1] == ' ')
		{
			value = value.replace(value.length() - 2, 1, "");
		}

		if (lower)
		{
			std::transform(value.begin(), value.end(), value.begin(),
			[](unsigned char character)
			{
				return std::tolower(character);
			});
		}

		return value;
	}

	// Adds a new entry or replaces a entry in the list of aliases
	string_aliases& add(std::string identifier, std::string value)
	{
		identifier = remove_whitespace(identifier);

		value = remove_whitespace(value);

		if (identifier == "" || value == "" || identifier == value)
		{
			return *this;
		}

		int index = index_of(identifiers, identifier);

		if (index == -1)
		{
			identifiers.push_back(identifier);

			values.push_back(value);
		}
		else
		{
			values[index] = value;
		}

		return *this;
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
	string_aliases& remove_at(int index)
	{
		if (index >= 0 && index < identifiers.size())
		{
			identifiers.erase(identifiers.begin() + index);

			values.erase(identifiers.begin() + index);
		}

		return *this;
	}

	// Clears the list of aliases
	string_aliases& clear()
	{
		identifiers.clear();

		values.clear();

		return *this;
	}

	// Replaces all aliases in the given message with their corresponding values. Replaces once, in order of each alias.
	std::string replace_aliases(std::string message)
	{
		for (int i = 0; i < identifiers.size(); i++)
		{
			if (message == identifiers[i])
			{
				message = values[i];

				i -= 1;

				continue;
			}

			int index = message.find(identifiers[i] + " ");

			if (index != message.npos)
			{
				message = message.erase(index, identifiers[i].size() + 1);

				message = message.insert(index, values[i] + " ");

				i -= 1;

				continue;
			}

			index = message.find(" " + identifiers[i]);

			if (index != message.npos)
			{
				message = message.erase(index, identifiers[i].size() + 1);

				message = message.insert(index, " " + values[i]);

				i -= 1;

				continue;
			}
		}

		return message;
	}

	// Replaces all of the given aliases in the given message with their corresponding values. Replaces once, in order of each alias.
	std::string replace_aliases(std::string message, int count, std::string identifiers[])
	{
		for (int j = 0; j < count; j++)
		{
			int i = index_of(this->identifiers, identifiers[j]);

			if (i == -1)
			{
				continue;
			}

			if (message == this->identifiers[i])
			{
				message = values[i];

				j -= 1;

				continue;
			}

			int index = message.find(this->identifiers[i] + " ");

			if (index != message.npos)
			{
				message = message.erase(index, this->identifiers[i].length() + 1);

				message = message.insert(index, values[i] + " ");

				j -= 1;

				continue;
			}

			index = message.find(" " + this->identifiers[i]);

			if (index != message.npos)
			{
				message = message.erase(index, this->identifiers[i].length() + 1);

				message = message.insert(index, " " + values[i]);

				j -= 1;

				continue;
			}
		}

		return message;
	}

	// Replaces all aliases in the given message with their corresponding values. Repeats until all aliases are filled in.
	std::string replace_aliases_recursively(std::string message)
	{
		message = replace_aliases(message);

		std::string newMessage = replace_aliases(message);

		while (message != newMessage)
		{
			message = newMessage;

			newMessage = replace_aliases(message);
		}

		return message;
	}

	// Replaces all of the given aliases in the given message with their corresponding values. Repeats until all aliases are filled in.
	std::string replace_aliases_recursively(std::string message, int count, std::string identifiers[])
	{
		message = replace_aliases(message, count, identifiers);

		std::string newMessage = replace_aliases(message, count, identifiers);

		while (message != newMessage)
		{
			message = newMessage;

			newMessage = replace_aliases(message, count, identifiers);
		}

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

		int index = index_of(identifiers, identifier);

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

		int index = index_of(values, value);

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
string_aliases string_aliases::global_aliases = string_aliases();

// Forward declaration of StringAliases
class StringAliases;

// Provides simple storage for string replacements.
class StringAliases
{
private:

	// VARIABLES

	// The strings to locate for replacement
	std::vector<std::string> identifiers = std::vector<std::string>();

	// The strings to replace the identifier with
	std::vector<std::string> values = std::vector<std::string>();


	// FUNCTIONS

	// Returns the index of the given value in a vector.
	template <typename DataType> static int IndexOf(std::vector<DataType> vector, DataType element)
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

public:

	// VARIABLES

	// Collection of globally used aliases
	static StringAliases globalAliases;


	// FUNCTIONS

	// Removes whitespace characters from the beginning and end of a string
	static std::string RemoveWhitespace(std::string value, bool lower = false)
	{
		if (value == " ")
		{
			return "";
		}

		for (int i = 0; i < value.length(); i++)
		{
			if (value[i] == '\n')
			{
				value.replace(i, 1, "");

				i--;
			}
		}

		while (value[0] == ' ')
		{
			value = value.replace(0, 1, "");
		}

		while (value[value.length() - 1] == ' ')
		{
			value = value.replace(value.length() - 2, 1, "");
		}

		if (lower)
		{
			std::transform(value.begin(), value.end(), value.begin(),
			[](unsigned char character)
			{
				return std::tolower(character);
			});
		}

		return value;
	}

	// Adds a new entry or replaces a entry in the list of aliases
	StringAliases& Add(std::string identifier, std::string value)
	{
		identifier = RemoveWhitespace(identifier);

		value = RemoveWhitespace(value);

		if (identifier == "" || value == "" || identifier == value)
		{
			return *this;
		}

		int index = IndexOf(identifiers, identifier);

		if (index == -1)
		{
			identifiers.push_back(identifier);

			values.push_back(value);
		}
		else
		{
			values[index] = value;
		}

		return *this;
	}

	// Removes the given identifier from the list of aliases and return the index
	int Remove(std::string identifier)
	{
		identifier = RemoveWhitespace(identifier);

		int index = IndexOf(identifiers, identifier);

		if (index != -1)
		{
			identifiers.erase(identifiers.begin() + index);

			values.erase(identifiers.begin() + index);
		}

		return index;
	}

	// Removes the given identifier from the list of aliases
	StringAliases& RemoveAt(int index)
	{
		if (index >= 0 && index < identifiers.size())
		{
			identifiers.erase(identifiers.begin() + index);

			values.erase(identifiers.begin() + index);
		}

		return *this;
	}

	// Clears the list of aliases
	StringAliases& Clear()
	{
		identifiers.clear();

		values.clear();

		return *this;
	}

	// Replaces all aliases in the given message with their corresponding values. Replaces once, in order of each alias.
	std::string ReplaceAliases(std::string message)
	{
		for (int i = 0; i < identifiers.size(); i++)
		{
			if (message == identifiers[i])
			{
				message = values[i];

				i -= 1;

				continue;
			}

			int index = message.find(identifiers[i] + " ");

			if (index != message.npos)
			{
				message = message.erase(index, identifiers[i].size() + 1);

				message = message.insert(index, values[i] + " ");

				i -= 1;

				continue;
			}

			index = message.find(" " + identifiers[i]);

			if (index != message.npos)
			{
				message = message.erase(index, identifiers[i].size() + 1);

				message = message.insert(index, " " + values[i]);

				i -= 1;

				continue;
			}
		}

		return message;
	}

	// Replaces all of the given aliases in the given message with their corresponding values. Replaces once, in order of each alias.
	std::string ReplaceAliases(std::string message, int count, std::string identifiers[])
	{
		for (int j = 0; j < count; j++)
		{
			int i = IndexOf(this->identifiers, identifiers[j]);

			if (i == -1)
			{
				continue;
			}

			if (message == this->identifiers[i])
			{
				message = values[i];

				j -= 1;

				continue;
			}

			int index = message.find(this->identifiers[i] + " ");

			if (index != message.npos)
			{
				message = message.erase(index, this->identifiers[i].length() + 1);

				message = message.insert(index, values[i] + " ");

				j -= 1;

				continue;
			}

			index = message.find(" " + this->identifiers[i]);

			if (index != message.npos)
			{
				message = message.erase(index, this->identifiers[i].length() + 1);

				message = message.insert(index, " " + values[i]);

				j -= 1;

				continue;
			}
		}

		return message;
	}

	// Replaces all aliases in the given message with their corresponding values. Repeats until all aliases are filled in.
	std::string ReplaceAliasesRecursively(std::string message)
	{
		message = ReplaceAliases(message);

		std::string newMessage = ReplaceAliases(message);

		while (message != newMessage)
		{
			message = newMessage;

			newMessage = ReplaceAliases(message);
		}

		return message;
	}

	// Replaces all of the given aliases in the given message with their corresponding values. Repeats until all aliases are filled in.
	std::string ReplaceAliasesRecursively(std::string message, int count, std::string identifiers[])
	{
		message = ReplaceAliases(message, count, identifiers);

		std::string newMessage = ReplaceAliases(message, count, identifiers);

		while (message != newMessage)
		{
			message = newMessage;

			newMessage = ReplaceAliases(message, count, identifiers);
		}

		return message;
	}

	// Returns whether the list of aliases contains the given identifier
	bool Contains(std::string identifier)
	{
		identifier = RemoveWhitespace(identifier);

		return IndexOf(identifiers, identifier) != -1;
	}

	// Returns the index of the given identifier
	int Find(std::string identifier)
	{
		identifier = RemoveWhitespace(identifier);

		return IndexOf(identifiers, identifier);
	}

	// Returns the total number of aliases
	int Count()
	{
		return identifiers.size();
	}

	// Returns the corresponding value of the given index
	std::string GetValue(int index)
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
	std::string GetIdentifier(int index)
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
	std::string GetValue(std::string identifier)
	{
		identifier = RemoveWhitespace(identifier);

		int index = IndexOf(identifiers, identifier);

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
	std::string GetIdentifier(std::string value)
	{
		value = RemoveWhitespace(value);

		int index = IndexOf(values, value);

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
	std::vector<std::string> GetIdentifiers()
	{
		return identifiers;
	}

	// Returns a vector of the values
	std::vector<std::string> GetValues()
	{
		return values;
	}

	// Returns a map of identifiers to values
	std::map<std::string, std::string> GetMap()
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
StringAliases StringAliases::globalAliases = StringAliases();
