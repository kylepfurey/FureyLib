// .hpp
// Generic Stack Buffer Class
// by Kyle Furey

#pragma once
#include <stdexcept>
#include <cstddef>
#include <cstdint>

/** A fixed-sized buffer of a certain type and size. */
template<typename T, size_t N>
class buffer final {
public:

    /** An ID used to locate data within a buffer. */
    using id = size_t;

    /** The value of a buffer ID that indicates the buffer is full. */
    static constexpr id ERROR = static_cast<id>(-1);

    /** The maximum size of this buffer. */
    static constexpr size_t SIZE = N;

private:

    /** The underlying array containing the data of this buffer. */
    uint8_t _buffer[N * sizeof(T)] = {};

    /** A bitset used to check whether data is being stored in this buffer. */
    uint8_t _available[(N + 7) / 8] = {};

    /** The current number of spaces occupied in this buffer. */
    size_t _count = 0;

    /** The next available ID in this buffer. */
    id _next_id = 0;

public:

    /** Returns a reference to the data with the given ID within this buffer, or throws an exception. */
    inline T& operator[](const id id) {
        if (id >= N || (_available[id / 8] & 1u << (id % 8)) == 0) {
            throw std::runtime_error("ERROR: Invalid ID when accessing buffer!");
        }
        return reinterpret_cast<T*>(_buffer)[id];
    }

    /** Returns a const reference to the data with the given ID within this buffer, or throws an exception. */
    inline const T& operator[](const id id) const {
        if (id >= N || (_available[id / 8] & 1u << (id % 8)) == 0) {
            throw std::runtime_error("ERROR: Invalid ID when accessing buffer!");
        }
        return reinterpret_cast<const T*>(_buffer)[id];
    }

    /** Allocates a new zeroed-out buffer. */
    inline buffer() {
    }

    /** Returns a const pointer to the underlying array containing the data of this buffer. */
    inline const T* data() const {
        return reinterpret_cast<const T*>(_buffer);
    }

    /** Returns a const pointer to the bitset used to check whether data is being stored in this buffer. */
    inline const uint8_t* available() const {
        return _available;
    }

    /** Returns the current number of spaces occupied in this buffer. */
    inline size_t count() const {
        return _count;
    }

    /** Returns the next available ID in this buffer. */
    inline id next_id() const {
        return _next_id;
    }

    /** Inserts new data into this buffer and returns its ID, or buffer<T, N>::ERROR if the buffer is full. */
    template<typename ... A>
    inline id insert(const A... args) {
        if (_count >= N) {
            return ERROR;
        }
        const id id = _next_id++;
        new(&reinterpret_cast<T*>(_buffer)[id]) T(args...);
        _available[id / 8] |= 1u << (id % 8);
        ++_count;
        while (_next_id < N && (_available[_next_id / 8] & 1u << (_next_id % 8)) != 0) {
            ++_next_id;
        }
        return id;
    }

    /** Erases the data in this buffer with the given ID and returns whether it was successful. */
    inline bool erase(const id id) {
        if (id >= N || (_available[id / 8] & 1u << (id % 8)) == 0) {
            return false;
        }
        reinterpret_cast<T*>(_buffer)[id].~T();
        _available[id / 8] &= ~(1u << (id % 8));
        --_count;
        _next_id = id < _next_id ? id : _next_id;
        return true;
    }

    /** Returns a pointer to the data in this buffer with the given ID, or nullptr if no data exists. */
    inline T* find(const id id) {
        if (id >= N || (_available[id / 8] & 1u << (id % 8)) == 0) {
            return nullptr;
        }
        return &reinterpret_cast<T*>(_buffer)[id];
    }

    /** Returns a const pointer to the data in this buffer with the given ID, or nullptr if no data exists. */
    inline const T* find(const id id) const {
        if (id >= N || (_available[id / 8] & 1u << (id % 8)) == 0) {
            return nullptr;
        }
        return &reinterpret_cast<const T*>(_buffer)[id];
    }

    /** Returns whether this buffer has data associated with the given ID. */
    inline bool contains(const id id) const {
        if (id >= N) {
            return false;
        }
        return (_available[id / 8] & 1u << (id % 8)) != 0;
    }

    /** Clears this buffer. */
    inline size_t clear() {
        const size_t count = _count;
        for (size_t i = 0; i < N; ++i) {
            if ((_available[i / 8] & 1u << (i % 8)) != 0) {
                reinterpret_cast<T*>(_buffer)[i].~T();
            }
        }
        for (size_t i = 0; i < (N + 7) / 8; ++i) {
            _available[i] = 0;
        }
        _count = 0;
        _next_id = 0;
        return count;
    }

    /** Iterates through this buffer with the given function and returns whether the iteration successfully completed. */
    inline bool foreach(bool(* const action)(T*)) {
        size_t count = _count;
        for (id id = 0; id < N && count > 0; ++id) {
            if ((_available[id / 8] & 1u << (id % 8)) != 0) {
                --count;
                if (!action(&reinterpret_cast<T*>(_buffer)[id])) {
                    return false;
                }
            }
        }
        return true;
    }

    /** Iterates through this buffer with the given const function and returns whether the iteration successfully completed. */
    inline bool foreach(bool(* const action)(const T*)) const {
        size_t count = _count;
        for (id id = 0; id < N && count > 0; ++id) {
            if ((_available[id / 8] & 1u << (id % 8)) != 0) {
                --count;
                if (!action(&reinterpret_cast<const T*>(_buffer)[id])) {
                    return false;
                }
            }
        }
        return true;
    }

    /** Iterates through this buffer with the given lambda and returns whether the iteration successfully completed. */
    template<typename F>
    inline bool foreach(F&& action) {
        size_t count = _count;
        for (id id = 0; id < N && count > 0; ++id) {
            if ((_available[id / 8] & 1u << (id % 8)) != 0) {
                --count;
                if (!action(&reinterpret_cast<T*>(_buffer)[id])) {
                    return false;
                }
            }
        }
        return true;
    }

    /** Iterates through this buffer with the given const lambda and returns whether the iteration successfully completed. */
    template<typename F>
    inline bool foreach(F&& action) const {
        size_t count = _count;
        for (id id = 0; id < N && count > 0; ++id) {
            if ((_available[id / 8] & 1u << (id % 8)) != 0) {
                --count;
                if (!action(&reinterpret_cast<const T*>(_buffer)[id])) {
                    return false;
                }
            }
        }
        return true;
    }
};
