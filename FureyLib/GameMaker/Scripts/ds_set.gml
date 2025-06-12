// .gml
// Set Data Structure
// by Kyle Furey
// REFERENCE: https://manual.gamemaker.io/lts/en/GameMaker_Language/GML_Reference/Data_Structures/DS_Maps/DS_Maps.htm

/** This function will return true if the specified key exists in the (previously created) DS set , and false if it does not. */
function ds_set_exists(id, key) {
	return ds_map_exists(id, key);
}

/** This function is used to create a new, empty DS set and will return a Handle to it which is then used to access the data structure in all other DS set functions. */
function ds_set_create() {
	return ds_map_create();
}

/** DS sets take up space in memory, which is allocated to them when they are created. */
function ds_set_destroy(id) {
	return ds_map_destroy(id);
}

/** This function should be used to add unique keys into the specified DS set. */
function ds_set_add(id, key) {
	return ds_map_add(id, key, undefined);
}

/** This function will clear the (previously created) DS set of all keys, but it will not delete the DS set itself from memory. */
function ds_set_clear(id) {
	return ds_map_clear(id);
}

/** You can use this function to copy the contents of one set into another one that you have previously created using ds_set_create(). */
function ds_set_copy(id, source) {
	return ds_map_copy(id, source);
}

/** With this function you can remove any given key from the given, previously created, DS set . */
function ds_set_delete(id, key) {
	return ds_map_delete(id, key);
}

/** This function will simply return false if the specified (previously created) DS set contains any keys, or true if it does not. */
function ds_set_empty(id) {
	return ds_map_empty(id);
}

/** With this function you can find how many keys the (previously created) DS set contains. */
function ds_set_size(id) {
	return ds_map_size(id);
}

/** This function returns the first key stored in the DS set. */
function ds_set_find_first(id) {
	return ds_map_find_first(id);
}

/** This function returns the last key stored in the DS set. */
function ds_set_find_last(id) {
	return ds_map_find_last(id);
}

/** This function returns the next key stored in the DS set after the one specified in the function. */
function ds_set_find_next(id, key) {
	return ds_map_find_next(id, key);
}

/** This function returns the previous key stored in the DS set before the one specified in the function. */
function ds_set_find_previous(id, key) {
	return ds_map_find_previous(id, key);
}

/** With this function you can retrieve all of the keys that a DS set contains. */
function ds_set_to_array(id, array) {
	if (is_undefined(array)) {
		return ds_map_keys_to_array(id);
	} else {
		return ds_map_keys_to_array(id, array);
	}
}

/** This function will take a string that has previously been created by the function ds_set_write() and then read it into a previously created DS set. */
function ds_set_read(id, str, legacy) {
	if (is_undefined(legacy)) {
		return ds_map_read(id, str);
	} else {
		return ds_map_read(id, str, legacy);
	}
}

/** This function will turn the DS set data of the specified set into string format which can then be written to an *.ini or a *.txt file for easy storage. */
function ds_set_write(id) {
	return ds_map_write(id);
}

/** This function will save the contents of the given DS set to a file that is linked to the device it was created on (meaning it can't be read if transferred to any other device). */
function ds_set_secure_save(set, filename) {
	return ds_map_secure_save(set, filename);
}

/** This function will save a previously created DS set to a buffer. */
function ds_set_secure_save_buffer(id, buffer) {
	return ds_map_secure_save_buffer(id, buffer);
}

/** This function will load a previously saved DS set from the given file. */
function ds_set_secure_load(filename) {
	return ds_map_secure_load(filename);
}

/** This function will load a secure saved DS set from a buffer. */
function ds_set_secure_load_buffer(buffer) {
	return ds_map_secure_load_buffer(buffer);
}
