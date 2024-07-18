
// Template Macro Library Script
// by Kyle Furey

use std::mem;
use std::io;
use std::string;
use std::collections::*;

// Include this heading to use the library
// mod macro;
// use crate::macro::*;

// Example macro (use "$log:expr" in the lambda to signify parameters)
#[macro_export]
macro_rules! MACRO
{
	() =>
	{
		println!("Macro inserted!");
	};
}
