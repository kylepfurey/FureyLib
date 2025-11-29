// .h
// Generic Higher-Order Function Library
// by Kyle Furey

#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

#include <stddef.h>
#include <stdbool.h>
#include <assert.h>

/**
 * Declares named higher-order functions for the given array type:
 * map(), filter(), reduce(), and foreach().
 */
#define DECLARE_FUNCTIONAL_NAMED(T, typename)\
\
/**\
 * Iterates <array> and fills <out> with each element returned by <transform>.\
 * Returns <out>. <out> cannot be NULL.\
 */\
static inline T *map_##typename(size_t n, const T *array, T(*transform)(T elem), T *out) {\
    assert(array != NULL);\
    assert(transform != NULL);\
    assert(out != NULL);\
    for (size_t i = 0; i < n; ++i) {\
        out[i] = transform(array[i]);\
    }\
    return out;\
}\
\
/**\
 * Iterates <array> and fills <out> with each elements that passes <predicate>.\
 * Returns the new size of <out>. <out> can be NULL.\
 */\
static inline size_t filter_##typename(size_t n, const T *array, bool(*predicate)(T elem), T *out) {\
    assert(array != NULL);\
    assert(predicate != NULL);\
    size_t count = 0;\
    if (out != NULL) {\
        for (size_t i = 0; i < n; ++i) {\
            if (predicate(array[i])) {\
                out[count++] = array[i];\
            }\
        }\
        return count;\
    }\
    for (size_t i = 0; i < n; ++i) {\
        if (predicate(array[i])) {\
            ++count;\
        }\
    }\
    return count;\
}\
\
/**\
 * Iterates <array>, setting <start> to the result of <accumulator> with <start> and the current element.\
 * Returns the final value created by <accumulator>.\
 */\
static inline T reduce_##typename(size_t n, const T *array, T(*accumulator)(T acc, T elem), T start) {\
    assert(array != NULL);\
    assert(accumulator != NULL);\
    for (size_t i = 0; i < n; ++i) {\
        start = accumulator(start, array[i]);\
    }\
    return start;\
}\
\
/**\
 * Iterates <array> and calls <action> on each element.\
 * <action> returns whether the loop should continue.\
 * <out> is set to the element that stopped the loop.\
 * Returns whether the loop successfully completed. <out> can be NULL. \
 */\
static inline bool foreach_##typename(size_t n, const T *array, bool(*action)(T elem), T *out) {\
    assert(array != NULL);\
    assert(action != NULL);\
    for (size_t i = 0; i < n; ++i) {\
        if (!action(array[i])) {\
            if (out != NULL) {\
                *out = array[i];\
            }\
            return false;\
        }\
    }\
    return true;\
}\
\
/**\
 * Reverses <array> into <out>.\
 * Returns <out>. <out> cannot be NULL.\
 */\
static inline T *reverse_##typename(size_t n, const T *array, T *out) {\
    assert(array != NULL);\
    assert(out != NULL);\
    if (array != out) {\
        for (size_t i = 0; i < n; ++i) {\
            out[i] = array[n - i - 1];\
        }\
        return out;\
    }\
    size_t count = n / 2;\
    for (size_t i = 0; i < count; ++i) {\
        size_t j = n - i - 1;\
        T temp = out[i];\
        out[i] = out[j];\
        out[j] = temp;\
    }\
    return out;\
}

/**
 * Declares higher-order functions for the given array type:
 * map(), filter(), reduce(), and foreach().
 */
#define DECLARE_FUNCTIONAL(T) DECLARE_FUNCTIONAL_NAMED(T, T)

#endif // FUNCTIONAL_H
