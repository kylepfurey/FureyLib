
// Enumeration Examples Script
// by Kyle Furey

#pragma once

// Template enum. Each exclusive value of this enum represents a unique option.
enum Enum
{
	// No Option
	None = 0,

	// Option 1
	Option1 = 1,

	// Option 2
	Option2 = 2,

	// Option 3
	Option3 = 3,
};

// �  Template bit flags enum. Each bit in this enum represents a flag that can be stored along with other flags.
// �  Use "enum = flag1 | flag2" to set multiple flags to this enum.
// �  Use "enum &= ~flag1" to remove a flag from this enum.
// �  Use "enum & flag1 != 0" to check if an enum has the given flag.
enum Flags
{
	// Empty Flag - 00000000
	Empty = 0,

	// Flag 1 - 00000001
	Flag1 = 1,

	// Flag 2 - 00000010
	Flag2 = 2,

	// Flag 3 - 00000100
	Flag3 = 4,

	// Flag 4 - 00001000
	Flag4 = 8,

	// Flag 5 - 00010000
	Flag5 = 16,

	// Flag 6 - 00100000
	Flag6 = 32,

	// Flag 7 - 01000000
	Flag7 = 64,

	// Flag 8 - 10000000
	Flag8 = 128
};

// Boolean enum. Represents a condition that can be enabled or disabled. Supports a NULL value.
enum Bool
{
	// Value is not set.
	False = 0,

	// Value is set.
	True = 1,

	// Value is considered null.
	Null = 255
};

// Bit enum. Represents a single bit with two possible values.
enum Bit
{
	// Bit is off.
	Off = 0,

	// Bit is on.
	On = 1
};

