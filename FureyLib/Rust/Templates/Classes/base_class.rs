
// Base Rust Class Structure Script
// by Kyle Furey

use std::mem::*;
use std::rc::*;
use std::boxed::*;
use std::io::*;
use std::string::*;
use std::vec::*;
use std::collections::*;
use std::ops::*;

// Include this heading to use the class
// mod base_class;
// use crate::base_class::*;

// A structure that owns its own data, methods, and can be inherited from to share different properties.
#[macro_export]
macro_rules! class { ($name:ident, $variables:tt) => {pub struct $name $variables}; }

// Template for a base class structure in Rust.
class!(BaseClass,
{
    // VARIABLES

    // New variables here
});

// Functions and methods for base class.
impl BaseClass
{
    // CONSTRUCTORS

    // Default constructor:
    // Returns a newly constructed instance of the given class
    pub fn new() -> BaseClass
    {
        let mut target: BaseClass = BaseClass
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
