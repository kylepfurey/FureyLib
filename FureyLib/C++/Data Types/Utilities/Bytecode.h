// .h
// Bytecode Reader Class
// by Kyle Furey

#pragma once
#include <array>
#include <functional>
#include <cstdint>
#include <optional>
#include <fstream>
#include <stdexcept>

/** A class used to read a file as bytecode mapped to different operation functions. */
class Bytecode final {

	// VARIABLES

	/** The total number of operations bound. */
	size_t count;

	/** Each mapped byte to each operation. */
	std::array<std::optional<std::function<bool(std::istream&)>>, 256> operations;

public:

	// CONSTRUCTORS

	/** Default constructor. */
	Bytecode() : count(0), operations() {
	}


	// OPERATORS

	/** Returns a reference to the operation mapped to a specific byte. */
	std::optional<std::function<bool(std::istream&)>>& operator[](const std::uint8_t byte) {
		return operations[byte];
	}

	/** Returns a constant reference to the operation mapped to a specific byte. */
	const std::optional<std::function<bool(std::istream&)>>& operator[](const std::uint8_t byte) const {
		return operations[byte];
	}


	// GETTERS

	/** Returns a reference to the operation mapped to a specific byte. */
	std::optional<std::function<bool(std::istream&)>>& GetOperation(const std::uint8_t byte) {
		return operations[byte];
	}

	/** Returns a constant reference to the operation mapped to a specific byte. */
	const std::optional<std::function<bool(std::istream&)>>& GetOperation(const std::uint8_t byte) const {
		return operations[byte];
	}

	/** Returns a reference to all mapped operations. */
	std::array<std::optional<std::function<bool(std::istream&)>>, 256>& GetOperations() {
		return operations;
	}

	/** Returns a constant reference to all mapped operations. */
	const std::array<std::optional<std::function<bool(std::istream&)>>, 256>& GetOperations() const {
		return operations;
	}


	// SETTERS

	/** Returns the total number of bound operations. */
	size_t OperationCount() const {
		return count;
	}

	/** Returns whether the given byte is mapped to an operation. */
	bool IsOperationBound(const std::uint8_t byte) const {
		return operations[byte].has_value();
	}

	/**
	 * Binds a new operation with the given byte and returns whether the operation was successfully bound.
	 * Each operation is a function that inputs the bytestream and outputs whether the operation was successful.
	 */
	bool BindOperation(const std::uint8_t byte, const std::function<bool(std::istream&)>& operation) {
		if (operations[byte].has_value()) {
			return false;
		}
		operations[byte] = operation;
		++count;
		return true;
	}

	/**
	 * Binds a new operation with the given byte and returns whether another operation was overwritten.
	 * Each operation is a function that inputs the bytestream and outputs whether the operation was successful.
	 */
	bool ReplaceOperation(const std::uint8_t byte, const std::function<bool(std::istream&)>& operation) {
		if (operations[byte].has_value()) {
			operations[byte] = operation;
			return true;
		}
		operations[byte] = operation;
		++count;
		return false;
	}

	/**
	 * Unbinds the operation that matches the given byte and returns whether the operation was successfully unbound.
	 * Each operation is a function that inputs the bytestream and outputs whether the operation was successful.
	 */
	bool UnbindOperation(const std::uint8_t byte) {
		if (!operations[byte].has_value()) {
			return false;
		}
		operations[byte].reset();
		--count;
		return true;
	}

	/** Clears all bound operations. */
	void Clear() {
		for (auto& operation : operations) {
			operation.reset();
		}
		count = 0;
	}


	// METHODS

	/** Executes the given stream as bytecode and returns whether the stream was successfully executed. */
	bool Execute(std::istream& stream) const {
		try {
			std::uint8_t operation;
			while (stream.read((char*)&operation, 1)) {
				if (!operations[operation].value()(stream)) {
					return false;
				}
			}
			return true;
		}
		catch (const std::exception&) {
			return false;
		}
	}

	/** Executes the given file as bytecode and returns whether the file was successfully executed. */
	bool Execute(const std::string& filePath) const {
		try {
			std::ifstream file(filePath, std::ios::binary);
			if (!file.is_open()) {
				return false;
			}
			const bool result = Execute(file);
			file.close();
			return result;
		}
		catch (const std::exception&) {
			return false;
		}
	}
};
