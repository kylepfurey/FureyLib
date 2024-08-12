
// Byte Data Type Header Script
// by Kyle Furey

// REQUIREMENT: byte.cpp

#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

// Include this heading to use the class
#include "byte.h"

// Emulates a single byte of memory through 8 boolean bits.
class byte
{
public:

	// Instance Byte Data

	std::vector<bool> bits;													// The 8 bits that make up the Byte
	bool is_unsigned = true;												// Whether this Byte is unsigned


	// Constructors and Destructors

	byte();																	// Constructor
	byte(byte& byte);														// Constructor (Byte)
	byte(bool boolean, bool is_unsigned);									// Constructor (Boolean)
	byte(std::vector<bool> new_bits);										// Constructor (Bits)
	byte(std::vector<bool> new_bits, bool is_unsigned);						// Constructor (Bits)
	byte(int new_bits[8]);													// Constructor (Int Bits)
	byte(int new_bits[8], bool is_unsigned);								// Constructor (Int Bits)
	byte(signed int integer);												// Constructor (Integer)
	byte(signed int integer, bool is_unsigned);								// Constructor (Integer)
	byte(unsigned int integer);												// Constructor (Unsigned Integer)
	byte(unsigned int integer, bool is_unsigned);							// Constructor (Unsigned Integer)
	byte(std::string new_string);											// Constructor (String)
	byte(std::string new_string, bool is_unsigned);							// Constructor (String)
	~byte();																// Destructor


	// Static Byte Conversions

	static byte& to_byte(std::vector<bool> bits);							// Convert Bits to Byte
	static byte& to_byte(int bits[8]);										// Convert Int Bits to Byte
	static byte& to_byte(signed int integer); 								// Convert Int to Byte
	static byte& to_byte(unsigned int integer);								// Convert Unsigned Int to Byte
	static byte& to_byte(std::string new_string);							// Convert String to Byte


	// Static Bit Conversions

	static std::vector<bool> to_bits(byte byte);							// Convert Byte to Bits
	static std::vector<bool> to_bits(int bits[8]);							// Convert Int Bits to Bits
	static std::vector<bool> to_bits(signed int integer);					// Convert Int to Bits
	static std::vector<bool> to_bits(unsigned int integer);					// Convert Unsigned Int to Bits
	static std::vector<bool> to_bits(std::string new_string);				// Convert String to Bits


	// Static Int Bit Conversions

	static int* to_bits_int(std::vector<bool> bits);						// Convert Bits to Int Bits
	static int* to_bits_int(byte byte);										// Convert Byte to Int Bits
	static int* to_bits_int(signed int integer);							// Convert Int to Int Bits
	static int* to_bits_int(unsigned int integer);							// Convert Unsigned Int to Int Bits
	static int* to_bits_int(std::string new_string);						// Convert String to Int Bits


	// Static Int Conversions

	static signed int to_int(std::vector<bool> bits);						// Convert Bits to Int
	static signed int to_int(byte byte);									// Convert Byte to Int
	static signed int to_int(int bits[8]);									// Convert Int Bits to Int
	static signed int to_int(unsigned int integer);							// Convert Unsigned Int to Int
	static signed int to_int(std::string new_string);						// Convert String to Int


	// Static Unsigned Int Conversions

	static unsigned int to_unsigned_int(std::vector<bool> bits);			// Convert Bits to Unsigned Int
	static unsigned int to_unsigned_int(byte byte);							// Convert Byte to Unsigned Int
	static unsigned int to_unsigned_int(int bits[8]);						// Convert Int Bits to Unsigned Int
	static unsigned int to_unsigned_int(signed int integer);				// Convert Int to Unsigned Int
	static unsigned int to_unsigned_int(std::string new_string);			// Convert String to Unsigned Int


	// Static String Conversion

	static std::string to_string(std::vector<bool> bits);					// Convert Bits to String
	static std::string to_string(byte byte);								// Convert Byte to String
	static std::string to_string(int bits[8]);								// Convert Int Bits to String
	static std::string to_string(signed int integer);						// Convert Int to String
	static std::string to_string(unsigned int integer);						// Convert Unsigned Int to String


	// Static Mathematical Functions

	static byte add(byte byteA, byte byteB);								// Addition Function
	static byte plus_plus(byte byteA);										// ++ Function
	static byte increment(byte byteA);										// ++ Function
	static byte subtract(byte byteA, byte byteB);							// Subtraction Function
	static byte minus_minus(byte byteA);									// -- Function
	static byte decrement(byte byteA);										// -- Function
	static byte multiply(byte byteA, byte byteB);							// Multiplication Function
	static byte divide(byte byteA, byte byteB);								// Division Function
	static byte modulo(byte byteA, byte byteB);								// Modulo Function


	// Static Bitwise Functions

	static byte bit_and(byte byteA, byte byteB);							// And Function
	static byte bit_or(byte byteA, byte byteB);								// Or Function
	static byte bit_xor(byte byteA, byte byteB);							// Exclusive Or Function
	static byte bit_left_shift(byte byte, int shift);						// Left Shift Function
	static byte bit_right_shift(byte byte, int shift);						// Right Shift Function
	static byte bit_not(byte byte);											// Not Function


	// Static Logical Functions

	static bool equal_to(byte byteA, byte byteB);							// Equal To Function
	static bool not_equal_to(byte byteA, byte byteB);						// Not Equal To Function
	static bool greater_than(byte byteA, byte byteB);						// Greater Than Function
	static bool greater_than_equal_to(byte byteA, byte byteB);				// Greater Than Equal To Function
	static bool less_than(byte byteA, byte byteB);							// Less Than Function
	static bool less_than_equal_to(byte byteA, byte byteB);					// Less Than Equal To Function
	static bool boolean(byte byteA);										// Bool Function
	static bool not_boolean(byte byteA);									// Not Bool Function


