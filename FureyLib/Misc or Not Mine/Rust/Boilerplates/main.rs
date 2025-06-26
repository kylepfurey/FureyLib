// .rs
// Program Main Entry Point Script

use std::boxed::*;
use std::collections::*;
use std::env::*;
use std::io::*;
use std::mem::*;
use std::rc::*;
use std::result::*;
use std::string::*;
use std::vec::*;

/// Entry point of the program.
fn main() -> Result<(), io::Error> {
    let args: Vec<String> = env::args().collect();
    
    println!("Hello, Dinner!");

    // New code here

    Ok(())
}
