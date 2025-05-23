// .cpp
// 2D Point Structure
// by Kyle Furey

#include "FPoint.h"


// POINT

// Default constructor.
Math::FPoint::FPoint(float x, float y) : X(x), Y(y) {
}

// Returns the magnitude of this point.
float Math::FPoint::Magnitude() const {
	return std::sqrt((X * X) + (Y * Y));
}

// Returns a string variation of this point.
std::string Math::FPoint::ToString(bool toInt) const {
	if (toInt) {
		return std::string("{ ") +
			   std::to_string(static_cast<int>(X)) +
			   ", " +
			   std::to_string(static_cast<int>(Y)) +
			   " }";
	}
	return std::string("{ ") +
		   std::to_string(X) +
		   ", " +
		   std::to_string(Y) +
		   " }";
}

// Normalizes this point.
Math::FPoint& Math::FPoint::Normalize() {
	float magnitude = Magnitude();
	X /= magnitude;
	Y /= magnitude;
	return *this;
}
