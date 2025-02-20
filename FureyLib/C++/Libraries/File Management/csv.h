// .h
// CSV Static Function Library
// by Kyle Furey

#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>

/** Provides functions for converting comma separated values (.csv) files into a collection and back into a file. */
namespace csv {
	// COLLECTION

	/** A collection of data that contains a map of a CSV’s rows to its columns to that row’s value at that column. */
	using csv_collection = std::unordered_map<std::string, std::unordered_map<std::string, std::string>>;

	// TO / FROM STRING

	/** Converts the given .csv string to a CSV collection, if possible. */
	static csv_collection from_csv(const std::string& csv, const bool ignore_quotes = false) {
		if (csv.empty()) {
			return {};
		}
		auto columns = std::vector<std::string>();
		std::string current = "";
		bool ignore_comma = false;
		int column_index = 0;
		for (const char character : csv) {
			if (character == '\n') {
				columns.push_back(current);
				current = "";
				break;
			}
			switch (character) {
			case '"':
			case '\'':
				if (!ignore_quotes) {
					ignore_comma = !ignore_comma;
					current += character;
				}
				break;
			case ',':
			case ';':
				if (ignore_comma) {
					current += character;
				}
				else {
					columns.push_back(current);
					current = "";
				}
				break;
			default:
				current += character;
				break;
			}
			++column_index;
		}
		if (columns.size() == 0) {
			return {};
		}
		auto collection = csv_collection();
		current = "";
		ignore_comma = false;
		std::string row = "";
		int i = column_index + 1;
		column_index = 0;
		for (; i < csv.length(); i++) {
			switch (csv[i]) {
			case '\n':
				if (column_index < columns.size() && collection.count(row)) {
					collection[row][columns[column_index]] = current;
				}
				current = "";
				column_index = 0;
				row = "";
				break;
			case '"':
			case '\'':
				if (!ignore_quotes) {
					ignore_comma = !ignore_comma;
					current += csv[i];
				}
				break;
			case ',':
			case ';':
				if (ignore_comma) {
					current += csv[i];
				}
				else {
					if (column_index == 0) {
						row = current;
						collection[row] = std::unordered_map<std::string, std::string>();
					}
					if (column_index < columns.size()) {
						collection[row][columns[column_index]] = current;
					}
					++column_index;
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

	/** Converts the given CSV collection to a .csv string, if possible. */
	static std::string to_csv(const csv_collection& collection, const bool add_quotes = false) {
		if (collection.empty()) {
			return "";
		}
		std::string csv = "";
		for (const auto& row : collection) {
			if (csv.length() == 0) {
				for (const auto& column : row.second) {
					if (add_quotes) {
						csv += '"' + column.first + "\",";
					}
					else {
						csv += column.first + ',';
					}
				}
				csv = csv.erase(csv.length() - 1, 1) + '\n';
			}
			for (const auto& column : row.second) {
				if (add_quotes) {
					csv += '"' + collection.at(row.first).at(column.first) + "\",";
				}
				else {
					csv += collection.at(row.first).at(column.first) + ',';
				}
			}
			csv = csv.erase(csv.length() - 1, 1) + '\n';
		}
		return csv;
	}

	// IMPORT / EXPORT

	/** Imports and returns a CSV collection from the .csv file at the give path, if possible. */
	static csv_collection import_csv(std::string path, const bool ignore_quotes = false) {
		if (path.find('.') == std::string::npos) {
			path += ".csv";
		}
		std::ifstream file(path);
		if (!file.is_open()) {
			return {};
		}
		std::stringstream buffer;
		buffer << file.rdbuf();
		file.close();
		return from_csv(buffer.str(), ignore_quotes);
	}

	/** Saves the given CSV collection to the given path, and returns whether it was successful. */
	static bool export_csv(const csv_collection& collection, std::string path, const bool add_quotes = false) {
		if (path.find('.') == std::string::npos) {
			path += ".csv";
		}
		std::ofstream file(path);
		if (!file.is_open()) {
			return false;
		}
		file << to_csv(collection, add_quotes);
		file.close();
		return true;
	}

	// COLLECTION METHODS

	/** Returns the comma separated value at the given row and column of the given CSV collection. */
	static std::string get_value(const csv_collection& collection, const std::string& row, const std::string& column) {
		if (collection.count(row)) {
			if (collection.at(row).count(column)) {
				return collection.at(row).at(column);
			}
		}
		return "";
	}

	/** Returns a list of the given CSV collection's columns. */
	static std::vector<std::string> get_columns(const csv_collection& collection) {
		auto columns = std::vector<std::string>();
		for (const auto& row : collection) {
			for (const auto& column : row.second) {
				columns.push_back(column.first);
			}

			return columns;
		}
		return columns;
	}

	/** Returns a list of the given CSV collection's rows. */
	static std::vector<std::string> get_rows(const csv_collection& collection) {
		std::vector<std::string> rows;
		for (const auto& row : collection) {
			rows.push_back(row.first);
		}
		return rows;
	}
}
