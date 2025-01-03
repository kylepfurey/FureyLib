// .rs
// Name
// Creator

use std::mem::*;
use std::rc::*;
use std::boxed::*;
use std::io::*;
use std::string::*;
use std::vec::*;
use std::collections::*;
use std::ops::*;


// STRUCTURE

/** Template structure script. */
pub struct Struct {
    // VARIABLES

    /** Example x variable. */
    pub x: f32,

    /** Example y variable. */
    pub y: f32

    // New variables here
}


// FUNCTIONS
impl Struct {
    // CONSTRUCTORS

    /** Initializes a new structure. */
    pub fn new(x: f32, y: f32) -> Self {
        Struct { x, y }
    }

    // New constructors here


    // METHODS

    /** Returns the magnitude of the given structure. */
    pub fn magnitude(&self) -> f32 {
        if self.x == 0.0 && self.y == 0.0 {
            return 0.0;
        }
        (self.x * self.x + self.y * self.y).sqrt()
    }

    /** Normalizes the given structure. */
    pub fn normalize(&mut self) -> &mut Self {
        let magnitude: f32 = self.magnitude();
        if magnitude == 0.0 {
            return self;
        }
        self.x /= magnitude;
        self.y /= magnitude;
        self
    }

    // New methods here
}


// DESTRUCTOR
impl Drop for Struct {
    /** Properly destroys the given structure. */
    fn drop(&mut self) {
        self.x = 0.0;
        self.y = 0.0;
    }
}
