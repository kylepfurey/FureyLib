
// Static Noise Functions Script
// by Kyle Furey, Sourced from Adrian Biagioli and Riven

// SOURCE: https://adrianb.io/2014/08/09/perlinnoise.html

using System;

// Include these headings to use the library.
using static Noise;
using static Perlin;

// The precision value of the noise value's alpha.
using Precision = System.Double;

/// <summary>
/// Generates noise values using different types of algorithms.
/// </summary>
public static class Noise
{
    // RANDOM SEED

    /// <summary>
    /// The seed used to calculate random noise values. The seed is random by default.
    /// </summary>
    public static int seed
    {
        get
        {
            return _seed;
        }

        set
        {
            random = new Random(value);

            _seed = value;
        }
    }

    /// <summary>
    /// The seed's value.
    /// </summary>
    private static int _seed = 0;

    /// <summary>
    /// The instance of the Random class used to generate random values.
    /// </summary>
    private static Random random = new Random(0);


    // STATIC CONSTRUCTOR

    /// <summary>
    /// Static constructor (randomizes seed).
    /// </summary>
    static Noise()
    {
        seed = new Random().Next();
    }


    // RANDOM VALUES

    /// <summary>
    /// Returns a random integer.
    /// </summary>
    public static int Random()
    {
        return random.Next();
    }

    /// <summary>
    /// Returns a random integer of the given range (exclusive).
    /// </summary>
    public static int Random(int max)
    {
        return Random() % max;
    }

    /// <summary>
    /// Returns a random integer of the given range (inclusive).
    /// </summary>
    public static int Random(int min, int max)
    {
        return (int)Math.Round(random.NextDouble() * (max - min) + min);
    }

    /// <summary>
    /// Returns a random double between 0 and 1.
    /// </summary>
    public static Precision RandomAlpha()
    {
        return (Precision)random.NextDouble();
    }


    // DISCRETE NOISE

    /// <summary>
    /// Returns an array of random alpha values (0 - 1) of the given size.
    /// </summary>
    public static Precision[] Discrete1D(int length)
    {
        Precision[] result = new Precision[length];

        for (int x = 0; x < length; x++)
        {
            result[x] = RandomAlpha();
        }

        return result;
    }

    /// <summary>
    /// Returns an array of random integers of the given size and range (exclusive).
    /// </summary>
    public static int[] Discrete1D(int length, int max)
    {
        int[] result = new int[length];

        for (int x = 0; x < length; x++)
        {
            result[x] = Random(max);
        }

        return result;
    }

    /// <summary>
    /// Returns an array of random integers of the given size and range (inclusive).
    /// </summary>
    public static int[] Discrete1D(int length, int min, int max)
    {
        int[] result = new int[length];

        for (int x = 0; x < length; x++)
        {
            result[x] = Random(min, max);
        }

        return result;
    }

    /// <summary>
    /// Returns a 2D array of random alpha values (0 - 1) of the given size.
    /// </summary>
    public static Precision[,] Discrete2D(int length, int width)
    {
        Precision[,] result = new Precision[length, width];

        for (int y = 0; y < width; y++)
        {
            for (int x = 0; x < length; x++)
            {
                result[x, y] = RandomAlpha();
            }
        }

        return result;
    }

    /// <summary>
    /// Returns a 2D array of random integers of the given size and range (exclusive).
    /// </summary>
    public static int[,] Discrete2D(int length, int width, int max)
    {
        int[,] result = new int[length, width];

        for (int y = 0; y < width; y++)
        {
            for (int x = 0; x < length; x++)
            {
                result[x, y] = Random(max);
            }
        }

        return result;
    }

    /// <summary>
    /// Returns a 2D array of random integers of the given size and range (inclusive).
    /// </summary>
    public static int[,] Discrete2D(int length, int width, int min, int max)
    {
        int[,] result = new int[length, width];

        for (int y = 0; y < width; y++)
        {
            for (int x = 0; x < length; x++)
            {
                result[x, y] = Random(min, max);
            }
        }

        return result;
    }

    /// <summary>
    /// Returns a 3D array of random alpha values (0 - 1) of the given size.
    /// </summary>
    public static Precision[,,] Discrete3D(int length, int width, int height)
    {
        Precision[,,] result = new Precision[length, width, height];

        for (int z = 0; z < height; z++)
        {
            for (int y = 0; y < width; y++)
            {
                for (int x = 0; x < length; x++)
                {
                    result[x, y, z] = RandomAlpha();
                }
            }
        }

        return result;
    }

