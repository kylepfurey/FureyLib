// .h
// Point Type
// by Kyle Furey

#pragma once
#include <string>
#include <initializer_list>
#include <cmath>
#include <stdexcept>

// The default floating point type used for precision.
#define DEFAULT_PRECISION double

/** A collection of useful collection types in C++. */
namespace Toolbox {

	// POINT

	/** Represents a point in space with variable dimensions. */
	template<size_t DIMENSIONS = 2, typename PrecisionType = DEFAULT_PRECISION>
	struct Point final {
		static_assert(DIMENSIONS != 0, "ERROR: Cannot initialize a point with 0 dimensions!");

	private:

		// DATA

		/** Each positional component of a point. */
		PrecisionType components[DIMENSIONS];

	public:

		// CONSTRUCTORS

		/** Default constructor. */
		Point(const PrecisionType Value = 0) : components() {
			for (size_t Index = 0; Index < DIMENSIONS; ++Index) {
				components[Index] = Value;
			}
		}

		/** Array constructor. */
		Point(const PrecisionType* Array) : components() {
			if (Array == nullptr) {
				for (size_t Index = 0; Index < DIMENSIONS; ++Index) {
					components[Index] = 0;
				}
				return;
			}
			for (size_t Index = 0; Index < DIMENSIONS; ++Index) {
				components[Index] = Array[Index];
			}
		}

		/** Initializer list constructor. */
		Point(const std::initializer_list<PrecisionType>& List) : components() {
			for (size_t Index = 0; Index < DIMENSIONS; ++Index) {
				components[Index] = 0;
			}
			size_t Count = List.size() > DIMENSIONS ? DIMENSIONS : List.size();
			for (size_t Index = 0; Index < Count; ++Index) {
				components[Index] = *(List.begin() + Index);
			}
		}


		// OPERATORS

		/** Returns whether the given point is equal to this point. */
		bool operator==(const Point& Other) const {
			for (size_t Index = 0; Index < DIMENSIONS; ++Index) {
				if (components[Index] != Other.components[Index]) {
					return false;
				}
			}
			return true;
		}

		/** Returns whether the given point is not equal to this point. */
		bool operator!=(const Point& Other) const {
			return !(*this == Other);
		}

		/** Returns a copy of this point added to the given point. */
		Point operator+(const Point& Other) const {
			Point Result = *this;
			Result += Other;
			return Result;
		}

		/** Returns a copy of this point subtracted by the given point. */
		Point operator-(const Point& Other) const {
			Point Result = *this;
			Result -= Other;
			return Result;
		}

		/** Returns a copy of this point multipied by the given point. */
		Point operator*(const Point& Other) const {
			Point Result = *this;
			Result *= Other;
			return Result;
		}

		/** Returns a copy of this point divided by the given point. */
		Point operator/(const Point& Other) const {
			Point Result = *this;
			Result /= Other;
			return Result;
		}

		/** Adds the given point to this point. */
		Point& operator+=(const Point& Other) {
			for (size_t Index = 0; Index < DIMENSIONS; ++Index) {
				components[Index] += Other.components[Index];
			}
			return *this;
		}

		/** Subtracts the given point from this point. */
		Point& operator-=(const Point& Other) {
			for (size_t Index = 0; Index < DIMENSIONS; ++Index) {
				components[Index] -= Other.components[Index];
			}
			return *this;
		}

		/** Multiplies the given point with this point. */
		Point& operator*=(const Point& Other) {
			for (size_t Index = 0; Index < DIMENSIONS; ++Index) {
				components[Index] *= Other.components[Index];
			}
			return *this;
		}

		/** Divides the given point from this point. */
		Point& operator/=(const Point& Other) {
			for (size_t Index = 0; Index < DIMENSIONS; ++Index) {
				components[Index] /= Other.components[Index];
			}
			return *this;
		}

		/** Returns a copy of this point added to the given scalar. */
		Point operator+(const PrecisionType& Scalar) const {
			Point Result = *this;
			Result += Scalar;
			return Result;
		}

