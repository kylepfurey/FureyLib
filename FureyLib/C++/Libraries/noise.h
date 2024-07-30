
// Static Noise Functions Script
// by Kyle Furey, Sourced from Adrian Biagioli and Riven

// REQUIRMENT: array_3D.h
// SOURCE: https://adrianb.io/2014/08/09/perlinnoise.html

#pragma once
#include <vector>
#include <random>
#include <cstdlib>
#include <cmath>
#include "array_3D.h"

// Include this heading to use the library.
#include "noise.h"

// The precision value of the noise value's alpha.
#define PRECISION double

// •  Generates a sample of Perlin Noise.
// •  SOURCE: https://adrianb.io/2014/08/09/perlinnoise.html by Adrian Biagioli.
class perlin
{
private:

	// PERMUTATION TABLE

	// Ken Perlin's permutation table.
	static unsigned char permutation[512];


	// PERLIN FUNCTIONS

	// Ken Perlin's fading function.
	static PRECISION fade(PRECISION value)
	{
		return value * value * value * (value * (value * 6 - 15) + 10);
	}

	// Increments the given index based on the set tiling value.
	static int increment(int index)
	{
		index++;

		if (tiling > 0)
		{
			index %= tiling;
		}

		return index;
	}

	// •  Riven's fast random gradient function.
	// •  SOURCE: http://riven8192.blogspot.com/2010/08/calculate-perlinnoise-twice-as-fast.html by Riven.
	static PRECISION gradient(int hash, PRECISION x, PRECISION y, PRECISION z)
	{
		switch (hash & 0xF)
		{
			case 0x0: return x + y;
			case 0x1: return -x + y;
			case 0x2: return x - y;
			case 0x3: return -x - y;
			case 0x4: return x + z;
			case 0x5: return -x + z;
			case 0x6: return x - z;
			case 0x7: return -x - z;
			case 0x8: return y + z;
			case 0x9: return -y + z;
			case 0xA: return y - z;
			case 0xB: return -y - z;
			case 0xC: return y + x;
			case 0xD: return -y + z;
			case 0xE: return y - x;
			case 0xF: return -y - z;
		}

		return 0;
	}


	// LINEAR INTERPOLATION

	// Linearly interpolates from the start to the end values at the given alpha.
	static PRECISION lerp(PRECISION start, PRECISION end, PRECISION alpha)
	{
		return start + alpha * (end - start);
	}

public:

	// TILING

	// The default value to tile the noise at.
	static int tiling;


	// PERMUTATION TABLE

	// Accesses a value in the permutation table.
	static unsigned char permutation_table(int index)
	{
		return permutation[index % 512];
	}


	// PERLIN NOISE

	// Samples a noise value at the given coordinates using Ken Perlin's Noise Algorithm.
	static PRECISION noise(PRECISION x, PRECISION y, PRECISION z)
	{
		return noise(x, y, z, tiling);
	}

	// Samples a noise value at the given coordinates using Ken Perlin's Noise Algorithm.
	static PRECISION noise(PRECISION x, PRECISION y, PRECISION z, int tiling)
	{
		if (tiling > 0)
		{
			x = x - (int)(x / tiling) * tiling;
			y = y - (int)(y / tiling) * tiling;
			z = z - (int)(z / tiling) * tiling;
		}

		int xi = (int)x & 255;
		int yi = (int)y & 255;
		int zi = (int)z & 255;

		PRECISION xf = x - (int)x;
		PRECISION yf = y - (int)y;
		PRECISION zf = z - (int)z;

		PRECISION u = fade(xf);
		PRECISION v = fade(yf);
		PRECISION w = fade(zf);

		int aaa, aba, aab, abb, baa, bba, bab, bbb;
		aaa = permutation[permutation[permutation[xi] + yi] + zi];
		aba = permutation[permutation[permutation[xi] + increment(yi)] + zi];
		aab = permutation[permutation[permutation[xi] + yi] + increment(zi)];
		abb = permutation[permutation[permutation[xi] + increment(yi)] + increment(zi)];
		baa = permutation[permutation[permutation[increment(xi)] + yi] + zi];
		bba = permutation[permutation[permutation[increment(xi)] + increment(yi)] + zi];
		bab = permutation[permutation[permutation[increment(xi)] + yi] + increment(zi)];
		bbb = permutation[permutation[permutation[increment(xi)] + increment(yi)] + increment(zi)];

		PRECISION x1, x2, y1, y2;
		x1 = lerp(gradient(aaa, xf, yf, zf), gradient(baa, xf - 1, yf, zf), u);
		x2 = lerp(gradient(aba, xf, yf - 1, zf), gradient(bba, xf - 1, yf - 1, zf), u);
		y1 = lerp(x1, x2, v);
		x1 = lerp(gradient(aab, xf, yf, zf - 1), gradient(bab, xf - 1, yf, zf - 1), u);
		x2 = lerp(gradient(abb, xf, yf - 1, zf - 1), gradient(bbb, xf - 1, yf - 1, zf - 1), u);
		y2 = lerp(x1, x2, v);

		return (lerp(y1, y2, w) + 1) / 2;
	}

