
// Byte Data Type Function Definitions Script
// by Kyle Furey

#pragma once

// Include this heading to use the class
#include "byte.h"

// Byte functions
byte::byte()
{
	bits = { false, false, false, false, false, false, false, false };

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
	bits = { false, false, false, false, false, false, false, false };

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

byte::byte(bool boolean, bool is_unsigned)
{
	bits = { false, false, false, false, false, false, false, false };

	is_unsigned = is_unsigned;

	bits[0] = boolean;
	bits[1] = boolean;
	bits[2] = boolean;
	bits[3] = boolean;
	bits[4] = boolean;
	bits[5] = boolean;
	bits[6] = boolean;
	bits[7] = boolean;
}

byte::byte(std::vector<bool> new_bits)
{
	bits = { false, false, false, false, false, false, false, false };

	is_unsigned = true;

	bits[0] = new_bits[0];
	bits[1] = new_bits[1];
	bits[2] = new_bits[2];
	bits[3] = new_bits[3];
	bits[4] = new_bits[4];
	bits[5] = new_bits[5];
	bits[6] = new_bits[6];
	bits[7] = new_bits[7];
}

byte::byte(std::vector<bool> new_bits, bool is_unsigned)
{
	bits = { false, false, false, false, false, false, false, false };

	is_unsigned = is_unsigned;

	bits[0] = new_bits[0];
	bits[1] = new_bits[1];
	bits[2] = new_bits[2];
	bits[3] = new_bits[3];
	bits[4] = new_bits[4];
	bits[5] = new_bits[5];
	bits[6] = new_bits[6];
	bits[7] = new_bits[7];
}

byte::byte(int new_bits[8])
{
	bits = { false, false, false, false, false, false, false, false };

	is_unsigned = true;

	bits[0] = new_bits[0];
	bits[1] = new_bits[1];
	bits[2] = new_bits[2];
	bits[3] = new_bits[3];
	bits[4] = new_bits[4];
	bits[5] = new_bits[5];
	bits[6] = new_bits[6];
	bits[7] = new_bits[7];
}

byte::byte(int new_bits[8], bool is_unsigned)
{
	bits = { false, false, false, false, false, false, false, false };

	is_unsigned = is_unsigned;

	bits[0] = new_bits[0];
	bits[1] = new_bits[1];
	bits[2] = new_bits[2];
	bits[3] = new_bits[3];
	bits[4] = new_bits[4];
	bits[5] = new_bits[5];
	bits[6] = new_bits[6];
	bits[7] = new_bits[7];
}

byte::byte(signed int integer)
{
	bits = { false, false, false, false, false, false, false, false };

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

byte::byte(signed int integer, bool is_unsigned)
{
	bits = { false, false, false, false, false, false, false, false };

	is_unsigned = is_unsigned;

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
	bits = { false, false, false, false, false, false, false, false };

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

byte::byte(unsigned int integer, bool is_unsigned)
{
	bits = { false, false, false, false, false, false, false, false };

	is_unsigned = is_unsigned;

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

byte::byte(std::string new_string)
{
	bits = { false, false, false, false, false, false, false, false };

	is_unsigned = true;

	bits[0] = new_string[7] - 48;
	bits[1] = new_string[6] - 48;
	bits[2] = new_string[5] - 48;
	bits[3] = new_string[4] - 48;
	bits[4] = new_string[3] - 48;
	bits[5] = new_string[2] - 48;
	bits[6] = new_string[1] - 48;
	bits[7] = new_string[0] - 48;
}

byte::byte(std::string new_string, bool is_unsigned)
{
	bits = { false, false, false, false, false, false, false, false };

	is_unsigned = is_unsigned;

	bits[0] = new_string[7] - 48;
	bits[1] = new_string[6] - 48;
	bits[2] = new_string[5] - 48;
	bits[3] = new_string[4] - 48;
	bits[4] = new_string[3] - 48;
	bits[5] = new_string[2] - 48;
	bits[6] = new_string[1] - 48;
	bits[7] = new_string[0] - 48;
}

byte::~byte() { }

byte& byte::to_byte(std::vector<bool> bits)
{
	static byte new_byte(bits);

	return new_byte;
}

byte& byte::to_byte(int bits[8])
{
	static byte new_byte(bits);

	return new_byte;
}

byte& byte::to_byte(signed int integer)
{
	static byte new_byte(integer);

	return new_byte;
}

byte& byte::to_byte(unsigned int integer)
{
	static byte new_byte(integer);

	return new_byte;
}

byte& byte::to_byte(std::string new_string)
{
	static byte new_byte(new_string);

	return new_byte;
}

std::vector<bool> byte::to_bits(byte byte)
{
	static std::vector<bool> new_bits = { false, false, false, false, false, false, false, false };

	new_bits[0] = byte.bits[0];
	new_bits[1] = byte.bits[1];
	new_bits[2] = byte.bits[2];
	new_bits[3] = byte.bits[3];
	new_bits[4] = byte.bits[4];
	new_bits[5] = byte.bits[5];
	new_bits[6] = byte.bits[6];
	new_bits[7] = byte.bits[7];

	return new_bits;
}

std::vector<bool> byte::to_bits(int bits[8])
{
	static std::vector<bool> new_bits = { false, false, false, false, false, false, false, false };

	new_bits[0] = bits[0];
	new_bits[1] = bits[1];
	new_bits[2] = bits[2];
	new_bits[3] = bits[3];
	new_bits[4] = bits[4];
	new_bits[5] = bits[5];
	new_bits[6] = bits[6];
	new_bits[7] = bits[7];

	return new_bits;
}

std::vector<bool> byte::to_bits(signed int integer)
{
	static std::vector<bool> new_bits = { false, false, false, false, false, false, false, false };

	new_bits[7] = integer < 0;
	integer += new_bits[7] ? 128 : 0;

	new_bits[6] = integer >= 64;
	integer -= new_bits[6] ? 64 : 0;

	new_bits[5] = integer >= 32;
	integer -= new_bits[5] ? 32 : 0;

	new_bits[4] = integer >= 16;
	integer -= new_bits[4] ? 16 : 0;

	new_bits[3] = integer >= 8;
	integer -= new_bits[3] ? 8 : 0;

	new_bits[2] = integer >= 4;
	integer -= new_bits[2] ? 4 : 0;

	new_bits[1] = integer >= 2;
	integer -= new_bits[1] ? 2 : 0;

	new_bits[0] = integer >= 1;

	return new_bits;
}

std::vector<bool> byte::to_bits(unsigned int integer)
{
	static std::vector<bool> new_bits = { false, false, false, false, false, false, false, false };

	new_bits[7] = integer >= 128;
	integer -= new_bits[7] ? 128 : 0;

	new_bits[6] = integer >= 64;
	integer -= new_bits[6] ? 64 : 0;

	new_bits[5] = integer >= 32;
	integer -= new_bits[5] ? 32 : 0;

	new_bits[4] = integer >= 16;
	integer -= new_bits[4] ? 16 : 0;

	new_bits[3] = integer >= 8;
	integer -= new_bits[3] ? 8 : 0;

	new_bits[2] = integer >= 4;
	integer -= new_bits[2] ? 4 : 0;

	new_bits[1] = integer >= 2;
	integer -= new_bits[1] ? 2 : 0;

	new_bits[0] = integer >= 1;

	return new_bits;
}

std::vector<bool> byte::to_bits(std::string new_string)
{
	static std::vector<bool> new_bits = { false, false, false, false, false, false, false, false };

	new_bits[0] = new_string[7] - 48;
	new_bits[1] = new_string[6] - 48;
	new_bits[2] = new_string[5] - 48;
	new_bits[3] = new_string[4] - 48;
	new_bits[4] = new_string[3] - 48;
	new_bits[5] = new_string[2] - 48;
	new_bits[6] = new_string[1] - 48;
	new_bits[7] = new_string[0] - 48;

	return new_bits;
}

int* byte::to_bits_int(std::vector<bool> bits)
{
	static int new_bits[8];

	new_bits[0] = bits[0];
	new_bits[1] = bits[1];
	new_bits[2] = bits[2];
	new_bits[3] = bits[3];
	new_bits[4] = bits[4];
	new_bits[5] = bits[5];
	new_bits[6] = bits[6];
	new_bits[7] = bits[7];

	return new_bits;
}

int* byte::to_bits_int(byte byte)
{
	return to_bits_int(byte.bits);
}

int* byte::to_bits_int(signed int integer)
{
	static int new_bits[8];

	new_bits[7] = integer < 0;
	integer *= new_bits[7] ? -1 : 1;

	new_bits[6] = integer >= 64;
	integer -= new_bits[6] ? 64 : 0;

	new_bits[5] = integer >= 32;
	integer -= new_bits[5] ? 32 : 0;

	new_bits[4] = integer >= 16;
	integer -= new_bits[4] ? 16 : 0;

	new_bits[3] = integer >= 8;
	integer -= new_bits[3] ? 8 : 0;

	new_bits[2] = integer >= 4;
	integer -= new_bits[2] ? 4 : 0;

	new_bits[1] = integer >= 2;
	integer -= new_bits[1] ? 2 : 0;

	new_bits[0] = integer >= 1;

	return new_bits;
}

int* byte::to_bits_int(unsigned int integer)
{
	static int new_bits[8];

	new_bits[7] = integer >= 128;
	integer -= new_bits[7] ? 128 : 0;

	new_bits[6] = integer >= 64;
	integer -= new_bits[6] ? 64 : 0;

	new_bits[5] = integer >= 32;
	integer -= new_bits[5] ? 32 : 0;

	new_bits[4] = integer >= 16;
	integer -= new_bits[4] ? 16 : 0;

	new_bits[3] = integer >= 8;
	integer -= new_bits[3] ? 8 : 0;

	new_bits[2] = integer >= 4;
	integer -= new_bits[2] ? 4 : 0;

	new_bits[1] = integer >= 2;
	integer -= new_bits[1] ? 2 : 0;

	new_bits[0] = integer >= 1;

	return new_bits;
}

int* byte::to_bits_int(std::string new_string)
{
	static int new_bits[8];

	new_bits[0] = new_string[7] - 48;
	new_bits[1] = new_string[6] - 48;
	new_bits[2] = new_string[5] - 48;
	new_bits[3] = new_string[4] - 48;
	new_bits[4] = new_string[3] - 48;
	new_bits[5] = new_string[2] - 48;
	new_bits[6] = new_string[1] - 48;
	new_bits[7] = new_string[0] - 48;

	return new_bits;
}

signed int byte::to_int(std::vector<bool> bits)
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
	std::vector<bool> new_bits = to_bits(bits);

	return to_unsigned_int(new_bits);
}

signed int byte::to_int(unsigned int integer)
{
	std::vector<bool> new_bits = to_bits(integer);

	integer = to_int(new_bits);

	return integer;
}

signed int byte::to_int(std::string new_string)
{
	std::vector<bool> new_bits = to_bits(new_string);

	return to_int(new_bits);
}

unsigned int byte::to_unsigned_int(std::vector<bool> bits)
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
	std::vector<bool> new_bits = to_bits(bits);

	return to_unsigned_int(new_bits);
}

unsigned int byte::to_unsigned_int(signed int integer)
{
	std::vector<bool> new_bits = to_bits(integer);

	integer = to_unsigned_int(new_bits);

	return integer;
}

unsigned int byte::to_unsigned_int(std::string new_string)
{
	std::vector<bool> new_bits = to_bits(new_string);

	return to_unsigned_int(new_bits);
}

std::string byte::to_string(std::vector<bool> bits)
{
	std::string new_string = "";

	new_string += std::to_string(static_cast<int>(bits[7]));
	new_string += std::to_string(static_cast<int>(bits[6]));
	new_string += std::to_string(static_cast<int>(bits[5]));
	new_string += std::to_string(static_cast<int>(bits[4]));
	new_string += std::to_string(static_cast<int>(bits[3]));
	new_string += std::to_string(static_cast<int>(bits[2]));
	new_string += std::to_string(static_cast<int>(bits[1]));
	new_string += std::to_string(static_cast<int>(bits[0]));

	return new_string;
}

std::string byte::to_string(byte byte)
{
	return to_string(byte.bits);
}

std::string byte::to_string(int bits[8])
{
	std::string new_string = "";

	new_string += std::to_string(bits[7]);
	new_string += std::to_string(bits[6]);
	new_string += std::to_string(bits[5]);
	new_string += std::to_string(bits[4]);
	new_string += std::to_string(bits[3]);
	new_string += std::to_string(bits[2]);
	new_string += std::to_string(bits[1]);
	new_string += std::to_string(bits[0]);

	return new_string;
}

std::string byte::to_string(signed int integer)
{
	std::string new_string = "";
	int new_bits[8];

	new_bits[7] = integer < 0;
	integer *= new_bits[7] ? -1 : 1;
	new_string += std::to_string(new_bits[7]);

	new_bits[6] = integer >= 64;
	integer -= new_bits[6] ? 64 : 0;
	new_string += std::to_string(new_bits[6]);

	new_bits[5] = integer >= 32;
	integer -= new_bits[5] ? 32 : 0;
	new_string += std::to_string(new_bits[5]);

	new_bits[4] = integer >= 16;
	integer -= new_bits[4] ? 16 : 0;
	new_string += std::to_string(new_bits[4]);

	new_bits[3] = integer >= 8;
	integer -= new_bits[3] ? 8 : 0;
	new_string += std::to_string(new_bits[3]);

	new_bits[2] = integer >= 4;
	integer -= new_bits[2] ? 4 : 0;
	new_string += std::to_string(new_bits[2]);

	new_bits[1] = integer >= 2;
	integer -= new_bits[1] ? 2 : 0;
	new_string += std::to_string(new_bits[1]);

	new_bits[0] = integer >= 1;
	new_string += std::to_string(new_bits[0]);

	std::reverse(new_string.begin(), new_string.end());

	return new_string;
}

std::string byte::to_string(unsigned int integer)
{
	std::string new_string = "";
	int new_bits[8];

	new_bits[7] = integer >= 128;
	integer -= new_bits[7] ? 128 : 0;
	new_string += std::to_string(new_bits[7]);

	new_bits[6] = integer >= 64;
	integer -= new_bits[6] ? 64 : 0;
	new_string += std::to_string(new_bits[6]);

	new_bits[5] = integer >= 32;
	integer -= new_bits[5] ? 32 : 0;
	new_string += std::to_string(new_bits[5]);

	new_bits[4] = integer >= 16;
	integer -= new_bits[4] ? 16 : 0;
	new_string += std::to_string(new_bits[4]);

	new_bits[3] = integer >= 8;
	integer -= new_bits[3] ? 8 : 0;
	new_string += std::to_string(new_bits[3]);

	new_bits[2] = integer >= 4;
	integer -= new_bits[2] ? 4 : 0;
	new_string += std::to_string(new_bits[2]);

	new_bits[1] = integer >= 2;
	integer -= new_bits[1] ? 2 : 0;
	new_string += std::to_string(new_bits[1]);

	new_bits[0] = integer >= 1;
	new_string += std::to_string(new_bits[0]);

	std::reverse(new_string.begin(), new_string.end());

	return new_string;
}

byte byte::add(byte byteA, byte byteB)
{
	byte new_byte(*byteA + *byteB);

	return new_byte;
}

byte byte::plus_plus(byte byteA)
{
	byte new_byte(*byteA + 1);

	return new_byte;
}

byte byte::increment(byte byteA)
{
	byte new_byte(*byteA + 1);

	return new_byte;
}

byte byte::subtract(byte byteA, byte byteB)
{
	byte new_byte(*byteA - *byteB);

	return new_byte;
}

byte byte::minus_minus(byte byteA)
{
	byte new_byte(*byteA - 1);

	return new_byte;
}

byte byte::decrement(byte byteA)
{
	byte new_byte(*byteA - 1);

	return new_byte;
}

byte byte::multiply(byte byteA, byte byteB)
{
	byte new_byte(*byteA * *byteB);

	return new_byte;
}

byte byte::divide(byte byteA, byte byteB)
{
	byte new_byte(*byteA / *byteB);

	return new_byte;
}

byte byte::modulo(byte byteA, byte byteB)
{
	byte new_byte(*byteA % *byteB);

	return new_byte;
}

byte byte::bit_and(byte byteA, byte byteB)
{
	byte new_byte(byteA.bits);

	new_byte.bits[0] = byteB.bits[0] && new_byte.bits[0] ? true : false;
	new_byte.bits[1] = byteB.bits[1] && new_byte.bits[1] ? true : false;
	new_byte.bits[2] = byteB.bits[2] && new_byte.bits[2] ? true : false;
	new_byte.bits[3] = byteB.bits[3] && new_byte.bits[3] ? true : false;
	new_byte.bits[4] = byteB.bits[4] && new_byte.bits[4] ? true : false;
	new_byte.bits[5] = byteB.bits[5] && new_byte.bits[5] ? true : false;
	new_byte.bits[6] = byteB.bits[6] && new_byte.bits[6] ? true : false;
	new_byte.bits[7] = byteB.bits[7] && new_byte.bits[7] ? true : false;

	return new_byte;
}

byte byte::bit_or(byte byteA, byte byteB)
{
	byte new_byte(byteA.bits);

	new_byte.bits[0] = byteB.bits[0] ? true : new_byte.bits[0];
	new_byte.bits[1] = byteB.bits[1] ? true : new_byte.bits[1];
	new_byte.bits[2] = byteB.bits[2] ? true : new_byte.bits[2];
	new_byte.bits[3] = byteB.bits[3] ? true : new_byte.bits[3];
	new_byte.bits[4] = byteB.bits[4] ? true : new_byte.bits[4];
	new_byte.bits[5] = byteB.bits[5] ? true : new_byte.bits[5];
	new_byte.bits[6] = byteB.bits[6] ? true : new_byte.bits[6];
	new_byte.bits[7] = byteB.bits[7] ? true : new_byte.bits[7];

	return new_byte;
}

byte byte::bit_xor(byte byteA, byte byteB)
{
	byte new_byte(byteA.bits);

	new_byte.bits[0] = byteB.bits[0] ^ new_byte.bits[0] ? true : false;
	new_byte.bits[1] = byteB.bits[1] ^ new_byte.bits[1] ? true : false;
	new_byte.bits[2] = byteB.bits[2] ^ new_byte.bits[2] ? true : false;
	new_byte.bits[3] = byteB.bits[3] ^ new_byte.bits[3] ? true : false;
	new_byte.bits[4] = byteB.bits[4] ^ new_byte.bits[4] ? true : false;
	new_byte.bits[5] = byteB.bits[5] ^ new_byte.bits[5] ? true : false;
	new_byte.bits[6] = byteB.bits[6] ^ new_byte.bits[6] ? true : false;
	new_byte.bits[7] = byteB.bits[7] ^ new_byte.bits[7] ? true : false;

	return new_byte;
}

byte byte::bit_left_shift(byte byteA, int shift)
{
	byte new_byte(*byteA << shift);

	return new_byte;
}

byte byte::bit_right_shift(byte byteA, int shift)
{
	byte new_byte(*byteA >> shift);

	return new_byte;
}

byte byte::bit_not(byte byteA)
{
	byte new_byte(byteA.bits);

	new_byte.bits[0] = !new_byte.bits[0];
	new_byte.bits[1] = !new_byte.bits[1];
	new_byte.bits[2] = !new_byte.bits[2];
	new_byte.bits[3] = !new_byte.bits[3];
	new_byte.bits[4] = !new_byte.bits[4];
	new_byte.bits[5] = !new_byte.bits[5];
	new_byte.bits[6] = !new_byte.bits[6];
	new_byte.bits[7] = !new_byte.bits[7];

	return new_byte;
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

byte byte::copy(byte& bytes, int byte_count)
{
	byte new_bytes = byte(byte_count);

	for (int currentByte = 0; currentByte < byte_count; currentByte++)
	{
		for (int currentBit = 0; currentBit < 8; currentBit++)
		{
			new_bytes[currentByte].bits[currentBit] = bytes[currentByte].bits[currentBit];
		}
	}

	return new_bytes;
}

std::vector<bool> byte::to_bits(byte& bytes, int byte_count)
{
	std::vector<bool> new_bits = std::vector<bool>(byte_count * 8);

	for (int currentByte = 0; currentByte < byte_count; currentByte++)
	{
		for (int currentBit = 0; currentBit < 8; currentBit++)
		{
			new_bits[currentByte * 8 + currentBit] = bytes[currentByte].bits[currentBit];
		}
	}

	return new_bits;
}

int* byte::to_bits_int(byte& bytes, int byte_count)
{
	int* new_bits = new int[byte_count * 8];

	for (int currentByte = 0; currentByte < byte_count; currentByte++)
	{
		for (int currentBit = 0; currentBit < 8; currentBit++)
		{
			new_bits[currentByte * 8 + currentBit] = bytes[currentByte].bits[currentBit];
		}
	}

	return new_bits;
}

signed int byte::to_int(byte& bytes, int byte_count)
{
	signed int integer = 0;

	for (int currentByte = 0; currentByte < byte_count - 1; currentByte++)
	{
		for (int currentBit = 0; currentBit < 8; currentBit++)
		{
			integer += (bytes[currentByte].bits[currentBit]) * (std::pow(2, (currentByte * 8 + currentBit)));
		}
	}

	for (int currentBit = 0; currentBit < 7; currentBit++)
	{
		integer += (bytes[byte_count - 1].bits[currentBit]) * (std::pow(2, ((byte_count - 1) * 8 + currentBit)));
	}

	integer *= bytes[byte_count - 1].bits[7] ? -1 : 1;

	return integer;
}

unsigned int byte::to_unsigned_int(byte& bytes, int byte_count)
{
	unsigned int integer = 0;

	for (int currentByte = 0; currentByte < byte_count; currentByte++)
	{
		for (int currentBit = 0; currentBit < 8; currentBit++)
		{
			integer += (bytes[currentByte].bits[currentBit]) * (std::pow(2, (currentByte * 8 + currentBit)));
		}
	}

	return integer;
}

std::string byte::to_string(byte& bytes, int byte_count)
{
	std::string new_string = "";

	for (int currentByte = byte_count - 1; currentByte >= 0; currentByte--)
	{
		for (int currentBit = 7; currentBit >= 0; currentBit--)
		{
			new_string += std::to_string((static_cast<int>(bytes[currentByte].bits[currentBit])));
		}
	}

	return new_string;
}

std::string byte::to_string_2(byte& bytes, int byte_count)
{
	std::string new_string = "";

	for (int currentByte = byte_count - 1; currentByte >= 0; currentByte--)
	{
		for (int currentBit = 7; currentBit >= 0; currentBit--)
		{
			new_string += std::to_string((static_cast<int>(bytes[currentByte].bits[currentBit])));
		}

		new_string += " ";
	}

	return new_string;
}

byte byte::copy()
{
	byte new_byte(bits);

	return new_byte;
}

std::vector<bool> byte::to_bits()
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

auto byte::get_bit(int index)
{
	return bits[index];
}

int byte::get_bit_int(int index)
{
	return bits[index];
}

byte& byte::set_bit(int index, bool new_value)
{
	bits[index] = new_value;

	return *this;
}

byte& byte::set_bit_int(int index, int new_value)
{
	bits[index] = new_value;

	return *this;
}

auto byte::flip_bit(int index)
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
	byte new_byte(add(*this, byteA).bits);

	equals(new_byte);

	return *this;
}

byte& byte::plus_plus()
{
	byte new_byte(plus_plus(*this).bits);

	equals(new_byte);

	return *this;
}

byte& byte::increment()
{
	byte new_byte(increment(*this).bits);

	equals(new_byte);

	return *this;
}

byte& byte::subtract(byte byteA)
{
	byte new_byte(subtract(*this, byteA).bits);

	equals(new_byte);

	return *this;
}

byte& byte::minus_minus()
{
	byte new_byte(minus_minus(*this).bits);

	equals(new_byte);

	return *this;
}

byte& byte::decrement()
{
	byte new_byte(decrement(*this).bits);

	equals(new_byte);

	return *this;
}

byte& byte::multiply(byte byteA)
{
	byte new_byte(multiply(*this, byteA).bits);

	equals(new_byte);

	return *this;
}

byte& byte::divide(byte byteA)
{
	byte new_byte(divide(*this, byteA).bits);

	equals(new_byte);

	return *this;
}

byte& byte::modulo(byte byteA)
{
	byte new_byte(modulo(*this, byteA).bits);

	equals(new_byte);

	return *this;
}

byte& byte::bit_and(byte byteA)
{
	byte new_byte(bit_and(*this, byteA).bits);

	equals(new_byte);

	return *this;
}

byte& byte::bit_or(byte byteA)
{
	byte new_byte(bit_or(*this, byteA).bits);

	equals(new_byte);

	return *this;
}

byte& byte::bit_xor(byte byteA)
{
	byte new_byte(bit_xor(*this, byteA).bits);

	equals(new_byte);

	return *this;
}

byte& byte::bit_left_shift(int shift)
{
	byte new_byte(bit_left_shift(*this, shift).bits);

	equals(new_byte);

	return *this;
}

byte& byte::bit_right_shift(int shift)
{
	byte new_byte(bit_right_shift(*this, shift).bits);

	equals(new_byte);

	return *this;
}

byte byte::bit_not()
{
	byte new_byte(bits);

	new_byte.bits[0] = !new_byte.bits[0];
	new_byte.bits[1] = !new_byte.bits[1];
	new_byte.bits[2] = !new_byte.bits[2];
	new_byte.bits[3] = !new_byte.bits[3];
	new_byte.bits[4] = !new_byte.bits[4];
	new_byte.bits[5] = !new_byte.bits[5];
	new_byte.bits[6] = !new_byte.bits[6];
	new_byte.bits[7] = !new_byte.bits[7];

	return new_byte;
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

auto byte::operator[](int index)
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
	byte new_byte(bits);

	new_byte.bits[0] = !new_byte.bits[0];
	new_byte.bits[1] = !new_byte.bits[1];
	new_byte.bits[2] = !new_byte.bits[2];
	new_byte.bits[3] = !new_byte.bits[3];
	new_byte.bits[4] = !new_byte.bits[4];
	new_byte.bits[5] = !new_byte.bits[5];
	new_byte.bits[6] = !new_byte.bits[6];
	new_byte.bits[7] = !new_byte.bits[7];

	return new_byte;
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
