// .js
// Name
// Creator

"use strict";

/** Template class script. */
class Class {
    // CONSTRUCTORS

    /** Default constructor. */
    constructor(x = 0, y = 0) {
        // VARIABLES

        /** Example x variable. */
        this.x = x;

        /** Example y variable. */
        this.y = y;

        // New variables here
    }

    // New constructors here


    // METHODS

    /** Returns the magnitude of this class. */
    magnitude() {
        if (this.x == 0 && this.y == 0) {
            return 0;
        }
        return Math.sqrt(this.x * this.x + this.y * this.y);
    }

    /** Normalizes this class. */
    normalize() {
        const magnitude = this.magnitude();
        if (magnitude == 0) {
            return this;
        }
        this.x /= magnitude;
        this.y /= magnitude;
        return this;
    }
}
