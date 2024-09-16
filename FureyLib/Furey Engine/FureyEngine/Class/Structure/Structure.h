// .h
// Furey Engine Structure Script
// by Kyle Furey

#pragma once
#include "../Class.h"

/**
 * The base struct for all structures in Furey Engine.
 * Structures are typically lightweight containers of data able to be passed by value.
 */
struct Structure : Class {
    // TO STRING

    /** Returns a string interpretation of this object. */
    [[nodiscard]] const char *ToString() const override;

    // EQUALITY

    /** Returns whether this instance is equal to the given instance. */
    [[nodiscard]] bool Equals(const Class &EqualTo) const override;

    /** Returns whether this instance is equal to the given instance. */
    [[nodiscard]] virtual bool Equals(const Structure &EqualTo) const;

    /** Returns whether this instance is equal to the given instance. */
    virtual bool operator==(const Structure &EqualTo) const;

    /** Returns whether this instance is not equal to the given instance. */
    virtual bool operator!=(const Structure &NotEqualTo) const;
};
