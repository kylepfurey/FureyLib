// .gml
// State Machine Object Script
// by Kyle Furey

// @description		Initializes the state machine's methods and starting state instance.


// METHODS

/// @function		get_state();
/// @description	Returns the state machine's current state instance.

get_state = function() {
	return state;
}

/// @function		get_state_obj();
/// @description	Returns the object index of the state machine's current state instance.

get_state_obj = function() {
	return state != noone ? state.object_index : noone;
}

/// @function		get_starting_state_obj();
/// @description	Returns the object index of the state machine's starting state instance.

get_starting_state_obj = function() {
	return starting_state_obj;
}

/// @function		is_state_valid();
/// @description	Returns whether the state machine's current state instance is valid.

is_state_valid = function() {
	return state != noone;
}

/// @function							state_is(obj);
/// @param {Asset.GMObject}		obj		The object index to compare the state's object index with.
/// @description						Returns whether the state machine's current state instance is an instance of the given object.

state_is = function(obj) {
	if (state == noone) {
		return false;
	}
	var current = state.object_index;
	while (current != -1) {
		if (current == obj) {
			return true;
		}
		current = object_get_parent(current);
	}
	return false;
}

/// @function							switch_state_to(new_state);
/// @param {ID.Instance}	new_state	The state instance to set as the state machine's current state.
/// @description						Switches the state machine's state instance to the given state instance.

switch_state_to = function(new_state) {
	if (state == new_state) {
		return state;
	}
	if (state != noone) {
		destroy_state();
	}
	state = new_state;
	if (state != noone && variable_instance_exists(state, "state_machine")) {
		state.state_machine = self;
	}
	return state;
}

/// @function							switch_state(obj);
/// @param {Asset.GMObject}		obj		The object index to instantiate as the state machine's current state.
/// @description						Switches the state machine's state instance to a new instance of the given object.

switch_state = function(obj) {
	if (obj == noone) {
		return switch_state_to(noone);
	}
	var new_state = noone;
	if (state != noone) {
		new_state = instance_create_depth(state.x, state.y, state.depth, obj);
	}
	else {
		new_state = instance_create_depth(x, y, depth, obj);
	}
	return switch_state_to(new_state);
}

/// @function		destroy_state();
/// @description	Destroys this state machine's current state instance based on its destroy behaviour.
///					Returns whether the instance was successfully destroyed.

destroy_state = function() {
	if (!destroy_state_on_switch || state == noone) {
		return false;
	}
	instance_destroy(state);
	state = noone;
	return true;
}


// CREATE

if (starting_state_obj != noone)
{
	switch_state(starting_state_obj);
}
