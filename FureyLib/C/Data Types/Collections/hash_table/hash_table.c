// .c
// C Hash Table Collection Script
// by Kyle Furey

#include "hash_table.h"

// CONSTRUCTORS AND DESTRUCTOR

// Initializes a new hash table with the given hash function.
// A NULL hash function uses the default_hash() function.
hash_table hash_table_new(const size_t size_of_type, const size_t bucket_count, const hash (*hash_func)(const void *)) {
    hash_table self = {
        size_of_type,
        0,
        bucket_count,
        calloc(bucket_count, sizeof(hash_pair)),
        hash_func != NULL ? hash_func : default_hash,
    };

    if (self.buckets == NULL) {
        self.bucket_count = 0;
    }

    return self;
}

// Properly destroys the given hash table.
void hash_table_free(hash_table *self) {
    if (self == NULL || self->buckets == NULL) {
        return;
    }

    for (size_t i = 0; i < self->bucket_count; ++i) {
        free(self->buckets[i].value);

        self->buckets[i].hash = 0;
        self->buckets[i].value = NULL;
    }

    free(self->buckets);

    self->size = 0;
    self->bucket_count = 0;
    self->buckets = NULL;
}

// FUNCTIONS

// Expands the hash table to have at least the given number of buckets.
// The new bucket count must successfully hold all values.
// All values are rehashed back into the expanded table to ensure values are retained with unique keys.
// Returns true if the hash table was successfully expanded.
bool hash_table_rehash(hash_table *self, const size_t new_bucket_count) {
    if (self == NULL || self->bucket_count >= new_bucket_count) {
        return false;
    }

    hash_pair *new_buckets = calloc(new_bucket_count, sizeof(hash_pair));
    if (new_buckets == NULL) {
        return false;
    }

    for (size_t i = 0; i < self->bucket_count; ++i) {
        if (self->buckets[i].value != NULL) {
            const hash_pair new_pair = {self->buckets[i].hash, self->buckets[i].value};
            new_buckets[self->buckets[i].hash % new_bucket_count] = new_pair;
        }
    }

    free(self->buckets);

    self->buckets = new_buckets;

    self->bucket_count = new_bucket_count;

    return true;
}

// Clears the hash table of all its values.
void hash_table_clear(hash_table *self) {
    if (self == NULL || self->buckets == NULL) {
        return;
    }

    for (size_t i = 0; i < self->bucket_count; ++i) {
        self->buckets[i].hash = 0;

        free(self->buckets[i].value);

        self->buckets[i].value = NULL;
    }

    self->size = 0;
}

// Inserts a new value into the hash table using the given hashed key.
// Returns a pointer to the new value or an existing value if a matching key was found.
// Returns NULL if the insertion failed.
void *hash_table_insert(hash_table *self, const void *key) {
    if (self == NULL || key == NULL) {
        return NULL;
    }

    const hash hash = self->hash_func(key);

    hash_pair *pair = &self->buckets[hash % self->bucket_count];

    if (pair->value != NULL) {
        if (pair->hash == hash) {
            return pair->value;
        }

        do {
            if (!hash_table_rehash(self, self->bucket_count > 0 ? self->bucket_count * 2 : 1)) {
                return NULL;
            }

            pair = &self->buckets[hash % self->bucket_count];
        } while (pair->value != NULL);
    }

    pair->value = malloc(self->element_size);
    if (pair->value == NULL) {
        return NULL;
    }

    pair->hash = hash;

    ++self->size;

    return pair->value;
}

// Erases the value within the hash table that matches the given hashed key.
// Returns whether a value was successfully erased.
bool hash_table_erase(hash_table *self, const void *key) {
    if (self == NULL || self->buckets == NULL || key == NULL) {
        return false;
    }

    const hash hash = self->hash_func(key) % self->bucket_count;

    if (self->buckets[hash].value == NULL) {
        return false;
    }

    --self->size;

    self->buckets[hash].hash = 0;

    free(self->buckets[hash].value);

    self->buckets[hash].value = NULL;

    return true;
}

// Locates the value within the hash table that matches the given hashed key.
// Returns a pointer to the matching value or NULL if no match was found.
void *hash_table_find(const hash_table *self, const void *key) {
    if (self == NULL || self->buckets == NULL || key == NULL) {
        return NULL;
    }

    const hash hash = self->hash_func(key);

    if (self->buckets[hash % self->bucket_count].hash == hash) {
        return self->buckets[hash % self->bucket_count].value;
    }

    return NULL;
}

// Copies all the hash table's values into a new array.
// NOTE: This array must be freed!
void *hash_table_values(const hash_table *self) {
    if (self == NULL || self->buckets == NULL) {
        return NULL;
    }

    void *array = malloc(self->element_size * self->size);
    if (array == NULL) {
        return NULL;
    }

    size_t i = 0;
    for (size_t j = 0; j < self->bucket_count; ++j) {
        if (self->buckets[j].value != NULL) {
            memcpy(array + i * self->element_size, self->buckets[j].value, self->element_size);
            ++i;
        }
    }

    return array;
}

// The default hash function.
// This simply reads the first byte of the given data.
hash default_hash(const void *key) {
    if (key == NULL) {
        return 0;
    }

    return *(int8_t *) key;
}