		/** Returns a copy of this point subtracted by the given scalar. */
		Point operator-(const PrecisionType& Scalar) const {
			Point Result = *this;
			Result -= Scalar;
			return Result;
		}

		/** Returns a copy of this point multipied by the given scalar. */
		Point operator*(const PrecisionType& Scalar) const {
			Point Result = *this;
			Result *= Scalar;
			return Result;
		}

		/** Returns a copy of this point divided by the given scalar. */
		Point operator/(const PrecisionType& Scalar) const {
			Point Result = *this;
			Result /= Scalar;
			return Result;
		}

		/** Adds the given scalar to this point. */
		Point& operator+=(const PrecisionType& Scalar) {
			for (size_t Index = 0; Index < DIMENSIONS; ++Index) {
				components[Index] += Scalar;
			}
			return *this;
		}

		/** Subtracts the given scalar from this point. */
		Point& operator-=(const PrecisionType& Scalar) {
			for (size_t Index = 0; Index < DIMENSIONS; ++Index) {
				components[Index] -= Scalar;
			}
			return *this;
		}

		/** Multiplies the given scalar with this point. */
		Point& operator*=(const PrecisionType& Scalar) {
			for (size_t Index = 0; Index < DIMENSIONS; ++Index) {
				components[Index] *= Scalar;
			}
			return *this;
		}

		/** Divides the given scalar from this point. */
		Point& operator/=(const PrecisionType& Scalar) {
			for (size_t Index = 0; Index < DIMENSIONS; ++Index) {
				components[Index] /= Scalar;
			}
			return *this;
		}

		/** Returns a copy of this point multiplied by -1. */
		Point operator-() const {
			Point Result = *this;
			Result *= -1;
			return Result;
		}

		/** Returns a reference to the component at the given index. */
		PrecisionType& operator[](const size_t Index) {
			if (Index >= DIMENSIONS) {
				throw std::runtime_error(std::string("ERROR: Cannot access point component ") + std::to_string(Index) + " when point only has " + std::to_string(DIMENSIONS) + " dimensions!");
			}
			return components[Index];
		}

		/** Returns a copy of the component at the given index. */
		PrecisionType operator[](const size_t Index) const {
			if (Index >= DIMENSIONS) {
				throw std::runtime_error(std::string("ERROR: Cannot access point component ") + std::to_string(Index) + " when point only has " + std::to_string(DIMENSIONS) + " dimensions!");
			}
			return components[Index];
		}


		// GETTERS

		/** Returns the number of dimensions in this point. */
		size_t Dimensions() const {
			return DIMENSIONS;
		}

		/** Returns a reference to the component at the given index. */
		PrecisionType& Get(const size_t Index) {
			if (Index >= DIMENSIONS) {
				throw std::runtime_error(std::string("ERROR: Cannot access point component ") + std::to_string(Index) + " when point only has " + std::to_string(DIMENSIONS) + " dimensions!");
			}
			return components[Index];
		}

		/** Returns a copy of the component at the given index. */
		PrecisionType Get(const size_t Index) const {
			if (Index >= DIMENSIONS) {
				throw std::runtime_error(std::string("ERROR: Cannot access point component ") + std::to_string(Index) + " when point only has " + std::to_string(DIMENSIONS) + " dimensions!");
			}
			return components[Index];
		}

		/** Returns the X component of this point. */
		PrecisionType& X() {
			return components[0];
		}

		/** Returns a copy of the X component of this point. */
		PrecisionType X() const {
			return components[0];
		}

		/** Returns the Y component of this point. */
		PrecisionType& Y() {
			static_assert(DIMENSIONS > 1, "ERROR: Point does not have at least 2 dimensions!");
			return components[1];
		}

		/** Returns a copy of the Y component of this point. */
		PrecisionType Y() const {
			static_assert(DIMENSIONS > 1, "ERROR: Point does not have at least 2 dimensions!");
			return components[1];
		}

