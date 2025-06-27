// .rs
// Program Main Entry Point Script

use std::boxed::*;
use std::collections::*;
use std::env::*;
use std::io::*;
use std::mem::*;
use std::process::*;
use std::rc::*;
use std::string::*;
use std::vec::*;

/// Entry point of the program.
fn main() -> ExitCode {
    let mut args: Vec<String> = args().collect();

    println!("Hello, Dinner!");

    // New code here

    ExitCode::SUCCESS
}
