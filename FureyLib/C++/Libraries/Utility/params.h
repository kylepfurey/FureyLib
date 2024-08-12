
// Varadic Argument Macros Script
// by Kyle Furey

#pragma once
#include <vector>
#include <cstdarg>

// Include this heading to use the library
#include "params.h"

// •  Insert this macro with a new parameter to automatically generate a varadic argument.
// •  Use the expand_params() macro to convert the varadic argument into a vector.
#define params(parameter) int argc, parameter ...

// •  Insert this macro with a varadic argument's type and identifier to automatically generate a vector with all of the arguments inside.
// •  The vector's identifier is "argv" and the number of arguments is "argc".
#define expand_params(type, parameter)\
\
va_list _va_list;\
\
va_start(_va_list, argc);\
\
std::vector<type> argv = std::vector<type>();\
\
for (int i = 0; i < argc; i++)\
{\
    argv.push_back(parameter);\
\
    parameter = va_arg(_va_list, type);\
}\
\
parameter = type();\
\
va_end(_va_list);
