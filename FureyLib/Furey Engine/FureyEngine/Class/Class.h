// .h
// Furey Engine Base Class Script
// by Kyle Furey

#pragma once
#include <typeinfo>
#include <cstring>

/**
 * The root class of all objects in Furey Engine.
 * All new classes should inherit from this class or its descendants.
 */
class Class {
public:
    // DESTRUCTOR

    /** Virtual destructor. */
    virtual ~Class() = default;

    // TYPE INFORMATION

    /** Returns a unique hash code for this object's type. */
    unsigned long long GetTypeID();

    /** Returns the name of this object's type. */
    const char *GetTypeName();

    // CASTING

    /**
     * Casts this instance into the given type.
     * Returns null if the cast fails.
     */
    template<typename NewType>
    NewType *Cast() { return dynamic_cast<NewType *>(this); }

    // TO STRING

    /** Returns a string interpretation of this object. */
    virtual const char *ToString();

    /** String conversion operator. */
    virtual operator const char *();

    // EQUALITY

    /**
     * Returns a unique hash code of this object's current value.
     * The default implementation uses the Fowler-Noll-Vo hash function on the ToString() value.
     */
    virtual unsigned long long GetHashCode();

    /** Returns whether this instance is equal to the given instance. */
    virtual bool Equals(Class &EqualTo);

    /** Returns whether this instance is equal to the given instance. */
    virtual bool operator==(Class &EqualTo);

    /** Returns whether this instance is not equal to the given instance. */
    virtual bool operator!=(Class &NotEqualTo);

    // FACTORY METHOD

    /** Creates a new instance of the given type. */
    template<typename Type, typename... ArgumentTypes>
    static Type New(ArgumentTypes... Arguments) { return Type(Arguments...); }

    // SERIALIZATION

    /** Converts this instance into a portable .json format. */
    virtual const char *Serialize();

    /**
     * Reads the given .json formatted string into this instance.
     * Returns whether the deserialization was successful.
     */
    virtual bool Deserialize(const char *Json);
};

// Returns a unique hash code for this object's type.
#define typeof(Type) typeid(Type).hash_code()

// Returns the name of this object's type.
#define nameof(Type) typeid(Type).name()
