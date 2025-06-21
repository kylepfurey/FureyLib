// .gml
// Multicast Event Structure
// by Kyle Furey

/// @function		Event();
/// @description	Constructs a collection of functions and IDs that can be bound, unbound, and invoked all at once.

function Event() constructor {

	// VARIABLES

	/** An array of each bound function and its ID. */
	bindings = array_create(0, undefined);


	// METHODS

	/// @function		count();
	/// @description	Returns the total number of bound functions.

	static count = function() {
		return array_length(bindings);
	}

	/// @function						bind(id,callback);
	/// @param {Any}		id			The ID of the bound function.
	/// @param {Function}	callback	The function being bound.
	/// @description					Binds a new function and its ID to this event.

	static bind = function(id, callback) {
		if (is_undefined(callback)) {
			return array_push(bindings, {
				id : id,
				callback : id
			});
		}
		return array_push(bindings, {
			id : id,
			callback : callback
		});
	}

	/// @function			unbind(id);
	/// @param {Any}	id	The ID of the function to unbind.
	/// @description		Unbinds the first bound function that matches the given ID from this event.

	static unbind = function(id) {
		var length = array_length(bindings);
		for (var i = 0; i < length; ++i) {
			if (bindings[i].id == id) {
				delete bindings[i];
				bindings[i] = undefined;
				array_delete(bindings, i, 1);
				return true;
			}
		}
		return false;
	}

	/// @function			is_bound(id);
	/// @param {Any}	id	The ID of the function to look for.
	/// @description		Returns whether at least one bound function matches the given ID.
	
	static is_bound = function(id) {
		var length = array_length(bindings);
		for (var i = 0; i < length; ++i) {
			if (bindings[i].id == id) {
				return true;
			}
		}
		return false;
	}

	/// @function		invoke(...);
	/// @description	Invokes each bound function with the given arguments and returns the most recent function's returned value.

	static invoke = function() {
		var result = undefined;
		var length = array_length(bindings);
		for (var i = 0; i < length; ++i) {
			result = bindings[i].callback(argument0, argument1, argument2, argument3, argument4, argument5, argument6, argument7, argument8, argument9, argument10, argument11, argument12, argument13, argument14, argument15);
		}
		return result;
	}

	/// @function		clear();
	/// @description	Unbinds all functions from this event.

	static clear = function() {
		var length = array_length(bindings);
		for (var i = 0; i < length; ++i) {
			delete bindings[i];
			bindings[i] = undefined;
		}
		return array_resize(bindings, 0);
	}
}
