// .hpp
// Multicast Event Type
// by Kyle Furey

#pragma once
#include <string>
#include <vector>
#include <functional>
#include <utility>
#include <stdexcept>
#include <cstdint>


// EVENT

/** A collection of functions that can be bound, unbound, and invoked all at once. */
template <typename T, typename... A>
class event final {
public:

    // TYPES

    /** The type of function pointer bound to this event. */
    using target = std::function<T(A...)>;

private:

    // DATA

    /** Each bound function and its ID. */
    std::vector<std::pair<std::string, target>> bindings;


    // EVENT

    /** Creates a string ID from the given function. */
    static std::string make_id(const target &callback) {
        if (callback.template target<T (*)(A...)>() == nullptr) {
            throw std::runtime_error("ERROR: Cannot implicitly generate an ID for a method or lambda!\n"
                                     "Use make_id<T>() on an object to generate a ID for your function!");
        }
        return std::to_string(reinterpret_cast<uintptr_t>(*callback.template target<T (*)(A...)>));
    }

public:

    // CONSTRUCTOR

    /** Default constructor. */
    explicit event(const size_t capacity = 8) : bindings() {
        bindings.reserve(capacity);
    }


    // OPERATORS

    /** Binds a new function to this event. */
    event &operator+=(const target &callback) {
        bind(callback);
        return *this;
    }

    /** Unbinds the first instance of the given function from this event. */
    event &operator-=(const target &callback) {
        unbind(callback);
        return *this;
    }

    /** Invokes each bound function with the given arguments and returns the most recent function's returned value. */
    T operator()(A... args) {
        return invoke(args...);
    }

    /** Invokes each bound function with the given arguments and returns the most recent function's returned value. */
    T operator()(A... args) const {
        return invoke(args...);
    }


    // EVENT

    /** Returns an iterator to the beginning of the event. */
    typename std::vector<std::pair<std::string, target>>::const_iterator begin() const {
        return bindings.begin();
    }

    /** Returns an iterator to the end of the event. */
    typename std::vector<std::pair<std::string, target>>::const_iterator end() const {
        return bindings.end();
    }

    /** Returns the total number of bound functions. */
    size_t count() const {
        return bindings.size();
    }

    /** Returns the maximum number of functions that can be bound before resizing. */
    size_t capacity() const {
        return bindings.capacity();
    }

    /** Binds a new function to this event. */
    void bind(const target &callback) {
        bind(make_id(callback), callback);
    }

    /** Binds a new function and its ID to this event. */
    void bind(const std::string &id, const target &callback) {
        if (callback == nullptr) {
            throw std::runtime_error("ERROR: Cannot bind an invalid function to an event!");
        }
        bindings.emplace_back(id, callback);
    }

    /** Unbinds the first bound function that matches the given ID from this event. */
    bool unbind(const std::string &id) {
        const size_t size = bindings.size();
        for (size_t i = 0; i < size; ++i) {
            if (bindings[i].first == id) {
                bindings.erase(bindings.begin() + i);
                return true;
            }
        }
        return false;
    }

    /** Unbinds the first bound function that matches the given function from this event. */
    bool unbind(const target &callback) {
        if (callback == nullptr) {
            return false;
        }
        return unbind(make_id(callback));
    }

    /** Returns whether at least one bound function matches the given function. */
    bool is_bound(const target &callback) const {
        if (callback == nullptr) {
            return false;
        }
        return is_bound(make_id(callback));
    }

    /** Returns whether at least one bound function matches the given ID. */
    bool is_bound(const std::string &id) const {
        for (auto &pair : bindings) {
            if (pair.first == id) {
                return true;
            }
        }
        return false;
    }

    /** Invokes each bound function with the given arguments and returns the most recent function's returned value. */
    T invoke(A... args) {
        T result = T();
        for (auto &pair : bindings) {
            if (pair.second == nullptr) {
                throw std::runtime_error("ERROR: Attempted to invoke an invalid function in an event!");
            }
            result = pair.second(args...);
        }
        return result;
    }

    /** Invokes each bound function with the given arguments and returns the most recent function's returned value. */
    T invoke(A... args) const {
        T result = T();
        for (auto &pair : bindings) {
            if (pair.second == nullptr) {
                throw std::runtime_error("ERROR: Attempted to invoke an invalid function in an event!");
            }
            result = pair.second(args...);
        }
        return result;
    }

    /** Unbinds all functions from this event. */
    void clear() {
        bindings.clear();
    }
};

/** A collection of functions that can be bound, unbound, and invoked all at once. */
template <typename... A>
class event<void, A...> final {
public:

    // TYPES

    /** The type of function pointer bound to this event. */
    using target = std::function<void(A...)>;

private:

