
// Derived Rust Class Structure Script
// by Kyle Furey

use std::mem;
use std::io;
use std::string;
use std::collections::*;
use std::ops;
mod base_class;
use crate::base_class::*;

// Include this heading to use the class
// mod derived_class;
// use crate::derived_class::*;

// Template for a derived class structure in Rust.
pub struct DerivedClass
{
    // BASE CLASS

    // The base class this class derives from
    pub base: BaseClass,


    // VARIABLES

    // New variables here
}

// Functions and methods for derived class.
impl DerivedClass
{
    // CONSTRUCTORS AND DESTRUCTOR

    // Default constructor:
    // Returns a newly constructed instance of the given class
    pub fn construct() -> DerivedClass
    {
        let target: DerivedClass = DerivedClass
        {
            // Call base constructor
            base: BaseClass::construct(),

            // New constructor code here
        };

        return target;
    }

    // New constructors here


    // FUNCTIONS

    // New functions here
}

// Destructor for derived class.
impl Drop for DerivedClass
{
    // DESTRUCTOR

    // Destructor:
    // Properly destroys this class
    fn drop(&mut self)
    {
        // New destructor code here

        // Note: Calls base destructor last
    }
}
