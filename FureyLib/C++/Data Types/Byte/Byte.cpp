
// Byte Data Type Function Definitions Script
// by Kyle Furey

#pragma once
#include <string>

// Include this heading to use the class
#include "Byte.h"

// Byte functions
byte::byte()
{
	is_unsigned = true;

	bits[0] = false;
	bits[1] = false;
	bits[2] = false;
	bits[3] = false;
	bits[4] = false;
	bits[5] = false;
	bits[6] = false;
	bits[7] = false;
}

byte::byte(byte& byte)
{
	is_unsigned = byte.is_unsigned;

	bits[0] = byte[0];
	bits[1] = byte[1];
	bits[2] = byte[2];
	bits[3] = byte[3];
	bits[4] = byte[4];
	bits[5] = byte[5];
	bits[6] = byte[6];
	bits[7] = byte[7];
}

byte::byte(bool boolean, bool isUnsigned)
{
	is_unsigned = isUnsigned;

	bits[0] = boolean;
	bits[1] = boolean;
	bits[2] = boolean;
	bits[3] = boolean;
	bits[4] = boolean;
	bits[5] = boolean;
	bits[6] = boolean;
	bits[7] = boolean;
}

byte::byte(bool newBits[8])
{
	is_unsigned = true;

	bits[0] = newBits[0];
	bits[1] = newBits[1];
	bits[2] = newBits[2];
	bits[3] = newBits[3];
	bits[4] = newBits[4];
	bits[5] = newBits[5];
	bits[6] = newBits[6];
	bits[7] = newBits[7];
}

byte::byte(bool newBits[8], bool isUnsigned)
{
	is_unsigned = isUnsigned;

	bits[0] = newBits[0];
	bits[1] = newBits[1];
	bits[2] = newBits[2];
	bits[3] = newBits[3];
	bits[4] = newBits[4];
	bits[5] = newBits[5];
	bits[6] = newBits[6];
	bits[7] = newBits[7];
}

byte::byte(int newBits[8])
{
	is_unsigned = true;

	bits[0] = newBits[0];
	bits[1] = newBits[1];
	bits[2] = newBits[2];
	bits[3] = newBits[3];
	bits[4] = newBits[4];
	bits[5] = newBits[5];
	bits[6] = newBits[6];
	bits[7] = newBits[7];
}

byte::byte(int newBits[8], bool isUnsigned)
{
	is_unsigned = isUnsigned;

	bits[0] = newBits[0];
	bits[1] = newBits[1];
	bits[2] = newBits[2];
	bits[3] = newBits[3];
	bits[4] = newBits[4];
	bits[5] = newBits[5];
	bits[6] = newBits[6];
	bits[7] = newBits[7];
}

byte::byte(signed int integer)
{
	is_unsigned = false;

	bits[7] = integer < 0;
	integer += bits[7] ? 128 : 0;

	bits[6] = integer >= 64;
	integer -= bits[6] ? 64 : 0;

	bits[5] = integer >= 32;
	integer -= bits[5] ? 32 : 0;

	bits[4] = integer >= 16;
	integer -= bits[4] ? 16 : 0;

	bits[3] = integer >= 8;
	integer -= bits[3] ? 8 : 0;

	bits[2] = integer >= 4;
	integer -= bits[2] ? 4 : 0;

	bits[1] = integer >= 2;
	integer -= bits[1] ? 2 : 0;

	bits[0] = integer >= 1;
}

byte::byte(signed int integer, bool isUnsigned)
{
	is_unsigned = isUnsigned;

	bits[7] = integer < 0;
	integer += bits[7] ? 128 : 0;

	bits[6] = integer >= 64;
	integer -= bits[6] ? 64 : 0;

	bits[5] = integer >= 32;
	integer -= bits[5] ? 32 : 0;

	bits[4] = integer >= 16;
	integer -= bits[4] ? 16 : 0;

	bits[3] = integer >= 8;
	integer -= bits[3] ? 8 : 0;

	bits[2] = integer >= 4;
	integer -= bits[2] ? 4 : 0;

	bits[1] = integer >= 2;
	integer -= bits[1] ? 2 : 0;

	bits[0] = integer >= 1;
}

byte::byte(unsigned int integer)
{
	is_unsigned = true;

	bits[7] = integer >= 128;
	integer -= bits[7] ? 128 : 0;

	bits[6] = integer >= 64;
	integer -= bits[6] ? 64 : 0;

	bits[5] = integer >= 32;
	integer -= bits[5] ? 32 : 0;

	bits[4] = integer >= 16;
	integer -= bits[4] ? 16 : 0;

	bits[3] = integer >= 8;
	integer -= bits[3] ? 8 : 0;

	bits[2] = integer >= 4;
	integer -= bits[2] ? 4 : 0;

	bits[1] = integer >= 2;
	integer -= bits[1] ? 2 : 0;

	bits[0] = integer >= 1;
}

byte::byte(unsigned int integer, bool isUnsigned)
{
	is_unsigned = isUnsigned;

	bits[7] = integer >= 128;
	integer -= bits[7] ? 128 : 0;

	bits[6] = integer >= 64;
	integer -= bits[6] ? 64 : 0;

	bits[5] = integer >= 32;
	integer -= bits[5] ? 32 : 0;

	bits[4] = integer >= 16;
	integer -= bits[4] ? 16 : 0;

	bits[3] = integer >= 8;
	integer -= bits[3] ? 8 : 0;

	bits[2] = integer >= 4;
	integer -= bits[2] ? 4 : 0;

	bits[1] = integer >= 2;
	integer -= bits[1] ? 2 : 0;

	bits[0] = integer >= 1;
}

byte::byte(std::string newString)
{
	is_unsigned = true;

	bits[0] = newString[7] - 48;
	bits[1] = newString[6] - 48;
	bits[2] = newString[5] - 48;
	bits[3] = newString[4] - 48;
	bits[4] = newString[3] - 48;
	bits[5] = newString[2] - 48;
	bits[6] = newString[1] - 48;
	bits[7] = newString[0] - 48;
}

byte::byte(std::string newString, bool isUnsigned)
{
	is_unsigned = isUnsigned;

	bits[0] = newString[7] - 48;
	bits[1] = newString[6] - 48;
	bits[2] = newString[5] - 48;
	bits[3] = newString[4] - 48;
	bits[4] = newString[3] - 48;
	bits[5] = newString[2] - 48;
	bits[6] = newString[1] - 48;
	bits[7] = newString[0] - 48;
}

byte::~byte() { }

byte& byte::to_byte(bool bits[8])
{
	static byte newByte(bits);

	return newByte;
}

byte& byte::to_byte(int bits[8])
{
	static byte newByte(bits);

	return newByte;
}

byte& byte::to_byte(signed int integer)
{
	static byte newByte(integer);

	return newByte;
}

byte& byte::to_byte(unsigned int integer)
{
	static byte newByte(integer);

	return newByte;
}

byte& byte::to_byte(std::string newString)
{
	static byte newByte(newString);

	return newByte;
}

bool* byte::to_bits(byte byte)
{
	static bool newBits[8];

	newBits[0] = byte.bits[0];
	newBits[1] = byte.bits[1];
	newBits[2] = byte.bits[2];
	newBits[3] = byte.bits[3];
	newBits[4] = byte.bits[4];
	newBits[5] = byte.bits[5];
	newBits[6] = byte.bits[6];
	newBits[7] = byte.bits[7];

	return newBits;
}

bool* byte::to_bits(int bits[8])
{
	static bool newBits[8];

	newBits[0] = bits[0];
	newBits[1] = bits[1];
	newBits[2] = bits[2];
	newBits[3] = bits[3];
	newBits[4] = bits[4];
	newBits[5] = bits[5];
	newBits[6] = bits[6];
	newBits[7] = bits[7];

	return newBits;
}

bool* byte::to_bits(signed int integer)
{
	static bool newBits[8];

	newBits[7] = integer < 0;
	integer += newBits[7] ? 128 : 0;

	newBits[6] = integer >= 64;
	integer -= newBits[6] ? 64 : 0;

	newBits[5] = integer >= 32;
	integer -= newBits[5] ? 32 : 0;

	newBits[4] = integer >= 16;
	integer -= newBits[4] ? 16 : 0;

	newBits[3] = integer >= 8;
	integer -= newBits[3] ? 8 : 0;

	newBits[2] = integer >= 4;
	integer -= newBits[2] ? 4 : 0;

	newBits[1] = integer >= 2;
	integer -= newBits[1] ? 2 : 0;

	newBits[0] = integer >= 1;

	return newBits;
}

bool* byte::to_bits(unsigned int integer)
{
	static bool newBits[8];

	newBits[7] = integer >= 128;
	integer -= newBits[7] ? 128 : 0;

	newBits[6] = integer >= 64;
	integer -= newBits[6] ? 64 : 0;

	newBits[5] = integer >= 32;
	integer -= newBits[5] ? 32 : 0;

	newBits[4] = integer >= 16;
	integer -= newBits[4] ? 16 : 0;

	newBits[3] = integer >= 8;
	integer -= newBits[3] ? 8 : 0;

	newBits[2] = integer >= 4;
	integer -= newBits[2] ? 4 : 0;

	newBits[1] = integer >= 2;
	integer -= newBits[1] ? 2 : 0;

	newBits[0] = integer >= 1;

	return newBits;
}

bool* byte::to_bits(std::string newString)
{
	static bool newBits[8];

	newBits[0] = newString[7] - 48;
	newBits[1] = newString[6] - 48;
	newBits[2] = newString[5] - 48;
	newBits[3] = newString[4] - 48;
	newBits[4] = newString[3] - 48;
	newBits[5] = newString[2] - 48;
	newBits[6] = newString[1] - 48;
	newBits[7] = newString[0] - 48;

	return newBits;
}

int* byte::to_bits_int(bool bits[8])
{
	static int newBits[8];

	newBits[0] = bits[0];
	newBits[1] = bits[1];
	newBits[2] = bits[2];
	newBits[3] = bits[3];
	newBits[4] = bits[4];
	newBits[5] = bits[5];
	newBits[6] = bits[6];
	newBits[7] = bits[7];

	return newBits;
}

int* byte::to_bits_int(byte byte)
{
	return to_bits_int(byte.bits);
}

int* byte::to_bits_int(signed int integer)
{
	static int newBits[8];

	newBits[7] = integer < 0;
	integer *= newBits[7] ? -1 : 1;

	newBits[6] = integer >= 64;
	integer -= newBits[6] ? 64 : 0;

	newBits[5] = integer >= 32;
	integer -= newBits[5] ? 32 : 0;

	newBits[4] = integer >= 16;
	integer -= newBits[4] ? 16 : 0;

	newBits[3] = integer >= 8;
	integer -= newBits[3] ? 8 : 0;

	newBits[2] = integer >= 4;
	integer -= newBits[2] ? 4 : 0;

	newBits[1] = integer >= 2;
	integer -= newBits[1] ? 2 : 0;

	newBits[0] = integer >= 1;

	return newBits;
}

int* byte::to_bits_int(unsigned int integer)
{
	static int newBits[8];

	newBits[7] = integer >= 128;
	integer -= newBits[7] ? 128 : 0;

	newBits[6] = integer >= 64;
	integer -= newBits[6] ? 64 : 0;

	newBits[5] = integer >= 32;
	integer -= newBits[5] ? 32 : 0;

	newBits[4] = integer >= 16;
	integer -= newBits[4] ? 16 : 0;

	newBits[3] = integer >= 8;
	integer -= newBits[3] ? 8 : 0;

	newBits[2] = integer >= 4;
	integer -= newBits[2] ? 4 : 0;

	newBits[1] = integer >= 2;
	integer -= newBits[1] ? 2 : 0;

	newBits[0] = integer >= 1;

	return newBits;
}

int* byte::to_bits_int(std::string newString)
{
	static int newBits[8];

	newBits[0] = newString[7] - 48;
	newBits[1] = newString[6] - 48;
	newBits[2] = newString[5] - 48;
	newBits[3] = newString[4] - 48;
	newBits[4] = newString[3] - 48;
	newBits[5] = newString[2] - 48;
	newBits[6] = newString[1] - 48;
	newBits[7] = newString[0] - 48;

	return newBits;
}

signed int byte::to_int(bool bits[8])
{
	signed int integer = 0;

	integer += bits[0] ? 1 : 0;
	integer += bits[1] ? 2 : 0;
	integer += bits[2] ? 4 : 0;
	integer += bits[3] ? 8 : 0;
	integer += bits[4] ? 16 : 0;
	integer += bits[5] ? 32 : 0;
	integer += bits[6] ? 64 : 0;

	if (bits[7])
	{
		integer = bits[7] ? -128 + integer : integer;

		return integer;
	}
	else
	{
		return integer;
	}
}

signed int byte::to_int(byte byte)
{
	return to_int(byte.bits);
}

signed int byte::to_int(int bits[8])
{
	bool* newBits = to_bits(bits);

	return to_unsigned_int(newBits);
}

signed int byte::to_int(unsigned int integer)
{
	bool* newBits = to_bits(integer);

	integer = to_int(newBits);

	return integer;
}

signed int byte::to_int(std::string newString)
{
	bool* newBits = to_bits(newString);

	return to_int(newBits);
}

unsigned int byte::to_unsigned_int(bool bits[8])
{
	unsigned int integer = 0;

	integer += bits[0] ? 1 : 0;
	integer += bits[1] ? 2 : 0;
	integer += bits[2] ? 4 : 0;
	integer += bits[3] ? 8 : 0;
	integer += bits[4] ? 16 : 0;
	integer += bits[5] ? 32 : 0;
	integer += bits[6] ? 64 : 0;
	integer += bits[7] ? 128 : 0;

	return integer;
}

unsigned int byte::to_unsigned_int(byte byte)
{
	return to_unsigned_int(byte.bits);
}

unsigned int byte::to_unsigned_int(int bits[8])
{
	bool* newBits = to_bits(bits);

	return to_unsigned_int(newBits);
}

unsigned int byte::to_unsigned_int(signed int integer)
{
	bool* newBits = to_bits(integer);

	integer = to_unsigned_int(newBits);

	return integer;
}

unsigned int byte::to_unsigned_int(std::string newString)
{
	bool* newBits = to_bits(newString);

	return to_unsigned_int(newBits);
}

std::string byte::to_string(bool bits[8])
{
	std::string newString = "";

	newString += std::to_string(static_cast<int>(bits[7]));
	newString += std::to_string(static_cast<int>(bits[6]));
	newString += std::to_string(static_cast<int>(bits[5]));
	newString += std::to_string(static_cast<int>(bits[4]));
	newString += std::to_string(static_cast<int>(bits[3]));
	newString += std::to_string(static_cast<int>(bits[2]));
	newString += std::to_string(static_cast<int>(bits[1]));
	newString += std::to_string(static_cast<int>(bits[0]));

	return newString;
}

std::string byte::to_string(byte byte)
{
	return to_string(byte.bits);
}

std::string byte::to_string(int bits[8])
{
	std::string newString = "";

	newString += std::to_string(bits[7]);
	newString += std::to_string(bits[6]);
	newString += std::to_string(bits[5]);
	newString += std::to_string(bits[4]);
	newString += std::to_string(bits[3]);
	newString += std::to_string(bits[2]);
	newString += std::to_string(bits[1]);
	newString += std::to_string(bits[0]);

	return newString;
}

std::string byte::to_string(signed int integer)
{
	std::string newString = "";
	int newBits[8];

	newBits[7] = integer < 0;
	integer *= newBits[7] ? -1 : 1;
	newString += std::to_string(newBits[7]);

	newBits[6] = integer >= 64;
	integer -= newBits[6] ? 64 : 0;
	newString += std::to_string(newBits[6]);

	newBits[5] = integer >= 32;
	integer -= newBits[5] ? 32 : 0;
	newString += std::to_string(newBits[5]);

	newBits[4] = integer >= 16;
	integer -= newBits[4] ? 16 : 0;
	newString += std::to_string(newBits[4]);

	newBits[3] = integer >= 8;
	integer -= newBits[3] ? 8 : 0;
	newString += std::to_string(newBits[3]);

	newBits[2] = integer >= 4;
	integer -= newBits[2] ? 4 : 0;
	newString += std::to_string(newBits[2]);

	newBits[1] = integer >= 2;
	integer -= newBits[1] ? 2 : 0;
	newString += std::to_string(newBits[1]);

	newBits[0] = integer >= 1;
	newString += std::to_string(newBits[0]);

	reverse(newString.begin(), newString.end());

	return newString;
}