    /// <summary>
    /// Returns a 3D array of random integers of the given size and range (exclusive).
    /// </summary>
    public static int[,,] Discrete3D(int length, int width, int height, int max)
    {
        int[,,] result = new int[length, width, height];

        for (int z = 0; z < height; z++)
        {
            for (int y = 0; y < width; y++)
            {
                for (int x = 0; x < length; x++)
                {
                    result[x, y, z] = Random(max);
                }
            }
        }

        return result;
    }

    /// <summary>
    /// Returns a 3D array of random integers of the given size and range (inclusive).
    /// </summary>
    public static int[,,] Discrete3D(int length, int width, int height, int min, int max)
    {
        int[,,] result = new int[length, width, height];

        for (int z = 0; z < height; z++)
        {
            for (int y = 0; y < width; y++)
            {
                for (int x = 0; x < length; x++)
                {
                    result[x, y, z] = Random(min, max);
                }
            }
        }

        return result;
    }


    // PERLIN NOISE

    /// <summary>
    /// Returns an array of alpha values (0 - 1) generated from the Perlin Noise Algorithm of the given size.
    /// </summary>
    public static Precision[] Perlin1D(int length, Precision magnitude = 10, int tiling = 0, Precision y = 0, Precision z = 0)
    {
        Precision[] result = new Precision[length];

        for (int x = 0; x < length; x++)
        {
            result[x] = Perlin.Noise(x / magnitude, y, z, tiling);
        }

        return result;
    }

    /// <summary>
    /// •  Returns an array of alpha values (0 - 1) generated from the Perlin Noise Algorithm of the given size.<br/>
    /// •  Features control over octaves and persistence values for a more natural noise.
    /// </summary>
    public static Precision[] Perlin1D(int length, Precision magnitude, int octaves, Precision persistence, int tiling = 0, Precision y = 0, Precision z = 0)
    {
        Precision[] result = new Precision[length];

        for (int x = 0; x < length; x++)
        {
            result[x] = Perlin.Noise(x / magnitude, y, z, octaves, persistence, tiling);
        }

        return result;
    }

    /// <summary>
    /// Returns a 2D array of alpha values (0 - 1) generated from the Perlin Noise Algorithm of the given size.
    /// </summary>
    public static Precision[,] Perlin2D(int length, int width, Precision magnitude = 10, int tiling = 0, Precision z = 0)
    {
        Precision[,] result = new Precision[length, width];

        for (int y = 0; y < width; y++)
        {
            for (int x = 0; x < length; x++)
            {
                result[x, y] = Perlin.Noise(x / magnitude, y / magnitude, z, tiling);
            }
        }

        return result;
    }

    /// <summary>
    /// •  Returns a 2D array of alpha values (0 - 1) generated from the Perlin Noise Algorithm of the given size.<br/>
    /// •  Features control over octaves and persistence values for a more natural noise.
    /// </summary>
    public static Precision[,] Perlin2D(int length, int width, Precision magnitude, int octaves, Precision persistence, int tiling = 0, Precision z = 0)
    {
        Precision[,] result = new Precision[length, width];

        for (int y = 0; y < width; y++)
        {
            for (int x = 0; x < length; x++)
            {
                result[x, y] = Perlin.Noise(x / magnitude, y / magnitude, z, octaves, persistence, tiling);
            }
        }

        return result;
    }

    /// <summary>
    /// Returns a 3D array of alpha values (0 - 1) generated from the Perlin Noise Algorithm of the given size.
    /// </summary>
    public static Precision[,,] Perlin3D(int length, int width, int height, Precision magnitude = 10, int tiling = 0)
    {
        Precision[,,] result = new Precision[length, width, height];

        for (int z = 0; z < height; z++)
        {
            for (int y = 0; y < width; y++)
            {
                for (int x = 0; x < length; x++)
                {
                    result[x, y, z] = Perlin.Noise(x / magnitude, y / magnitude, z / magnitude, tiling);
                }
            }
        }

        return result;
    }

    /// <summary>
    /// •  Returns a 3D array of alpha values (0 - 1) generated from the Perlin Noise Algorithm of the given size.<br/>
    /// •  Features control over octaves and persistence values for a more natural noise.
    /// </summary>
    public static Precision[,,] Perlin3D(int length, int width, int height, Precision magnitude, int octaves, Precision persistence, int tiling = 0)
    {
        Precision[,,] result = new Precision[length, width, height];

        for (int z = 0; z < height; z++)
        {
            for (int y = 0; y < width; y++)
            {
                for (int x = 0; x < length; x++)
                {
                    result[x, y, z] = Perlin.Noise(x / magnitude, y / magnitude, z / magnitude, octaves, persistence, tiling);
                }
            }
        }

        return result;
    }


    // BLURRING

