
// Template Function Library Script
// by Kyle Furey

use std::mem::*;
use std::rc::*;
use std::boxed::*;
use std::io::*;
use std::string::*;
use std::vec::*;
use std::collections::*;

// Include this heading to use the library
// mod function;
// use crate::function::*;

// Example function
pub fn function()
{
    println!("Function called!");
}

// Prints a message to the console
pub fn print(log: &str)
{
    println!("{}", log);
}
