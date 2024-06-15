
// Byte Data Type Header Script
// by Kyle Furey

#pragma once
#include <string>

// Include this heading to use the class
#include "Byte.h"

// Emulates a single byte of memory through 8 boolean bits.
class byte
{
public:
																			// Instance Byte Data

	bool bits[8];															// The 8 bits that make up the Byte
	bool is_unsigned = true;												// Whether this Byte is unsigned


																			// Constructors and Deconstructors

	byte();																	// Constructor
	byte(byte& byte);														// Constructor (Byte)
	byte(bool boolean, bool isUnsigned);									// Constructor (Boolean)
	byte(bool newBits[8]);													// Constructor (Bits)
	byte(bool newBits[8], bool isUnsigned);									// Constructor (Bits)
	byte(int newBits[8]);													// Constructor (Int Bits)
	byte(int newBits[8], bool isUnsigned);									// Constructor (Int Bits)
	byte(signed int integer);												// Constructor (Integer)
	byte(signed int integer, bool isUnsigned);								// Constructor (Integer)
	byte(unsigned int integer);												// Constructor (Unsigned Integer)
	byte(unsigned int integer, bool isUnsigned);							// Constructor (Unsigned Integer)
	byte(std::string newString);											// Constructor (String)
	byte(std::string newString, bool isUnsigned);							// Constructor (String)
	~byte();																// Deconstructor


																			// Static Byte Conversions

	static byte& to_byte(bool bits[8]);										// Convert Bits to Byte
	static byte& to_byte(int bits[8]);										// Convert Int Bits to Byte
	static byte& to_byte(signed int integer); 								// Convert Int to Byte
	static byte& to_byte(unsigned int integer);								// Convert Unsigned Int to Byte
	static byte& to_byte(std::string newString);							// Convert String to Byte


																			// Static Bit Conversions

	static bool* to_bits(byte byte);										// Convert Byte to Bits
	static bool* to_bits(int bits[8]);										// Convert Int Bits to Bits
	static bool* to_bits(signed int integer);								// Convert Int to Bits
	static bool* to_bits(unsigned int integer);								// Convert Unsigned Int to Bits
	static bool* to_bits(std::string newString);							// Convert String to Bits


																			// Static Int Bit Conversions

	static int* to_bits_int(bool bits[8]);									// Convert Bits to Int Bits
	static int* to_bits_int(byte byte);										// Convert Byte to Int Bits
	static int* to_bits_int(signed int integer);							// Convert Int to Int Bits
	static int* to_bits_int(unsigned int integer);							// Convert Unsigned Int to Int Bits
	static int* to_bits_int(std::string newString);							// Convert String to Int Bits


																			// Static Int Conversions

	static signed int to_int(bool bits[8]);									// Convert Bits to Int
	static signed int to_int(byte byte);									// Convert Byte to Int
	static signed int to_int(int bits[8]);									// Convert Int Bits to Int
	static signed int to_int(unsigned int integer);							// Convert Unsigned Int to Int
	static signed int to_int(std::string newString);						// Convert String to Int


																			// Static Unsigned Int Conversions

	static unsigned int to_unsigned_int(bool bits[8]);						// Convert Bits to Unsigned Int
	static unsigned int to_unsigned_int(byte byte);							// Convert Byte to Unsigned Int
	static unsigned int to_unsigned_int(int bits[8]);						// Convert Int Bits to Unsigned Int
	static unsigned int to_unsigned_int(signed int integer);				// Convert Int to Unsigned Int
	static unsigned int to_unsigned_int(std::string newString);				// Convert String to Unsigned Int


																			// Static String Conversion

	static std::string to_string(bool bits[8]);								// Convert Bits to String
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

	static byte* copy(byte* bytes, int byteCount);							// Copies the Bytes
	static bool* to_bits(byte* bytes, int byteCount);						// Converts Bytes to Bits
	static int* to_bits_int(byte* bytes, int byteCount);					// Converts Bytes to Int Bits
	static signed int to_int(byte* bytes, int byteCount);					// Converts Bytes to Int
	static unsigned int to_unsigned_int(byte* bytes, int byteCount);		// Converts Bytes to Unsigned Int
	static std::string to_string(byte* bytes, int byteCount);				// Converts Bytes to Int Bits
	static std::string to_string_2(byte* bytes, int byteCount);				// Converts Bytes to Int Bits (With Spaces Between Bytes)