		/** Returns the Z component of this point. */
		PrecisionType& Z() {
			static_assert(DIMENSIONS > 2, "ERROR: Point does not have at least 3 dimensions!");
			return components[2];
		}

		/** Returns a copy of the Z component of this point. */
		PrecisionType Z() const {
			static_assert(DIMENSIONS > 2, "ERROR: Point does not have at least 3 dimensions!");
			return components[2];
		}

		/** Returns the W component of this point. */
		PrecisionType& W() {
			static_assert(DIMENSIONS > 3, "ERROR: Point does not have at least 4 dimensions!");
			return components[3];
		}

		/** Returns a copy of the W component of this point. */
		PrecisionType W() const {
			static_assert(DIMENSIONS > 3, "ERROR: Point does not have at least 4 dimensions!");
			return components[3];
		}

		/** Returns the point's magnitude (length). */
		PrecisionType Magnitude() const {
			PrecisionType Sum = 0;
			for (size_t Index = 0; Index < DIMENSIONS; ++Index) {
				Sum += components[Index] * components[Index];
			}
			return std::sqrt(Sum);
		}

		/** Normalizes this point so its magnitude is one. */
		Point& Normalize() {
			PrecisionType Mag = Magnitude();
			if (Mag == 0) {
				return *this;
			}
			for (size_t Index = 0; Index < DIMENSIONS; ++Index) {
				components[Index] /= Mag;
			}
			return *this;
		}

		/** Returns a normalized version of the point. */
		Point Normalized() const {
			Point Normal = *this;
			return Normal.Normalize();
		}


		// ITERATORS

		/** Returns a pointer to the first component. */
		PrecisionType* begin() {
			return components;
		}

		/** Returns a constant pointer to the first component. */
		const PrecisionType* begin() const {
			return components;
		}

		/** Returns a pointer to after the last component. */
		PrecisionType* end() {
			return components + DIMENSIONS;
		}

		/** Returns a pointer to after the last component. */
		const PrecisionType* end() const {
			return components + DIMENSIONS;
		}


		// TO STRING

		/** Returns the point's components as a string. */
		std::string ToString() {
			std::string String = "{ ";
			for (size_t Index = 0; Index < DIMENSIONS; ++Index) {
				String += std::to_string(components[Index]) + ", ";
			}
			String.erase(String.length() - 2, 2);
			String += " }";
			return String;
		}


		// AS ARRAY

		/** Returns the point's components as an array. */
		PrecisionType* AsArray() {
			return components;
		}

		/** Returns the point's components as an array. */
		const PrecisionType* AsArray() const {
			return components;
		}


		// CONSTANTS

		/** Returns a point initialized with zero. */
		static Point Zero() {
			return Point(0);
		}

		/** Returns a point initialized with one. */
		static Point One() {
			return Point(1);
		}

		/** Returns a 2D point facing right. */
		static Point Right() {
			return { 1 };
		}

		/** Returns a 2D point facing up. */
		static Point Up() {
			return { 0, 1 };
		}

		/** Returns a 3D point facing forward. */
		static Point Forward() {
			return { 0, 0, 1 };
		}

		/** Returns a 2D point facing left. */
		static Point Left() {
			return { -1 };
		}

		/** Returns a 2D point facing down. */
		static Point Down() {
			return { 0, -1 };
		}

		/** Returns a 3D point facing backward. */
		static Point Backward() {
			return { 0, 0, -1 };
		}
	};


	// COMPONENT

	/** An enumeration of indicies to point components. */
	enum class Component {
		X = 0,
		Y = 1,
		Z = 2,
		W = 3
	};


	// VECTOR TYPES

	/**
	 * A two dimensional point.<br/>
	 * { X, Y }
	 */
	using Vector2 = Point<2, double>;

	/**
	 * A three dimensional point.<br/>
	 * { X, Y, Z }
	 */
	using Vector3 = Point<3, double>;

	/**
	 * A four dimensional point.<br/>
	 * { X, Y, Z, W }
	 */
	using Vector4 = Point<4, double>;
}
