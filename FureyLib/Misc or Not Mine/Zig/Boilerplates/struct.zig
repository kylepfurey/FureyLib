// .zig
// Name
// Creator

const std = @import("std");

/// Template structure script.
pub const Struct = struct {
    // VARIABLES

    /// Example x variable.
    x: f32,

    /// Example y variable.
    y: f32,

    // New variables here


    // CONSTRUCTORS AND DESTRUCTOR

    /// Initializes a new structure.
    pub fn init(x: f32, y: f32) Struct {
        const self = Struct{
            .x = x,
            .y = y
        };
        return self;
    }

    // New constructors here

    /// Properly destroys the given structure.
    pub fn deinit(self: *Struct) void {
        self.x = 0;
        self.y = 0;
    }


    // METHODS

    /// Returns the magnitude of the given structure.
    pub fn magnitude(self: *const Struct) f32 {
        if (self.x == 0 and self.y == 0) {
            return 0;
        }
        return std.math.sqrt(self.x * self.x + self.y * self.y);
    }

    /// Normalizes the given structure.
    pub fn normalize(self: *Struct) *Struct {
        const mag = self.magnitude();
        if (mag == 0) {
            return self;
        }
        self.x /= mag;
        self.y /= mag;
        return self;
    }

    // New methods here
};


