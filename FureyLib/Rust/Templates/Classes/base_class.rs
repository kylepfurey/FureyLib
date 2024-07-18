
// Base Rust Class Structure Script
// by Kyle Furey

use std::mem;
use std::io;
use std::string;
use std::collections::*;
use std::ops;

// Include this heading to use the class
// mod base_class;
// use crate::base_class::*;

// Template for a base class structure in Rust.
pub struct BaseClass
{
    // VARIABLES

    // New variables here
}

// Functions and methods for base class.
impl BaseClass
{
    // CONSTRUCTORS

    // Default constructor:
    // Returns a newly constructed instance of the given class
    pub fn construct() -> BaseClass
    {
        let target: BaseClass = BaseClass
        {
            // New constructor code here
        };

        return target;
    }

    // New constructors here


    // FUNCTIONS

    // New functions here
}

// Destructor for base class.
impl Drop for BaseClass
{
    // DESTRUCTOR

    // Destructor:
    // Properly destroys this class
    fn drop(&mut self)
    {
        // New destructor code here
    }
}
