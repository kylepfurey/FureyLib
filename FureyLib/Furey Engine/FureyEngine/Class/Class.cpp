// .cpp
// Furey Engine Base Class Script
// by Kyle Furey

#include "Class.h"

// TYPE INFORMATION

// Returns a unique hash code for this object's type.
unsigned long long Class::GetTypeID() {
    return typeid(*this).hash_code();
}

// Returns the name of this object's type.
const char *Class::GetTypeName() {
    return typeid(*this).name();
}

// TO STRING

// Returns a string interpretation of this object.
const char *Class::ToString() {
    return "Instance";
}

// String conversion operator.
Class::operator const char *() {
    return ToString();
}

// EQUALITY

// Returns a unique hash code of this object's current value.
// The default implementation uses the Fowler-Noll-Vo hash function on the ToString() value.
unsigned long long Class::GetHashCode() {
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
bool Class::Equals(Class &EqualTo) {
    return this == &EqualTo;
}

// Returns whether this instance is equal to the given instance.
bool Class::operator==(Class &EqualTo) {
    return Equals(EqualTo);
}

// Returns whether this instance is not equal to the given instance.
bool Class::operator!=(Class &NotEqualTo) {
    return !Equals(NotEqualTo);
}

// SERIALIZATION

// Converts this instance into a portable .json format.
const char *Class::Serialize() {
    return "{}";
}

// Reads the given .json formatted string into this instance.
// Returns whether the deserialization was successful.
bool Class::Deserialize(const char *Json) {
    return false;
}
