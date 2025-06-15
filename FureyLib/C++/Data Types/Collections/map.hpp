// .hpp
// Hash Map Type
// by Kyle Furey

#pragma once
#include <vector>
#include <list>
#include <utility>
#include <cstdlib>

// The max number of elements that can be contained within a bucket before rehashing a map.
#define BUCKET_CAPACITY 3


// MAP

/** Key-value hash map collection. */
template <typename K, typename V>
class map final {

    // PAIR

    /** A key, its hash, and its value. */
    struct pair {

        // DATA

        /** The hash of this pair's key. */
        const size_t hash;

        /** A copy of this pair's key. */
        const K key;

        /** This pair's value. */
        V value;
    };


    // DATA

    /** The number of pairs in the map. */
    size_t count;

    /** An array of buckets holding each key-value pair. */
    std::vector<std::list<pair>> pairs;

public:

    // CONSTRUCTOR

    /** Default constructor. */
    map(const size_t buckets = 16) : count(0), pairs(buckets) {
    }


    // MAP

    /** Returns the number of pairs. */
    size_t size() const {
        return count;
    }

    /** Returns the number of buckets. */
    size_t buckets() const {
        return pairs.size();
    }

    /** Moves all elements to a new set of buckets. */
    void rehash(const size_t buckets) {
        if (buckets == 0 || buckets == pairs.size()) {
            return;
        }
        std::vector<std::list<pair>> new_pairs(buckets);
        for (auto &bucket : pairs) {
            for (auto &elem : bucket) {
                const size_t index = elem.hash % new_pairs.size();
                new_pairs[index].push_back(elem);
            }
        }
        pairs = std::move(new_pairs);
    }

    /** Returns a pointer to the value with the given key (or nullptr). */
    V *find(const K &key) {
        const size_t hash = std::hash<K>{}(key);
        const size_t index = hash % pairs.size();
        for (auto &elem : pairs[index]) {
            if (elem.hash == hash && elem.key == key) {
                return &elem.value;
            }
        }
        return nullptr;
    }

    /** Returns a pointer to the value with the given key (or nullptr). */
    const V *find(const K &key) const {
        const size_t hash = std::hash<K>{}(key);
        const size_t index = hash % pairs.size();
        for (auto &elem : pairs[index]) {
            if (elem.hash == hash && elem.key == key) {
                return &elem.value;
            }
        }
        return nullptr;
    }

    /** Returns whether the map contains the given key. */
    bool contains(const K &key) const {
        return find(key) != nullptr;
    }

    /** Inserts a new pair with the given key and value. */
    V &insert(const K &key, const V &value) {
        const size_t hash = std::hash<K>{}(key);
        size_t index = hash % pairs.size();
        for (auto &elem : pairs[index]) {
            if (elem.hash == hash && elem.key == key) {
                elem.value = value;
                return elem.value;
            }
        }
        if (pairs[index].size() + 1 > BUCKET_CAPACITY) {
            rehash(pairs.size() * 2);
            index = hash % pairs.size();
        }
        ++count;
        pairs[index].push_back(pair{hash, key, value});
        return pairs[index].back().value;
    }

    /** Removes the pair that matches the given key. */
    bool erase(const K &key) {
        const size_t hash = std::hash<K>{}(key);
        const size_t index = hash % pairs.size();
        auto iter = pairs[index].begin();
        for (auto &elem : pairs[index]) {
            if (elem.hash == hash && elem.key == key) {
                pairs[index].erase(iter);
                --count;
                return true;
            }
            ++iter;
        }
        return false;
    }

    /** Clears the map of all its pairs. */
    void clear() {
        for (auto &bucket : pairs) {
            bucket.clear();
        }
        count = 0;
    }

    /** Returns a reference to the value of a pair that matches the given key. */
    V &operator[](const K &key) {
        const size_t hash = std::hash<K>{}(key);
        size_t index = hash % pairs.size();
        for (auto &elem : pairs[index]) {
            if (elem.hash == hash && elem.key == key) {
                return elem.value;
            }
        }
        if (pairs[index].size() + 1 > BUCKET_CAPACITY) {
            rehash(pairs.size() * 2);
            index = hash % pairs.size();
        }
        ++count;
        pairs[index].push_back(pair{hash, key, V()});
        return pairs[index].back().value;
    }
};