	// •  Samples a noise value at the given coordinates using Ken Perlin's Noise Algorithm.
	// •  Features control over octaves and persistence values for a more natural noise.
	static PRECISION noise(PRECISION x, PRECISION y, PRECISION z, int octaves, PRECISION persistence)
	{
		return noise(x, y, z, octaves, persistence, tiling);
	}

	// •  Samples a noise value at the given coordinates using Ken Perlin's Noise Algorithm.
	// •  Features control over octaves and persistence values for a more natural noise.
	static PRECISION noise(PRECISION x, PRECISION y, PRECISION z, int octaves, PRECISION persistence, int tiling)
	{
		PRECISION total = 0;
		PRECISION frequency = 1;
		PRECISION amplitude = 1;
		PRECISION max_value = 0;

		for (int i = 0; i < octaves; i++)
		{
			total += noise(x * frequency, y * frequency, z * frequency) * amplitude;

			max_value += amplitude;

			amplitude *= persistence;

			frequency *= 2;
		}

		return total / max_value;
	}
};

// Generates noise values using different types of algorithms.
class noise
{
private:

	// RANDOM SEED

	// The seed used to calculate random noise values. The seed is random by default.
	static int seed;


	// LINEAR INTERPOLATION

	// Linearly interpolates from the start to the end values at the given alpha.
	static PRECISION lerp(PRECISION start, PRECISION end, PRECISION alpha)
	{
		return start + alpha * (end - start);
	}

public:

	// RANDOM SEED

	// •  Gets the current noise seed.
	// •  Use set_seed() to change the noise seed.
	// •  Note: If std::srand() is called, the noise seed will not match the current random seed.
	static int get_seed()
	{
		return seed;
	}

	// •  Sets the current noise seed.
	// •  Use get_seed() to get the current noise seed.
	// •  Note: If std::srand() is called, the noise seed will not match the current random seed.
	static int set_seed(int new_seed)
	{
		std::srand(new_seed);

		seed = new_seed;

		return seed;
	}


	// RANDOM VALUES

	// Returns a random integer.
	static int random()
	{
		return std::rand();
	}

	// Returns a random integer of the given range (exclusive).
	static int random(int max)
	{
		return random() % max;
	}

	// Returns a random integer of the given range (inclusive).
	static int random(int min, int max)
	{
		return (int)std::round(((double)std::rand() / (double)RAND_MAX) * (max - min) + min);
	}

	// Returns a random double between 0 and 1.
	static PRECISION random_alpha()
	{
		return (PRECISION)((double)std::rand() / (double)RAND_MAX);
	}


	// DISCRETE NOISE

	// Returns a vector of random alpha values (0 - 1) of the given size.
	static std::vector<PRECISION> discrete_1D(int size)
	{
		std::vector<PRECISION> result = std::vector<PRECISION>(size);

		for (int x = 0; x < size; x++)
		{
			result[x] = random_alpha();
		}

		return result;
	}

	// Returns a vector of random integers of the given size and range (exclusive).
	static std::vector<int> discrete_1D(int size, int max)
	{
		std::vector<int> result = std::vector<int>(size);

		for (int x = 0; x < size; x++)
		{
			result[x] = random(max);
		}

		return result;
	}

