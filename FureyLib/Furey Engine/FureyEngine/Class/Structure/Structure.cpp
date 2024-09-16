// .cpp
// Furey Engine Structure Script
// by Kyle Furey

#include "Structure.h"

// TO STRING

// Returns a string interpretation of this object.
const char *Structure::ToString() const {
    return "Structure";
}

// EQUALITY

// Returns whether this instance is equal to the given instance.
[[nodiscard]] bool Structure::Equals(const Class &EqualTo) const {
    return GetHashCode() == EqualTo.GetHashCode();
}

// Returns whether this instance is equal to the given instance.
[[nodiscard]] bool Structure::Equals(const Structure &EqualTo) const {
    return GetHashCode() == EqualTo.GetHashCode();
}

// Returns whether this instance is equal to the given instance.
bool Structure::operator==(const Structure &EqualTo) const {
    return Equals(EqualTo);
}

// Returns whether this instance is not equal to the given instance.
bool Structure::operator!=(const Structure &NotEqualTo) const {
    return !Equals(NotEqualTo);
}
