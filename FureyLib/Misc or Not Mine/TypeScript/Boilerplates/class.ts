// .ts
// Name
// Creator

"use strict";

/** Template class script. */
class Class {
    // VARIABLES
    
    /** Example x variable. */
    public x: number;

    /** Example y variable. */
    public y: number;

    // New variables here


    // CONSTRUCTORS

    /** Default constructor. */
    constructor(x: number = 0, y: number = 0) {
        this.x = x;
        this.y = y;
    }

    // New constructors here


    // METHODS

    /** Returns the magnitude of this class. */
    public magnitude(): number {
        if (this.x == 0 && this.y == 0) {
            return 0;
        }
        return Math.sqrt(this.x * this.x + this.y * this.y);
    }

    /** Normalizes this class. */
    public normalize(): Class {
        const magnitude = this.magnitude();
        if (magnitude == 0) {
            return this;
        }
        this.x /= magnitude;
        this.y /= magnitude;
        return this;
    }

    // New methods here
}
