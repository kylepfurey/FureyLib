// .hpp
// Slab Type
// by Kyle Furey

#pragma once
#include <string>
#include <vector>
#include <queue>
#include <optional>
#include <utility>
#include <stdexcept>


// SLAB

/** A collection that manages the memory of each object it contains by providing handles to access the objects. */
template<typename T>
class slab final {
public:

	// TYPES

	/** A unique ID used to lookup an object in a slab. */
	using id = size_t;

private:

	// DATA

	/** The underlying array of objects in the slab. */
	std::vector<std::optional<T>> objects;

	/** Each ID that can be reused in the slab. */
	std::queue<id> next_ids;

	/** The current number of objects in the slab. */
	size_t total;

public:

	// CONSTRUCTOR

	/** Default constructor. */
	slab(const size_t capacity = 16) : objects(capacity), next_ids(), total(0) {
		for (size_t i = 0; i < capacity; ++i) {
			next_ids.push(i);
		}
	}


	// OPERATORS

	/** Finds the object with the specified ID if it is valid. */
	T& operator[](const id id) {
		T* obj = find(id);
		if (obj == nullptr) {
			throw std::runtime_error(std::string("ERROR: ID ") + std::to_string(id) + " was not valid!");
		}
		return *obj;
	}

	/** Finds the object with the specified ID if it is valid. */
	const T& operator[](const id id) const {
		const T* obj = find(id);
		if (obj == nullptr) {
			throw std::runtime_error(std::string("ERROR: ID ") + std::to_string(id) + " was not valid!");
		}
		return *obj;
	}


	// SLAB

	/** Returns an iterator to the beginning of the slab. */
	auto begin() {
		return objects.begin();
	}

	/** Returns an iterator to the beginning of the slab. */
	auto begin() const {
		return objects.begin();
	}

	/** Returns an iterator to the end of the slab. */
	auto end() {
		return objects.end();
	}

	/** Returns an iterator to the end of the slab. */
	auto end() const {
		return objects.end();
	}

	/** Returns the number of objects currently in the slab. */
	size_t size() const {
		return total;
	}

	/** The maximum number of objects that can be stored before resizing the slab. */
	size_t capacity() const {
		return objects.size();
	}

	/** Adds the object to the slab and returns its unique ID. */
	id insert(const T& obj) {
		if (next_ids.empty()) {
			const size_t size = objects.size();
			const size_t capacity = size == 0 ? 16 : size * 2;
			objects.resize(capacity);
			for (size_t i = size; i < capacity; ++i) {
				next_ids.push(i);
			}
		}
		const id id = next_ids.front();
		objects[id] = obj;
		next_ids.pop();
		++total;
		return id;
	}

	/** Constructs an object within the slab and returns its unique ID. */
	template<typename ... A>
	id emplace(A&&... args) {
		if (next_ids.empty()) {
			const size_t size = objects.size();
			const size_t capacity = size == 0 ? 16 : size * 2;
			objects.resize(capacity);
			for (size_t i = size; i < capacity; ++i) {
				next_ids.push(i);
			}
		}
		const id id = next_ids.front();
		objects[id] = T(std::forward<A>(args)...);
		next_ids.pop();
		++total;
		return id;
	}

	/** Removes the object that matches the given ID from the slab, and returns whether it was successful. */
	bool erase(const id id) {
		if (id >= objects.size() || !objects[id].has_value()) {
			return false;
		}
		objects[id].reset();
		next_ids.push(id);
		--total;
		return true;
	}

	/** Returns whether the slab contains an object with the given ID. */
	bool count(const id id) const {
		return (id < objects.size()) && (objects[id].has_value());
	}

	/** Returns the object with the given ID if it exists, or null if it does not. */
	T* find(const id id) {
		return (id < objects.size() && objects[id].has_value()) ? (&objects[id].value()) : (nullptr);
	}

	/** Returns the object with the given ID if it exists, or null if it does not. */
	const T* find(const id id) const {
		return (id < objects.size() && objects[id].has_value()) ? (&objects[id].value()) : (nullptr);
	}

	/** Clears the slab of all its objects. */
	void clear(const size_t capacity = 16) {
		objects.clear();
		next_ids = std::queue<id>();
		total = 0;
		for (size_t i = 0; i < capacity; ++i) {
			next_ids.push(i);
			objects.emplace_back();
		}
	}
};