																			// Instance Functions

	byte copy();															// Copies the byte
	bool* to_bits();														// Converts the Byte to Bits
	int* to_bits_int();														// Converts the Byte to Int Bits
	signed int to_int();													// Converts the Byte to an Int
	unsigned int to_unsigned_int();											// Converts the Byte to an Unsigned Int
	std::string to_string();												// Convert the Byte to String


																			// Instance Bit Functions 

	bool& get_bit(int index);												// Get a bit
	int get_bit_int(int index);												// Get a bit with an integer
	byte& set_bit(int index, bool newValue);								// Set a bit
	byte& set_bit_int(int index, int newValue);								// Set a bit with an integer
	bool& flip_bit(int index);												// Flips a bit
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

	bool& operator[](int index);											// Array Operator
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

// Emulates a single byte of memory through 8 boolean bits.
class Byte
{
public:
																			// Instance Byte Data

	bool bits[8];															// The 8 bits that make up the Byte
	bool isUnsigned = true;													// Whether this Byte is unsigned


																			// Constructors and Deconstructors

	Byte();																	// Constructor
	Byte(Byte& byte);														// Constructor (Byte)
	Byte(bool boolean, bool is_unsigned);									// Constructor (Boolean)
	Byte(bool newBits[8]);													// Constructor (Bits)
	Byte(bool newBits[8], bool is_unsigned);								// Constructor (Bits)
	Byte(int newBits[8]);													// Constructor (Int Bits)
	Byte(int newBits[8], bool is_unsigned);									// Constructor (Int Bits)
	Byte(signed int integer);												// Constructor (Integer)
	Byte(signed int integer, bool is_unsigned);								// Constructor (Integer)
	Byte(unsigned int integer);												// Constructor (Unsigned Integer)
	Byte(unsigned int integer, bool is_unsigned);							// Constructor (Unsigned Integer)
	Byte(std::string newString);											// Constructor (String)
	Byte(std::string newString, bool is_unsigned);							// Constructor (String)
	~Byte();																// Deconstructor


																			// Static Byte Conversions

	static Byte& ToByte(bool bits[8]);										// Convert Bits to Byte
	static Byte& ToByte(int bits[8]);										// Convert Int Bits to Byte
	static Byte& ToByte(signed int integer); 								// Convert Int to Byte
	static Byte& ToByte(unsigned int integer);								// Convert Unsigned Int to Byte
	static Byte& ToByte(std::string newString);								// Convert String to Byte


																			// Static Bit Conversions

	static bool* ToBits(Byte byte);											// Convert Byte to Bits
	static bool* ToBits(int bits[8]);										// Convert Int Bits to Bits
	static bool* ToBits(signed int integer);								// Convert Int to Bits
	static bool* ToBits(unsigned int integer);								// Convert Unsigned Int to Bits
	static bool* ToBits(std::string newString);								// Convert String to Bits


																			// Static Int Bit Conversions

	static int* ToBitsInt(bool bits[8]);									// Convert Bits to Int Bits
	static int* ToBitsInt(Byte byte);										// Convert Byte to Int Bits
	static int* ToBitsInt(signed int integer);								// Convert Int to Int Bits
	static int* ToBitsInt(unsigned int integer);							// Convert Unsigned Int to Int Bits
	static int* ToBitsInt(std::string newString);							// Convert String to Int Bits


																			// Static Int Conversions

	static signed int ToInt(bool bits[8]);									// Convert Bits to Int
	static signed int ToInt(Byte byte);										// Convert Byte to Int
	static signed int ToInt(int bits[8]);									// Convert Int Bits to Int
	static signed int ToInt(unsigned int integer);							// Convert Unsigned Int to Int
	static signed int ToInt(std::string newString);							// Convert String to Int


																			// Static Unsigned Int Conversions