    /// <summary>
    /// Blurs the given noise array together based on the given alpha value.
    /// </summary>
    public static Precision[] Blur(Precision[] array, Precision alpha)
    {
        Precision[] copiedArray = new Precision[array.Length];

        for (int x = 0; x < array.Length; x++)
        {
            Precision average = array[x];

            int denominator = 1;

            // LEFT
            if (x - 1 >= 0)
            {
                denominator++;

                average += array[x - 1];
            }

            // RIGHT
            if (x + 1 < array.Length)
            {
                denominator++;

                average += array[x + 1];
            }

            average /= denominator;

            copiedArray[x] = Lerp(array[x], average, alpha);
        }

        return copiedArray;
    }

    /// <summary>
    /// Blurs the given noise array together based on the given alpha value.
    /// </summary>
    public static Precision[,] Blur(Precision[,] array, Precision alpha)
    {
        int xLength = array.GetLength(0);

        int yLength = array.GetLength(1);

        Precision[,] copiedArray = new Precision[xLength, yLength];

        for (int y = 0; y < yLength; y++)
        {
            for (int x = 0; x < xLength; x++)
            {
                Precision average = array[x, y];

                int denominator = 1;

                // LEFT
                if (x - 1 >= 0)
                {
                    denominator++;

                    average += array[x - 1, y];
                }

                // RIGHT
                if (x + 1 < xLength)
                {
                    denominator++;

                    average += array[x + 1, y];
                }

                // DOWN
                if (y - 1 >= 0)
                {
                    denominator++;

                    average += array[x, y - 1];
                }

                // UP
                if (y + 1 < yLength)
                {
                    denominator++;

                    average += array[x, y + 1];
                }

                // LEFT DOWN
                if (x - 1 >= 0 && y - 1 >= 0)
                {
                    denominator++;

                    average += array[x - 1, y - 1];
                }

                // RIGHT DOWN
                if (x + 1 < xLength && y - 1 >= 0)
                {
                    denominator++;

                    average += array[x + 1, y - 1];
                }

                // RIGHT UP
                if (x + 1 < xLength && y + 1 < yLength)
                {
                    denominator++;

                    average += array[x + 1, y + 1];
                }

                // LEFT UP
                if (x - 1 >= 0 && y + 1 < yLength)
                {
                    denominator++;

                    average += array[x - 1, y + 1];
                }

                average /= denominator;

                copiedArray[x, y] = Lerp(array[x, y], average, alpha);
            }
        }

        return copiedArray;
    }

    /// <summary>
    /// Blurs the given noise array together based on the given alpha value.
    /// </summary>
    public static Precision[,,] Blur(Precision[,,] array, Precision alpha)
    {
        int xLength = array.GetLength(0);

        int yLength = array.GetLength(1);

        int zLength = array.GetLength(2);

        Precision[,,] copiedArray = new Precision[xLength, yLength, zLength];

        for (int z = 0; z < zLength; z++)
        {
            for (int y = 0; y < yLength; y++)
            {
                for (int x = 0; x < xLength; x++)
                {
                    Precision average = 0;

                    int denominator = 0;

                    for (int zOffset = -1; zOffset < 2; zOffset++)
                    {
                        for (int yOffset = -1; yOffset < 2; yOffset++)
                        {
                            for (int xOffset = -1; xOffset < 2; xOffset++)
                            {
                                if (x + xOffset >= 0 && x + xOffset < xLength && y + yOffset >= 0 && y + yOffset < yLength && z + zOffset >= 0 && z + zOffset < zLength)
                                {
                                    denominator++;

                                    average += array[x + xOffset, y + yOffset, z + zOffset];
                                }
                            }
                        }
                    }

                    average /= denominator;

                    copiedArray[x, y, z] = Lerp(array[x, y, z], average, alpha);
                }
            }
        }

        return copiedArray;
    }


    // LINEAR INTERPOLATION

    /// <summary>
    /// Linearly interpolates from the start to the end values at the given alpha.
    /// </summary>
    private static Precision Lerp(Precision start, Precision end, Precision alpha)
    {
        return start + alpha * (end - start);
    }
}

/// <summary>
/// •  Generates a sample of Perlin Noise.<br/>
/// •  SOURCE: https://adrianb.io/2014/08/09/perlinnoise.html by Adrian Biagioli.
/// </summary>
public static class Perlin
{
    // PERMUTATION TABLE

    /// <summary>
    /// Ken Perlin's permutation table.
    /// </summary>
    public static readonly byte[] permutation =
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


    // TILING

    /// <summary>
    /// The default value to tile the noise at.
    /// </summary>
    public static int tiling { get; set; } = 0;


