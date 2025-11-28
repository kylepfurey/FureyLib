// .h
// Generic Higher-Order Function Library
// by Kyle Furey

#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

/**
 * Declares higher-order functions for the given type:
 * map(), filter(), reduce(), and foreach().
 */
#define DECLARE_FUNCTIONAL(T)\
\
/** Iterates <array> and fills <out> with each element returned by <transform>. */\
static inline T *map_##T(size_t n, const T *array, T(*transform)(const T *), T *out) {\
    assert(array != NULL);\
    assert(transform != NULL);\
    assert(out != NULL);\
    for (size_t i = 0; i < n; ++i) {\
        out[i] = transform(array + i);\
    }\
    return out;\
}\
\
/**\
 * Iterates <array> and fills <out> with each elements that passes <predicate>.\
 * Returns the new size of <out>. \
 */\
static inline size_t filter_##T(size_t n, const T *array, bool(*predicate)(const T *), T *out) {\
    assert(array != NULL);\
    assert(predicate != NULL);\
    size_t count = 0;\
    for (size_t i = 0; i < n; ++i) {\
        if (predicate(array + i)) {\
            ++count;\
            if (out != NULL) {\
                *out++ = array[i];\
            }\
        }\
    }\
    return count;\
}\
\
/** Iterates <array> and returns the final value created by <accumulator>. */\
static inline T reduce_##T(size_t n, const T *array, void(*accumulator)(T*, const T *)) {\
    assert(array != NULL);\
    assert(accumulator != NULL);\
    T final;\
    memset(&final, 0, sizeof(T));\
    for (size_t i = 0; i < n; ++i) {\
        accumulator(&final, array + i);\
    }\
    return final;\
}\
\
/** Iterates <array> and calls <action> on each element. */\
static inline void foreach_##T(size_t n, T *array, void(*action)(T *)) {\
    assert(array != NULL);\
    assert(action != NULL);\
    for (size_t i = 0; i < n; ++i) {\
        action(array + i);\
    }\
}\
\
/** Iterates <array> and calls <action> on each element. */\
static inline void foreach_##T##_const(size_t n, const T *array, void(*action)(const T *)) {\
    assert(array != NULL);\
    assert(action != NULL);\
    for (size_t i = 0; i < n; ++i) {\
        action(array + i);\
    }\
}

#endif // FUNCTIONAL_H
