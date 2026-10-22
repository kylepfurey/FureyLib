// .h
// Dynamic Array and Hash Map
// by Kyle Furey

#ifndef VECMAP_H
#define VECMAP_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int T;

typedef struct vec {
    T *array;
    size_t count;
    size_t capacity;
} vec_t;

bool vec_resize (      vec_t *self, size_t capacity  );
bool vec_push   (      vec_t *self,           T value);
   T vec_pop    (      vec_t *self                   );
bool vec_insert (      vec_t *self, size_t i, T value);
   T vec_erase  (      vec_t *self, size_t i         );
   T vec_get    (const vec_t *self, size_t i         );
void vec_set    (      vec_t *self, size_t i, T value);
void vec_clear  (      vec_t *self                   );
void vec_free   (      vec_t *self                   );

typedef int K;
typedef int V;

typedef struct pair {
    K key;
    V value;
    int state;
} pair_t;

typedef struct map {
    pair_t *pairs;
    size_t count;
    size_t capacity;
} map_t;

     bool map_resize     (      map_t *self, size_t capacity);
     bool map_insert     (      map_t *self, K key, V value );
     bool map_erase      (      map_t *self, K key          );
      V * map_find       (      map_t *self, K key          );
const V * map_find_const (const map_t *self, K key          );
     void map_clear      (      map_t *self                 );
     void map_free       (      map_t *self                 );

#ifdef __cplusplus
}
#endif

#endif // VECMAP_H