std::string byte::to_string(unsigned int integer)
{
	std::string newString = "";
	int newBits[8];

	newBits[7] = integer >= 128;
	integer -= newBits[7] ? 128 : 0;
	newString += std::to_string(newBits[7]);

	newBits[6] = integer >= 64;
	integer -= newBits[6] ? 64 : 0;
	newString += std::to_string(newBits[6]);

	newBits[5] = integer >= 32;
	integer -= newBits[5] ? 32 : 0;
	newString += std::to_string(newBits[5]);

	newBits[4] = integer >= 16;
	integer -= newBits[4] ? 16 : 0;
	newString += std::to_string(newBits[4]);

	newBits[3] = integer >= 8;
	integer -= newBits[3] ? 8 : 0;
	newString += std::to_string(newBits[3]);

	newBits[2] = integer >= 4;
	integer -= newBits[2] ? 4 : 0;
	newString += std::to_string(newBits[2]);

	newBits[1] = integer >= 2;
	integer -= newBits[1] ? 2 : 0;
	newString += std::to_string(newBits[1]);

	newBits[0] = integer >= 1;
	newString += std::to_string(newBits[0]);

	reverse(newString.begin(), newString.end());

	return newString;
}

byte byte::add(byte byteA, byte byteB)
{
	byte newByte(*byteA + *byteB);

	return newByte;
}

byte byte::plus_plus(byte byteA)
{
	byte newByte(*byteA + 1);

	return newByte;
}

byte byte::increment(byte byteA)
{
	byte newByte(*byteA + 1);

	return newByte;
}

byte byte::subtract(byte byteA, byte byteB)
{
	byte newByte(*byteA - *byteB);

	return newByte;
}

byte byte::minus_minus(byte byteA)
{
	byte newByte(*byteA - 1);

	return newByte;
}

byte byte::decrement(byte byteA)
{
	byte newByte(*byteA - 1);

	return newByte;
}

byte byte::multiply(byte byteA, byte byteB)
{
	byte newByte(*byteA * *byteB);

	return newByte;
}

byte byte::divide(byte byteA, byte byteB)
{
	byte newByte(*byteA / *byteB);

	return newByte;
}

byte byte::modulo(byte byteA, byte byteB)
{
	byte newByte(*byteA % *byteB);

	return newByte;
}

byte byte::bit_and(byte byteA, byte byteB)
{
	byte newByte(byteA.bits);

	newByte.bits[0] = byteB.bits[0] && newByte.bits[0] ? true : false;
	newByte.bits[1] = byteB.bits[1] && newByte.bits[1] ? true : false;
	newByte.bits[2] = byteB.bits[2] && newByte.bits[2] ? true : false;
	newByte.bits[3] = byteB.bits[3] && newByte.bits[3] ? true : false;
	newByte.bits[4] = byteB.bits[4] && newByte.bits[4] ? true : false;
	newByte.bits[5] = byteB.bits[5] && newByte.bits[5] ? true : false;
	newByte.bits[6] = byteB.bits[6] && newByte.bits[6] ? true : false;
	newByte.bits[7] = byteB.bits[7] && newByte.bits[7] ? true : false;

	return newByte;
}

byte byte::bit_or(byte byteA, byte byteB)
{
	byte newByte(byteA.bits);

	newByte.bits[0] = byteB.bits[0] ? true : newByte.bits[0];
	newByte.bits[1] = byteB.bits[1] ? true : newByte.bits[1];
	newByte.bits[2] = byteB.bits[2] ? true : newByte.bits[2];
	newByte.bits[3] = byteB.bits[3] ? true : newByte.bits[3];
	newByte.bits[4] = byteB.bits[4] ? true : newByte.bits[4];
	newByte.bits[5] = byteB.bits[5] ? true : newByte.bits[5];
	newByte.bits[6] = byteB.bits[6] ? true : newByte.bits[6];
	newByte.bits[7] = byteB.bits[7] ? true : newByte.bits[7];

	return newByte;
}

byte byte::bit_xor(byte byteA, byte byteB)
{
	byte newByte(byteA.bits);

	newByte.bits[0] = byteB.bits[0] ^ newByte.bits[0] ? true : false;
	newByte.bits[1] = byteB.bits[1] ^ newByte.bits[1] ? true : false;
	newByte.bits[2] = byteB.bits[2] ^ newByte.bits[2] ? true : false;
	newByte.bits[3] = byteB.bits[3] ^ newByte.bits[3] ? true : false;
	newByte.bits[4] = byteB.bits[4] ^ newByte.bits[4] ? true : false;
	newByte.bits[5] = byteB.bits[5] ^ newByte.bits[5] ? true : false;
	newByte.bits[6] = byteB.bits[6] ^ newByte.bits[6] ? true : false;
	newByte.bits[7] = byteB.bits[7] ^ newByte.bits[7] ? true : false;

	return newByte;
}

byte byte::bit_left_shift(byte byteA, int shift)
{
	byte newByte(*byteA << shift);

	return newByte;
}

byte byte::bit_right_shift(byte byteA, int shift)
{
	byte newByte(*byteA >> shift);

	return newByte;
}

byte byte::bit_not(byte byteA)
{
	byte newByte(byteA.bits);

	newByte.bits[0] = !newByte.bits[0];
	newByte.bits[1] = !newByte.bits[1];
	newByte.bits[2] = !newByte.bits[2];
	newByte.bits[3] = !newByte.bits[3];
	newByte.bits[4] = !newByte.bits[4];
	newByte.bits[5] = !newByte.bits[5];
	newByte.bits[6] = !newByte.bits[6];
	newByte.bits[7] = !newByte.bits[7];

	return newByte;
}

bool byte::equal_to(byte byteA, byte byteB)
{
	return (byteA.bits[0] == byteB.bits[0]) && (byteA.bits[1] == byteB.bits[1]) && (byteA.bits[2] == byteB.bits[2]) && (byteA.bits[3] == byteB.bits[3]) && (byteA.bits[4] == byteB.bits[4]) && (byteA.bits[5] == byteB.bits[5]) && (byteA.bits[6] == byteB.bits[6]) && (byteA.bits[7] == byteB.bits[7]);
}

bool byte::not_equal_to(byte byteA, byte byteB)
{
	return (byteA.bits[7] != byteB.bits[7]) || (byteA.bits[6] != byteB.bits[6]) || (byteA.bits[5] != byteB.bits[5]) || (byteA.bits[4] != byteB.bits[4]) || (byteA.bits[3] != byteB.bits[3]) || (byteA.bits[2] != byteB.bits[2]) || (byteA.bits[1] != byteB.bits[1]) || (byteA.bits[0] != byteB.bits[0]);
}

