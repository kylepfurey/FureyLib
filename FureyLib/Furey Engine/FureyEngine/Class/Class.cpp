// .cpp
// Furey Engine Base Class Script
// by Kyle Furey

#include "Class.h"

// TYPE INFORMATION

// Returns a unique hash code for this object's type.
[[nodiscard]] unsigned long long Class::GetTypeID() const {
    return typeid(*this).hash_code();
}

// Returns the name of this object's type.
[[nodiscard]] const char *Class::GetTypeName() const {
    return typeid(*this).name();
}

// TO STRING

// Returns a string interpretation of this object.
[[nodiscard]] const char *Class::ToString() const {
    return "Class";
}

// String conversion operator.
Class::operator const char *() const {
    return ToString();
}

// EQUALITY

// Returns a unique hash code of this object's current value.
// The default implementation uses the Fowler-Noll-Vo hash function on the ToString() value.
[[nodiscard]] unsigned long long Class::GetHashCode() const {
    const char *String = ToString();
    const size_t Length = strlen(String);
    unsigned long long Code = 14695981039346656037;
    for (int i = 0; i < Length; ++i) {
        Code ^= String[i];
        Code *= 1099511628211; // FNV Prime
    }
    return Code;
}

// Returns whether this instance is equal to the given instance.
[[nodiscard]] bool Class::Equals(const Class &EqualTo) const {
    return this == &EqualTo;
}

// Returns whether this instance is equal to the given instance.
bool Class::operator==(const Class &EqualTo) const {
    return Equals(EqualTo);
}

// Returns whether this instance is not equal to the given instance.
bool Class::operator!=(const Class &NotEqualTo) const {
    return !Equals(NotEqualTo);
}

// SERIALIZATION

// Converts this instance into a portable .json format.
[[nodiscard]] const char *Class::Serialize() const {
    return "{}";
}

// Reads the given .json formatted string into this instance.
// Returns whether the deserialization was successful.
bool Class::Deserialize(const char *Json) const {
    return false;
}