// Byte enum. Represents a single unsigned byte value ranging from 0 - 255.
enum Byte
{
	Zero = 0,
	One = 1,
	Two = 2,
	Three = 3,
	Four = 4,
	Five = 5,
	Six = 6,
	Seven = 7,
	Eight = 8,
	Nine = 9,
	Ten = 10,
	Eleven = 11,
	Twelve = 12,
	Thirteen = 13,
	Fourteen = 14,
	Fifteen = 15,
	Sixteen = 16,
	Seventeen = 17,
	Eighteen = 18,
	Nineteen = 19,
	Twenty = 20,
	TwentyOne = 21,
	TwentyTwo = 22,
	TwentyThree = 23,
	TwentyFour = 24,
	TwentyFive = 25,
	TwentySix = 26,
	TwentySeven = 27,
	TwentyEight = 28,
	TwentyNine = 29,
	Thirty = 30,
	ThirtyOne = 31,
	ThirtyTwo = 32,
	ThirtyThree = 33,
	ThirtyFour = 34,
	ThirtyFive = 35,
	ThirtySix = 36,
	ThirtySeven = 37,
	ThirtyEight = 38,
	ThirtyNine = 39,
	Forty = 40,
	FortyOne = 41,
	FortyTwo = 42,
	FortyThree = 43,
	FortyFour = 44,
	FortyFive = 45,
	FortySix = 46,
	FortySeven = 47,
	FortyEight = 48,
	FortyNine = 49,
	Fifty = 50,
	FiftyOne = 51,
	FiftyTwo = 52,
	FiftyThree = 53,
	FiftyFour = 54,
	FiftyFive = 55,
	FiftySix = 56,
	FiftySeven = 57,
	FiftyEight = 58,
	FiftyNine = 59,
	Sixty = 60,
	SixtyOne = 61,
	SixtyTwo = 62,
	SixtyThree = 63,
	SixtyFour = 64,
	SixtyFive = 65,
	SixtySix = 66,
	SixtySeven = 67,
	SixtyEight = 68,
	SixtyNine = 69,
	Seventy = 70,
	SeventyOne = 71,
	SeventyTwo = 72,
	SeventyThree = 73,
	SeventyFour = 74,
	SeventyFive = 75,
	SeventySix = 76,
	SeventySeven = 77,
	SeventyEight = 78,
	SeventyNine = 79,
	Eighty = 80,
	EightyOne = 81,
	EightyTwo = 82,
	EightyThree = 83,
	EightyFour = 84,
	EightyFive = 85,
	EightySix = 86,
	EightySeven = 87,
	EightyEight = 88,
	EightyNine = 89,
	Ninety = 90,
	NinetyOne = 91,
	NinetyTwo = 92,
	NinetyThree = 93,
	NinetyFour = 94,
	NinetyFive = 95,
	NinetySix = 96,
	NinetySeven = 97,
	NinetyEight = 98,
	NinetyNine = 99,
	OneHundred = 100,
	OneHundredOne = 101,
	OneHundredTwo = 102,
	OneHundredThree = 103,
	OneHundredFour = 104,
	OneHundredFive = 105,
	OneHundredSix = 106,
	OneHundredSeven = 107,
	OneHundredEight = 108,
	OneHundredNine = 109,
	OneHundredTen = 110,
	OneHundredEleven = 111,
	OneHundredTwelve = 112,
	OneHundredThirteen = 113,
	OneHundredFourteen = 114,
	OneHundredFifteen = 115,
	OneHundredSixteen = 116,
	OneHundredSeventeen = 117,
	OneHundredEighteen = 118,
	OneHundredNineteen = 119,
	OneHundredTwenty = 120,
	OneHundredTwentyOne = 121,
	OneHundredTwentyTwo = 122,
	OneHundredTwentyThree = 123,
	OneHundredTwentyFour = 124,
	OneHundredTwentyFive = 125,
	OneHundredTwentySix = 126,
	OneHundredTwentySeven = 127,
	OneHundredTwentyEight = 128,
	OneHundredTwentyNine = 129,
	OneHundredThirty = 130,
	OneHundredThirtyOne = 131,
	OneHundredThirtyTwo = 132,
	OneHundredThirtyThree = 133,
	OneHundredThirtyFour = 134,
	OneHundredThirtyFive = 135,
	OneHundredThirtySix = 136,
	OneHundredThirtySeven = 137,
	OneHundredThirtyEight = 138,
	OneHundredThirtyNine = 139,
	OneHundredForty = 140,
	OneHundredFortyOne = 141,
	OneHundredFortyTwo = 142,
	OneHundredFortyThree = 143,
	OneHundredFortyFour = 144,
	OneHundredFortyFive = 145,
	OneHundredFortySix = 146,
	OneHundredFortySeven = 147,
	OneHundredFortyEight = 148,
	OneHundredFortyNine = 149,
	OneHundredFifty = 150,
	OneHundredFiftyOne = 151,
	OneHundredFiftyTwo = 152,
	OneHundredFiftyThree = 153,
	OneHundredFiftyFour = 154,
	OneHundredFiftyFive = 155,
	OneHundredFiftySix = 156,
	OneHundredFiftySeven = 157,
	OneHundredFiftyEight = 158,
	OneHundredFiftyNine = 159,
	OneHundredSixty = 160,
	OneHundredSixtyOne = 161,
	OneHundredSixtyTwo = 162,
	OneHundredSixtyThree = 163,
	OneHundredSixtyFour = 164,
	OneHundredSixtyFive = 165,
	OneHundredSixtySix = 166,
	OneHundredSixtySeven = 167,
	OneHundredSixtyEight = 168,
	OneHundredSixtyNine = 169,
	OneHundredSeventy = 170,
	OneHundredSeventyOne = 171,
	OneHundredSeventyTwo = 172,
	OneHundredSeventyThree = 173,
	OneHundredSeventyFour = 174,
	OneHundredSeventyFive = 175,
	OneHundredSeventySix = 176,
	OneHundredSeventySeven = 177,
	OneHundredSeventyEight = 178,
	OneHundredSeventyNine = 179,
	OneHundredEighty = 180,
	OneHundredEightyOne = 181,
	OneHundredEightyTwo = 182,
	OneHundredEightyThree = 183,
	OneHundredEightyFour = 184,
	OneHundredEightyFive = 185,
	OneHundredEightySix = 186,
	OneHundredEightySeven = 187,
	OneHundredEightyEight = 188,
	OneHundredEightyNine = 189,
	OneHundredNinety = 190,
	OneHundredNinetyOne = 191,
	OneHundredNinetyTwo = 192,
	OneHundredNinetyThree = 193,
	OneHundredNinetyFour = 194,
	OneHundredNinetyFive = 195,
	OneHundredNinetySix = 196,
	OneHundredNinetySeven = 197,
	OneHundredNinetyEight = 198,
	OneHundredNinetyNine = 199,
	TwoHundred = 200,
	TwoHundredOne = 201,
	TwoHundredTwo = 202,
	TwoHundredThree = 203,
	TwoHundredFour = 204,
	TwoHundredFive = 205,
	TwoHundredSix = 206,
	TwoHundredSeven = 207,
	TwoHundredEight = 208,
	TwoHundredNine = 209,
	TwoHundredTen = 210,
	TwoHundredEleven = 211,
	TwoHundredTwelve = 212,
	TwoHundredThirteen = 213,
	TwoHundredFourteen = 214,
	TwoHundredFifteen = 215,
	TwoHundredSixteen = 216,
	TwoHundredSeventeen = 217,
	TwoHundredEighteen = 218,
	TwoHundredNineteen = 219,
	TwoHundredTwenty = 220,
	TwoHundredTwentyOne = 221,
	TwoHundredTwentyTwo = 222,
	TwoHundredTwentyThree = 223,
	TwoHundredTwentyFour = 224,
	TwoHundredTwentyFive = 225,
	TwoHundredTwentySix = 226,
	TwoHundredTwentySeven = 227,
	TwoHundredTwentyEight = 228,
	TwoHundredTwentyNine = 229,
	TwoHundredThirty = 230,
	TwoHundredThirtyOne = 231,
	TwoHundredThirtyTwo = 232,
	TwoHundredThirtyThree = 233,
	TwoHundredThirtyFour = 234,
	TwoHundredThirtyFive = 235,
	TwoHundredThirtySix = 236,
	TwoHundredThirtySeven = 237,
	TwoHundredThirtyEight = 238,
	TwoHundredThirtyNine = 239,
	TwoHundredForty = 240,
	TwoHundredFortyOne = 241,
	TwoHundredFortyTwo = 242,
	TwoHundredFortyThree = 243,
	TwoHundredFortyFour = 244,
	TwoHundredFortyFive = 245,
	TwoHundredFortySix = 246,
	TwoHundredFortySeven = 247,
	TwoHundredFortyEight = 248,
	TwoHundredFortyNine = 249,
	TwoHundredFifty = 250,
	TwoHundredFiftyOne = 251,
	TwoHundredFiftyTwo = 252,
	TwoHundredFiftyThree = 253,
	TwoHundredFiftyFour = 254,
	TwoHundredFiftyFive = 255
};

