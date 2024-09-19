// .h
// Furey Engine Base Class Script
// by Kyle Furey

#pragma once
#include <typeinfo>

/**
 * The root class of all objects in Furey Engine.<br/>
 * All new classes should inherit from this class or its descendants.
 */
class Class {
public:
    // DESTRUCTOR

    /** Virtual destructor. */
    virtual ~Class() = default;

    // TYPE INFORMATION

    /** Returns a unique 64-bit hash code for this object's type. */
    [[nodiscard]] unsigned long long GetTypeID() const;

    /** Returns the name of this object's type. */
    [[nodiscard]] const char *GetTypeName() const;

    /** Returns whether this instance is the given type. */
    template<typename NewType>
    [[nodiscard]] bool Is() const { return GetTypeID() == typeid(NewType).hash_code(); }

    // CASTING

    /**
     * Casts this instance into the given type.<br/>
     * Returns null if the cast fails.
     */
    template<typename NewType>
    NewType *Cast() { return dynamic_cast<NewType *>(this); }

    // TO STRING

    /** Returns a string interpretation of this object. */
    [[nodiscard]] virtual const char *ToString() const;

    /** String conversion operator. */
    virtual operator const char *() const;

    // EQUALITY

    /**
     * Returns a unique 64-bit hash code of this object's current value.<br/>
     * The default implementation uses the Fowler-Noll-Vo hash function on the ToString() value.
     */
    [[nodiscard]] virtual unsigned long long GetHashCode() const;

    /** Returns whether this instance is equal to the given instance. */
    [[nodiscard]] virtual bool Equals(const Class &EqualTo) const;

    /** Returns whether this instance is equal to the given instance. */
    virtual bool operator==(const Class &EqualTo) const;

    /** Returns whether this instance is not equal to the given instance. */
    virtual bool operator!=(const Class &NotEqualTo) const;

    // FACTORY METHOD

    /** Creates a new instance of the given type. */
    template<typename Type, typename... ArgumentTypes>
    static Type New(ArgumentTypes... Arguments) { return Type(Arguments...); }

    // SERIALIZATION

    /** Converts this instance into a portable .json format. */
    [[nodiscard]] virtual const char *Serialize() const;

    /**
     * Reads the given .json formatted string into this instance.<br/>
     * Returns whether the deserialization was successful.
     */
    virtual bool Deserialize(const char *Json) const;
};

// Returns a unique hash code for this object's type.
#define typeof(Type) typeid(Type).hash_code()

// Returns the name of this object's type.
#define nameof(Type) typeid(Type).name()
