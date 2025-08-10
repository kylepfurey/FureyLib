// .go
// Name
// Creator

package MyStruct

import "math"

// STRUCTURE VARIABLES

/** Template structure script. */
type MyStruct struct {
	/** Example x variable. */
	X float32

	/** Example y variable. */
	Y float32

	// New variables here
}

// STRUCTURE CONSTRUCTORS

/** Default constructor. */
func NewStruct(x float32, y float32) MyStruct {
	return MyStruct{x, y}
}

// New constructors here

// STRUCTURE METHODS

/** Returns the magnitude of this structure. */
func (self *MyStruct) Magnitude() float32 {
	if self.X == 0.0 && self.Y == 0.0 {
		return 0.0
	}
	return float32(math.Sqrt(float64(self.X*self.X + self.Y*self.Y)))
}

/** Normalizes this structure. */
func (self *MyStruct) Normalize() *MyStruct {
	var magnitude float32 = self.Magnitude()
	if magnitude == 0.0 {
		return self
	}
	self.X /= magnitude
	self.Y /= magnitude
	return self
}

// New methods here