	static unsigned int ToUInt(bool bits[8]);								// Convert Bits to Unsigned Int
	static unsigned int ToUInt(Byte byte);									// Convert Byte to Unsigned Int
	static unsigned int ToUInt(int bits[8]);								// Convert Int Bits to Unsigned Int
	static unsigned int ToUInt(signed int integer);							// Convert Int to Unsigned Int
	static unsigned int ToUInt(std::string newString);						// Convert String to Unsigned Int


																			// Static String Conversion

	static std::string ToString(bool bits[8]);								// Convert Bits to String
	static std::string ToString(Byte byte);									// Convert Byte to String
	static std::string ToString(int bits[8]);								// Convert Int Bits to String
	static std::string ToString(signed int integer);						// Convert Int to String
	static std::string ToString(unsigned int integer);						// Convert Unsigned Int to String


																			// Static Mathematical Functions

	static Byte Add(Byte byteA, Byte byteB);								// Addition Function
	static Byte PlusPlus(Byte byte);										// ++ Function
	static Byte Increment(Byte byte);										// ++ Function
	static Byte Subtract(Byte byte, Byte byteB);							// Subtraction Function
	static Byte MinusMinus(Byte byte);										// -- Function
	static Byte Decrement(Byte byte);										// -- Function
	static Byte Multiply(Byte byteA, Byte byteB);							// Multiplication Function
	static Byte Divide(Byte byteA, Byte byteB);								// Division Function
	static Byte Modulo(Byte byteA, Byte byteB);								// Modulo Function


																			// Static Bitwise Functions

	static Byte And(Byte byteA, Byte byteB);								// And Function
	static Byte Or(Byte byteA, Byte byteB);									// Or Function
	static Byte Xor(Byte byteA, Byte byteB);								// Exclusive Or Function
	static Byte LeftShift(Byte byte, int shift);							// Left Shift Function
	static Byte RightShift(Byte byte, int shift);							// Right Shift Function
	static Byte Not(Byte byte);												// Not Function


																			// Static Logical Functions

	static bool EqualTo(Byte byteA, Byte byteB);							// Equal To Function
	static bool NotEqualTo(Byte byteA, Byte byteB);							// Not Equal To Function
	static bool GreaterThan(Byte byteA, Byte byteB);						// Greater Than Function
	static bool GreaterThanEqualTo(Byte byteA, Byte byteB);					// Greater Than Equal To Function
	static bool LessThan(Byte byteA, Byte byteB);							// Less Than Function
	static bool LessThanEqualTo(Byte byteA, Byte byteB);					// Less Than Equal To Function
	static bool Bool(Byte byte);											// Bool Function
	static bool NotBool(Byte byte);											// Not Bool Function


																			// Static Byte Array Conversions

	static Byte* Copy(Byte* bytes, int byteCount);							// Copies the Bytes
	static bool* ToBits(Byte* bytes, int byteCount);						// Converts Bytes to Bits
	static int* ToBitsInt(Byte* bytes, int byteCount);						// Converts Bytes to Int Bits
	static signed int ToInt(Byte* bytes, int byteCount);					// Converts Bytes to Int
	static unsigned int ToUInt(Byte* bytes, int byteCount);					// Converts Bytes to Unsigned Int
	static std::string ToString(Byte* bytes, int byteCount);				// Converts Bytes to Int Bits
	static std::string ToString2(Byte* bytes, int byteCount);				// Converts Bytes to Int Bits (With Spaces Between Bytes)


																			// Instance Functions

	Byte Copy();															// Copies the byte
	bool* ToBits();															// Converts the Byte to Bits
	int* ToBitsInt();														// Converts the Byte to Int Bits
	signed int ToInt();														// Converts the Byte to an Int
	unsigned int ToUInt();													// Converts the Byte to an Unsigned Int
	std::string ToString();													// Convert the Byte to String


																			// Instance Bit Functions 

	bool& GetBit(int index);												// Get a bit
	int GetBitInt(int index);												// Get a bit with an integer
	Byte& SetBit(int index, bool newValue);									// Set a bit
	Byte& SetBitInt(int index, int newValue);								// Set a bit with an integer
	bool& FlipBit(int index);												// Flips a bit
	int Value();															// Dereferencing Variable Int Operator
	bool& SwitchSign();														// Switching Integer Signage Function
	bool& SwitchSign(bool newSign);											// Switching Integer Signage Function