    // PERLIN NOISE

    /// <summary>
    /// Samples a noise value at the given coordinates using Ken Perlin's Noise Algorithm.
    /// </summary>
    public static Precision Noise(Precision x, Precision y, Precision z)
    {
        return Noise(x, y, z, tiling);
    }

    /// <summary>
    /// Samples a noise value at the given coordinates using Ken Perlin's Noise Algorithm.
    /// </summary>
    public static Precision Noise(Precision x, Precision y, Precision z, int tiling)
    {
        if (tiling > 0)
        {
            x = x % tiling;
            y = y % tiling;
            z = z % tiling;
        }

        int xi = (int)x & 255;
        int yi = (int)y & 255;
        int zi = (int)z & 255;

        Precision xf = x - (int)x;
        Precision yf = y - (int)y;
        Precision zf = z - (int)z;

        Precision u = Fade(xf);
        Precision v = Fade(yf);
        Precision w = Fade(zf);

        int aaa, aba, aab, abb, baa, bba, bab, bbb;
        aaa = permutation[permutation[permutation[xi] + yi] + zi];
        aba = permutation[permutation[permutation[xi] + Increment(yi)] + zi];
        aab = permutation[permutation[permutation[xi] + yi] + Increment(zi)];
        abb = permutation[permutation[permutation[xi] + Increment(yi)] + Increment(zi)];
        baa = permutation[permutation[permutation[Increment(xi)] + yi] + zi];
        bba = permutation[permutation[permutation[Increment(xi)] + Increment(yi)] + zi];
        bab = permutation[permutation[permutation[Increment(xi)] + yi] + Increment(zi)];
        bbb = permutation[permutation[permutation[Increment(xi)] + Increment(yi)] + Increment(zi)];

        Precision x1, x2, y1, y2;
        x1 = Lerp(Gradient(aaa, xf, yf, zf), Gradient(baa, xf - 1, yf, zf), u);
        x2 = Lerp(Gradient(aba, xf, yf - 1, zf), Gradient(bba, xf - 1, yf - 1, zf), u);
        y1 = Lerp(x1, x2, v);
        x1 = Lerp(Gradient(aab, xf, yf, zf - 1), Gradient(bab, xf - 1, yf, zf - 1), u);
        x2 = Lerp(Gradient(abb, xf, yf - 1, zf - 1), Gradient(bbb, xf - 1, yf - 1, zf - 1), u);
        y2 = Lerp(x1, x2, v);

        return (Lerp(y1, y2, w) + 1) / 2;
    }

    /// <summary>
    /// •  Samples a noise value at the given coordinates using Ken Perlin's Noise Algorithm.<br/>
    /// •  Features control over octaves and persistence values for a more natural noise.
    /// </summary>
    public static Precision Noise(Precision x, Precision y, Precision z, int octaves, Precision persistence)
    {
        return Noise(x, y, z, octaves, persistence, tiling);
    }

    /// <summary>
    /// •  Samples a noise value at the given coordinates using Ken Perlin's Noise Algorithm.<br/>
    /// •  Features control over octaves and persistence values for a more natural noise.
    /// </summary>
    public static Precision Noise(Precision x, Precision y, Precision z, int octaves, Precision persistence, int tiling)
    {
        Precision total = 0;
        Precision frequency = 1;
        Precision amplitude = 1;
        Precision maxValue = 0;

        for (int i = 0; i < octaves; i++)
        {
            total += Noise(x * frequency, y * frequency, z * frequency) * amplitude;

            maxValue += amplitude;

            amplitude *= persistence;

            frequency *= 2;
        }

        return total / maxValue;
    }


    // PERLIN FUNCTIONS

    /// <summary>
    /// Ken Perlin's fading function.
    /// </summary>
    private static Precision Fade(Precision value)
    {
        return value * value * value * (value * (value * 6 - 15) + 10);
    }

    /// <summary>
    /// Increments the given index based on the set tiling value.
    /// </summary>
    private static int Increment(int index)
    {
        index++;

        if (tiling > 0)
        {
            index %= tiling;
        }

        return index;
    }

    /// <summary>
    /// •  Riven's fast random gradient function.<br/>
    /// •  SOURCE: http://riven8192.blogspot.com/2010/08/calculate-perlinnoise-twice-as-fast.html by Riven.
    /// </summary>
    private static Precision Gradient(int hash, Precision x, Precision y, Precision z)
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

    /// <summary>
    /// Linearly interpolates from the start to the end values at the given alpha.
    /// </summary>
    private static Precision Lerp(Precision start, Precision end, Precision alpha)
    {
        return start + alpha * (end - start);
    }
}
