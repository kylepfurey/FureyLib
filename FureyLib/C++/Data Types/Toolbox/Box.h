// .h
// Box Type
// by Kyle Furey

#pragma once
#include "Point.h"

/** A collection of useful collection types in C++. */
namespace Toolbox {

	// BOX

	/** Represents an axis-aligned bounding box with a center point and extensions used for collisions and intersections. */
	template<size_t DIMENSIONS = 2, typename PrecisionType = DEFAULT_PRECISION>
	struct Box final {
		static_assert(DIMENSIONS != 0, "ERROR: Cannot initialize a point with 0 dimensions!");

		// POINT

		/** Represents a point in space with variable dimensions. */
		using Point = Point<DIMENSIONS, PrecisionType>;


		// DATA

		/** The location of this box in dimensional space. */
		Point Origin;

		/** The size of each extent of the box, starting from its origin. */
		PrecisionType HalfSize;


		// CONSTRUCTOR

		/** Default constructor. */
		Box(const Point& Origin = Point(), const PrecisionType HalfSize = 5) :Origin(Origin), HalfSize(HalfSize) {
		}


		// GETTERS

		/** Returns the number of dimensions this box has. */
		size_t Dimensions() const {
			return DIMENSIONS;
		}

		/** Returns the length of one edge of the box. */
		PrecisionType Length() const {
			return HalfSize * 2;
		}

		/** Returns the corner point representing the greatest value of the box. */
		Point Max() const {
			Point Max = Origin;
			for (size_t Index = 0; Index < DIMENSIONS; ++Index) {
				Max[Index] += HalfSize;
			}
			return Max;
		}

		/** Returns the corner point representing the lowest value of the box. */
		Point Min() const {
			Point Min = Origin;
			for (size_t Index = 0; Index < DIMENSIONS; ++Index) {
				Min[Index] -= HalfSize;
			}
			return Min;
		}

		/** Returns the perimeter of this box. */
		PrecisionType Perimeter() const {
			return HalfSize * 2 * DIMENSIONS * std::pow(2, DIMENSIONS - 1);
		}

		/** Returns the volume of the box. */
		PrecisionType Volume() const {
			return std::pow(HalfSize * 2, DIMENSIONS);
		}

		/** Returns the surface area of this box. */
		PrecisionType SurfaceArea() const {
			return DIMENSIONS * 2 * std::pow(HalfSize * 2, DIMENSIONS - 1);
		}

		/** Returns the total number of edges of this box. */
		size_t Edges() const {
			return DIMENSIONS * std::pow(2, DIMENSIONS - 1);
		}


		// COLLISION

		/** Returns whether the given point is within this box. */
		bool Contains(const Point& Point) const {
			for (size_t Index = 0; Index < DIMENSIONS; ++Index) {
				if (std::abs(Point[Index] - Origin[Index]) > HalfSize) {
					return false;
				}
			}
			return true;
		}

		/** Returns whether the given box's bounds overlaps with this box's bounds. */
		bool Intersects(const Box& Other) const {
			for (size_t Index = 0; Index < DIMENSIONS; ++Index) {
				if (std::abs(Origin[Index] - Other.Origin[Index]) > (HalfSize + Other.HalfSize)) {
					return false;
				}
			}
			return true;
		}

		/**
		 * Creates a copy of this box divided in the corner based on the given positive dimensions.<br/>
		 * For example: A 2D box divided with { true, false } will be the bottom right quadrant.
		 */
		Box Divide(const bool PositiveDimensions[DIMENSIONS]) const {
			Box Result = *this;
			Result.HalfSize /= 2;
			for (size_t Index = 0; Index < DIMENSIONS; ++Index) {
				if (PositiveDimensions[Index]) {
					Result.Origin[Index] += Result.HalfSize;
				}
				else {
					Result.Origin[Index] -= Result.HalfSize;
				}
			}
			return Result;
		}


		// TO STRING

		/** Returns this box's minimum and maximum value as a string. */
		std::string ToString() const {
			std::string String = "{ ";
			String += Min().ToString() + " -> " + Max().ToString() + " }";
			return String;
		}
	};


	// BOX TYPES

	/** A two dimensional box. */
	using Box2D = Box<2, double>;

	/** A three dimensional box. */
	using Box3D = Box<3, double>;

	/** A four dimensional box. */
	using Box4D = Box<4, double>;
}