	// Returns a vector of random integers of the given size and range (inclusive).
	static std::vector<int> discrete_1D(int size, int min, int max)
	{
		std::vector<int> result = std::vector<int>(size);

		for (int x = 0; x < size; x++)
		{
			result[x] = random(min, max);
		}

		return result;
	}

	// Returns a 2D vector of random alpha values (0 - 1) of the given size.
	static array_2D<PRECISION> discrete_2D(int size, int width)
	{
		array_2D<PRECISION> result = array_2D<PRECISION>(size, width);

		for (int y = 0; y < width; y++)
		{
			for (int x = 0; x < size; x++)
			{
				result[{x, y}] = random_alpha();
			}
		}

		return result;
	}

	// Returns a 2D vector of random integers of the given size and range (exclusive).
	static array_2D<int> discrete_2D(int size, int width, int max)
	{
		array_2D<int> result = array_2D<int>(size, width);

		for (int y = 0; y < width; y++)
		{
			for (int x = 0; x < size; x++)
			{
				result[{x, y}] = random(max);
			}
		}

		return result;
	}

	// Returns a 2D vector of random integers of the given size and range (inclusive).
	static array_2D<int> discrete_2D(int size, int width, int min, int max)
	{
		array_2D<int> result = array_2D<int>(size, width);

		for (int y = 0; y < width; y++)
		{
			for (int x = 0; x < size; x++)
			{
				result[{x, y}] = random(min, max);
			}
		}

		return result;
	}

	// Returns a 3D vector of random alpha values (0 - 1) of the given size.
	static array_3D<PRECISION> discrete_3D(int size, int width, int height)
	{
		array_3D<PRECISION> result = array_3D<PRECISION>(size, width, height);

		for (int z = 0; z < height; z++)
		{
			for (int y = 0; y < width; y++)
			{
				for (int x = 0; x < size; x++)
				{
					result[{x, y, z}] = random_alpha();
				}
			}
		}

		return result;
	}

	// Returns a 3D vector of random integers of the given size and range (exclusive).
	static array_3D<int> discrete_3D(int size, int width, int height, int max)
	{
		array_3D<int> result = array_3D<int>(size, width, height);

		for (int z = 0; z < height; z++)
		{
			for (int y = 0; y < width; y++)
			{
				for (int x = 0; x < size; x++)
				{
					result[{x, y, z}] = random(max);
				}
			}
		}

		return result;
	}

	// Returns a 3D vector of random integers of the given size and range (inclusive).
	static array_3D<int> discrete_3D(int size, int width, int height, int min, int max)
	{
		array_3D<int> result = array_3D<int>(size, width, height);

		for (int z = 0; z < height; z++)
		{
			for (int y = 0; y < width; y++)
			{
				for (int x = 0; x < size; x++)
				{
					result[{x, y, z}] = random(min, max);
				}
			}
		}

		return result;
	}


	// PERLIN NOISE

	// Returns a vector of alpha values (0 - 1) generated from the Perlin Noise Algorithm of the given size.
	static std::vector<PRECISION> perlin_1D(int size, PRECISION magnitude = 10, int tiling = 0, PRECISION y = 0, PRECISION z = 0)
	{
		std::vector<PRECISION> result = std::vector<PRECISION>(size);

		for (int x = 0; x < size; x++)
		{
			result[x] = perlin::noise(x / magnitude, y, z, tiling);
		}

		return result;
	}

	// •  Returns a vector of alpha values (0 - 1) generated from the Perlin Noise Algorithm of the given size.
	// •  Features control over octaves and persistence values for a more natural noise.
	static std::vector<PRECISION> perlin_1D(int size, PRECISION magnitude, int octaves, PRECISION persistence, int tiling = 0, PRECISION y = 0, PRECISION z = 0)
	{
		std::vector<PRECISION> result = std::vector<PRECISION>(size);

		for (int x = 0; x < size; x++)
		{
			result[x] = perlin::noise(x / magnitude, y, z, octaves, persistence, tiling);
		}

		return result;
	}

