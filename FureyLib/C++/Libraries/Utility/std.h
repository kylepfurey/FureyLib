
// Standard Library Declarations Script
// by Kyle Furey

#pragma once
#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <functional>
#include <thread>
#include <typeinfo>

// Include this heading to include and rename standard library classes
#include "std.h"

// STANDARD LIBRARY

template<typename Type>
using shared_pointer = std::shared_ptr<Type>;

template<typename Type>
using unique_pointer = std::unique_ptr<Type>;

template<typename Type>
using weak_pointer = std::weak_ptr<Type>;

using string = std::string;

template<typename Type>
using vector = std::vector<Type>;

template<typename Type>
using list = std::list<Type>;

template<typename KeyType, typename ValueType>
using map = std::map<KeyType, ValueType>;

template<typename ReturnType, typename... ArgumentTypes>
using function = std::function<ReturnType(ArgumentTypes...)>;

using thread = std::thread;