    // DATA

    /** Each bound function and its ID. */
    std::vector<std::pair<std::string, target>> bindings;


    // EVENT

    /** Creates a string ID from the given function. */
    static std::string make_id(const target &callback) {
        if (callback.template target<void (*)(A...)>() == nullptr){
            throw std::runtime_error("ERROR: Cannot implicitly generate an ID for a method or lambda!\n"
                                     "Use make_id<T>() on an object to generate a ID for your function!");
        }
        return std::to_string(reinterpret_cast<uintptr_t>(*callback.template target<void (*)(A...)>()));
    }

public:

    // CONSTRUCTOR

    /** Default constructor. */
    explicit event(const size_t capacity = 8) : bindings() {
        bindings.reserve(capacity);
    }


    // OPERATORS

    /** Binds a new function to this event. */
    event &operator+=(const target &callback) {
        bind(callback);
        return *this;
    }

    /** Unbinds the first instance of the given function from this event. */
    event &operator-=(const target &callback) {
        unbind(callback);
        return *this;
    }

    /** Invokes each bound function with the given arguments. */
    void operator()(A... args) {
        invoke(args...);
    }

    /** Invokes each bound function with the given arguments. */
    void operator()(A... args) const {
        invoke(args...);
    }

    // EVENT

    /** Returns an iterator to the beginning of the event. */
    typename std::vector<std::pair<std::string, target>>::const_iterator begin() const {
        return bindings.begin();
    }

    /** Returns an iterator to the end of the event. */
    typename std::vector<std::pair<std::string, target>>::const_iterator end() const {
        return bindings.end();
    }

    /** Returns the total number of bound functions. */
    size_t count() const {
        return bindings.size();
    }

    /** Returns the maximum number of functions that can be bound before resizing. */
    size_t capacity() const {
        return bindings.capacity();
    }

    /** Binds a new function to this event. */
    void bind(const target &callback) {
        bind(make_id(callback), callback);
    }

    /** Binds a new function and its ID to this event. */
    void bind(const std::string &id, const target &callback) {
        if (callback == nullptr) {
            throw std::runtime_error("ERROR: Cannot bind an invalid function to an event!");
        }
        bindings.emplace_back(id, callback);
    }

    /** Unbinds the first bound function that matches the given ID from this event. */
    bool unbind(const std::string &id) {
        const size_t size = bindings.size();
        for (size_t i = 0; i < size; ++i) {
            if (bindings[i].first == id) {
                bindings.erase(bindings.begin() + i);
                return true;
            }
        }
        return false;
    }

    /** Unbinds the first bound function that matches the given function from this event. */
    bool unbind(const target &callback) {
        if (callback == nullptr) {
            return false;
        }
        return unbind(make_id(callback));
    }

    /** Returns whether at least one bound function matches the given ID. */
    bool is_bound(const std::string &id) const {
        for (auto &pair : bindings) {
            if (pair.first == id) {
                return true;
            }
        }
        return false;
    }

    /** Returns whether at least one bound function matches the given function. */
    bool is_bound(const target &callback) const {
        if (callback == nullptr) {
            return false;
        }
        return is_bound(make_id(callback));
    }

    /** Invokes each bound function with the given arguments and returns the most recent function's returned value. */
    void invoke(A... args) {
        for (auto &pair : bindings) {
            if (pair.second == nullptr) {
                throw std::runtime_error("ERROR: Attempted to invoke an invalid function in an event!");
            }
            pair.second(args...);
        }
    }

    /** Invokes each bound function with the given arguments and returns the most recent function's returned value. */
    void invoke(A... args) const {
        for (auto &pair : bindings) {
            if (pair.second == nullptr) {
                throw std::runtime_error("ERROR: Attempted to invoke an invalid function in an event!");
            }
            pair.second(args...);
        }
    }

    /** Unbinds all functions from this event. */
    void clear() {
        bindings.clear();
    }
};

// ID

/** Creates a string ID from the given data's address. */
template <typename T>
static std::string make_id(const T &data) {
    return std::to_string(reinterpret_cast<uintptr_t>(&data));
}

// UNWRAP METHOD

/** Converts the given pointer to a method into a function pointer. */
template <typename I, typename T, typename... A>
static T (*unwrap_method(T (I::*const method)(A...) const))(const I &, A...) {
    return reinterpret_cast<T (*)(const I &, A...)>(method);
}

/** Converts the given pointer to a method into a function pointer. */
template <typename I, typename T, typename... A>
static T (*unwrap_method(T (I::*const method)(A...)))(I &, A...) {
    return reinterpret_cast<T (*)(I &, A...)>(method);
}