	// Returns a 2D vector of alpha values (0 - 1) generated from the Perlin Noise Algorithm of the given size.
	static array_2D<PRECISION> perlin_2D(int size, int width, PRECISION magnitude = 10, int tiling = 0, PRECISION z = 0)
	{
		array_2D<PRECISION> result = array_2D<PRECISION>(size, width);

		for (int y = 0; y < width; y++)
		{
			for (int x = 0; x < size; x++)
			{
				result[{x, y}] = perlin::noise(x / magnitude, y / magnitude, z, tiling);
			}
		}

		return result;
	}

	// •  Returns a 2D vector of alpha values (0 - 1) generated from the Perlin Noise Algorithm of the given size.
	// •  Features control over octaves and persistence values for a more natural noise.
	static array_2D<PRECISION> perlin_2D(int size, int width, PRECISION magnitude, int octaves, PRECISION persistence, int tiling = 0, PRECISION z = 0)
	{
		array_2D<PRECISION> result = array_2D<PRECISION>(size, width);

		for (int y = 0; y < width; y++)
		{
			for (int x = 0; x < size; x++)
			{
				result[{x, y}] = perlin::noise(x / magnitude, y / magnitude, z, octaves, persistence, tiling);
			}
		}

		return result;
	}

	// Returns a 3D vector of alpha values (0 - 1) generated from the Perlin Noise Algorithm of the given size.
	static array_3D<PRECISION> perlin_3D(int size, int width, int height, PRECISION magnitude = 10, int tiling = 0)
	{
		array_3D<PRECISION> result = array_3D<PRECISION>(size, width, height);

		for (int z = 0; z < height; z++)
		{
			for (int y = 0; y < width; y++)
			{
				for (int x = 0; x < size; x++)
				{
					result[{x, y, z}] = perlin::noise(x / magnitude, y / magnitude, z / magnitude, tiling);
				}
			}
		}

		return result;
	}

	// •  Returns a 3D vector of alpha values (0 - 1) generated from the Perlin Noise Algorithm of the given size.
	// •  Features control over octaves and persistence values for a more natural noise.
	static array_3D<PRECISION> perlin_3D(int size, int width, int height, PRECISION magnitude, int octaves, PRECISION persistence, int tiling = 0)
	{
		array_3D<PRECISION> result = array_3D<PRECISION>(size, width, height);

		for (int z = 0; z < height; z++)
		{
			for (int y = 0; y < width; y++)
			{
				for (int x = 0; x < size; x++)
				{
					result[{x, y, z}] = perlin::noise(x / magnitude, y / magnitude, z / magnitude, octaves, persistence, tiling);
				}
			}
		}

		return result;
	}


	// BLURRING

	// Blurs the given noise vector together based on the given alpha value.
	static std::vector<PRECISION> blur(std::vector<PRECISION> vector, PRECISION alpha)
	{
		std::vector<PRECISION> copied_vector = std::vector<PRECISION>(vector.size());

		for (int x = 0; x < vector.size(); x++)
		{
			PRECISION average = vector[x];

			int denominator = 1;

			// LEFT
			if (x - 1 >= 0)
			{
				denominator++;

				average += vector[x - 1];
			}

			// RIGHT
			if (x + 1 < vector.size())
			{
				denominator++;

				average += vector[x + 1];
			}

			average /= denominator;

			copied_vector[x] = lerp(vector[x], average, alpha);
		}

		return copied_vector;
	}

