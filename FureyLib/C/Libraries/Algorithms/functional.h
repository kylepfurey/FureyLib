// .h
// Generic Higher-Order Function Library
// by Kyle Furey

#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
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
 * Returns the new size of <out>.\
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
static inline T reduce_##T(size_t n, const T *array, void(*accumulator)(T *, const T *), T start) {\
    assert(array != NULL);\
    assert(accumulator != NULL);\
    for (size_t i = 0; i < n; ++i) {\
        accumulator(&start, array + i);\
    }\
    return start;\
}\
\
/**\
 * Iterates <array> and calls <action> on each element.\
 * <action> returns whether the foreach should continue.\
 * Returns whether element that stopped the loop or NULL.\
 */\
static inline T *foreach_##T(size_t n, T *array, bool(*action)(T *)) {\
    assert(array != NULL);\
    assert(action != NULL);\
    for (size_t i = 0; i < n; ++i) {\
        T *elem = array + i;\
        if (!action(elem)) {\
            return elem;\
        }\
    }\
    return NULL;\
}\
\
/**\
 * Iterates <array> and calls <action> on each element.\
 * <action> returns whether the foreach should continue.\
 * Returns whether element that stopped the loop or NULL.\
 */\
static inline const T *foreach_##T##_const(size_t n, const T *array, bool(*action)(const T *)) {\
    assert(array != NULL);\
    assert(action != NULL);\
    for (size_t i = 0; i < n; ++i) {\
        const T *elem = array + i;\
        if (!action(elem)) {\
            return elem;\
        }\
    }\
    return NULL;\
}\
\
/** Reverses <array>. */\
static inline T *reverse_##T(size_t n, T *array) {\
    assert(array != NULL);\
    size_t count = n / 2;\
    for (size_t i = 0; i < count; ++i) {\
        size_t j = n - i - 1;\
        T temp = array[i];\
        array[i] = array[j];\
        array[j] = temp;\
    }\
    return array;\
}

#endif // FUNCTIONAL_H
