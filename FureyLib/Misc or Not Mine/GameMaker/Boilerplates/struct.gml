// .gml
// Name
// Creator

/// @function			struct(_x, _y);
/// @param {Real}	_x	Example x variable.
/// @param {Real}	_y	Example y variable.
/// @description		Template structure script.

function struct(_x = 0, _y = 0) constructor {

	// VARIABLES

	/** Example x variable. */
	x = _x;

	/** Example y variable. */
	y = _y;


	// METHODS

	/// @function		magnitude();
	/// @description	Returns the magnitude of this structure.

	static magnitude = function() {
		if (x == 0 && y == 0) {
			return 0;
		}
		return sqrt(sqr(x) + sqr(y));
	}

	/// @function		normalize();
	/// @description	Normalizes this structure.

	static normalize = function() {
		var mag = magnitude();
		if (mag == 0) {
			return;
		}
		x /= mag;
		y /= mag;
	}
}
