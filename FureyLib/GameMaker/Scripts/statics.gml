// .gml
// Singleton Statics Storage
// by Kyle Furey

/// @function		get_statics();
/// @description	Initializes and returns static read-only data for this game.

function get_statics() {
	if (!variable_global_exists("statics")) {
		show_debug_message("Initializing static variables.");
		global.statics = {
			start_datetime : date_current_datetime(),
			// New static variables here
		};
	}
	return global.statics;
}

// Initialize statics
get_statics();
show_debug_message($"Game started at {date_datetime_string(global.statics.start_datetime)}.");