																			// Instance Mathematical Functions

	Byte& Equals(Byte byte);												// Equals Function
	Byte& Add(Byte byte);													// Addition Function
	Byte& PlusPlus();														// ++ Function
	Byte& Increment();														// ++ Function
	Byte& Subtract(Byte byte);												// Subtraction Function
	Byte& MinusMinus();														// -- Function
	Byte& Decrement();														// -- Function
	Byte& Multiply(Byte byte);												// Multiplication Function
	Byte& Divide(Byte byte);												// Division Function
	Byte& Modulo(Byte byte);												// Modulo Function


																			// Instance Bitwise Functions

	Byte& And(Byte byte);													// And Function
	Byte& Or(Byte byte);													// Or Function
	Byte& Xor(Byte byte);													// Exclusive Or Function
	Byte& LeftShift(int shift);												// Left Shift Function
	Byte& RightShift(int shift);											// Right Shift Function
	Byte Not();																// Not Function
	Byte& Flip();															// Flip Function


																			// Instance Logical Functions

	bool EqualTo(Byte byte);												// Equal To Function
	bool NotEqualTo(Byte byte);												// Not Equal To Function
	bool GreaterThan(Byte byte);											// Greater Than Function
	bool GreaterThanEqualTo(Byte byte);										// Greater Than Equal To Function
	bool LessThan(Byte byte);												// Less Than Function
	bool LessThanEqualTo(Byte byte);										// Less Than Equal To Function
	bool Bool();															// Bool Function
	bool NotBool();															// Not Bool Function


																			// Instance Bit Functions 

	bool& operator[](int index);											// Array Operator
	operator int();															// Dereferencing Int Operator
	int operator*();														// Dereferencing Int Operator
	signed int operator-();													// Dereferencing Int Operator
	unsigned int operator+();												// Dereferencing Unsigned Int Operator


																			// Instance Mathematical Operators

	Byte operator+(Byte byte);												// Addition Operator
	Byte operator-(Byte byte);												// Subtraction Operator
	Byte operator*(Byte byte);												// Multiplication Operator
	Byte operator/(Byte byte);												// Division Operator
	Byte operator%(Byte byte);												// Modulo Operator


																			// Instance Bitwise Operators

	Byte operator&(Byte byte);												// And Operator
	Byte operator|(Byte byte);												// Or Operator
	Byte operator^(Byte byte);												// Exclusive Or Operator
	Byte operator<<(int shift);												// Left Shift Operator
	Byte operator>>(int shift);												// Right Shift Operator
	Byte operator~();														// Not Operator


																			// Instance Mathematical Operators

	Byte& operator=(Byte byte);												// Equals Operator
	Byte& operator+=(Byte byte);											// Addition Equals Operator
	Byte& operator++();														// ++ Operator
	Byte& operator-=(Byte byte);											// Subtraction Equals Operator
	Byte& operator--();														// -- Operator
	Byte& operator*=(Byte byte);											// Multiplication Equals Operator
	Byte& operator/=(Byte byte);											// Division Equals Operator
	Byte& operator%=(Byte byte);											// Modulo Equals Operator


																			// Instance Bitwise Operators

	Byte& operator&=(Byte byte);											// And Equals Operator
	Byte& operator|=(Byte byte);											// Or Equals Operator
	Byte& operator^=(Byte byte);											// Exclusive Or Equals Operator
	Byte& operator<<=(int shift);											// Left Shift Equals Operator
	Byte& operator>>=(int shift);											// Right Shift Equals Operator


																			// Instance Logical Operators

	bool operator==(Byte byte);												// Equal To Operator
	bool operator!=(Byte byte);												// Not Equal To Operator
	bool operator>(Byte byte);												// Greater Than Operator
	bool operator>=(Byte byte);												// Greater Than Equal To Operator
	bool operator<(Byte byte);												// Less Than Operator
	bool operator<=(Byte byte);												// Less Than Equal To Operator
	operator bool();														// Boolean Operator
	bool operator!();														// Not Boolean Operator
};