	// Static Byte Array Conversions

	static byte copy(byte& bytes, int byte_count);							// Copies the Bytes
	static std::vector<bool> to_bits(byte& bytes, int byte_count);			// Converts Bytes to Bits
	static int* to_bits_int(byte& bytes, int byte_count);					// Converts Bytes to Int Bits
	static signed int to_int(byte& bytes, int byte_count);					// Converts Bytes to Int
	static unsigned int to_unsigned_int(byte& bytes, int byte_count);		// Converts Bytes to Unsigned Int
	static std::string to_string(byte& bytes, int byte_count);				// Converts Bytes to Int Bits
	static std::string to_string_2(byte& bytes, int byte_count);			// Converts Bytes to Int Bits (With Spaces Between Bytes)


	// Instance Functions

	byte copy();															// Copies the byte
	std::vector<bool> to_bits();											// Converts the Byte to Bits
	int* to_bits_int();														// Converts the Byte to Int Bits
	signed int to_int();													// Converts the Byte to an Int
	unsigned int to_unsigned_int();											// Converts the Byte to an Unsigned Int
	std::string to_string();												// Convert the Byte to String


	// Instance Bit Functions

	auto get_bit(int index);												// Get a bit
	int get_bit_int(int index);												// Get a bit with an integer
	byte& set_bit(int index, bool new_value);								// Set a bit
	byte& set_bit_int(int index, int new_value);							// Set a bit with an integer
	auto flip_bit(int index);												// Flips a bit
	int value();															// Dereferencing Variable Int Operator
	bool& switch_sign();													// Switching Integer Signage Function
	bool& switch_sign(bool newSign);										// Switching Integer Signage Function


	// Instance Mathematical Functions

	byte& equals(byte byte);												// Equals Function
	byte& add(byte byte);													// Addition Function
	byte& plus_plus();														// ++ Function
	byte& increment();														// ++ Function
	byte& subtract(byte byte);												// Subtraction Function
	byte& minus_minus();													// -- Function
	byte& decrement();														// -- Function
	byte& multiply(byte byte);												// Multiplication Function
	byte& divide(byte byte);												// Division Function
	byte& modulo(byte byte);												// Modulo Function


	// Instance Bitwise Functions

	byte& bit_and(byte byte);												// And Function
	byte& bit_or(byte byte);												// Or Function
	byte& bit_xor(byte byte);												// Exclusive Or Function
	byte& bit_left_shift(int shift);										// Left Shift Function
	byte& bit_right_shift(int shift);										// Right Shift Function
	byte bit_not();															// Not Function
	byte& bit_flip();														// Flip Function


	// Instance Logical Functions

	bool equal_to(byte byte);												// Equal To Function
	bool not_equal_to(byte byte);											// Not Equal To Function
	bool greater_than(byte byte);											// Greater Than Function
	bool greater_than_equal_to(byte byte);									// Greater Than Equal To Function
	bool less_than(byte byte);												// Less Than Function
	bool less_than_equal_to(byte byte);										// Less Than Equal To Function
	bool boolean();															// Bool Function
	bool not_boolean();														// Not Bool Function


	// Instance Bit Functions

	auto operator[](int index);												// Array Operator
	operator int();															// Dereferencing Int Operator
	int operator*();														// Dereferencing Int Operator
	signed int operator-();													// Dereferencing Int Operator
	unsigned int operator+();												// Dereferencing Unsigned Int Operator


	// Instance Mathematical Operators

	byte operator+(byte byte);												// Addition Operator
	byte operator-(byte byte);												// Subtraction Operator
	byte operator*(byte byte);												// Multiplication Operator
	byte operator/(byte byte);												// Division Operator
	byte operator%(byte byte);												// Modulo Operator


	// Instance Bitwise Operators

	byte operator&(byte byte);												// And Operator
	byte operator|(byte byte);												// Or Operator
	byte operator^(byte byte);												// Exclusive Or Operator
	byte operator<<(int shift);												// Left Shift Operator
	byte operator>>(int shift);												// Right Shift Operator
	byte operator~();														// Not Operator


	// Instance Mathematical Operators

	byte& operator=(byte byte);												// Equals Operator
	byte& operator+=(byte byte);											// Addition Equals Operator
	byte& operator++();														// ++ Operator
	byte& operator-=(byte byte);											// Subtraction Equals Operator
	byte& operator--();														// -- Operator
	byte& operator*=(byte byte);											// Multiplication Equals Operator
	byte& operator/=(byte byte);											// Division Equals Operator
	byte& operator%=(byte byte);											// Modulo Equals Operator


	// Instance Bitwise Operators

	byte& operator&=(byte byte);											// And Equals Operator
	byte& operator|=(byte byte);											// Or Equals Operator
	byte& operator^=(byte byte);											// Exclusive Or Equals Operator
	byte& operator<<=(int shift);											// Left Shift Equals Operator
	byte& operator>>=(int shift);											// Right Shift Equals Operator


	// Instance Logical Operators

	bool operator==(byte byte);												// Equal To Operator
	bool operator!=(byte byte);												// Not Equal To Operator
	bool operator>(byte byte);												// Greater Than Operator
	bool operator>=(byte byte);												// Greater Than Equal To Operator
	bool operator<(byte byte);												// Less Than Operator
	bool operator<=(byte byte);												// Less Than Equal To Operator
	operator bool();														// Boolean Operator
	bool operator!();														// Not Boolean Operator
};
