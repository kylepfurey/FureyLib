// .h
// Static Math Functions
// by Kyle Furey

#pragma once
#include "Point.h"

// Pi constant.
#define PI 3.14159265359

// Scalar used for converting degrees to radians.
#define DEG_TO_RAD 57.2958

// Scalar used for converting radians to degrees.
#define RAD_TO_DEG (1 / 57.2958)

/** A collection of useful collection types in C++. */
namespace Toolbox {

	/** Useful math functions. */
	namespace Math {

		// MATH

		/** Returns the dot product of the given points. */
		template<size_t DIMENSIONS = 3, typename PrecisionType = DEFAULT_PRECISION>
		static PrecisionType DotProduct(const Point<DIMENSIONS, PrecisionType>& Left, const Point<DIMENSIONS, PrecisionType>& Right) {
			PrecisionType Sum = 0;
			for (size_t Index = 0; Index < DIMENSIONS; ++Index) {
				Sum += Left[Index] * Right[Index];
			}
			return Sum;
		}

		/** Returns the distance from the start point to the end point. */
		template<size_t DIMENSIONS = 3, typename PrecisionType = DEFAULT_PRECISION>
		static PrecisionType Distance(const Point<DIMENSIONS, PrecisionType>& Start, const Point<DIMENSIONS, PrecisionType>& End) {
			Point<DIMENSIONS, PrecisionType> Delta = Start - End;
			return Delta.Magnitude();
		}

		/** Rotates the given 2D point by the given radians. */
		template<typename PrecisionType = DEFAULT_PRECISION>
		static Point<2, PrecisionType> Rotate(const Point<2, PrecisionType>& Point, const PrecisionType Radians) {
			PrecisionType Cos = std::cos(Radians);
			PrecisionType Sin = std::sin(Radians);
			return {
				Point.X() * Cos - Point.Y() * Sin,
				Point.X() * Sin + Point.Y() * Cos
			};
		}

		/** Returns the cross product of the given 3D points. */
		template<typename PrecisionType = DEFAULT_PRECISION>
		static Point<3, PrecisionType> CrossProduct(const Point<3, PrecisionType>& Left, const Point<3, PrecisionType>& Right) {
			return {
				Left.Y() * Right.Z() - Left.Z() * Right.Y(),
				Left.Z() * Right.X() - Left.X() * Right.Z(),
				Left.X() * Right.Y() - Left.Y() * Right.X()
			};
		}

		/** Converts the given radians value to degrees. */
		template<typename PrecisionType = DEFAULT_PRECISION>
		static PrecisionType ToDegrees(const PrecisionType Radians) {
			return Radians * DEG_TO_RAD;
		}

		/** Converts the given degrees value to radians. */
		template<typename PrecisionType = DEFAULT_PRECISION>
		static PrecisionType ToRadians(const PrecisionType Degrees) {
			return Degrees / DEG_TO_RAD;
		}
	}
}
