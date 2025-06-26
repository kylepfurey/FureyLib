// .rs
// Name
// Creator

use std::boxed::*;
use std::collections::*;
use std::env::*;
use std::io::*;
use std::mem::*;
use std::ops::*;
use std::rc::*;
use std::result::*;
use std::string::*;
use std::vec::*;

// STRUCTURE VARIABLES

/// Template structure script.
pub struct Struct {
    /// Example x variable.
    pub x: f32,

    /// Example y variable.
    pub y: f32, // New variables here
}

// STRUCTURE METHODS

impl Struct {
    // CONSTRUCTORS

    /// Default constructor.
    pub fn new(x: f32, y: f32) -> Self {
        Struct { x, y }
    }

    // New constructors here

    // METHODS

    /// Returns the magnitude of the given structure.
    pub fn magnitude(&self) -> f32 {
        if self.x == 0.0 && self.y == 0.0 {
            return 0.0;
        }
        (self.x * self.x + self.y * self.y).sqrt()
    }

    /// Normalizes the given structure.
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
