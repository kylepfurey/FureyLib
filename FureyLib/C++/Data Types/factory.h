
// Object Factory Class Script
// by Kyle Furey

#include <list>
#include <algorithm>
#include "object.h"

// Include this heading to use the class.
#include "factory.h"

// The default base type used in factory classes.
#define FACTORY_BASE object

// Provides easy and safe instantiation of new dynamically allocated derived objects from a base type.
template<typename base_type = FACTORY_BASE> class factory
{
public:

	// OBJECTS

	// All dynamically allocated objects.
	std::list<base_type*> objects = std::list<base_type*>();


	// INSTANTIATE

	// Instantiates a new derived object of the given type.
	template<typename derived_type = FACTORY_BASE, typename ... argument_types> derived_type* instantiate(argument_types ... arguments)
	{
		derived_type* instantiated = new derived_type(arguments...);

		objects.push_back(instantiated);

		return instantiated;
	}


	// DESTROY

	// Manually deallocates the given factory object.
	template<typename derived_type = FACTORY_BASE> void destroy(derived_type*& destroyed)
	{
		if (destroyed == nullptr)
		{
			return;
		}

		auto item = std::find(objects.begin(), objects.end(), destroyed);

		if (item != objects.end())
		{
			objects.erase(item);
		}

		delete destroyed;

		destroyed = nullptr;
	}

	// Deallocates all of the objects in the factory and return its previous size.
	int destroy_all()
	{
		int size = objects.size();

		for (auto destroyed : objects)
		{
			delete destroyed;
		}

		objects.clear();

		return size;
	}


	// SIZE

	// Returns the current size of the factory.
	int size()
	{
		return objects.size();
	}


	// CONTAINS

	// Returns whether the given factory object is present in this factory.
	template<typename derived_type = FACTORY_BASE> bool contains(derived_type* found)
	{
		if (found == nullptr)
		{
			return false;
		}

		return std::find(objects.begin(), objects.end(), found) != objects.end();
	}


	// CONSTRUCTORS AND DESTRUCTOR

	// Default constructor.
	factory()
	{
		objects = std::list<base_type*>();
	}

	// Remove copy constructor.
	factory(const factory& copied) = delete;

	// Move constructor.
	factory(factory&& moved)
	{
		objects = moved.objects();

		moved.objects.clear();
	}

	// Deallocates all of the factory’s objects.
	virtual ~factory()
	{
		destroy_all();
	}


	// OPERATORS

	// Remove copy assignment operator.
	factory<base_type>& operator=(const factory& copied) = delete;

	// Move assignment operator.
	factory<base_type>& operator=(factory&& moved)
	{
		objects = moved.objects();

		moved.objects.clear();

		return *this;
	}
};
