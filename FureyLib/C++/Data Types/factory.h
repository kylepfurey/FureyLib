
// Factory Class Script
// by Kyle Furey

#pragma once

// Include this heading to use the class.
#include "factory.h"

// Provides three functions used for easy instantiation of derived objects.
template<typename base_class = void> class factory
{
public:

	// INSTANTIATION

	// Instantiates a new object of the given derived type.
	template <typename derived_type, typename ... argument_types> static derived_type instantiate(argument_types ... arguments)
	{
		return derived_type(arguments...);
	}

	// Instantiates a new derived object of the given template.
	template <typename derived_type> static derived_type instantiate(derived_type _template)
	{
		return derived_type(_template);
	}

	// Instantiates a new derived object of the given template.
	template <typename derived_type> static derived_type instantiate(derived_type* _template)
	{
		return derived_type(*_template);
	}
};
