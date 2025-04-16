// .h
// Tree Type
// by Kyle Furey

#pragma once
#include "Box.h"

/** A collection of useful collection types in C++. */
namespace Toolbox {

	// TREE

	/** */
	template<typename Type, size_t DIMENSIONS = 2, typename PrecisionType = double>
	class Tree final {

		// NODE

		/** */
		struct Node final {
		private:

			// DATA

		public:

			// CONSTRUCTOR
		};


		// DATA

	public:

		// CONSTRUCTOR
	};


	// TREE TYPES

	/** */
	template<typename Type>
	using BinaryTree = Tree<Type, 1, double>;

	/** */
	template<typename Type>
	using Quadtree = Tree<Type, 2, double>;

	/** */
	template<typename Type>
	using Octree = Tree<Type, 3, double>;
}