// Signed byte enum. Represents a single signed byte value ranging from -128 - 127.
enum SignedByte
{
	NegativeOneHundredTwentyEight = -128,
	NegativeOneHundredTwentySeven = -127,
	NegativeOneHundredTwentySix = -126,
	NegativeOneHundredTwentyFive = -125,
	NegativeOneHundredTwentyFour = -124,
	NegativeOneHundredTwentyThree = -123,
	NegativeOneHundredTwentyTwo = -122,
	NegativeOneHundredTwentyOne = -121,
	NegativeOneHundredTwenty = -120,
	NegativeOneHundredNineteen = -119,
	NegativeOneHundredEighteen = -118,
	NegativeOneHundredSeventeen = -117,
	NegativeOneHundredSixteen = -116,
	NegativeOneHundredFifteen = -115,
	NegativeOneHundredFourteen = -114,
	NegativeOneHundredThirteen = -113,
	NegativeOneHundredTwelve = -112,
	NegativeOneHundredEleven = -111,
	NegativeOneHundredTen = -110,
	NegativeOneHundredNine = -109,
	NegativeOneHundredEight = -108,
	NegativeOneHundredSeven = -107,
	NegativeOneHundredSix = -106,
	NegativeOneHundredFive = -105,
	NegativeOneHundredFour = -104,
	NegativeOneHundredThree = -103,
	NegativeOneHundredTwo = -102,
	NegativeOneHundredOne = -101,
	NegativeOneHundred = -100,
	NegativeNinetyNine = -99,
	NegativeNinetyEight = -98,
	NegativeNinetySeven = -97,
	NegativeNinetySix = -96,
	NegativeNinetyFive = -95,
	NegativeNinetyFour = -94,
	NegativeNinetyThree = -93,
	NegativeNinetyTwo = -92,
	NegativeNinetyOne = -91,
	NegativeNinety = -90,
	NegativeEightyNine = -89,
	NegativeEightyEight = -88,
	NegativeEightySeven = -87,
	NegativeEightySix = -86,
	NegativeEightyFive = -85,
	NegativeEightyFour = -84,
	NegativeEightyThree = -83,
	NegativeEightyTwo = -82,
	NegativeEightyOne = -81,
	NegativeEighty = -80,
	NegativeSeventyNine = -79,
	NegativeSeventyEight = -78,
	NegativeSeventySeven = -77,
	NegativeSeventySix = -76,
	NegativeSeventyFive = -75,
	NegativeSeventyFour = -74,
	NegativeSeventyThree = -73,
	NegativeSeventyTwo = -72,
	NegativeSeventyOne = -71,
	NegativeSeventy = -70,
	NegativeSixtyNine = -69,
	NegativeSixtyEight = -68,
	NegativeSixtySeven = -67,
	NegativeSixtySix = -66,
	NegativeSixtyFive = -65,
	NegativeSixtyFour = -64,
	NegativeSixtyThree = -63,
	NegativeSixtyTwo = -62,
	NegativeSixtyOne = -61,
	NegativeSixty = -60,
	NegativeFiftyNine = -59,
	NegativeFiftyEight = -58,
	NegativeFiftySeven = -57,
	NegativeFiftySix = -56,
	NegativeFiftyFive = -55,
	NegativeFiftyFour = -54,
	NegativeFiftyThree = -53,
	NegativeFiftyTwo = -52,
	NegativeFiftyOne = -51,
	NegativeFifty = -50,
	NegativeFortyNine = -49,
	NegativeFortyEight = -48,
	NegativeFortySeven = -47,
	NegativeFortySix = -46,
	NegativeFortyFive = -45,
	NegativeFortyFour = -44,
	NegativeFortyThree = -43,
	NegativeFortyTwo = -42,
	NegativeFortyOne = -41,
	NegativeForty = -40,
	NegativeThirtyNine = -39,
	NegativeThirtyEight = -38,
	NegativeThirtySeven = -37,
	NegativeThirtySix = -36,
	NegativeThirtyFive = -35,
	NegativeThirtyFour = -34,
	NegativeThirtyThree = -33,
	NegativeThirtyTwo = -32,
	NegativeThirtyOne = -31,
	NegativeThirty = -30,
	NegativeTwentyNine = -29,
	NegativeTwentyEight = -28,
	NegativeTwentySeven = -27,
	NegativeTwentySix = -26,
	NegativeTwentyFive = -25,
	NegativeTwentyFour = -24,
	NegativeTwentyThree = -23,
	NegativeTwentyTwo = -22,
	NegativeTwentyOne = -21,
	NegativeTwenty = -20,
	NegativeNineteen = -19,
	NegativeEighteen = -18,
	NegativeSeventeen = -17,
	NegativeSixteen = -16,
	NegativeFifteen = -15,
	NegativeFourteen = -14,
	NegativeThirteen = -13,
	NegativeTwelve = -12,
	NegativeEleven = -11,
	NegativeTen = -10,
	NegativeNine = -9,
	NegativeEight = -8,
	NegativeSeven = -7,
	NegativeSix = -6,
	NegativeFive = -5,
	NegativeFour = -4,
	NegativeThree = -3,
	NegativeTwo = -2,
	NegativeOne = -1,
	PositiveZero = 0,
	PositiveOne = 1,
	PositiveTwo = 2,
	PositiveThree = 3,
	PositiveFour = 4,
	PositiveFive = 5,
	PositiveSix = 6,
	PositiveSeven = 7,
	PositiveEight = 8,
	PositiveNine = 9,
	PositiveTen = 10,
	PositiveEleven = 11,
	PositiveTwelve = 12,
	PositiveThirteen = 13,
	PositiveFourteen = 14,
	PositiveFifteen = 15,
	PositiveSixteen = 16,
	PositiveSeventeen = 17,
	PositiveEighteen = 18,
	PositiveNineteen = 19,
	PositiveTwenty = 20,
	PositiveTwentyOne = 21,
	PositiveTwentyTwo = 22,
	PositiveTwentyThree = 23,
	PositiveTwentyFour = 24,
	PositiveTwentyFive = 25,
	PositiveTwentySix = 26,
	PositiveTwentySeven = 27,
	PositiveTwentyEight = 28,
	PositiveTwentyNine = 29,
	PositiveThirty = 30,
	PositiveThirtyOne = 31,
	PositiveThirtyTwo = 32,
	PositiveThirtyThree = 33,
	PositiveThirtyFour = 34,
	PositiveThirtyFive = 35,
	PositiveThirtySix = 36,
	PositiveThirtySeven = 37,
	PositiveThirtyEight = 38,
	PositiveThirtyNine = 39,
	PositiveForty = 40,
	PositiveFortyOne = 41,
	PositiveFortyTwo = 42,
	PositiveFortyThree = 43,
	PositiveFortyFour = 44,
	PositiveFortyFive = 45,
	PositiveFortySix = 46,
	PositiveFortySeven = 47,
	PositiveFortyEight = 48,
	PositiveFortyNine = 49,
	PositiveFifty = 50,
	PositiveFiftyOne = 51,
	PositiveFiftyTwo = 52,
	PositiveFiftyThree = 53,
	PositiveFiftyFour = 54,
	PositiveFiftyFive = 55,
	PositiveFiftySix = 56,
	PositiveFiftySeven = 57,
	PositiveFiftyEight = 58,
	PositiveFiftyNine = 59,
	PositiveSixty = 60,
	PositiveSixtyOne = 61,
	PositiveSixtyTwo = 62,
	PositiveSixtyThree = 63,
	PositiveSixtyFour = 64,
	PositiveSixtyFive = 65,
	PositiveSixtySix = 66,
	PositiveSixtySeven = 67,
	PositiveSixtyEight = 68,
	PositiveSixtyNine = 69,
	PositiveSeventy = 70,
	PositiveSeventyOne = 71,
	PositiveSeventyTwo = 72,
	PositiveSeventyThree = 73,
	PositiveSeventyFour = 74,
	PositiveSeventyFive = 75,
	PositiveSeventySix = 76,
	PositiveSeventySeven = 77,
	PositiveSeventyEight = 78,
	PositiveSeventyNine = 79,
	PositiveEighty = 80,
	PositiveEightyOne = 81,
	PositiveEightyTwo = 82,
	PositiveEightyThree = 83,
	PositiveEightyFour = 84,
	PositiveEightyFive = 85,
	PositiveEightySix = 86,
	PositiveEightySeven = 87,
	PositiveEightyEight = 88,
	PositiveEightyNine = 89,
	PositiveNinety = 90,
	PositiveNinetyOne = 91,
	PositiveNinetyTwo = 92,
	PositiveNinetyThree = 93,
	PositiveNinetyFour = 94,
	PositiveNinetyFive = 95,
	PositiveNinetySix = 96,
	PositiveNinetySeven = 97,
	PositiveNinetyEight = 98,
	PositiveNinetyNine = 99,
	PositiveOneHundred = 100,
	PositiveOneHundredOne = 101,
	PositiveOneHundredTwo = 102,
	PositiveOneHundredThree = 103,
	PositiveOneHundredFour = 104,
	PositiveOneHundredFive = 105,
	PositiveOneHundredSix = 106,
	PositiveOneHundredSeven = 107,
	PositiveOneHundredEight = 108,
	PositiveOneHundredNine = 109,
	PositiveOneHundredTen = 110,
	PositiveOneHundredEleven = 111,
	PositiveOneHundredTwelve = 112,
	PositiveOneHundredThirteen = 113,
	PositiveOneHundredFourteen = 114,
	PositiveOneHundredFifteen = 115,
	PositiveOneHundredSixteen = 116,
	PositiveOneHundredSeventeen = 117,
	PositiveOneHundredEighteen = 118,
	PositiveOneHundredNineteen = 119,
	PositiveOneHundredTwenty = 120,
	PositiveOneHundredTwentyOne = 121,
	PositiveOneHundredTwentyTwo = 122,
	PositiveOneHundredTwentyThree = 123,
	PositiveOneHundredTwentyFour = 124,
	PositiveOneHundredTwentyFive = 125,
	PositiveOneHundredTwentySix = 126,
	PositiveOneHundredTwentySeven = 127
};