bool byte::greater_than(byte byteA, byte byteB)
{
	if (!byteA.is_unsigned)		// A is both?
	{
		if (!byteB.is_unsigned)	// B is both?
		{
			// A is both, B is both.
			if (!byteA.bits[7])
			{
				// A is positive, B is positive.
				if (!byteB.bits[7])
				{
					if (byteA.bits[6] && !byteB.bits[6])
					{
						return true;
					}
					else if (!byteA.bits[6] && byteB.bits[6])
					{
						return false;
					}
					else if (byteA.bits[5] && !byteB.bits[5])
					{
						return true;
					}
					else if (!byteA.bits[5] && byteB.bits[5])
					{
						return false;
					}
					else if (byteA.bits[4] && !byteB.bits[4])
					{
						return true;
					}
					else if (!byteA.bits[4] && byteB.bits[4])
					{
						return false;
					}
					else if (byteA.bits[3] && !byteB.bits[3])
					{
						return true;
					}
					else if (!byteA.bits[3] && byteB.bits[3])
					{
						return false;
					}
					else if (byteA.bits[2] && !byteB.bits[2])
					{
						return true;
					}
					else if (!byteA.bits[2] && byteB.bits[2])
					{
						return false;
					}
					else if (byteA.bits[1] && !byteB.bits[1])
					{
						return true;
					}
					else if (!byteA.bits[1] && byteB.bits[1])
					{
						return false;
					}
					else if (byteA.bits[0] && !byteB.bits[0])
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				// A is positive, B is negative.
				else
				{
					return true;
				}
			}
			else
			{
				// A is negative, B is positive.
				if (!byteB.bits[7])
				{
					return false;
				}
				// A is negative, B is negative.
				else
				{
					if (byteA.bits[6] && byteB.bits[6])
					{
						return true;
					}
					else if (!byteA.bits[6] && byteB.bits[6])
					{
						return false;
					}
					else if (byteA.bits[5] && !byteB.bits[5])
					{
						return true;
					}
					else if (!byteA.bits[5] && byteB.bits[5])
					{
						return false;
					}
					else if (byteA.bits[4] && !byteB.bits[4])
					{
						return true;
					}
					else if (!byteA.bits[4] && byteB.bits[4])
					{
						return false;
					}
					else if (byteA.bits[3] && !byteB.bits[3])
					{
						return true;
					}
					else if (!byteA.bits[3] && byteB.bits[3])
					{
						return false;
					}
					else if (byteA.bits[2] && !byteB.bits[2])
					{
						return true;
					}
					else if (!byteA.bits[2] && byteB.bits[2])
					{
						return false;
					}
					else if (byteA.bits[1] && !byteB.bits[1])
					{
						return true;
					}
					else if (!byteA.bits[1] && byteB.bits[1])
					{
						return false;
					}
					else if (byteA.bits[0] && !byteB.bits[0])
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
		}
		// A is both, B is positive.
		else
		{
			// A is positive, B is positive.
			if (!byteB.bits[7])
			{
				if (byteA.bits[6] && !byteB.bits[6])
				{
					return true;
				}
				else if (!byteA.bits[6] && byteB.bits[6])
				{
					return false;
				}
				else if (byteA.bits[5] && !byteB.bits[5])
				{
					return true;
				}
				else if (!byteA.bits[5] && byteB.bits[5])
				{
					return false;
				}
				else if (byteA.bits[4] && !byteB.bits[4])
				{
					return true;
				}
				else if (!byteA.bits[4] && byteB.bits[4])
				{
					return false;
				}
				else if (byteA.bits[3] && !byteB.bits[3])
				{
					return true;
				}
				else if (!byteA.bits[3] && byteB.bits[3])
				{
					return false;
				}
				else if (byteA.bits[2] && !byteB.bits[2])
				{
					return true;
				}
				else if (!byteA.bits[2] && byteB.bits[2])
				{
					return false;
				}
				else if (byteA.bits[1] && !byteB.bits[1])
				{
					return true;
				}
				else if (!byteA.bits[1] && byteB.bits[1])
				{
					return false;
				}
				else if (byteA.bits[0] && !byteB.bits[0])
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			// A is negative, B is positive.
			else
			{
				return false;
			}
		}
	}
	else
	{
		// A is positive, B is both.
		if (!byteB.is_unsigned)
		{
			// A is positive, B is positive.
			if (!byteB.bits[7])
			{
				if (byteA.bits[6] && !byteB.bits[6])
				{
					return true;
				}
				else if (!byteA.bits[6] && byteB.bits[6])
				{
					return false;
				}
				else if (byteA.bits[5] && !byteB.bits[5])
				{
					return true;
				}
				else if (!byteA.bits[5] && byteB.bits[5])
				{
					return false;
				}
				else if (byteA.bits[4] && !byteB.bits[4])
				{
					return true;
				}
				else if (!byteA.bits[4] && byteB.bits[4])
				{
					return false;
				}
				else if (byteA.bits[3] && !byteB.bits[3])
				{
					return true;
				}
				else if (!byteA.bits[3] && byteB.bits[3])
				{
					return false;
				}
				else if (byteA.bits[2] && !byteB.bits[2])
				{
					return true;
				}
				else if (!byteA.bits[2] && byteB.bits[2])
				{
					return false;
				}
				else if (byteA.bits[1] && !byteB.bits[1])
				{
					return true;
				}
				else if (!byteA.bits[1] && byteB.bits[1])
				{
					return false;
				}
				else if (byteA.bits[0] && !byteB.bits[0])
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			// A is positive, B is negative.
			else
			{
				return true;
			}
		}
		// A is positive, B is positive.
		else
		{
			if (byteA.bits[7] && !byteB.bits[7])
			{
				return true;
			}
			else if (!byteA.bits[7] && byteB.bits[7])
			{
				return false;
			}
			else if (byteA.bits[6] && !byteB.bits[6])
			{
				return true;
			}
			else if (!byteA.bits[6] && byteB.bits[6])
			{
				return false;
			}
			else if (byteA.bits[5] && !byteB.bits[5])
			{
				return true;
			}
			else if (!byteA.bits[5] && byteB.bits[5])
			{
				return false;
			}
			else if (byteA.bits[4] && !byteB.bits[4])
			{
				return true;
			}
			else if (!byteA.bits[4] && byteB.bits[4])
			{
				return false;
			}
			else if (byteA.bits[3] && !byteB.bits[3])
			{
				return true;
			}
			else if (!byteA.bits[3] && byteB.bits[3])
			{
				return false;
			}
			else if (byteA.bits[2] && !byteB.bits[2])
			{
				return true;
			}
			else if (!byteA.bits[2] && byteB.bits[2])
			{
				return false;
			}
			else if (byteA.bits[1] && !byteB.bits[1])
			{
				return true;
			}
			else if (!byteA.bits[1] && byteB.bits[1])
			{
				return false;
			}
			else if (byteA.bits[0] && !byteB.bits[0])
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}

bool byte::greater_than_equal_to(byte byteA, byte byteB)
{
	if (!byteA.is_unsigned)		// A is both?
	{
		if (!byteB.is_unsigned)	// B is both?
		{
			// A is both, B is both.
			if (!byteA.bits[7])
			{
				// A is positive, B is positive.
				if (!byteB.bits[7])
				{
					if (byteA.bits[6] && !byteB.bits[6])
					{
						return true;
					}
					else if (!byteA.bits[6] && byteB.bits[6])
					{
						return false;
					}
					else if (byteA.bits[5] && !byteB.bits[5])
					{
						return true;
					}
					else if (!byteA.bits[5] && byteB.bits[5])
					{
						return false;
					}
					else if (byteA.bits[4] && !byteB.bits[4])
					{
						return true;
					}
					else if (!byteA.bits[4] && byteB.bits[4])
					{
						return false;
					}
					else if (byteA.bits[3] && !byteB.bits[3])
					{
						return true;
					}
					else if (!byteA.bits[3] && byteB.bits[3])
					{
						return false;
					}
					else if (byteA.bits[2] && !byteB.bits[2])
					{
						return true;
					}
					else if (!byteA.bits[2] && byteB.bits[2])
					{
						return false;
					}
					else if (byteA.bits[1] && !byteB.bits[1])
					{
						return true;
					}
					else if (!byteA.bits[1] && byteB.bits[1])
					{
						return false;
					}
					else if (byteA.bits[0] && !byteB.bits[0])
					{
						return true;
					}
					else if (!byteA.bits[0] && byteB.bits[0])
					{
						return false;
					}
					else
					{
						return true;
					}
				}
				// A is positive, B is negative.
				else
				{
					return true;
				}
			}
			else
			{
				// A is negative, B is positive.
				if (!byteB.bits[7])
				{
					return false;
				}
				// A is negative, B is negative.
				else
				{
					if (byteA.bits[6] && byteB.bits[6])
					{
						return true;
					}
					else if (!byteA.bits[6] && byteB.bits[6])
					{
						return false;
					}
					else if (byteA.bits[5] && !byteB.bits[5])
					{
						return true;
					}
					else if (!byteA.bits[5] && byteB.bits[5])
					{
						return false;
					}
					else if (byteA.bits[4] && !byteB.bits[4])
					{
						return true;
					}
					else if (!byteA.bits[4] && byteB.bits[4])
					{
						return false;
					}
					else if (byteA.bits[3] && !byteB.bits[3])
					{
						return true;
					}
					else if (!byteA.bits[3] && byteB.bits[3])
					{
						return false;
					}
					else if (byteA.bits[2] && !byteB.bits[2])
					{
						return true;
					}
					else if (!byteA.bits[2] && byteB.bits[2])
					{
						return false;
					}
					else if (byteA.bits[1] && !byteB.bits[1])
					{
						return true;
					}
					else if (!byteA.bits[1] && byteB.bits[1])
					{
						return false;
					}
					else if (byteA.bits[0] && !byteB.bits[0])
					{
						return true;
					}
					else
					{
						return true;
					}
				}
			}
		}
		// A is both, B is positive.
		else
		{
			// A is positive, B is positive.
			if (!byteB.bits[7])
			{
				if (byteA.bits[6] && !byteB.bits[6])
				{
					return true;
				}
				else if (!byteA.bits[6] && byteB.bits[6])
				{
					return false;
				}
				else if (byteA.bits[5] && !byteB.bits[5])
				{
					return true;
				}
				else if (!byteA.bits[5] && byteB.bits[5])
				{
					return false;
				}
				else if (byteA.bits[4] && !byteB.bits[4])
				{
					return true;
				}
				else if (!byteA.bits[4] && byteB.bits[4])
				{
					return false;
				}
				else if (byteA.bits[3] && !byteB.bits[3])
				{
					return true;
				}
				else if (!byteA.bits[3] && byteB.bits[3])
				{
					return false;
				}
				else if (byteA.bits[2] && !byteB.bits[2])
				{
					return true;
				}
				else if (!byteA.bits[2] && byteB.bits[2])
				{
					return false;
				}
				else if (byteA.bits[1] && !byteB.bits[1])
				{
					return true;
				}
				else if (!byteA.bits[1] && byteB.bits[1])
				{
					return false;
				}
				else if (byteA.bits[0] && !byteB.bits[0])
				{
					return true;
				}
				else if (!byteA.bits[0] && byteB.bits[0])
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			// A is negative, B is positive.
			else
			{
				return false;
			}
		}
	}
	else
	{
		// A is positive, B is both.
		if (!byteB.is_unsigned)
		{
			// A is positive, B is positive.
			if (!byteB.bits[7])
			{
				if (byteA.bits[6] && !byteB.bits[6])
				{
					return true;
				}
				else if (!byteA.bits[6] && byteB.bits[6])
				{
					return false;
				}
				else if (byteA.bits[5] && !byteB.bits[5])
				{
					return true;
				}
				else if (!byteA.bits[5] && byteB.bits[5])
				{
					return false;
				}
				else if (byteA.bits[4] && !byteB.bits[4])
				{
					return true;
				}
				else if (!byteA.bits[4] && byteB.bits[4])
				{
					return false;
				}
				else if (byteA.bits[3] && !byteB.bits[3])
				{
					return true;
				}
				else if (!byteA.bits[3] && byteB.bits[3])
				{
					return false;
				}
				else if (byteA.bits[2] && !byteB.bits[2])
				{
					return true;
				}
				else if (!byteA.bits[2] && byteB.bits[2])
				{
					return false;
				}
				else if (byteA.bits[1] && !byteB.bits[1])
				{
					return true;
				}
				else if (!byteA.bits[1] && byteB.bits[1])
				{
					return false;
				}
				else if (byteA.bits[0] && !byteB.bits[0])
				{
					return true;
				}
				else if (!byteA.bits[0] && byteB.bits[0])
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			// A is positive, B is negative.
			else
			{
				return true;
			}
		}
		// A is positive, B is positive.
		else
		{
			if (byteA.bits[7] && !byteB.bits[7])
			{
				return true;
			}
			else if (!byteA.bits[7] && byteB.bits[7])
			{
				return false;
			}
			else if (byteA.bits[6] && !byteB.bits[6])
			{
				return true;
			}
			else if (!byteA.bits[6] && byteB.bits[6])
			{
				return false;
			}
			else if (byteA.bits[5] && !byteB.bits[5])
			{
				return true;
			}
			else if (!byteA.bits[5] && byteB.bits[5])
			{
				return false;
			}
			else if (byteA.bits[4] && !byteB.bits[4])
			{
				return true;
			}
			else if (!byteA.bits[4] && byteB.bits[4])
			{
				return false;
			}
			else if (byteA.bits[3] && !byteB.bits[3])
			{
				return true;
			}
			else if (!byteA.bits[3] && byteB.bits[3])
			{
				return false;
			}
			else if (byteA.bits[2] && !byteB.bits[2])
			{
				return true;
			}
			else if (!byteA.bits[2] && byteB.bits[2])
			{
				return false;
			}
			else if (byteA.bits[1] && !byteB.bits[1])
			{
				return true;
			}
			else if (!byteA.bits[1] && byteB.bits[1])
			{
				return false;
			}
			else if (byteA.bits[0] && !byteB.bits[0])
			{
				return true;
			}
			else if (!byteA.bits[0] && byteB.bits[0])
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}
}

bool byte::less_than(byte byteA, byte byteB)
{
	if (!byteA.is_unsigned)		// A is both?
	{
		if (!byteB.is_unsigned)	// B is both?
		{
			// A is both, B is both.
			if (!byteA.bits[7])
			{
				// A is positive, B is positive.
				if (!byteB.bits[7])
				{
					if (!byteA.bits[6] && byteB.bits[6])
					{
						return true;
					}
					else if (byteA.bits[6] && !byteB.bits[6])
					{
						return false;
					}
					else if (!byteA.bits[5] && byteB.bits[5])
					{
						return true;
					}
					else if (byteA.bits[5] && !byteB.bits[5])
					{
						return false;
					}
					else if (!byteA.bits[4] && byteB.bits[4])
					{
						return true;
					}
					else if (byteA.bits[4] && !byteB.bits[4])
					{
						return false;
					}
					else if (!byteA.bits[3] && byteB.bits[3])
					{
						return true;
					}
					else if (byteA.bits[3] && !byteB.bits[3])
					{
						return false;
					}
					else if (!byteA.bits[2] && byteB.bits[2])
					{
						return true;
					}
					else if (byteA.bits[2] && !byteB.bits[2])
					{
						return false;
					}
					else if (!byteA.bits[1] && byteB.bits[1])
					{
						return true;
					}
					else if (byteA.bits[1] && !byteB.bits[1])
					{
						return false;
					}
					else if (!byteA.bits[0] && byteB.bits[0])
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				// A is positive, B is negative.
				else
				{
					return false;
				}
			}
			else
			{
				// A is negative, B is positive.
				if (!byteB.bits[7])
				{
					return true;
				}
				// A is negative, B is negative.
				else
				{
					if (!byteA.bits[6] && byteB.bits[6])
					{
						return true;
					}
					else if (byteA.bits[6] && !byteB.bits[6])
					{
						return false;
					}
					else if (!byteA.bits[5] && byteB.bits[5])
					{
						return true;
					}
					else if (byteA.bits[5] && !byteB.bits[5])
					{
						return false;
					}
					else if (!byteA.bits[4] && byteB.bits[4])
					{
						return true;
					}
					else if (byteA.bits[4] && !byteB.bits[4])
					{
						return false;
					}
					else if (!byteA.bits[3] && byteB.bits[3])
					{
						return true;
					}
					else if (byteA.bits[3] && !byteB.bits[3])
					{
						return false;
					}
					else if (!byteA.bits[2] && byteB.bits[2])
					{
						return true;
					}
					else if (byteA.bits[2] && !byteB.bits[2])
					{
						return false;
					}
					else if (!byteA.bits[1] && byteB.bits[1])
					{
						return true;
					}
					else if (byteA.bits[1] && !byteB.bits[1])
					{
						return false;
					}
					else if (!byteA.bits[0] && byteB.bits[0])
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
		}
		// A is both, B is positive.
		else
		{
			// A is positive, B is positive.
			if (!byteB.bits[7])
			{
				if (!byteA.bits[6] && byteB.bits[6])
				{
					return true;
				}
				else if (byteA.bits[6] && !byteB.bits[6])
				{
					return false;
				}
				else if (!byteA.bits[5] && byteB.bits[5])
				{
					return true;
				}
				else if (byteA.bits[5] && !byteB.bits[5])
				{
					return false;
				}
				else if (!byteA.bits[4] && byteB.bits[4])
				{
					return true;
				}
				else if (byteA.bits[4] && !byteB.bits[4])
				{
					return false;
				}
				else if (!byteA.bits[3] && byteB.bits[3])
				{
					return true;
				}
				else if (byteA.bits[3] && !byteB.bits[3])
				{
					return false;
				}
				else if (!byteA.bits[2] && byteB.bits[2])
				{
					return true;
				}
				else if (byteA.bits[2] && !byteB.bits[2])
				{
					return false;
				}
				else if (!byteA.bits[1] && byteB.bits[1])
				{
					return true;
				}
				else if (byteA.bits[1] && !byteB.bits[1])
				{
					return false;
				}
				else if (!byteA.bits[0] && byteB.bits[0])
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			// A is negative, B is positive.
			else
			{
				return true;
			}
		}
	}
	else
	{
		// A is positive, B is both.
		if (!byteB.is_unsigned)
		{
			// A is positive, B is positive.
			if (!byteB.bits[7])
			{
				if (!byteA.bits[6] && byteB.bits[6])
				{
					return true;
				}
				else if (byteA.bits[6] && !byteB.bits[6])
				{
					return false;
				}
				else if (!byteA.bits[5] && byteB.bits[5])
				{
					return true;
				}
				else if (byteA.bits[5] && !byteB.bits[5])
				{
					return false;
				}
				else if (!byteA.bits[4] && byteB.bits[4])
				{
					return true;
				}
				else if (byteA.bits[4] && !byteB.bits[4])
				{
					return false;
				}
				else if (!byteA.bits[3] && byteB.bits[3])
				{
					return true;
				}
				else if (byteA.bits[3] && !byteB.bits[3])
				{
					return false;
				}
				else if (!byteA.bits[2] && byteB.bits[2])
				{
					return true;
				}
				else if (byteA.bits[2] && !byteB.bits[2])
				{
					return false;
				}
				else if (!byteA.bits[1] && byteB.bits[1])
				{
					return true;
				}
				else if (byteA.bits[1] && !byteB.bits[1])
				{
					return false;
				}
				else if (!byteA.bits[0] && byteB.bits[0])
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			// A is positive, B is negative.
			else
			{
				return false;
			}
		}
		// A is positive, B is positive.
		else
		{
			if (!byteA.bits[7] && byteB.bits[7])
			{
				return true;
			}
			else if (byteA.bits[7] && !byteB.bits[7])
			{
				return false;
			}
			else if (!byteA.bits[6] && byteB.bits[6])
			{
				return true;
			}
			else if (byteA.bits[6] && !byteB.bits[6])
			{
				return false;
			}
			else if (!byteA.bits[5] && byteB.bits[5])
			{
				return true;
			}
			else if (byteA.bits[5] && !byteB.bits[5])
			{
				return false;
			}
			else if (!byteA.bits[4] && byteB.bits[4])
			{
				return true;
			}
			else if (byteA.bits[4] && !byteB.bits[4])
			{
				return false;
			}
			else if (!byteA.bits[3] && byteB.bits[3])
			{
				return true;
			}
			else if (byteA.bits[3] && !byteB.bits[3])
			{
				return false;
			}
			else if (!byteA.bits[2] && byteB.bits[2])
			{
				return true;
			}
			else if (byteA.bits[2] && !byteB.bits[2])
			{
				return false;
			}
			else if (!byteA.bits[1] && byteB.bits[1])
			{
				return true;
			}
			else if (byteA.bits[1] && !byteB.bits[1])
			{
				return false;
			}
			else if (!byteA.bits[0] && byteB.bits[0])
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}

bool byte::less_than_equal_to(byte byteA, byte byteB)
{
	if (!byteA.is_unsigned)		// A is both?
	{
		if (!byteB.is_unsigned)	// B is both?
		{
			// A is both, B is both.
			if (!byteA.bits[7])
			{
				// A is positive, B is positive.
				if (!byteB.bits[7])
				{
					if (!byteA.bits[6] && byteB.bits[6])
					{
						return true;
					}
					else if (byteA.bits[6] && !byteB.bits[6])
					{
						return false;
					}
					else if (!byteA.bits[5] && byteB.bits[5])
					{
						return true;
					}
					else if (byteA.bits[5] && !byteB.bits[5])
					{
						return false;
					}
					else if (!byteA.bits[4] && byteB.bits[4])
					{
						return true;
					}
					else if (byteA.bits[4] && !byteB.bits[4])
					{
						return false;
					}
					else if (!byteA.bits[3] && byteB.bits[3])
					{
						return true;
					}
					else if (byteA.bits[3] && !byteB.bits[3])
					{
						return false;
					}
					else if (!byteA.bits[2] && byteB.bits[2])
					{
						return true;
					}
					else if (byteA.bits[2] && !byteB.bits[2])
					{
						return false;
					}
					else if (!byteA.bits[1] && byteB.bits[1])
					{
						return true;
					}
					else if (byteA.bits[1] && !byteB.bits[1])
					{
						return false;
					}
					else if (!byteA.bits[0] && byteB.bits[0])
					{
						return true;
					}
					else if (byteA.bits[0] && !byteB.bits[0])
					{
						return false;
					}
					else
					{
						return true;
					}
				}
				// A is positive, B is negative.
				else
				{
					return false;
				}
			}
			else
			{
				// A is negative, B is positive.
				if (!byteB.bits[7])
				{
					return true;
				}
				// A is negative, B is negative.
				else
				{
					if (!byteA.bits[6] && byteB.bits[6])
					{
						return true;
					}
					else if (byteA.bits[6] && !byteB.bits[6])
					{
						return false;
					}
					else if (!byteA.bits[5] && byteB.bits[5])
					{
						return true;
					}
					else if (byteA.bits[5] && !byteB.bits[5])
					{
						return false;
					}
					else if (!byteA.bits[4] && byteB.bits[4])
					{
						return true;
					}
					else if (byteA.bits[4] && !byteB.bits[4])
					{
						return false;
					}
					else if (!byteA.bits[3] && byteB.bits[3])
					{
						return true;
					}
					else if (byteA.bits[3] && !byteB.bits[3])
					{
						return false;
					}
					else if (!byteA.bits[2] && byteB.bits[2])
					{
						return true;
					}
					else if (byteA.bits[2] && !byteB.bits[2])
					{
						return false;
					}
					else if (!byteA.bits[1] && byteB.bits[1])
					{
						return true;
					}
					else if (byteA.bits[1] && !byteB.bits[1])
					{
						return false;
					}
					else if (!byteA.bits[0] && byteB.bits[0])
					{
						return true;
					}
					else
					{
						return true;
					}
				}
			}
		}
		// A is both, B is positive.
		else
		{
			// A is positive, B is positive.
			if (!byteB.bits[7])
			{
				if (!byteA.bits[6] && byteB.bits[6])
				{
					return true;
				}
				else if (byteA.bits[6] && !byteB.bits[6])
				{
					return false;
				}
				else if (!byteA.bits[5] && byteB.bits[5])
				{
					return true;
				}
				else if (byteA.bits[5] && !byteB.bits[5])
				{
					return false;
				}
				else if (!byteA.bits[4] && byteB.bits[4])
				{
					return true;
				}
				else if (byteA.bits[4] && !byteB.bits[4])
				{
					return false;
				}
				else if (!byteA.bits[3] && byteB.bits[3])
				{
					return true;
				}
				else if (byteA.bits[3] && !byteB.bits[3])
				{
					return false;
				}
				else if (!byteA.bits[2] && byteB.bits[2])
				{
					return true;
				}
				else if (byteA.bits[2] && !byteB.bits[2])
				{
					return false;
				}
				else if (!byteA.bits[1] && byteB.bits[1])
				{
					return true;
				}
				else if (byteA.bits[1] && !byteB.bits[1])
				{
					return false;
				}
				else if (!byteA.bits[0] && byteB.bits[0])
				{
					return true;
				}
				else if (byteA.bits[0] && !byteB.bits[0])
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			// A is negative, B is positive.
			else
			{
				return true;
			}
		}
	}
	else
	{
		// A is positive, B is both.
		if (!byteB.is_unsigned)
		{
			// A is positive, B is positive.
			if (!byteB.bits[7])
			{
				if (!byteA.bits[6] && byteB.bits[6])
				{
					return true;
				}
				else if (byteA.bits[6] && !byteB.bits[6])
				{
					return false;
				}
				else if (!byteA.bits[5] && byteB.bits[5])
				{
					return true;
				}
				else if (byteA.bits[5] && !byteB.bits[5])
				{
					return false;
				}
				else if (!byteA.bits[4] && byteB.bits[4])
				{
					return true;
				}
				else if (byteA.bits[4] && !byteB.bits[4])
				{
					return false;
				}
				else if (!byteA.bits[3] && byteB.bits[3])
				{
					return true;
				}
				else if (byteA.bits[3] && !byteB.bits[3])
				{
					return false;
				}
				else if (!byteA.bits[2] && byteB.bits[2])
				{
					return true;
				}
				else if (byteA.bits[2] && !byteB.bits[2])
				{
					return false;
				}
				else if (!byteA.bits[1] && byteB.bits[1])
				{
					return true;
				}
				else if (byteA.bits[1] && !byteB.bits[1])
				{
					return false;
				}
				else if (!byteA.bits[0] && byteB.bits[0])
				{
					return true;
				}
				else if (byteA.bits[0] && !byteB.bits[0])
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			// A is positive, B is negative.
			else
			{
				return false;
			}
		}
		// A is positive, B is positive.
		else
		{
			if (!byteA.bits[7] && byteB.bits[7])
			{
				return true;
			}
			else if (byteA.bits[7] && !byteB.bits[7])
			{
				return false;
			}
			else if (!byteA.bits[6] && byteB.bits[6])
			{
				return true;
			}
			else if (byteA.bits[6] && !byteB.bits[6])
			{
				return false;
			}
			else if (!byteA.bits[5] && byteB.bits[5])
			{
				return true;
			}
			else if (byteA.bits[5] && !byteB.bits[5])
			{
				return false;
			}
			else if (!byteA.bits[4] && byteB.bits[4])
			{
				return true;
			}
			else if (byteA.bits[4] && !byteB.bits[4])
			{
				return false;
			}
			else if (!byteA.bits[3] && byteB.bits[3])
			{
				return true;
			}
			else if (byteA.bits[3] && !byteB.bits[3])
			{
				return false;
			}
			else if (!byteA.bits[2] && byteB.bits[2])
			{
				return true;
			}
			else if (byteA.bits[2] && !byteB.bits[2])
			{
				return false;
			}
			else if (!byteA.bits[1] && byteB.bits[1])
			{
				return true;
			}
			else if (byteA.bits[1] && !byteB.bits[1])
			{
				return false;
			}
			else if (!byteA.bits[0] && byteB.bits[0])
			{
				return true;
			}
			else if (byteA.bits[0] && !byteB.bits[0])
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}
}

bool byte::boolean(byte byteA)
{
	if (byteA.bits[0])
	{
		return true;
	}
	else if (byteA.bits[1])
	{
		return true;
	}
	else if (byteA.bits[2])
	{
		return true;
	}
	else if (byteA.bits[3])
	{
		return true;
	}
	else if (byteA.bits[4])
	{
		return true;
	}
	else if (byteA.bits[5])
	{
		return true;
	}
	else if (byteA.bits[6])
	{
		return true;
	}
	else if (byteA.bits[7])
	{
		return true;
	}

	return false;
}

bool byte::not_boolean(byte byteA)
{
	if (byteA.bits[0])
	{
		return false;
	}
	else if (byteA.bits[1])
	{
		return false;
	}
	else if (byteA.bits[2])
	{
		return false;
	}
	else if (byteA.bits[3])
	{
		return false;
	}
	else if (byteA.bits[4])
	{
		return false;
	}
	else if (byteA.bits[5])
	{
		return false;
	}
	else if (byteA.bits[6])
	{
		return false;
	}
	else if (byteA.bits[7])
	{
		return false;
	}

	return true;
}

byte* byte::copy(byte* bytes, int byteCount)
{
	byte* newBytes = new byte(byteCount);

	for (int currentByte = 0; currentByte < byteCount; currentByte++)
	{
		for (int currentBit = 0; currentBit < 8; currentBit++)
		{
			newBytes[currentByte].bits[currentBit] = bytes[currentByte].bits[currentBit];
		}
	}

	return newBytes;
}

bool* byte::to_bits(byte* bytes, int byteCount)
{
	bool* newBits = new bool[byteCount * 8];

	for (int currentByte = 0; currentByte < byteCount; currentByte++)
	{
		for (int currentBit = 0; currentBit < 8; currentBit++)
		{
			newBits[currentByte * 8 + currentBit] = bytes[currentByte].bits[currentBit];
		}
	}

	return newBits;
}

int* byte::to_bits_int(byte* bytes, int byteCount)
{
	int* newBits = new int[byteCount * 8];

	for (int currentByte = 0; currentByte < byteCount; currentByte++)
	{
		for (int currentBit = 0; currentBit < 8; currentBit++)
		{
			newBits[currentByte * 8 + currentBit] = bytes[currentByte].bits[currentBit];
		}
	}

	return newBits;
}

signed int byte::to_int(byte* bytes, int byteCount)
{
	signed int integer = 0;

	for (int currentByte = 0; currentByte < byteCount - 1; currentByte++)
	{
		for (int currentBit = 0; currentBit < 8; currentBit++)
		{
			integer += (bytes[currentByte].bits[currentBit]) * (pow(2, (currentByte * 8 + currentBit)));
		}
	}

	for (int currentBit = 0; currentBit < 7; currentBit++)
	{
		integer += (bytes[byteCount - 1].bits[currentBit]) * (pow(2, ((byteCount - 1) * 8 + currentBit)));
	}

	integer *= bytes[byteCount - 1].bits[7] ? -1 : 1;

	return integer;
}

unsigned int byte::to_unsigned_int(byte* bytes, int byteCount)
{
	unsigned int integer = 0;

	for (int currentByte = 0; currentByte < byteCount; currentByte++)
	{
		for (int currentBit = 0; currentBit < 8; currentBit++)
		{
			integer += (bytes[currentByte].bits[currentBit]) * (pow(2, (currentByte * 8 + currentBit)));
		}
	}

	return integer;
}

std::string byte::to_string(byte* bytes, int byteCount)
{
	std::string newString = "";

	for (int currentByte = byteCount - 1; currentByte >= 0; currentByte--)
	{
		for (int currentBit = 7; currentBit >= 0; currentBit--)
		{
			newString += std::to_string((static_cast<int>(bytes[currentByte].bits[currentBit])));
		}
	}

	return newString;
}

std::string byte::to_string_2(byte* bytes, int byteCount)
{
	std::string newString = "";

	for (int currentByte = byteCount - 1; currentByte >= 0; currentByte--)
	{
		for (int currentBit = 7; currentBit >= 0; currentBit--)
		{
			newString += std::to_string((static_cast<int>(bytes[currentByte].bits[currentBit])));
		}

		newString += " ";
	}

	return newString;
}

byte byte::copy()
{
	byte newByte(bits);

	return newByte;
}

bool* byte::to_bits()
{
	return to_bits(bits);
}

int* byte::to_bits_int()
{
	return to_bits_int(bits);
}

signed int byte::to_int()
{
	return to_int(bits);
}

unsigned int byte::to_unsigned_int()
{
	return to_unsigned_int(bits);
}

std::string byte::to_string()
{
	return to_string(bits);
}

bool& byte::get_bit(int index)
{
	return bits[index];
}

int byte::get_bit_int(int index)
{
	return bits[index];
}

byte& byte::set_bit(int index, bool newValue)
{
	bits[index] = newValue;

	return *this;
}

byte& byte::set_bit_int(int index, int newValue)
{
	bits[index] = newValue;

	return *this;
}

bool& byte::flip_bit(int index)
{
	bits[index] = !bits[index];

	return bits[index];
}

int byte::value()
{
	return is_unsigned ? to_int() : to_unsigned_int();
}

bool& byte::switch_sign()
{
	is_unsigned = !is_unsigned;

	return is_unsigned;
}

bool& byte::switch_sign(bool newSign)
{
	is_unsigned = newSign;

	return is_unsigned;
}

byte& byte::equals(byte byte)
{
	bits[0] = byte[0];
	bits[1] = byte[1];
	bits[2] = byte[2];
	bits[3] = byte[3];
	bits[4] = byte[4];
	bits[5] = byte[5];
	bits[6] = byte[6];
	bits[7] = byte[7];

	return *this;
}

byte& byte::add(byte byteA)
{
	byte newByte(add(*this, byteA).bits);

	equals(newByte);

	return *this;
}

byte& byte::plus_plus()
{
	byte newByte(plus_plus(*this).bits);

	equals(newByte);

	return *this;
}

byte& byte::increment()
{
	byte newByte(increment(*this).bits);

	equals(newByte);

	return *this;
}

byte& byte::subtract(byte byteA)
{
	byte newByte(subtract(*this, byteA).bits);

	equals(newByte);

	return *this;
}

byte& byte::minus_minus()
{
	byte newByte(minus_minus(*this).bits);

	equals(newByte);

	return *this;
}

byte& byte::decrement()
{
	byte newByte(decrement(*this).bits);

	equals(newByte);

	return *this;
}

byte& byte::multiply(byte byteA)
{
	byte newByte(multiply(*this, byteA).bits);

	equals(newByte);

	return *this;
}

byte& byte::divide(byte byteA)
{
	byte newByte(divide(*this, byteA).bits);

	equals(newByte);

	return *this;
}

byte& byte::modulo(byte byteA)
{
	byte newByte(modulo(*this, byteA).bits);

	equals(newByte);

	return *this;
}

byte& byte::bit_and(byte byteA)
{
	byte newByte(bit_and(*this, byteA).bits);

	equals(newByte);

	return *this;
}

byte& byte::bit_or(byte byteA)
{
	byte newByte(bit_or(*this, byteA).bits);

	equals(newByte);

	return *this;
}

byte& byte::bit_xor(byte byteA)
{
	byte newByte(bit_xor(*this, byteA).bits);

	equals(newByte);

	return *this;
}

byte& byte::bit_left_shift(int shift)
{
	byte newByte(bit_left_shift(*this, shift).bits);

	equals(newByte);

	return *this;
}

byte& byte::bit_right_shift(int shift)
{
	byte newByte(bit_right_shift(*this, shift).bits);

	equals(newByte);

	return *this;
}

byte byte::bit_not()
{
	byte newByte(bits);

	newByte.bits[0] = !newByte.bits[0];
	newByte.bits[1] = !newByte.bits[1];
	newByte.bits[2] = !newByte.bits[2];
	newByte.bits[3] = !newByte.bits[3];
	newByte.bits[4] = !newByte.bits[4];
	newByte.bits[5] = !newByte.bits[5];
	newByte.bits[6] = !newByte.bits[6];
	newByte.bits[7] = !newByte.bits[7];

	return newByte;
}

byte& byte::bit_flip()
{
	bits[0] = !bits[0];
	bits[1] = !bits[1];
	bits[2] = !bits[2];
	bits[3] = !bits[3];
	bits[4] = !bits[4];
	bits[5] = !bits[5];
	bits[6] = !bits[6];
	bits[7] = !bits[7];

	return *this;
}

bool byte::equal_to(byte byte)
{
	return equal_to(*this, byte);
}

bool byte::not_equal_to(byte byte)
{
	return not_equal_to(*this, byte);
}

bool byte::greater_than(byte byte)
{
	return greater_than(*this, byte);
}

bool byte::greater_than_equal_to(byte byte)
{
	return greater_than_equal_to(*this, byte);
}

bool byte::less_than(byte byte)
{
	return less_than(*this, byte);
}

bool byte::less_than_equal_to(byte byte)
{
	return less_than_equal_to(*this, byte);
}

bool byte::boolean()
{
	return boolean(*this);
}

bool byte::not_boolean()
{
	return not_boolean(*this);
}

bool& byte::operator[](int index)
{
	return bits[index];
}

byte::operator int()
{
	return value();
}

int byte::operator*()
{
	return is_unsigned ? to_unsigned_int() : to_int();
}

signed int byte::operator-()
{
	return to_int();
}

unsigned int byte::operator+()
{
	return to_unsigned_int();
}

byte byte::operator+(byte byte)
{
	return add(byte);
}

byte byte::operator-(byte byte)
{
	return subtract(byte);
}

byte byte::operator*(byte byte)
{
	return multiply(byte);
}

byte byte::operator/(byte byte)
{
	return divide(byte);
}

byte byte::operator%(byte byte)
{
	return modulo(byte);
}

byte byte::operator&(byte byte)
{
	return bit_and(byte);
}

byte byte::operator|(byte byte)
{
	return bit_or(byte);
}

byte byte::operator^(byte byte)
{
	return bit_xor(byte);
}

byte byte::operator<<(int shift)
{
	return bit_left_shift(shift);
}

byte byte::operator>>(int shift)
{
	return bit_right_shift(shift);
}

byte byte::operator~()
{
	byte newByte(bits);

	newByte.bits[0] = !newByte.bits[0];
	newByte.bits[1] = !newByte.bits[1];
	newByte.bits[2] = !newByte.bits[2];
	newByte.bits[3] = !newByte.bits[3];
	newByte.bits[4] = !newByte.bits[4];
	newByte.bits[5] = !newByte.bits[5];
	newByte.bits[6] = !newByte.bits[6];
	newByte.bits[7] = !newByte.bits[7];

	return newByte;
}

byte& byte::operator=(byte byte)
{
	return equals(byte);
}

byte& byte::operator+=(byte byte)
{
	return add(byte);
}

byte& byte::operator++()
{
	return plus_plus();
}

byte& byte::operator-=(byte byte)
{
	return subtract(byte);
}

byte& byte::operator--()
{
	return minus_minus();
}

byte& byte::operator*=(byte byte)
{
	return multiply(byte);
}

byte& byte::operator/=(byte byte)
{
	return divide(byte);
}

byte& byte::operator%=(byte byte)
{
	return modulo(byte);
}

byte& byte::operator&=(byte byte)
{
	return bit_and(byte);
}

byte& byte::operator|=(byte byte)
{
	return bit_or(byte);
}

byte& byte::operator^=(byte byte)
{
	return bit_xor(byte);
}

byte& byte::operator<<=(int shift)
{
	return bit_left_shift(shift);
}

byte& byte::operator>>=(int shift)
{
	return bit_right_shift(shift);
}

bool byte::operator==(byte byte)
{
	return equal_to(byte);
}

bool byte::operator!=(byte byte)
{
	return not_equal_to(byte);
}

bool byte::operator>(byte byte)
{
	return greater_than(byte);
}

bool byte::operator>=(byte byte)
{
	return greater_than_equal_to(byte);
}

bool byte::operator<(byte byte)
{
	return less_than(byte);
}

bool byte::operator<=(byte byte)
{
	return less_than_equal_to(byte);
}

byte::operator bool()
{
	return boolean();
}

bool byte::operator!()
{
	return not_boolean();
}

// Byte functions
Byte::Byte()
{
	isUnsigned = true;

	bits[0] = false;
	bits[1] = false;
	bits[2] = false;
	bits[3] = false;
	bits[4] = false;
	bits[5] = false;
	bits[6] = false;
	bits[7] = false;
}

Byte::Byte(Byte& byte)
{
	isUnsigned = byte.isUnsigned;

	bits[0] = byte[0];
	bits[1] = byte[1];
	bits[2] = byte[2];
	bits[3] = byte[3];
	bits[4] = byte[4];
	bits[5] = byte[5];
	bits[6] = byte[6];
	bits[7] = byte[7];
}

Byte::Byte(bool boolean, bool is_unsigned)
{
	isUnsigned = is_unsigned;

	bits[0] = boolean;
	bits[1] = boolean;
	bits[2] = boolean;
	bits[3] = boolean;
	bits[4] = boolean;
	bits[5] = boolean;
	bits[6] = boolean;
	bits[7] = boolean;
}

Byte::Byte(bool newBits[8])
{
	isUnsigned = true;

	bits[0] = newBits[0];
	bits[1] = newBits[1];
	bits[2] = newBits[2];
	bits[3] = newBits[3];
	bits[4] = newBits[4];
	bits[5] = newBits[5];
	bits[6] = newBits[6];
	bits[7] = newBits[7];
}

Byte::Byte(bool newBits[8], bool is_unsigned)
{
	isUnsigned = is_unsigned;

	bits[0] = newBits[0];
	bits[1] = newBits[1];
	bits[2] = newBits[2];
	bits[3] = newBits[3];
	bits[4] = newBits[4];
	bits[5] = newBits[5];
	bits[6] = newBits[6];
	bits[7] = newBits[7];
}

Byte::Byte(int newBits[8])
{
	isUnsigned = true;

	bits[0] = newBits[0];
	bits[1] = newBits[1];
	bits[2] = newBits[2];
	bits[3] = newBits[3];
	bits[4] = newBits[4];
	bits[5] = newBits[5];
	bits[6] = newBits[6];
	bits[7] = newBits[7];
}

Byte::Byte(int newBits[8], bool is_unsigned)
{
	isUnsigned = is_unsigned;

	bits[0] = newBits[0];
	bits[1] = newBits[1];
	bits[2] = newBits[2];
	bits[3] = newBits[3];
	bits[4] = newBits[4];
	bits[5] = newBits[5];
	bits[6] = newBits[6];
	bits[7] = newBits[7];
}

Byte::Byte(signed int integer)
{
	isUnsigned = false;

	bits[7] = integer < 0;
	integer += bits[7] ? 128 : 0;

	bits[6] = integer >= 64;
	integer -= bits[6] ? 64 : 0;

	bits[5] = integer >= 32;
	integer -= bits[5] ? 32 : 0;

	bits[4] = integer >= 16;
	integer -= bits[4] ? 16 : 0;

	bits[3] = integer >= 8;
	integer -= bits[3] ? 8 : 0;

	bits[2] = integer >= 4;
	integer -= bits[2] ? 4 : 0;

	bits[1] = integer >= 2;
	integer -= bits[1] ? 2 : 0;

	bits[0] = integer >= 1;
}

Byte::Byte(signed int integer, bool is_unsigned)
{
	isUnsigned = is_unsigned;

	bits[7] = integer < 0;
	integer += bits[7] ? 128 : 0;

	bits[6] = integer >= 64;
	integer -= bits[6] ? 64 : 0;

	bits[5] = integer >= 32;
	integer -= bits[5] ? 32 : 0;

	bits[4] = integer >= 16;
	integer -= bits[4] ? 16 : 0;

	bits[3] = integer >= 8;
	integer -= bits[3] ? 8 : 0;

	bits[2] = integer >= 4;
	integer -= bits[2] ? 4 : 0;

	bits[1] = integer >= 2;
	integer -= bits[1] ? 2 : 0;

	bits[0] = integer >= 1;
}

Byte::Byte(unsigned int integer)
{
	isUnsigned = true;

	bits[7] = integer >= 128;
	integer -= bits[7] ? 128 : 0;

	bits[6] = integer >= 64;
	integer -= bits[6] ? 64 : 0;

	bits[5] = integer >= 32;
	integer -= bits[5] ? 32 : 0;

	bits[4] = integer >= 16;
	integer -= bits[4] ? 16 : 0;

	bits[3] = integer >= 8;
	integer -= bits[3] ? 8 : 0;

	bits[2] = integer >= 4;
	integer -= bits[2] ? 4 : 0;

	bits[1] = integer >= 2;
	integer -= bits[1] ? 2 : 0;

	bits[0] = integer >= 1;
}

Byte::Byte(unsigned int integer, bool is_unsigned)
{
	isUnsigned = is_unsigned;

	bits[7] = integer >= 128;
	integer -= bits[7] ? 128 : 0;

	bits[6] = integer >= 64;
	integer -= bits[6] ? 64 : 0;

	bits[5] = integer >= 32;
	integer -= bits[5] ? 32 : 0;

	bits[4] = integer >= 16;
	integer -= bits[4] ? 16 : 0;

	bits[3] = integer >= 8;
	integer -= bits[3] ? 8 : 0;

	bits[2] = integer >= 4;
	integer -= bits[2] ? 4 : 0;

	bits[1] = integer >= 2;
	integer -= bits[1] ? 2 : 0;

	bits[0] = integer >= 1;
}

Byte::Byte(std::string newString)
{
	isUnsigned = true;

	bits[0] = newString[7] - 48;
	bits[1] = newString[6] - 48;
	bits[2] = newString[5] - 48;
	bits[3] = newString[4] - 48;
	bits[4] = newString[3] - 48;
	bits[5] = newString[2] - 48;
	bits[6] = newString[1] - 48;
	bits[7] = newString[0] - 48;
}

Byte::Byte(std::string newString, bool is_unsigned)
{
	isUnsigned = is_unsigned;

	bits[0] = newString[7] - 48;
	bits[1] = newString[6] - 48;
	bits[2] = newString[5] - 48;
	bits[3] = newString[4] - 48;
	bits[4] = newString[3] - 48;
	bits[5] = newString[2] - 48;
	bits[6] = newString[1] - 48;
	bits[7] = newString[0] - 48;
}

Byte::~Byte() { }

Byte& Byte::ToByte(bool bits[8])
{
	static Byte newByte(bits);

	return newByte;
}

Byte& Byte::ToByte(int bits[8])
{
	static Byte newByte(bits);

	return newByte;
}

Byte& Byte::ToByte(signed int integer)
{
	static Byte newByte(integer);

	return newByte;
}

Byte& Byte::ToByte(unsigned int integer)
{
	static Byte newByte(integer);

	return newByte;
}

Byte& Byte::ToByte(std::string newString)
{
	static Byte newByte(newString);

	return newByte;
}

bool* Byte::ToBits(Byte byte)
{
	static bool newBits[8];

	newBits[0] = byte.bits[0];
	newBits[1] = byte.bits[1];
	newBits[2] = byte.bits[2];
	newBits[3] = byte.bits[3];
	newBits[4] = byte.bits[4];
	newBits[5] = byte.bits[5];
	newBits[6] = byte.bits[6];
	newBits[7] = byte.bits[7];

	return newBits;
}

bool* Byte::ToBits(int bits[8])
{
	static bool newBits[8];

	newBits[0] = bits[0];
	newBits[1] = bits[1];
	newBits[2] = bits[2];
	newBits[3] = bits[3];
	newBits[4] = bits[4];
	newBits[5] = bits[5];
	newBits[6] = bits[6];
	newBits[7] = bits[7];

	return newBits;
}

bool* Byte::ToBits(signed int integer)
{
	static bool newBits[8];

	newBits[7] = integer < 0;
	integer += newBits[7] ? 128 : 0;

	newBits[6] = integer >= 64;
	integer -= newBits[6] ? 64 : 0;

	newBits[5] = integer >= 32;
	integer -= newBits[5] ? 32 : 0;

	newBits[4] = integer >= 16;
	integer -= newBits[4] ? 16 : 0;

	newBits[3] = integer >= 8;
	integer -= newBits[3] ? 8 : 0;

	newBits[2] = integer >= 4;
	integer -= newBits[2] ? 4 : 0;

	newBits[1] = integer >= 2;
	integer -= newBits[1] ? 2 : 0;

	newBits[0] = integer >= 1;

	return newBits;
}

bool* Byte::ToBits(unsigned int integer)
{
	static bool newBits[8];

	newBits[7] = integer >= 128;
	integer -= newBits[7] ? 128 : 0;

	newBits[6] = integer >= 64;
	integer -= newBits[6] ? 64 : 0;

	newBits[5] = integer >= 32;
	integer -= newBits[5] ? 32 : 0;

	newBits[4] = integer >= 16;
	integer -= newBits[4] ? 16 : 0;

	newBits[3] = integer >= 8;
	integer -= newBits[3] ? 8 : 0;

	newBits[2] = integer >= 4;
	integer -= newBits[2] ? 4 : 0;

	newBits[1] = integer >= 2;
	integer -= newBits[1] ? 2 : 0;

	newBits[0] = integer >= 1;

	return newBits;
}

bool* Byte::ToBits(std::string newString)
{
	static bool newBits[8];

	newBits[0] = newString[7] - 48;
	newBits[1] = newString[6] - 48;
	newBits[2] = newString[5] - 48;
	newBits[3] = newString[4] - 48;
	newBits[4] = newString[3] - 48;
	newBits[5] = newString[2] - 48;
	newBits[6] = newString[1] - 48;
	newBits[7] = newString[0] - 48;

	return newBits;
}

int* Byte::ToBitsInt(bool bits[8])
{
	static int newBits[8];

	newBits[0] = bits[0];
	newBits[1] = bits[1];
	newBits[2] = bits[2];
	newBits[3] = bits[3];
	newBits[4] = bits[4];
	newBits[5] = bits[5];
	newBits[6] = bits[6];
	newBits[7] = bits[7];

	return newBits;
}

int* Byte::ToBitsInt(Byte byte)
{
	return ToBitsInt(byte.bits);
}

int* Byte::ToBitsInt(signed int integer)
{
	static int newBits[8];

	newBits[7] = integer < 0;
	integer *= newBits[7] ? -1 : 1;

	newBits[6] = integer >= 64;
	integer -= newBits[6] ? 64 : 0;

	newBits[5] = integer >= 32;
	integer -= newBits[5] ? 32 : 0;

	newBits[4] = integer >= 16;
	integer -= newBits[4] ? 16 : 0;

	newBits[3] = integer >= 8;
	integer -= newBits[3] ? 8 : 0;

	newBits[2] = integer >= 4;
	integer -= newBits[2] ? 4 : 0;

	newBits[1] = integer >= 2;
	integer -= newBits[1] ? 2 : 0;

	newBits[0] = integer >= 1;

	return newBits;
}

int* Byte::ToBitsInt(unsigned int integer)
{
	static int newBits[8];

	newBits[7] = integer >= 128;
	integer -= newBits[7] ? 128 : 0;

	newBits[6] = integer >= 64;
	integer -= newBits[6] ? 64 : 0;

	newBits[5] = integer >= 32;
	integer -= newBits[5] ? 32 : 0;

	newBits[4] = integer >= 16;
	integer -= newBits[4] ? 16 : 0;

	newBits[3] = integer >= 8;
	integer -= newBits[3] ? 8 : 0;

	newBits[2] = integer >= 4;
	integer -= newBits[2] ? 4 : 0;

	newBits[1] = integer >= 2;
	integer -= newBits[1] ? 2 : 0;

	newBits[0] = integer >= 1;

	return newBits;
}

int* Byte::ToBitsInt(std::string newString)
{
	static int newBits[8];

	newBits[0] = newString[7] - 48;
	newBits[1] = newString[6] - 48;
	newBits[2] = newString[5] - 48;
	newBits[3] = newString[4] - 48;
	newBits[4] = newString[3] - 48;
	newBits[5] = newString[2] - 48;
	newBits[6] = newString[1] - 48;
	newBits[7] = newString[0] - 48;

	return newBits;
}

signed int Byte::ToInt(bool bits[8])
{
	signed int integer = 0;

	integer += bits[0] ? 1 : 0;
	integer += bits[1] ? 2 : 0;
	integer += bits[2] ? 4 : 0;
	integer += bits[3] ? 8 : 0;
	integer += bits[4] ? 16 : 0;
	integer += bits[5] ? 32 : 0;
	integer += bits[6] ? 64 : 0;

	if (bits[7])
	{
		integer = bits[7] ? -128 + integer : integer;

		return integer;
	}
	else
	{
		return integer;
	}
}

signed int Byte::ToInt(Byte byte)
{
	return ToInt(byte.bits);
}

signed int Byte::ToInt(int bits[8])
{
	bool* newBits = ToBits(bits);

	return ToUInt(newBits);
}

signed int Byte::ToInt(unsigned int integer)
{
	bool* newBits = ToBits(integer);

	integer = ToInt(newBits);

	return integer;
}

signed int Byte::ToInt(std::string newString)
{
	bool* newBits = ToBits(newString);

	return ToInt(newBits);
}

unsigned int Byte::ToUInt(bool bits[8])
{
	unsigned int integer = 0;

	integer += bits[0] ? 1 : 0;
	integer += bits[1] ? 2 : 0;
	integer += bits[2] ? 4 : 0;
	integer += bits[3] ? 8 : 0;
	integer += bits[4] ? 16 : 0;
	integer += bits[5] ? 32 : 0;
	integer += bits[6] ? 64 : 0;
	integer += bits[7] ? 128 : 0;

	return integer;
}

unsigned int Byte::ToUInt(Byte byte)
{
	return ToUInt(byte.bits);
}

unsigned int Byte::ToUInt(int bits[8])
{
	bool* newBits = ToBits(bits);

	return ToUInt(newBits);
}

unsigned int Byte::ToUInt(signed int integer)
{
	bool* newBits = ToBits(integer);

	integer = ToUInt(newBits);

	return integer;
}

unsigned int Byte::ToUInt(std::string newString)
{
	bool* newBits = ToBits(newString);

	return ToUInt(newBits);
}

std::string Byte::ToString(bool bits[8])
{
	std::string newString = "";

	newString += std::to_string(static_cast<int>(bits[7]));
	newString += std::to_string(static_cast<int>(bits[6]));
	newString += std::to_string(static_cast<int>(bits[5]));
	newString += std::to_string(static_cast<int>(bits[4]));
	newString += std::to_string(static_cast<int>(bits[3]));
	newString += std::to_string(static_cast<int>(bits[2]));
	newString += std::to_string(static_cast<int>(bits[1]));
	newString += std::to_string(static_cast<int>(bits[0]));

	return newString;
}

std::string Byte::ToString(Byte byte)
{
	return ToString(byte.bits);
}

std::string Byte::ToString(int bits[8])
{
	std::string newString = "";

	newString += std::to_string(bits[7]);
	newString += std::to_string(bits[6]);
	newString += std::to_string(bits[5]);
	newString += std::to_string(bits[4]);
	newString += std::to_string(bits[3]);
	newString += std::to_string(bits[2]);
	newString += std::to_string(bits[1]);
	newString += std::to_string(bits[0]);

	return newString;
}

std::string Byte::ToString(signed int integer)
{
	std::string newString = "";
	int newBits[8];

	newBits[7] = integer < 0;
	integer *= newBits[7] ? -1 : 1;
	newString += std::to_string(newBits[7]);

	newBits[6] = integer >= 64;
	integer -= newBits[6] ? 64 : 0;
	newString += std::to_string(newBits[6]);

	newBits[5] = integer >= 32;
	integer -= newBits[5] ? 32 : 0;
	newString += std::to_string(newBits[5]);

	newBits[4] = integer >= 16;
	integer -= newBits[4] ? 16 : 0;
	newString += std::to_string(newBits[4]);

	newBits[3] = integer >= 8;
	integer -= newBits[3] ? 8 : 0;
	newString += std::to_string(newBits[3]);

	newBits[2] = integer >= 4;
	integer -= newBits[2] ? 4 : 0;
	newString += std::to_string(newBits[2]);

	newBits[1] = integer >= 2;
	integer -= newBits[1] ? 2 : 0;
	newString += std::to_string(newBits[1]);

	newBits[0] = integer >= 1;
	newString += std::to_string(newBits[0]);

	reverse(newString.begin(), newString.end());

	return newString;
}

std::string Byte::ToString(unsigned int integer)
{
	std::string newString = "";
	int newBits[8];

	newBits[7] = integer >= 128;
	integer -= newBits[7] ? 128 : 0;
	newString += std::to_string(newBits[7]);

	newBits[6] = integer >= 64;
	integer -= newBits[6] ? 64 : 0;
	newString += std::to_string(newBits[6]);

	newBits[5] = integer >= 32;
	integer -= newBits[5] ? 32 : 0;
	newString += std::to_string(newBits[5]);

	newBits[4] = integer >= 16;
	integer -= newBits[4] ? 16 : 0;
	newString += std::to_string(newBits[4]);

	newBits[3] = integer >= 8;
	integer -= newBits[3] ? 8 : 0;
	newString += std::to_string(newBits[3]);

	newBits[2] = integer >= 4;
	integer -= newBits[2] ? 4 : 0;
	newString += std::to_string(newBits[2]);

	newBits[1] = integer >= 2;
	integer -= newBits[1] ? 2 : 0;
	newString += std::to_string(newBits[1]);

	newBits[0] = integer >= 1;
	newString += std::to_string(newBits[0]);

	reverse(newString.begin(), newString.end());

	return newString;
}

Byte Byte::Add(Byte byteA, Byte byteB)
{
	Byte newByte(*byteA + *byteB);

	return newByte;
}

Byte Byte::PlusPlus(Byte byte)
{
	Byte newByte(*byte + 1);

	return newByte;
}

Byte Byte::Increment(Byte byte)
{
	Byte newByte(*byte + 1);

	return newByte;
}

Byte Byte::Subtract(Byte byteA, Byte byteB)
{
	Byte newByte(*byteA - *byteB);

	return newByte;
}

Byte Byte::MinusMinus(Byte byte)
{
	Byte newByte(*byte - 1);

	return newByte;
}

Byte Byte::Decrement(Byte byte)
{
	Byte newByte(*byte - 1);

	return newByte;
}

Byte Byte::Multiply(Byte byteA, Byte byteB)
{
	Byte newByte(*byteA * *byteB);

	return newByte;
}

Byte Byte::Divide(Byte byteA, Byte byteB)
{
	Byte newByte(*byteA / *byteB);

	return newByte;
}

Byte Byte::Modulo(Byte byteA, Byte byteB)
{
	Byte newByte(*byteA % *byteB);

	return newByte;
}

Byte Byte::And(Byte byteA, Byte byteB)
{
	Byte newByte(byteA.bits);

	newByte.bits[0] = byteB.bits[0] && newByte.bits[0] ? true : false;
	newByte.bits[1] = byteB.bits[1] && newByte.bits[1] ? true : false;
	newByte.bits[2] = byteB.bits[2] && newByte.bits[2] ? true : false;
	newByte.bits[3] = byteB.bits[3] && newByte.bits[3] ? true : false;
	newByte.bits[4] = byteB.bits[4] && newByte.bits[4] ? true : false;
	newByte.bits[5] = byteB.bits[5] && newByte.bits[5] ? true : false;
	newByte.bits[6] = byteB.bits[6] && newByte.bits[6] ? true : false;
	newByte.bits[7] = byteB.bits[7] && newByte.bits[7] ? true : false;

	return newByte;
}

Byte Byte::Or(Byte byteA, Byte byteB)
{
	Byte newByte(byteA.bits);

	newByte.bits[0] = byteB.bits[0] ? true : newByte.bits[0];
	newByte.bits[1] = byteB.bits[1] ? true : newByte.bits[1];
	newByte.bits[2] = byteB.bits[2] ? true : newByte.bits[2];
	newByte.bits[3] = byteB.bits[3] ? true : newByte.bits[3];
	newByte.bits[4] = byteB.bits[4] ? true : newByte.bits[4];
	newByte.bits[5] = byteB.bits[5] ? true : newByte.bits[5];
	newByte.bits[6] = byteB.bits[6] ? true : newByte.bits[6];
	newByte.bits[7] = byteB.bits[7] ? true : newByte.bits[7];

	return newByte;
}

Byte Byte::Xor(Byte byteA, Byte byteB)
{
	Byte newByte(byteA.bits);

	newByte.bits[0] = byteB.bits[0] ^ newByte.bits[0] ? true : false;
	newByte.bits[1] = byteB.bits[1] ^ newByte.bits[1] ? true : false;
	newByte.bits[2] = byteB.bits[2] ^ newByte.bits[2] ? true : false;
	newByte.bits[3] = byteB.bits[3] ^ newByte.bits[3] ? true : false;
	newByte.bits[4] = byteB.bits[4] ^ newByte.bits[4] ? true : false;
	newByte.bits[5] = byteB.bits[5] ^ newByte.bits[5] ? true : false;
	newByte.bits[6] = byteB.bits[6] ^ newByte.bits[6] ? true : false;
	newByte.bits[7] = byteB.bits[7] ^ newByte.bits[7] ? true : false;

	return newByte;
}

Byte Byte::LeftShift(Byte byte, int shift)
{
	Byte newByte(*byte << shift);

	return newByte;
}

Byte Byte::RightShift(Byte byte, int shift)
{
	Byte newByte(*byte >> shift);

	return newByte;
}

Byte Byte::Not(Byte byte)
{
	Byte newByte(byte.bits);

	newByte.bits[0] = !newByte.bits[0];
	newByte.bits[1] = !newByte.bits[1];
	newByte.bits[2] = !newByte.bits[2];
	newByte.bits[3] = !newByte.bits[3];
	newByte.bits[4] = !newByte.bits[4];
	newByte.bits[5] = !newByte.bits[5];
	newByte.bits[6] = !newByte.bits[6];
	newByte.bits[7] = !newByte.bits[7];

	return newByte;
}

bool Byte::EqualTo(Byte byteA, Byte byteB)
{
	return (byteA.bits[0] == byteB.bits[0]) && (byteA.bits[1] == byteB.bits[1]) && (byteA.bits[2] == byteB.bits[2]) && (byteA.bits[3] == byteB.bits[3]) && (byteA.bits[4] == byteB.bits[4]) && (byteA.bits[5] == byteB.bits[5]) && (byteA.bits[6] == byteB.bits[6]) && (byteA.bits[7] == byteB.bits[7]);
}

bool Byte::NotEqualTo(Byte byteA, Byte byteB)
{
	return (byteA.bits[7] != byteB.bits[7]) || (byteA.bits[6] != byteB.bits[6]) || (byteA.bits[5] != byteB.bits[5]) || (byteA.bits[4] != byteB.bits[4]) || (byteA.bits[3] != byteB.bits[3]) || (byteA.bits[2] != byteB.bits[2]) || (byteA.bits[1] != byteB.bits[1]) || (byteA.bits[0] != byteB.bits[0]);
}

bool Byte::GreaterThan(Byte byteA, Byte byteB)
{
	if (!byteA.isUnsigned)		// A is both?
	{
		if (!byteB.isUnsigned)	// B is both?
		{
			// A is both, B is both.
			if (!byteA.bits[7])
			{
				// A is positive, B is positive.
				if (!byteB.bits[7])
				{
					if (byteA.bits[6] && !byteB.bits[6])
					{
						return true;
					}
					else if (!byteA.bits[6] && byteB.bits[6])
					{
						return false;
					}
					else if (byteA.bits[5] && !byteB.bits[5])
					{
						return true;
					}
					else if (!byteA.bits[5] && byteB.bits[5])
					{
						return false;
					}
					else if (byteA.bits[4] && !byteB.bits[4])
					{
						return true;
					}
					else if (!byteA.bits[4] && byteB.bits[4])
					{
						return false;
					}
					else if (byteA.bits[3] && !byteB.bits[3])
					{
						return true;
					}
					else if (!byteA.bits[3] && byteB.bits[3])
					{
						return false;
					}
					else if (byteA.bits[2] && !byteB.bits[2])
					{
						return true;
					}
					else if (!byteA.bits[2] && byteB.bits[2])
					{
						return false;
					}
					else if (byteA.bits[1] && !byteB.bits[1])
					{
						return true;
					}
					else if (!byteA.bits[1] && byteB.bits[1])
					{
						return false;
					}
					else if (byteA.bits[0] && !byteB.bits[0])
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				// A is positive, B is negative.
				else
				{
					return true;
				}
			}
			else
			{
				// A is negative, B is positive.
				if (!byteB.bits[7])
				{
					return false;
				}
				// A is negative, B is negative.
				else
				{
					if (byteA.bits[6] && byteB.bits[6])
					{
						return true;
					}
					else if (!byteA.bits[6] && byteB.bits[6])
					{
						return false;
					}
					else if (byteA.bits[5] && !byteB.bits[5])
					{
						return true;
					}
					else if (!byteA.bits[5] && byteB.bits[5])
					{
						return false;
					}
					else if (byteA.bits[4] && !byteB.bits[4])
					{
						return true;
					}
					else if (!byteA.bits[4] && byteB.bits[4])
					{
						return false;
					}
					else if (byteA.bits[3] && !byteB.bits[3])
					{
						return true;
					}
					else if (!byteA.bits[3] && byteB.bits[3])
					{
						return false;
					}
					else if (byteA.bits[2] && !byteB.bits[2])
					{
						return true;
					}
					else if (!byteA.bits[2] && byteB.bits[2])
					{
						return false;
					}
					else if (byteA.bits[1] && !byteB.bits[1])
					{
						return true;
					}
					else if (!byteA.bits[1] && byteB.bits[1])
					{
						return false;
					}
					else if (byteA.bits[0] && !byteB.bits[0])
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
		}
		// A is both, B is positive.
		else
		{
			// A is positive, B is positive.
			if (!byteB.bits[7])
			{
				if (byteA.bits[6] && !byteB.bits[6])
				{
					return true;
				}
				else if (!byteA.bits[6] && byteB.bits[6])
				{
					return false;
				}
				else if (byteA.bits[5] && !byteB.bits[5])
				{
					return true;
				}
				else if (!byteA.bits[5] && byteB.bits[5])
				{
					return false;
				}
				else if (byteA.bits[4] && !byteB.bits[4])
				{
					return true;
				}
				else if (!byteA.bits[4] && byteB.bits[4])
				{
					return false;
				}
				else if (byteA.bits[3] && !byteB.bits[3])
				{
					return true;
				}
				else if (!byteA.bits[3] && byteB.bits[3])
				{
					return false;
				}
				else if (byteA.bits[2] && !byteB.bits[2])
				{
					return true;
				}
				else if (!byteA.bits[2] && byteB.bits[2])
				{
					return false;
				}
				else if (byteA.bits[1] && !byteB.bits[1])
				{
					return true;
				}
				else if (!byteA.bits[1] && byteB.bits[1])
				{
					return false;
				}
				else if (byteA.bits[0] && !byteB.bits[0])
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			// A is negative, B is positive.
			else
			{
				return false;
			}
		}
	}
	else
	{
		// A is positive, B is both.
		if (!byteB.isUnsigned)
		{
			// A is positive, B is positive.
			if (!byteB.bits[7])
			{
				if (byteA.bits[6] && !byteB.bits[6])
				{
					return true;
				}
				else if (!byteA.bits[6] && byteB.bits[6])
				{
					return false;
				}
				else if (byteA.bits[5] && !byteB.bits[5])
				{
					return true;
				}
				else if (!byteA.bits[5] && byteB.bits[5])
				{
					return false;
				}
				else if (byteA.bits[4] && !byteB.bits[4])
				{
					return true;
				}
				else if (!byteA.bits[4] && byteB.bits[4])
				{
					return false;
				}
				else if (byteA.bits[3] && !byteB.bits[3])
				{
					return true;
				}
				else if (!byteA.bits[3] && byteB.bits[3])
				{
					return false;
				}
				else if (byteA.bits[2] && !byteB.bits[2])
				{
					return true;
				}
				else if (!byteA.bits[2] && byteB.bits[2])
				{
					return false;
				}
				else if (byteA.bits[1] && !byteB.bits[1])
				{
					return true;
				}
				else if (!byteA.bits[1] && byteB.bits[1])
				{
					return false;
				}
				else if (byteA.bits[0] && !byteB.bits[0])
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			// A is positive, B is negative.
			else
			{
				return true;
			}
		}
		// A is positive, B is positive.
		else
		{
			if (byteA.bits[7] && !byteB.bits[7])
			{
				return true;
			}
			else if (!byteA.bits[7] && byteB.bits[7])
			{
				return false;
			}
			else if (byteA.bits[6] && !byteB.bits[6])
			{
				return true;
			}
			else if (!byteA.bits[6] && byteB.bits[6])
			{
				return false;
			}
			else if (byteA.bits[5] && !byteB.bits[5])
			{
				return true;
			}
			else if (!byteA.bits[5] && byteB.bits[5])
			{
				return false;
			}
			else if (byteA.bits[4] && !byteB.bits[4])
			{
				return true;
			}
			else if (!byteA.bits[4] && byteB.bits[4])
			{
				return false;
			}
			else if (byteA.bits[3] && !byteB.bits[3])
			{
				return true;
			}
			else if (!byteA.bits[3] && byteB.bits[3])
			{
				return false;
			}
			else if (byteA.bits[2] && !byteB.bits[2])
			{
				return true;
			}
			else if (!byteA.bits[2] && byteB.bits[2])
			{
				return false;
			}
			else if (byteA.bits[1] && !byteB.bits[1])
			{
				return true;
			}
			else if (!byteA.bits[1] && byteB.bits[1])
			{
				return false;
			}
			else if (byteA.bits[0] && !byteB.bits[0])
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}

bool Byte::GreaterThanEqualTo(Byte byteA, Byte byteB)
{
	if (!byteA.isUnsigned)		// A is both?
	{
		if (!byteB.isUnsigned)	// B is both?
		{
			// A is both, B is both.
			if (!byteA.bits[7])
			{
				// A is positive, B is positive.
				if (!byteB.bits[7])
				{
					if (byteA.bits[6] && !byteB.bits[6])
					{
						return true;
					}
					else if (!byteA.bits[6] && byteB.bits[6])
					{
						return false;
					}
					else if (byteA.bits[5] && !byteB.bits[5])
					{
						return true;
					}
					else if (!byteA.bits[5] && byteB.bits[5])
					{
						return false;
					}
					else if (byteA.bits[4] && !byteB.bits[4])
					{
						return true;
					}
					else if (!byteA.bits[4] && byteB.bits[4])
					{
						return false;
					}
					else if (byteA.bits[3] && !byteB.bits[3])
					{
						return true;
					}
					else if (!byteA.bits[3] && byteB.bits[3])
					{
						return false;
					}
					else if (byteA.bits[2] && !byteB.bits[2])
					{
						return true;
					}
					else if (!byteA.bits[2] && byteB.bits[2])
					{
						return false;
					}
					else if (byteA.bits[1] && !byteB.bits[1])
					{
						return true;
					}
					else if (!byteA.bits[1] && byteB.bits[1])
					{
						return false;
					}
					else if (byteA.bits[0] && !byteB.bits[0])
					{
						return true;
					}
					else if (!byteA.bits[0] && byteB.bits[0])
					{
						return false;
					}
					else
					{
						return true;
					}
				}
				// A is positive, B is negative.
				else
				{
					return true;
				}
			}
			else
			{
				// A is negative, B is positive.
				if (!byteB.bits[7])
				{
					return false;
				}
				// A is negative, B is negative.
				else
				{
					if (byteA.bits[6] && byteB.bits[6])
					{
						return true;
					}
					else if (!byteA.bits[6] && byteB.bits[6])
					{
						return false;
					}
					else if (byteA.bits[5] && !byteB.bits[5])
					{
						return true;
					}
					else if (!byteA.bits[5] && byteB.bits[5])
					{
						return false;
					}
					else if (byteA.bits[4] && !byteB.bits[4])
					{
						return true;
					}
					else if (!byteA.bits[4] && byteB.bits[4])
					{
						return false;
					}
					else if (byteA.bits[3] && !byteB.bits[3])
					{
						return true;
					}
					else if (!byteA.bits[3] && byteB.bits[3])
					{
						return false;
					}
					else if (byteA.bits[2] && !byteB.bits[2])
					{
						return true;
					}
					else if (!byteA.bits[2] && byteB.bits[2])
					{
						return false;
					}
					else if (byteA.bits[1] && !byteB.bits[1])
					{
						return true;
					}
					else if (!byteA.bits[1] && byteB.bits[1])
					{
						return false;
					}
					else if (byteA.bits[0] && !byteB.bits[0])
					{
						return true;
					}
					else
					{
						return true;
					}
				}
			}
		}
		// A is both, B is positive.
		else
		{
			// A is positive, B is positive.
			if (!byteB.bits[7])
			{
				if (byteA.bits[6] && !byteB.bits[6])
				{
					return true;
				}
				else if (!byteA.bits[6] && byteB.bits[6])
				{
					return false;
				}
				else if (byteA.bits[5] && !byteB.bits[5])
				{
					return true;
				}
				else if (!byteA.bits[5] && byteB.bits[5])
				{
					return false;
				}
				else if (byteA.bits[4] && !byteB.bits[4])
				{
					return true;
				}
				else if (!byteA.bits[4] && byteB.bits[4])
				{
					return false;
				}
				else if (byteA.bits[3] && !byteB.bits[3])
				{
					return true;
				}
				else if (!byteA.bits[3] && byteB.bits[3])
				{
					return false;
				}
				else if (byteA.bits[2] && !byteB.bits[2])
				{
					return true;
				}
				else if (!byteA.bits[2] && byteB.bits[2])
				{
					return false;
				}
				else if (byteA.bits[1] && !byteB.bits[1])
				{
					return true;
				}
				else if (!byteA.bits[1] && byteB.bits[1])
				{
					return false;
				}
				else if (byteA.bits[0] && !byteB.bits[0])
				{
					return true;
				}
				else if (!byteA.bits[0] && byteB.bits[0])
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			// A is negative, B is positive.
			else
			{
				return false;
			}
		}
	}
	else
	{
		// A is positive, B is both.
		if (!byteB.isUnsigned)
		{
			// A is positive, B is positive.
			if (!byteB.bits[7])
			{
				if (byteA.bits[6] && !byteB.bits[6])
				{
					return true;
				}
				else if (!byteA.bits[6] && byteB.bits[6])
				{
					return false;
				}
				else if (byteA.bits[5] && !byteB.bits[5])
				{
					return true;
				}
				else if (!byteA.bits[5] && byteB.bits[5])
				{
					return false;
				}
				else if (byteA.bits[4] && !byteB.bits[4])
				{
					return true;
				}
				else if (!byteA.bits[4] && byteB.bits[4])
				{
					return false;
				}
				else if (byteA.bits[3] && !byteB.bits[3])
				{
					return true;
				}
				else if (!byteA.bits[3] && byteB.bits[3])
				{
					return false;
				}
				else if (byteA.bits[2] && !byteB.bits[2])
				{
					return true;
				}
				else if (!byteA.bits[2] && byteB.bits[2])
				{
					return false;
				}
				else if (byteA.bits[1] && !byteB.bits[1])
				{
					return true;
				}
				else if (!byteA.bits[1] && byteB.bits[1])
				{
					return false;
				}
				else if (byteA.bits[0] && !byteB.bits[0])
				{
					return true;
				}
				else if (!byteA.bits[0] && byteB.bits[0])
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			// A is positive, B is negative.
			else
			{
				return true;
			}
		}
		// A is positive, B is positive.
		else
		{
			if (byteA.bits[7] && !byteB.bits[7])
			{
				return true;
			}
			else if (!byteA.bits[7] && byteB.bits[7])
			{
				return false;
			}
			else if (byteA.bits[6] && !byteB.bits[6])
			{
				return true;
			}
			else if (!byteA.bits[6] && byteB.bits[6])
			{
				return false;
			}
			else if (byteA.bits[5] && !byteB.bits[5])
			{
				return true;
			}
			else if (!byteA.bits[5] && byteB.bits[5])
			{
				return false;
			}
			else if (byteA.bits[4] && !byteB.bits[4])
			{
				return true;
			}
			else if (!byteA.bits[4] && byteB.bits[4])
			{
				return false;
			}
			else if (byteA.bits[3] && !byteB.bits[3])
			{
				return true;
			}
			else if (!byteA.bits[3] && byteB.bits[3])
			{
				return false;
			}
			else if (byteA.bits[2] && !byteB.bits[2])
			{
				return true;
			}
			else if (!byteA.bits[2] && byteB.bits[2])
			{
				return false;
			}
			else if (byteA.bits[1] && !byteB.bits[1])
			{
				return true;
			}
			else if (!byteA.bits[1] && byteB.bits[1])
			{
				return false;
			}
			else if (byteA.bits[0] && !byteB.bits[0])
			{
				return true;
			}
			else if (!byteA.bits[0] && byteB.bits[0])
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}
}

bool Byte::LessThan(Byte byteA, Byte byteB)
{
	if (!byteA.isUnsigned)		// A is both?
	{
		if (!byteB.isUnsigned)	// B is both?
		{
			// A is both, B is both.
			if (!byteA.bits[7])
			{
				// A is positive, B is positive.
				if (!byteB.bits[7])
				{
					if (!byteA.bits[6] && byteB.bits[6])
					{
						return true;
					}
					else if (byteA.bits[6] && !byteB.bits[6])
					{
						return false;
					}
					else if (!byteA.bits[5] && byteB.bits[5])
					{
						return true;
					}
					else if (byteA.bits[5] && !byteB.bits[5])
					{
						return false;
					}
					else if (!byteA.bits[4] && byteB.bits[4])
					{
						return true;
					}
					else if (byteA.bits[4] && !byteB.bits[4])
					{
						return false;
					}
					else if (!byteA.bits[3] && byteB.bits[3])
					{
						return true;
					}
					else if (byteA.bits[3] && !byteB.bits[3])
					{
						return false;
					}
					else if (!byteA.bits[2] && byteB.bits[2])
					{
						return true;
					}
					else if (byteA.bits[2] && !byteB.bits[2])
					{
						return false;
					}
					else if (!byteA.bits[1] && byteB.bits[1])
					{
						return true;
					}
					else if (byteA.bits[1] && !byteB.bits[1])
					{
						return false;
					}
					else if (!byteA.bits[0] && byteB.bits[0])
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				// A is positive, B is negative.
				else
				{
					return false;
				}
			}
			else
			{
				// A is negative, B is positive.
				if (!byteB.bits[7])
				{
					return true;
				}
				// A is negative, B is negative.
				else
				{
					if (!byteA.bits[6] && byteB.bits[6])
					{
						return true;
					}
					else if (byteA.bits[6] && !byteB.bits[6])
					{
						return false;
					}
					else if (!byteA.bits[5] && byteB.bits[5])
					{
						return true;
					}
					else if (byteA.bits[5] && !byteB.bits[5])
					{
						return false;
					}
					else if (!byteA.bits[4] && byteB.bits[4])
					{
						return true;
					}
					else if (byteA.bits[4] && !byteB.bits[4])
					{
						return false;
					}
					else if (!byteA.bits[3] && byteB.bits[3])
					{
						return true;
					}
					else if (byteA.bits[3] && !byteB.bits[3])
					{
						return false;
					}
					else if (!byteA.bits[2] && byteB.bits[2])
					{
						return true;
					}
					else if (byteA.bits[2] && !byteB.bits[2])
					{
						return false;
					}
					else if (!byteA.bits[1] && byteB.bits[1])
					{
						return true;
					}
					else if (byteA.bits[1] && !byteB.bits[1])
					{
						return false;
					}
					else if (!byteA.bits[0] && byteB.bits[0])
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
		}
		// A is both, B is positive.
		else
		{
			// A is positive, B is positive.
			if (!byteB.bits[7])
			{
				if (!byteA.bits[6] && byteB.bits[6])
				{
					return true;
				}
				else if (byteA.bits[6] && !byteB.bits[6])
				{
					return false;
				}
				else if (!byteA.bits[5] && byteB.bits[5])
				{
					return true;
				}
				else if (byteA.bits[5] && !byteB.bits[5])
				{
					return false;
				}
				else if (!byteA.bits[4] && byteB.bits[4])
				{
					return true;
				}
				else if (byteA.bits[4] && !byteB.bits[4])
				{
					return false;
				}
				else if (!byteA.bits[3] && byteB.bits[3])
				{
					return true;
				}
				else if (byteA.bits[3] && !byteB.bits[3])
				{
					return false;
				}
				else if (!byteA.bits[2] && byteB.bits[2])
				{
					return true;
				}
				else if (byteA.bits[2] && !byteB.bits[2])
				{
					return false;
				}
				else if (!byteA.bits[1] && byteB.bits[1])
				{
					return true;
				}
				else if (byteA.bits[1] && !byteB.bits[1])
				{
					return false;
				}
				else if (!byteA.bits[0] && byteB.bits[0])
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			// A is negative, B is positive.
			else
			{
				return true;
			}
		}
	}
	else
	{
		// A is positive, B is both.
		if (!byteB.isUnsigned)
		{
			// A is positive, B is positive.
			if (!byteB.bits[7])
			{
				if (!byteA.bits[6] && byteB.bits[6])
				{
					return true;
				}
				else if (byteA.bits[6] && !byteB.bits[6])
				{
					return false;
				}
				else if (!byteA.bits[5] && byteB.bits[5])
				{
					return true;
				}
				else if (byteA.bits[5] && !byteB.bits[5])
				{
					return false;
				}
				else if (!byteA.bits[4] && byteB.bits[4])
				{
					return true;
				}
				else if (byteA.bits[4] && !byteB.bits[4])
				{
					return false;
				}
				else if (!byteA.bits[3] && byteB.bits[3])
				{
					return true;
				}
				else if (byteA.bits[3] && !byteB.bits[3])
				{
					return false;
				}
				else if (!byteA.bits[2] && byteB.bits[2])
				{
					return true;
				}
				else if (byteA.bits[2] && !byteB.bits[2])
				{
					return false;
				}
				else if (!byteA.bits[1] && byteB.bits[1])
				{
					return true;
				}
				else if (byteA.bits[1] && !byteB.bits[1])
				{
					return false;
				}
				else if (!byteA.bits[0] && byteB.bits[0])
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			// A is positive, B is negative.
			else
			{
				return false;
			}
		}
		// A is positive, B is positive.
		else
		{
			if (!byteA.bits[7] && byteB.bits[7])
			{
				return true;
			}
			else if (byteA.bits[7] && !byteB.bits[7])
			{
				return false;
			}
			else if (!byteA.bits[6] && byteB.bits[6])
			{
				return true;
			}
			else if (byteA.bits[6] && !byteB.bits[6])
			{
				return false;
			}
			else if (!byteA.bits[5] && byteB.bits[5])
			{
				return true;
			}
			else if (byteA.bits[5] && !byteB.bits[5])
			{
				return false;
			}
			else if (!byteA.bits[4] && byteB.bits[4])
			{
				return true;
			}
			else if (byteA.bits[4] && !byteB.bits[4])
			{
				return false;
			}
			else if (!byteA.bits[3] && byteB.bits[3])
			{
				return true;
			}
			else if (byteA.bits[3] && !byteB.bits[3])
			{
				return false;
			}
			else if (!byteA.bits[2] && byteB.bits[2])
			{
				return true;
			}
			else if (byteA.bits[2] && !byteB.bits[2])
			{
				return false;
			}
			else if (!byteA.bits[1] && byteB.bits[1])
			{
				return true;
			}
			else if (byteA.bits[1] && !byteB.bits[1])
			{
				return false;
			}
			else if (!byteA.bits[0] && byteB.bits[0])
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}

bool Byte::LessThanEqualTo(Byte byteA, Byte byteB)
{
	if (!byteA.isUnsigned)		// A is both?
	{
		if (!byteB.isUnsigned)	// B is both?
		{
			// A is both, B is both.
			if (!byteA.bits[7])
			{
				// A is positive, B is positive.
				if (!byteB.bits[7])
				{
					if (!byteA.bits[6] && byteB.bits[6])
					{
						return true;
					}
					else if (byteA.bits[6] && !byteB.bits[6])
					{
						return false;
					}
					else if (!byteA.bits[5] && byteB.bits[5])
					{
						return true;
					}
					else if (byteA.bits[5] && !byteB.bits[5])
					{
						return false;
					}
					else if (!byteA.bits[4] && byteB.bits[4])
					{
						return true;
					}
					else if (byteA.bits[4] && !byteB.bits[4])
					{
						return false;
					}
					else if (!byteA.bits[3] && byteB.bits[3])
					{
						return true;
					}
					else if (byteA.bits[3] && !byteB.bits[3])
					{
						return false;
					}
					else if (!byteA.bits[2] && byteB.bits[2])
					{
						return true;
					}
					else if (byteA.bits[2] && !byteB.bits[2])
					{
						return false;
					}
					else if (!byteA.bits[1] && byteB.bits[1])
					{
						return true;
					}
					else if (byteA.bits[1] && !byteB.bits[1])
					{
						return false;
					}
					else if (!byteA.bits[0] && byteB.bits[0])
					{
						return true;
					}
					else if (byteA.bits[0] && !byteB.bits[0])
					{
						return false;
					}
					else
					{
						return true;
					}
				}
				// A is positive, B is negative.
				else
				{
					return false;
				}
			}
			else
			{
				// A is negative, B is positive.
				if (!byteB.bits[7])
				{
					return true;
				}
				// A is negative, B is negative.
				else
				{
					if (!byteA.bits[6] && byteB.bits[6])
					{
						return true;
					}
					else if (byteA.bits[6] && !byteB.bits[6])
					{
						return false;
					}
					else if (!byteA.bits[5] && byteB.bits[5])
					{
						return true;
					}
					else if (byteA.bits[5] && !byteB.bits[5])
					{
						return false;
					}
					else if (!byteA.bits[4] && byteB.bits[4])
					{
						return true;
					}
					else if (byteA.bits[4] && !byteB.bits[4])
					{
						return false;
					}
					else if (!byteA.bits[3] && byteB.bits[3])
					{
						return true;
					}
					else if (byteA.bits[3] && !byteB.bits[3])
					{
						return false;
					}
					else if (!byteA.bits[2] && byteB.bits[2])
					{
						return true;
					}
					else if (byteA.bits[2] && !byteB.bits[2])
					{
						return false;
					}
					else if (!byteA.bits[1] && byteB.bits[1])
					{
						return true;
					}
					else if (byteA.bits[1] && !byteB.bits[1])
					{
						return false;
					}
					else if (!byteA.bits[0] && byteB.bits[0])
					{
						return true;
					}
					else
					{
						return true;
					}
				}
			}
		}
		// A is both, B is positive.
		else
		{
			// A is positive, B is positive.
			if (!byteB.bits[7])
			{
				if (!byteA.bits[6] && byteB.bits[6])
				{
					return true;
				}
				else if (byteA.bits[6] && !byteB.bits[6])
				{
					return false;
				}
				else if (!byteA.bits[5] && byteB.bits[5])
				{
					return true;
				}
				else if (byteA.bits[5] && !byteB.bits[5])
				{
					return false;
				}
				else if (!byteA.bits[4] && byteB.bits[4])
				{
					return true;
				}
				else if (byteA.bits[4] && !byteB.bits[4])
				{
					return false;
				}
				else if (!byteA.bits[3] && byteB.bits[3])
				{
					return true;
				}
				else if (byteA.bits[3] && !byteB.bits[3])
				{
					return false;
				}
				else if (!byteA.bits[2] && byteB.bits[2])
				{
					return true;
				}
				else if (byteA.bits[2] && !byteB.bits[2])
				{
					return false;
				}
				else if (!byteA.bits[1] && byteB.bits[1])
				{
					return true;
				}
				else if (byteA.bits[1] && !byteB.bits[1])
				{
					return false;
				}
				else if (!byteA.bits[0] && byteB.bits[0])
				{
					return true;
				}
				else if (byteA.bits[0] && !byteB.bits[0])
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			// A is negative, B is positive.
			else
			{
				return true;
			}
		}
	}
	else
	{
		// A is positive, B is both.
		if (!byteB.isUnsigned)
		{
			// A is positive, B is positive.
			if (!byteB.bits[7])
			{
				if (!byteA.bits[6] && byteB.bits[6])
				{
					return true;
				}
				else if (byteA.bits[6] && !byteB.bits[6])
				{
					return false;
				}
				else if (!byteA.bits[5] && byteB.bits[5])
				{
					return true;
				}
				else if (byteA.bits[5] && !byteB.bits[5])
				{
					return false;
				}
				else if (!byteA.bits[4] && byteB.bits[4])
				{
					return true;
				}
				else if (byteA.bits[4] && !byteB.bits[4])
				{
					return false;
				}
				else if (!byteA.bits[3] && byteB.bits[3])
				{
					return true;
				}
				else if (byteA.bits[3] && !byteB.bits[3])
				{
					return false;
				}
				else if (!byteA.bits[2] && byteB.bits[2])
				{
					return true;
				}
				else if (byteA.bits[2] && !byteB.bits[2])
				{
					return false;
				}
				else if (!byteA.bits[1] && byteB.bits[1])
				{
					return true;
				}
				else if (byteA.bits[1] && !byteB.bits[1])
				{
					return false;
				}
				else if (!byteA.bits[0] && byteB.bits[0])
				{
					return true;
				}
				else if (byteA.bits[0] && !byteB.bits[0])
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			// A is positive, B is negative.
			else
			{
				return false;
			}
		}
		// A is positive, B is positive.
		else
		{
			if (!byteA.bits[7] && byteB.bits[7])
			{
				return true;
			}
			else if (byteA.bits[7] && !byteB.bits[7])
			{
				return false;
			}
			else if (!byteA.bits[6] && byteB.bits[6])
			{
				return true;
			}
			else if (byteA.bits[6] && !byteB.bits[6])
			{
				return false;
			}
			else if (!byteA.bits[5] && byteB.bits[5])
			{
				return true;
			}
			else if (byteA.bits[5] && !byteB.bits[5])
			{
				return false;
			}
			else if (!byteA.bits[4] && byteB.bits[4])
			{
				return true;
			}
			else if (byteA.bits[4] && !byteB.bits[4])
			{
				return false;
			}
			else if (!byteA.bits[3] && byteB.bits[3])
			{
				return true;
			}
			else if (byteA.bits[3] && !byteB.bits[3])
			{
				return false;
			}
			else if (!byteA.bits[2] && byteB.bits[2])
			{
				return true;
			}
			else if (byteA.bits[2] && !byteB.bits[2])
			{
				return false;
			}
			else if (!byteA.bits[1] && byteB.bits[1])
			{
				return true;
			}
			else if (byteA.bits[1] && !byteB.bits[1])
			{
				return false;
			}
			else if (!byteA.bits[0] && byteB.bits[0])
			{
				return true;
			}
			else if (byteA.bits[0] && !byteB.bits[0])
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}
}

bool Byte::Bool(Byte byte)
{
	if (byte.bits[0])
	{
		return true;
	}
	else if (byte.bits[1])
	{
		return true;
	}
	else if (byte.bits[2])
	{
		return true;
	}
	else if (byte.bits[3])
	{
		return true;
	}
	else if (byte.bits[4])
	{
		return true;
	}
	else if (byte.bits[5])
	{
		return true;
	}
	else if (byte.bits[6])
	{
		return true;
	}
	else if (byte.bits[7])
	{
		return true;
	}

	return false;
}

bool Byte::NotBool(Byte byte)
{
	if (byte.bits[0])
	{
		return false;
	}
	else if (byte.bits[1])
	{
		return false;
	}
	else if (byte.bits[2])
	{
		return false;
	}
	else if (byte.bits[3])
	{
		return false;
	}
	else if (byte.bits[4])
	{
		return false;
	}
	else if (byte.bits[5])
	{
		return false;
	}
	else if (byte.bits[6])
	{
		return false;
	}
	else if (byte.bits[7])
	{
		return false;
	}

	return true;
}

Byte* Byte::Copy(Byte* bytes, int byteCount)
{
	Byte* newBytes = new Byte[byteCount];

	for (int currentByte = 0; currentByte < byteCount; currentByte++)
	{
		for (int currentBit = 0; currentBit < 8; currentBit++)
		{
			newBytes[currentByte].bits[currentBit] = bytes[currentByte].bits[currentBit];
		}
	}

	return newBytes;
}

bool* Byte::ToBits(Byte* bytes, int byteCount)
{
	bool* newBits = new bool[byteCount * 8];

	for (int currentByte = 0; currentByte < byteCount; currentByte++)
	{
		for (int currentBit = 0; currentBit < 8; currentBit++)
		{
			newBits[currentByte * 8 + currentBit] = bytes[currentByte].bits[currentBit];
		}
	}

	return newBits;
}

int* Byte::ToBitsInt(Byte* bytes, int byteCount)
{
	int* newBits = new int[byteCount * 8];

	for (int currentByte = 0; currentByte < byteCount; currentByte++)
	{
		for (int currentBit = 0; currentBit < 8; currentBit++)
		{
			newBits[currentByte * 8 + currentBit] = bytes[currentByte].bits[currentBit];
		}
	}

	return newBits;
}

signed int Byte::ToInt(Byte* bytes, int byteCount)
{
	signed int integer = 0;

	for (int currentByte = 0; currentByte < byteCount - 1; currentByte++)
	{
		for (int currentBit = 0; currentBit < 8; currentBit++)
		{
			integer += (bytes[currentByte].bits[currentBit]) * (pow(2, (currentByte * 8 + currentBit)));
		}
	}

	for (int currentBit = 0; currentBit < 7; currentBit++)
	{
		integer += (bytes[byteCount - 1].bits[currentBit]) * (pow(2, ((byteCount - 1) * 8 + currentBit)));
	}

	integer *= bytes[byteCount - 1].bits[7] ? -1 : 1;

	return integer;
}

unsigned int Byte::ToUInt(Byte* bytes, int byteCount)
{
	unsigned int integer = 0;

	for (int currentByte = 0; currentByte < byteCount; currentByte++)
	{
		for (int currentBit = 0; currentBit < 8; currentBit++)
		{
			integer += (bytes[currentByte].bits[currentBit]) * (pow(2, (currentByte * 8 + currentBit)));
		}
	}

	return integer;
}

std::string Byte::ToString(Byte* bytes, int byteCount)
{
	std::string newString = "";

	for (int currentByte = byteCount - 1; currentByte >= 0; currentByte--)
	{
		for (int currentBit = 7; currentBit >= 0; currentBit--)
		{
			newString += std::to_string((static_cast<int>(bytes[currentByte].bits[currentBit])));
		}
	}

	return newString;
}

std::string Byte::ToString2(Byte* bytes, int byteCount)
{
	std::string newString = "";

	for (int currentByte = byteCount - 1; currentByte >= 0; currentByte--)
	{
		for (int currentBit = 7; currentBit >= 0; currentBit--)
		{
			newString += std::to_string((static_cast<int>(bytes[currentByte].bits[currentBit])));
		}

		newString += " ";
	}

	return newString;
}

Byte Byte::Copy()
{
	Byte newByte(bits);

	return newByte;
}

bool* Byte::ToBits()
{
	return ToBits(bits);
}

int* Byte::ToBitsInt()
{
	return ToBitsInt(bits);
}

signed int Byte::ToInt()
{
	return ToInt(bits);
}

unsigned int Byte::ToUInt()
{
	return ToUInt(bits);
}

std::string Byte::ToString()
{
	return ToString(bits);
}

bool& Byte::GetBit(int index)
{
	return bits[index];
}

int Byte::GetBitInt(int index)
{
	return bits[index];
}

Byte& Byte::SetBit(int index, bool newValue)
{
	bits[index] = newValue;

	return *this;
}

Byte& Byte::SetBitInt(int index, int newValue)
{
	bits[index] = newValue;

	return *this;
}

bool& Byte::FlipBit(int index)
{
	bits[index] = !bits[index];

	return bits[index];
}

int Byte::Value()
{
	return isUnsigned ? ToInt() : ToUInt();
}

bool& Byte::SwitchSign()
{
	isUnsigned = !isUnsigned;

	return isUnsigned;
}

bool& Byte::SwitchSign(bool newSign)
{
	isUnsigned = newSign;

	return isUnsigned;
}

Byte& Byte::Equals(Byte byte)
{
	bits[0] = byte[0];
	bits[1] = byte[1];
	bits[2] = byte[2];
	bits[3] = byte[3];
	bits[4] = byte[4];
	bits[5] = byte[5];
	bits[6] = byte[6];
	bits[7] = byte[7];

	return *this;
}

Byte& Byte::Add(Byte byte)
{
	Byte newByte(Add(*this, byte).bits);

	Equals(newByte);

	return *this;
}

Byte& Byte::PlusPlus()
{
	Byte newByte(PlusPlus(*this).bits);

	Equals(newByte);

	return *this;
}

Byte& Byte::Increment()
{
	Byte newByte(Increment(*this).bits);

	Equals(newByte);

	return *this;
}

Byte& Byte::Subtract(Byte byte)
{
	Byte newByte(Subtract(*this, byte).bits);

	Equals(newByte);

	return *this;
}

Byte& Byte::MinusMinus()
{
	Byte newByte(MinusMinus(*this).bits);

	Equals(newByte);

	return *this;
}

Byte& Byte::Decrement()
{
	Byte newByte(Decrement(*this).bits);

	Equals(newByte);

	return *this;
}

Byte& Byte::Multiply(Byte byte)
{
	Byte newByte(Multiply(*this, byte).bits);

	Equals(newByte);

	return *this;
}

Byte& Byte::Divide(Byte byte)
{
	Byte newByte(Divide(*this, byte).bits);

	Equals(newByte);

	return *this;
}

Byte& Byte::Modulo(Byte byte)
{
	Byte newByte(Modulo(*this, byte).bits);

	Equals(newByte);

	return *this;
}

Byte& Byte::And(Byte byte)
{
	Byte newByte(And(*this, byte).bits);

	Equals(newByte);

	return *this;
}

Byte& Byte::Or(Byte byte)
{
	Byte newByte(Or(*this, byte).bits);

	Equals(newByte);

	return *this;
}

Byte& Byte::Xor(Byte byte)
{
	Byte newByte(Xor(*this, byte).bits);

	Equals(newByte);

	return *this;
}

Byte& Byte::LeftShift(int shift)
{
	Byte newByte(LeftShift(*this, shift).bits);

	Equals(newByte);

	return *this;
}

Byte& Byte::RightShift(int shift)
{
	Byte newByte(RightShift(*this, shift).bits);

	Equals(newByte);

	return *this;
}

Byte Byte::Not()
{
	Byte newByte(bits);

	newByte.bits[0] = !newByte.bits[0];
	newByte.bits[1] = !newByte.bits[1];
	newByte.bits[2] = !newByte.bits[2];
	newByte.bits[3] = !newByte.bits[3];
	newByte.bits[4] = !newByte.bits[4];
	newByte.bits[5] = !newByte.bits[5];
	newByte.bits[6] = !newByte.bits[6];
	newByte.bits[7] = !newByte.bits[7];

	return newByte;
}

Byte& Byte::Flip()
{
	bits[0] = !bits[0];
	bits[1] = !bits[1];
	bits[2] = !bits[2];
	bits[3] = !bits[3];
	bits[4] = !bits[4];
	bits[5] = !bits[5];
	bits[6] = !bits[6];
	bits[7] = !bits[7];

	return *this;
}

bool Byte::EqualTo(Byte byte)
{
	return EqualTo(*this, byte);
}

bool Byte::NotEqualTo(Byte byte)
{
	return NotEqualTo(*this, byte);
}

bool Byte::GreaterThan(Byte byte)
{
	return GreaterThan(*this, byte);
}

bool Byte::GreaterThanEqualTo(Byte byte)
{
	return GreaterThanEqualTo(*this, byte);
}

bool Byte::LessThan(Byte byte)
{
	return LessThan(*this, byte);
}

bool Byte::LessThanEqualTo(Byte byte)
{
	return LessThanEqualTo(*this, byte);
}

bool Byte::Bool()
{
	return Bool(*this);
}

bool Byte::NotBool()
{
	return NotBool(*this);
}

bool& Byte::operator[](int index)
{
	return bits[index];
}

Byte::operator int()
{
	return Value();
}

int Byte::operator*()
{
	return isUnsigned ? ToUInt() : ToInt();
}

signed int Byte::operator-()
{
	return ToInt();
}

unsigned int Byte::operator+()
{
	return ToUInt();
}

Byte Byte::operator+(Byte byte)
{
	return Add(byte);
}

Byte Byte::operator-(Byte byte)
{
	return Subtract(byte);
}

Byte Byte::operator*(Byte byte)
{
	return Multiply(byte);
}

Byte Byte::operator/(Byte byte)
{
	return Divide(byte);
}

Byte Byte::operator%(Byte byte)
{
	return Modulo(byte);
}

Byte Byte::operator&(Byte byte)
{
	return And(byte);
}

Byte Byte::operator|(Byte byte)
{
	return Or(byte);
}

Byte Byte::operator^(Byte byte)
{
	return Xor(byte);
}

Byte Byte::operator<<(int shift)
{
	return LeftShift(shift);
}

Byte Byte::operator>>(int shift)
{
	return RightShift(shift);
}

Byte Byte::operator~()
{
	Byte newByte(bits);

	newByte.bits[0] = !newByte.bits[0];
	newByte.bits[1] = !newByte.bits[1];
	newByte.bits[2] = !newByte.bits[2];
	newByte.bits[3] = !newByte.bits[3];
	newByte.bits[4] = !newByte.bits[4];
	newByte.bits[5] = !newByte.bits[5];
	newByte.bits[6] = !newByte.bits[6];
	newByte.bits[7] = !newByte.bits[7];

	return newByte;
}

Byte& Byte::operator=(Byte byte)
{
	return Equals(byte);
}

Byte& Byte::operator+=(Byte byte)
{
	return Add(byte);
}

Byte& Byte::operator++()
{
	return PlusPlus();
}

Byte& Byte::operator-=(Byte byte)
{
	return Subtract(byte);
}

Byte& Byte::operator--()
{
	return MinusMinus();
}

Byte& Byte::operator*=(Byte byte)
{
	return Multiply(byte);
}

Byte& Byte::operator/=(Byte byte)
{
	return Divide(byte);
}

Byte& Byte::operator%=(Byte byte)
{
	return Modulo(byte);
}

Byte& Byte::operator&=(Byte byte)
{
	return And(byte);
}

Byte& Byte::operator|=(Byte byte)
{
	return Or(byte);
}

Byte& Byte::operator^=(Byte byte)
{
	return Xor(byte);
}

Byte& Byte::operator<<=(int shift)
{
	return LeftShift(shift);
}

Byte& Byte::operator>>=(int shift)
{
	return RightShift(shift);
}

bool Byte::operator==(Byte byte)
{
	return EqualTo(byte);
}

bool Byte::operator!=(Byte byte)
{
	return NotEqualTo(byte);
}

bool Byte::operator>(Byte byte)
{
	return GreaterThan(byte);
}

bool Byte::operator>=(Byte byte)
{
	return GreaterThanEqualTo(byte);
}

bool Byte::operator<(Byte byte)
{
	return LessThan(byte);
}

bool Byte::operator<=(Byte byte)
{
	return LessThanEqualTo(byte);
}

Byte::operator bool()
{
	return Bool();
}

bool Byte::operator!()
{
	return NotBool();
}
