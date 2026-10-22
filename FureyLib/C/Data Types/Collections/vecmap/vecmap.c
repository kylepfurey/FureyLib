// .c
// Dynamic Array and Hash Map
// by Kyle Furey

#include "vecmap.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

bool vec_resize(vec_t *self, size_t capacity) {
    assert(self != NULL);
    if (capacity == 0) {
        free(self->array);
        *self = (vec_t){0};
        return true;
    }
    if (capacity > SIZE_MAX / sizeof(T)) {
        return false;
    }
    T *result = (T *) realloc(self->array, capacity * sizeof(T));
    if (result == NULL) {
        return false;
    }
    self->array = result;
    self->count = self->count > capacity ? capacity : self->count;
    self->capacity = capacity;
    return true;
}

bool vec_push(vec_t *self, T value) {
    assert(self != NULL);
    if (self->count == self->capacity) {
        if (self->capacity > SIZE_MAX / 2) {
            return false;
        }
        if (!vec_resize(
            self,
            self->capacity >= 4 ? self->capacity * 2 : 4
        )) {
            return false;
        }
    }
    self->array[self->count++] = value;
    return true;
}

T vec_pop(vec_t *self) {
    assert(self != NULL);
    assert(self->count > 0);
    return self->array[--self->count];
}

bool vec_insert(vec_t *self, size_t i, T value) {
    assert(self != NULL);
    assert(i <= self->count);
    if (self->count == self->capacity) {
        if (self->capacity > SIZE_MAX / 2) {
            return false;
        }
        if (!vec_resize(
            self,
            self->capacity >= 4 ? self->capacity * 2 : 4
        )) {
            return false;
        }
    }
    memmove(
        &self->array[i + 1],
        &self->array[i],
        (self->count - i) * sizeof(T)
    );
    self->array[i] = value;
    ++self->count;
    return true;
}

T vec_erase(vec_t *self, size_t i) {
    assert(self != NULL);
    assert(i < self->count);
    T value = self->array[i];
    memmove(
        &self->array[i],
        &self->array[i + 1],
        (self->count - i - 1) * sizeof(T)
    );
    --self->count;
    return value;
}

T vec_get(const vec_t *self, size_t i) {
    assert(self != NULL);
    assert(i < self->count);
    return self->array[i];
}

void vec_set(vec_t *self, size_t i, T value) {
    assert(self != NULL);
    assert(i < self->count);
    self->array[i] = value;
}

void vec_clear(vec_t *self) {
    assert(self != NULL);
    self->count = 0;
}

void vec_free(vec_t *self) {
    assert(self != NULL);
    free(self->array);
    *self = (vec_t){0};
}

static size_t hash(K key) {
    uint32_t h = 2166136261u;
    const uint8_t *bytes = (const uint8_t *) &key;
    for (size_t i = 0; i < sizeof(K); ++i) {
        h ^= bytes[i];
        h *= 16777619u;
    }
    return (size_t) h;
}

static bool equate(K left, K right) {
    return memcmp(&left, &right, sizeof(K)) == 0;
}

bool map_resize(map_t *self, size_t capacity) {
    assert(self != NULL);
    capacity = capacity < self->count ? self->count : capacity;
    if (capacity == 0) {
        free(self->pairs);
        *self = (map_t){0};
        return true;
    }
    pair_t *result = (pair_t *) calloc(capacity, sizeof(pair_t));
    if (result == NULL) {
        return false;
    }
    pair_t *old_pairs = self->pairs;
    size_t old_capacity = self->capacity;
    self->pairs = result;
    self->count = 0;
    self->capacity = capacity;
    for (size_t i = 0; i < old_capacity; ++i) {
        if (old_pairs[i].state == 1) {
            size_t start = hash(old_pairs[i].key) % capacity;
            for (size_t j = 0; j < capacity; ++j) {
                size_t k = (start + j) % capacity;
                if (self->pairs[k].state == 0) {
                    self->pairs[k].key = old_pairs[i].key;
                    self->pairs[k].value = old_pairs[i].value;
                    self->pairs[k].state = 1;
                    ++self->count;
                    break;
                }
            }
        }
    }
    free(old_pairs);
    return true;
}

bool map_insert(map_t *self, K key, V value) {
    assert(self != NULL);
    V *found = map_find(self, key);
    if (found != NULL) {
        *found = value;
        return true;
    }
    if (self->count >= self->capacity / 4 * 3) {
        if (self->capacity > SIZE_MAX / 2) {
            return false;
        }
        if (!map_resize(
            self,
            self->capacity >= 8 ? self->capacity * 2 : 8
        )) {
            return false;
        }
    }
    size_t start = hash(key) % self->capacity;
    size_t j;
    for (size_t i = 0; i < self->capacity; ++i) {
        j = (start + i) % self->capacity;
        if (self->pairs[j].state != 1) {
            break;
        }
    }
    ++self->count;
    self->pairs[j].key = key;
    self->pairs[j].value = value;
    self->pairs[j].state = 1;
    return true;
}

bool map_erase(map_t *self, K key) {
    assert(self != NULL);
    if (self->count == 0) {
        return false;
    }
    size_t start = hash(key) % self->capacity;
    for (size_t i = 0; i < self->capacity; ++i) {
        size_t j = (start + i) % self->capacity;
        if (self->pairs[j].state == 1) {
            if (equate(self->pairs[j].key, key)) {
                self->pairs[j].state = -1;
                --self->count;
                return true;
            }
        } else if (self->pairs[j].state == 0) {
            return false;
        }
    }
    return false;
}

V *map_find(map_t *self, K key) {
    assert(self != NULL);
    return (V *) map_find_const(self, key);
}

const V *map_find_const(const map_t *self, K key) {
    assert(self != NULL);
    if (self->count == 0) {
        return NULL;
    }
    size_t start = hash(key) % self->capacity;
    for (size_t i = 0; i < self->capacity; ++i) {
        size_t j = (start + i) % self->capacity;
        if (self->pairs[j].state == 1) {
            if (equate(self->pairs[j].key, key)) {
                return &self->pairs[j].value;
            }
        } else if (self->pairs[j].state == 0) {
            return NULL;
        }
    }
    return NULL;
}

void map_clear(map_t *self) {
    assert(self != NULL);
    if (self->pairs != NULL) {
        memset(self->pairs, 0, self->capacity * sizeof(pair_t));
        self->count = 0;
    }
}

void map_free(map_t *self) {
    assert(self != NULL);
    free(self->pairs);
    *self = (map_t){0};
}
