// .gml
// State Machine Interface Script
// by Kyle Furey

/// @description	Create() is called once before Step() by GameMaker.


// GETTERS

/// @function		get_state_machine();
/// @description	Returns the obj_state_machine instance that owns this state.

get_state_machine = function() {
	return state_machine;
}


// CREATE