	// Blurs the given noise vector together based on the given alpha value.
	static array_2D<PRECISION> blur(array_2D<PRECISION> vector, PRECISION alpha)
	{
		int size_x = vector.size_x();

		int size_y = vector.size_y();

		array_2D<PRECISION> copied_vector = array_2D<PRECISION>(size_x, size_y);

		for (int y = 0; y < size_y; y++)
		{
			for (int x = 0; x < size_x; x++)
			{
				PRECISION average = vector[{x, y}];

				int denominator = 1;

				// LEFT
				if (x - 1 >= 0)
				{
					denominator++;

					average += vector[{x - 1, y}];
				}

				// RIGHT
				if (x + 1 < size_x)
				{
					denominator++;

					average += vector[{x + 1, y}];
				}

				// DOWN
				if (y - 1 >= 0)
				{
					denominator++;

					average += vector[{x, y - 1}];
				}

				// UP
				if (y + 1 < size_y)
				{
					denominator++;

					average += vector[{x, y + 1}];
				}

				// LEFT DOWN
				if (x - 1 >= 0 && y - 1 >= 0)
				{
					denominator++;

					average += vector[{x - 1, y - 1}];
				}

				// RIGHT DOWN
				if (x + 1 < size_x && y - 1 >= 0)
				{
					denominator++;

					average += vector[{x + 1, y - 1}];
				}

				// RIGHT UP
				if (x + 1 < size_x && y + 1 < size_y)
				{
					denominator++;

					average += vector[{x + 1, y + 1}];
				}

				// LEFT UP
				if (x - 1 >= 0 && y + 1 < size_y)
				{
					denominator++;

					average += vector[{x - 1, y + 1}];
				}

				average /= denominator;

				copied_vector[{x, y}] = lerp(vector[{x, y}], average, alpha);
			}
		}

		return copied_vector;
	}

	// Blurs the given noise vector together based on the given alpha value.
	static array_3D<PRECISION> blur(array_3D<PRECISION> vector, PRECISION alpha)
	{
		int size_x = vector.size_x();

		int size_y = vector.size_y();

		int size_z = vector.size_z();

		array_3D<PRECISION> copied_vector = array_3D<PRECISION>(size_x, size_y, size_z);

		for (int z = 0; z < size_z; z++)
		{
			for (int y = 0; y < size_y; y++)
			{
				for (int x = 0; x < size_x; x++)
				{
					PRECISION average = 0;

					int denominator = 0;

					for (int z_offset = -1; z_offset < 2; z_offset++)
					{
						for (int y_offset = -1; y_offset < 2; y_offset++)
						{
							for (int x_offset = -1; x_offset < 2; x_offset++)
							{
								if (x + x_offset >= 0 && x + x_offset < size_x && y + y_offset >= 0 && y + y_offset < size_y && z + z_offset >= 0 && z + z_offset < size_z)
								{
									denominator++;

									average += vector[{x + x_offset, y + y_offset, z + z_offset}];
								}
							}
						}
					}

					average /= denominator;

					copied_vector[{x, y, z}] = lerp(vector[{x, y, z}], average, alpha);
				}
			}
		}

		return copied_vector;
	}
};


// STATIC VARIABLE INITIALIZATION

int noise::seed = noise::set_seed(std::random_device()());
int perlin::tiling = 0;
unsigned char perlin::permutation[] =
{
	151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,190,6,148,
	247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168,68,
	175,74,165,71,134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
	102,143,54,65,25,63,161,1,216,80,73,209,76,132,187,208,89,18,169,200,196,135,130,116,188,159,86,164,100,109,
	198,173,186,3,64,52,217,226,250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,
	189,28,42,223,183,170,213,119,248,152,2,44,154,163,70,221,153,101,155,167,43,172,9,129,22,39,253,19,98,108,
	110,79,113,224,232,178,185,112,104,218,246,97,228,251,34,242,193,238,210,144,12,191,179,162,241,81,51,145,
	235,249,14,239,107,49,192,214,31,181,199,106,157,184,84,204,176,115,121,50,45,127,4,150,254,138,236,205,93,
	222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,
	225,140,36,103,30,69,142,8,99,37,240,21,10,23,190,6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,
	32,57,177,33,88,237,149,56,87,174,20,125,136,171,168,68,175,74,165,71,134,139,48,27,166,77,146,158,231,83,
	111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,102,143,54,65,25,63,161,1,216,80,73,209,76,132,
	187,208,89,18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186,3,64,52,217,226,250,124,123,5,202,
	38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,223,183,170,213,119,248,152,2,44,154,
	163,70,221,153,101,155,167,43,172,9,129,22,39,253,19,98,108,110,79,113,224,232,178,185,112,104,218,246,97,
	228,251,34,242,193,238,210,144,12,191,179,162,241,81,51,145,235,249,14,239,107,49,192,214,31,181,199,106,
	157,184,84,204,176,115,121,50,45,127,4,150,254,138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,
	61,156,180
};
