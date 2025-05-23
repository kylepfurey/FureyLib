// .h
// 2D Point Structure
// by Kyle Furey

#pragma once
#include <string>
#include <cmath>


// MATH

/** Types for mathematical operations. */
namespace Math {

	// POINT

	/** Represents a point in 2D space. */
	struct FPoint final {

		// PUBLIC DATA

		/** The X value of this point. */
		float X;

		/** The Y value of this point. */
		float Y;


		// CONSTRUCTORS

		/** Default constructor. */
		FPoint(float x = 0.0f, float y = 0.0f);


		// GETTERS

		/** Returns the magnitude of this point. */
		float Magnitude() const;

		/** Returns a string variation of this point. */
		std::string ToString(bool toInt = false) const;


		// SETTERS

		/** Normalizes this point. */
		FPoint& Normalize();
	};
}
