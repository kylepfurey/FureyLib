
// Red-Black Binary Search Tree Container Script
// by Kyle Furey

// REFERENCES: https://cplusplus.com/reference/set/set/, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.hashset-1?view=net-8.0,
// https://www.geeksforgeeks.org/introduction-to-red-black-tree/

#pragma once
#include <string>
#include <vector>
#include <list>
#include <cstdarg>
#include <initializer_list>

// Include this heading to use the class
#include "red_black_tree.h"

// The color of a node in a red-black binary search tree.
enum red_black_color { black = 0, red = 1 };

// Forward declaration of red_black_node
template<typename data_type> class red_black_node;

// Class that stores unique data, a red or black value, and connections to the left and right nodes in a red-black binary search tree.
template<typename data_type> class red_black_node
{
public:

	// VARIABLES

	// This node's data
	data_type data = data_type();

	// A link to the parent (above) node
	red_black_node<data_type>* parent = nullptr;

	// A link to the left (lesser) node
	red_black_node<data_type>* left = nullptr;

	// A link to the right (greater) node
	red_black_node<data_type>* right = nullptr;

	// Whether this node is red or black
	red_black_color color = red_black_color::red;


	// CONSTRUCTOR

	// Default constructor
	red_black_node(data_type data = data_type(), red_black_color color = red_black_color::red, red_black_node<data_type>* left = nullptr, red_black_node<data_type>* right = nullptr, red_black_node<data_type>* parent = nullptr)
	{
		this->data = data;

		this->color = color;

		this->left = left;

		this->right = right;

		this->parent = parent;
	}


	// FUNCTIONS

	// Searches for the given data by traversing this node's connected nodes and returns the node that matches (or nullptr)
	red_black_node<data_type> binary_search(data_type data)
	{
		red_black_node<data_type>* current = this;

		while (current != nullptr)
		{
			if (current->data == data)
			{
				return current;
			}
			else
			{
				if (data > current->data)
				{
					current = current->left;
				}
				else
				{
					current = current->right;
				}
			}
		}

		return current;
	}

	// Returns the leftmost node of this node
	red_black_node<data_type>* lower_bound()
	{
		red_black_node<data_type>* node = this;

		while (node->left != nullptr)
		{
			node = node->left;
		}

		return node;
	}

	// Returns the root node of this node
	red_black_node<data_type>* root()
	{
		red_black_node<data_type>* node = this;

		while (node->parent != nullptr)
		{
			node = node->parent;
		}

		return node;
	}

	// Returns the rightmost node of this node
	red_black_node<data_type>* upper_bound()
	{
		red_black_node<data_type>* node = this;

		while (node->right != nullptr)
		{
			node = node->right;
		}

		return node;
	}

	// Returns whether this node has no children
	bool is_leaf()
	{
		return left == nullptr && right == nullptr;
	}

	// Returns whether this node is red
	bool is_red()
	{
		return color == red_black_color::red;
	}

	// Returns whether this node is black
	bool is_black()
	{
		return color == red_black_color::black;
	}
};

// Class used to store a sorted red-black binary search tree for fast retrieval of nodes with unique data.
template<typename data_type> class red_black_tree
{
private:

	// VARIABLES

	// The root (starting) node of the binary tree
	red_black_node<data_type>* root = nullptr;

	// The current number of nodes in the binary tree
	int node_size = 0;


	// DEALLOCATION

	// Deallocates the current and connected nodes recursively
	void static deallocate_recursively(red_black_node<data_type>*& current_node)
	{
		if (current_node->left != nullptr)
		{
			deallocate_recursively(current_node->left);
		}

		red_black_node<data_type>* node = current_node;

		if (current_node->right != nullptr)
		{
			deallocate_recursively(current_node->right);
		}

		delete node;
	}

	// Deallocates each of the binary tree's node's memory
	void deallocate()
	{
		if (root != nullptr)
		{
			deallocate_recursively(root);
		}
	}


	// TO ARRAY AND VECTOR

	// Fills an array with this node and all of its children recursively in an array of nodes
	void static fill_array_recursively(int& index, data_type*& current_array, red_black_node<data_type>*& current_node)
	{
		if (current_node->left != nullptr)
		{
			fill_array_recursively(index, current_array, current_node->left);
		}

		current_array[index] = current_node->data;

		index++;

		if (current_node->right != nullptr)
		{
			fill_array_recursively(index, current_array, current_node->right);
		}
	}

	// Pushes this node and all of its children recursively to a vector of nodes
	void static push_vector_recursively(std::vector<data_type>& current_vector, red_black_node<data_type>*& current_node)
	{
		if (current_node->left != nullptr)
		{
			push_vector_recursively(current_vector, current_node->left);
		}

		current_vector.push_back(current_node->data);

		if (current_node->right != nullptr)
		{
			push_vector_recursively(current_vector, current_node->right);
		}
	}


	// INSERTION

	// Inserts the given node and all of the its children recursively to the given tree
	void static insert_children_recursively(red_black_tree<data_type>& current_tree, red_black_node<data_type>*& current_node)
	{
		current_tree.insert(current_node);

		if (current_node->left != nullptr)
		{
			insert_children_recursively(current_tree, current_node->left);
		}

		if (current_node->right != nullptr)
		{
			insert_children_recursively(current_tree, current_node->right);
		}
	}


	// REBALANCING TREE

	// Rotates the given node left relative to its connected nodes
	void rotate_left(red_black_node<data_type>* node)
	{
		if (node == nullptr || node->right == nullptr)
		{
			return;
		}

		red_black_node<data_type>* right = node->right;

		node->right = right->left;

		if (right->left != nullptr)
		{
			right->left->parent = node;
		}

		right->parent = node->parent;

		if (node->parent == nullptr)
		{
			root = right;
		}
		else if (node == node->parent->left)
		{
			node->parent->left = right;
		}
		else
		{
			node->parent->right = right;
		}

		right->left = node;

		node->parent = right;
	}

	// Rotates the given node right relative to its connected nodes
	void rotate_right(red_black_node<data_type>* node)
	{
		if (node == nullptr || node->left == nullptr)
		{
			return;
		}

		red_black_node<data_type>* left = node->left;

		node->left = left->right;

		if (left->right != nullptr)
		{
			left->right->parent = node;
		}

		left->parent = node->parent;

		if (node->parent == nullptr)
		{
			root = left;
		}
		else if (node == node->parent->right)
		{
			node->parent->right = left;
		}
		else
		{
			node->parent->left = left;
		}

		left->right = node;

		node->parent = left;
	}

	// Rebalances the tree's colors based on the given incoming node's relatives
	void rebalance_insertion(red_black_node<data_type>* node)
	{
		if (node->parent->color == red_black_color::red)
		{
			red_black_node<data_type>* uncle = nullptr;

			bool parent_is_right = false;

			if (node->parent->parent->left == node->parent)
			{
				uncle = node->parent->parent->right;

				parent_is_right = false;
			}
			else
			{
				uncle = node->parent->parent->left;

				parent_is_right = true;
			}

			if (uncle != nullptr && uncle->color == red_black_color::red)
			{
				node->parent->color = red_black_color::black;

				uncle->color = red_black_color::black;

				node->parent->parent->color = red_black_color::red;

				if (node->parent->parent != root)
				{
					rebalance_insertion(node->parent->parent);
				}
			}
			else
			{
				red_black_node<data_type>* grandparent = node->parent->parent;

				red_black_color swapped = grandparent->color;

				if (!parent_is_right)
				{
					// LEFT LEFT
					if (node->parent->left == node)
					{
						grandparent->color = node->parent->color;

						node->parent->color = swapped;

						rotate_right(grandparent);
					}
					// LEFT RIGHT
					else
					{
						grandparent->color = node->color;

						node->color = swapped;

						swapped = grandparent->color;

						grandparent->color = node->parent->color;

						node->parent->color = swapped;

						rotate_left(node->parent);

						rotate_right(grandparent);
					}
				}
				else
				{
					// RIGHT RIGHT
					if (node->parent->right == node)
					{
						grandparent->color = node->parent->color;

						node->parent->color = swapped;

						rotate_left(grandparent);
					}
					// RIGHT LEFT
					else
					{
						grandparent->color = node->color;

						node->color = swapped;

						swapped = grandparent->color;

						grandparent->color = node->parent->color;

						node->parent->color = swapped;

						rotate_right(node->parent);

						rotate_left(grandparent);
					}
				}
			}
		}

		root->color = red_black_color::black;
	}

	// Rebalances the tree's colors based on the given removed node's relatives
	void rebalance_removal(red_black_node<data_type>* node, red_black_color removed_color)
	{
		if (node->color == red_black_color::red || removed_color == red_black_color::red)
		{
			node->color = red_black_color::black;

			return;
		}

		while (node->parent != nullptr && node->color == red_black_color::black)
		{
			red_black_node<data_type>* sibling = nullptr;

			if (node == node->parent->left)
			{
				sibling = node->parent->right;

				if (sibling != nullptr)
				{
					if (sibling->color == red_black_color::red)
					{
						sibling->color = red_black_color::black;

						node->parent->color = red_black_color::red;

						rotate_left(node->parent);

						sibling = node->parent->right;

						if (sibling == nullptr)
						{
							node = node->parent;

							continue;
						}
					}

					if ((sibling->left == nullptr || sibling->left->color == red_black_color::black) && (sibling->right == nullptr || sibling->right->color == red_black_color::black))
					{
						sibling->color = red_black_color::red;

						node = node->parent;
					}
					else
					{
						if (sibling->right == nullptr || sibling->right->color == red_black_color::black)
						{
							if (sibling->left != nullptr)
							{
								sibling->left->color = red_black_color::black;
							}

							sibling->color = red_black_color::red;

							rotate_right(sibling);

							sibling = node->parent->right;
						}

						sibling->color = node->parent->color;

						node->parent->color = red_black_color::black;

						if (sibling->right != nullptr)
						{
							sibling->right->color = red_black_color::black;
						}

						rotate_left(node->parent);

						break;
					}
				}
				else
				{
					node = node->parent;
				}
			}
			else
			{
				sibling = node->parent->left;

				if (sibling != nullptr)
				{
					if (sibling->color == red_black_color::red)
					{
						sibling->color = red_black_color::black;

						node->parent->color = red_black_color::red;

						rotate_right(node->parent);

						sibling = node->parent->left;

						if (sibling == nullptr)
						{
							node = node->parent;

							continue;
						}
					}

					if ((sibling->right == nullptr || sibling->right->color == red_black_color::black) && (sibling->left == nullptr || sibling->left->color == red_black_color::black))
					{
						sibling->color = red_black_color::red;

						node = node->parent;
					}
					else
					{
						if (sibling->left == nullptr || sibling->left->color == red_black_color::black)
						{
							if (sibling->right != nullptr)
							{
								sibling->right->color = red_black_color::black;
							}

							sibling->color = red_black_color::red;

							rotate_left(sibling);

							sibling = node->parent->left;
						}

						sibling->color = node->parent->color;

						node->parent->color = red_black_color::black;

						if (sibling->left != nullptr)
						{
							sibling->left->color = red_black_color::black;
						}

						rotate_right(node->parent);

						break;
					}
				}
				else
				{
					node = node->parent;
				}
			}
		}

		root->color = red_black_color::black;
	}

public:

	// TO ARRAY AND VECTOR

	// Returns a sorted array of the current binary tree (MUST BE DEALLOCATED)
	data_type* to_new_array()
	{
		if (node_size == 0)
		{
			return new data_type[0];
		}

		data_type* new_array = new data_type[node_size];

		int index = 0;

		fill_array_recursively(index, new_array, root);

		return new_array;
	}

	// Returns a sorted vector of the current binary tree
	std::vector<data_type> to_vector()
	{
		if (node_size == 0)
		{
			return nullptr;
		}

		std::vector<data_type> new_vector = std::vector<data_type>();

		push_vector_recursively(new_vector, root);

		return new_vector;
	}


	// CONSTRUCTORS

	// Default constructor
	red_black_tree()
	{
		root = nullptr;

		node_size = 0;
	}

	// Copy constructor
	red_black_tree(const red_black_tree<data_type>& copied_tree)
	{
		if (copied_tree.root == nullptr)
		{
			root = nullptr;

			node_size = 0;

			return;
		}

		data_type* array = copied_tree.to_new_array();

		for (int i = 0; i < copied_tree.node_size; i++)
		{
			insert(array[i]);
		}

		delete[] array;

		array = nullptr;
	}

	// Move constructor
	red_black_tree(red_black_tree<data_type>&& moved_tree) noexcept
	{
		root = moved_tree.root;

		node_size = moved_tree.node_size;

		moved_tree.root = nullptr;

		moved_tree.node_size = 0;
	}

	// Data constructor
	red_black_tree(data_type data)
	{
		root = new red_black_node<data_type>(data);

		node_size = 1;
	}

	// Array constructor
	red_black_tree(int array_size, data_type* array)
	{
		if (array_size == 0)
		{
			root = nullptr;

			node_size = 0;

			return;
		}

		for (int i = 0; i < array_size; i++)
		{
			insert(array[i]);
		}
	}

	// Array constructor
	red_black_tree(int argc, data_type array ...)
	{
		if (argc == 0)
		{
			root = nullptr;

			node_size = 0;

			return;
		}

		va_list _va_list;

		va_start(_va_list, argc);

		data_type* argv = new data_type[argc];

		for (int i = 0; i < argc; i++)
		{
			argv[i] = array;

			array = va_arg(_va_list, data_type);
		}

		va_end(_va_list);

		for (int i = 0; i < argc; i++)
		{
			insert(argv[i]);
		}

		delete[] argv;

		argv = nullptr;
	}

	// Vector constructor
	red_black_tree(std::vector<data_type> vector)
	{
		if (vector.size() == 0)
		{
			root = nullptr;

			node_size = 0;

			return;
		}

		for (int i = 0; i < vector.size(); i++)
		{
			insert(vector[i]);
		}
	}

	// Linked list constructor
	red_black_tree(std::list<data_type> list)
	{
		if (list.size() == 0)
		{
			root = nullptr;

			node_size = 0;

			return;
		}

		for (int i = 0; i < list.size(); i++)
		{
			insert(list.begin() + i);
		}
	}

	// List constructor
	red_black_tree(std::initializer_list<data_type> list)
	{
		if (list.size() == 0)
		{
			root = nullptr;

			node_size = 0;

			return;
		}

		for (int i = 0; i < list.size(); i++)
		{
			insert(*(list.begin() + i));
		}
	}

	// Destructor
	virtual ~red_black_tree()
	{
		deallocate();
	}


	// OPERATORS

	// Copy assignment operator
	red_black_tree<data_type>& operator=(const red_black_tree<data_type>& copied_tree)
	{
		deallocate();

		if (copied_tree.root == nullptr)
		{
			root = nullptr;

			node_size = 0;

			return *this;
		}

		data_type* array = copied_tree.to_new_array();

		for (int i = 0; i < copied_tree.node_size; i++)
		{
			insert(array[i]);
		}

		delete[] array;

		array = nullptr;

		return *this;
	}

	// Move assignment operator
	red_black_tree<data_type>& operator=(red_black_tree<data_type>&& moved_tree) noexcept
	{
		deallocate();

		root = moved_tree.root;

		node_size = moved_tree.node_size;

		moved_tree.root = nullptr;

		moved_tree.node_size = 0;

		return *this;
	}


	// EQUALITY

	// Check if another binary tree is equal to the binary tree
	bool equals(red_black_tree<data_type>& compared_tree)
	{
		if (node_size == 0 || compared_tree.node_size == 0)
		{
			return false;
		}

		if (node_size != compared_tree.node_size)
		{
			return false;
		}

		data_type array1 = to_new_array();

		data_type array2 = compared_tree.to_new_array();

		for (int i = 0; i < node_size; i++)
		{
			if (array1[i] != array2[i])
			{
				delete[] array1;

				array1 = nullptr;

				delete[] array2;

				array2 = nullptr;

				return false;
			}
		}

		delete[] array1;

		array1 = nullptr;

		delete[] array2;

		array2 = nullptr;

		return true;
	}

	// Check if another binary tree is equal to the binary tree
	bool operator ==(red_black_tree<data_type>& compared_tree)
	{
		return equals(compared_tree);
	}

	// Check if another binary tree is not equal to the binary tree
	bool operator !=(red_black_tree<data_type>& compared_tree)
	{
		return !equals(compared_tree);
	}


	// ITERATORS

	// Returns the leftmost node in the binary tree
	red_black_node<data_type>* begin()
	{
		red_black_node<data_type>* node = root;

		while (node->left != nullptr)
		{
			node = node->left;
		}

		return node;
	}

	// Returns the root node in the binary tree
	red_black_node<data_type>* middle()
	{
		return root;
	}

	// Returns the rightmost node in the binary tree
	red_black_node<data_type>* end()
	{
		red_black_node<data_type>* node = root;

		while (node->right != nullptr)
		{
			node = node->right;
		}

		return node;
	}


	// CAPACITY

	// Returns whether the binary tree is empty
	bool empty()
	{
		return node_size == 0;
	}

	// Returns the current number of nodes of the binary tree
	int size()
	{
		return node_size;
	}


	// ELEMENT ACCESS

	// Returns the leftmost node's data in the binary tree
	data_type front()
	{
		return begin()->data;
	}

	// Returns the root node's data in the binary tree
	data_type top()
	{
		return root->data;
	}

	// Returns the rightmost node's data in the binary tree
	data_type back()
	{
		return end()->data;
	}

	// Attempts to retrieve the given matching value from this binary tree
	bool try_get(data_type value, data_type& result)
	{
		if (!count(value))
		{
			result = data_type();

			return false;
		}

		result = find(value)->data;

		return true;
	}


	// MODIFIERS

	// Assigns the binary tree's nodes from another binary tree's nodes
	red_black_tree<data_type>& assign(red_black_tree<data_type>& new_data)
	{
		if (new_data.root == nullptr)
		{
			deallocate();

			root = nullptr;

			node_size = 0;

			return *this;
		}

		clear();

		data_type* array = new_data.to_new_array();

		for (int i = 0; i < new_data.node_size; i++)
		{
			insert(array[i]);
		}

		delete[] array;

		array = nullptr;

		return *this;
	}

	// Inserts a new node of the given data into the binary tree
	red_black_node<data_type>* insert(data_type data)
	{
		red_black_node<data_type>* new_node = new red_black_node<data_type>(data);

		insert(new_node);

		return new_node;
	}

	// Inserts a new node of the given data into the binary tree
	red_black_tree<data_type>& insert(red_black_node<data_type>* new_node)
	{
		if (node_size == 0)
		{
			new_node->color = red_black_color::black;

			root = new_node;

			node_size = 1;

			return *this;
		}

		new_node->color = red_black_color::red;

		red_black_node<data_type>* node = root;

		while (!node->is_leaf())
		{
			if (node->data == new_node->data)
			{
				node->data = new_node->data;

				return *this;
			}

			if (node->data > new_node->data)
			{
				if (node->left == nullptr)
				{
					node->left = new_node;

					new_node->parent = node;

					node_size++;

					rebalance_insertion(new_node);

					return *this;
				}
				else
				{
					node = node->left;
				}
			}
			else
			{
				if (node->right == nullptr)
				{
					node->right = new_node;

					new_node->parent = node;

					node_size++;

					rebalance_insertion(new_node);

					return *this;
				}
				else
				{
					node = node->right;
				}
			}
		}

		if (node->data == new_node->data)
		{
			node->data = new_node->data;

			return *this;
		}

		if (node->data > new_node->data)
		{
			node->left = new_node;
		}
		else
		{
			node->right = new_node;
		}

		new_node->parent = node;

		node_size++;

		rebalance_insertion(new_node);

		return *this;
	}

	// Remove, deallocate, and return a node of the given data if it is present
	red_black_node<data_type>* erase(data_type data)
	{
		red_black_node<data_type>* node = find(data);

		erase(node);

		return node;
	}

	// Removes and deallocates a node from the binary tree
	data_type erase(red_black_node<data_type>* removed_node)
	{
		if (!count(removed_node))
		{
			return data_type();
		}

		data_type data = removed_node->data;

		node_size--;

		if (node_size <= 0)
		{
			delete removed_node;

			root = nullptr;

			node_size = 0;

			return data;
		}

		red_black_node<data_type>* replacing_node = nullptr;

		if (removed_node->is_leaf())
		{
			// NIL NODE
			replacing_node = new red_black_node<data_type>();

			replacing_node->color = red_black_color::black;

			replacing_node->parent = removed_node->parent;

			if (removed_node->parent->left == removed_node)
			{
				removed_node->parent->left = replacing_node;
			}
			else
			{
				removed_node->parent->right = replacing_node;
			}

			rebalance_removal(replacing_node, removed_node->color);

			if (replacing_node->parent->left == replacing_node)
			{
				replacing_node->parent->left = nullptr;
			}
			else
			{
				replacing_node->parent->right = nullptr;
			}

			delete replacing_node;

			replacing_node = nullptr;

			delete removed_node;

			return data;
		}
		else if (removed_node->right == nullptr)
		{
			replacing_node = removed_node->left;

			removed_node->left->parent = removed_node->parent;

			if (removed_node != root)
			{
				if (removed_node->parent->left == removed_node)
				{
					removed_node->parent->left = removed_node->left;
				}
				else
				{
					removed_node->parent->right = removed_node->left;
				}
			}
			else
			{
				root = removed_node->left;
			}

			removed_node->left->color = removed_node->color;
		}
		else if (removed_node->left == nullptr)
		{
			replacing_node = removed_node->right;

			removed_node->right->parent = removed_node->parent;

			if (removed_node != root)
			{
				if (removed_node->parent->left == removed_node)
				{
					removed_node->parent->left = removed_node->right;
				}
				else
				{
					removed_node->parent->right = removed_node->right;
				}
			}
			else
			{
				root = removed_node->right;
			}

			removed_node->right->color = removed_node->color;
		}
		else
		{
			red_black_node<data_type>* node = removed_node->right;

			while (node->left != nullptr)
			{
				node = node->left;
			}

			replacing_node = node;

			if (removed_node != root)
			{
				if (removed_node->parent->right == removed_node)
				{
					removed_node->parent->right = node;
				}
				else
				{
					removed_node->parent->left = node;
				}
			}
			else
			{
				root = node;
			}

			if (removed_node->right != node)
			{
				node->parent->left = node->right;

				if (node->right != nullptr)
				{
					node->right->parent = node->parent;
				}

				node->right = removed_node->right;

				removed_node->right->parent = node;
			}

			node->left = removed_node->left;

			removed_node->left->parent = node;

			node->parent = removed_node->parent;

			node->color = removed_node->color;
		}

		rebalance_removal(replacing_node, removed_node->color);

		delete removed_node;

		return data;
	}

	// Remove and return the leftmost node from its connected nodes in the binary tree
	data_type erase_front()
	{
		return erase(front());
	}

	// Remove and return the root node from its connected nodes in the binary tree
	data_type erase_top()
	{
		return erase(root->data);
	}

	// Remove and return the rightmost node from its connected nodes in the binary tree
	data_type erase_back()
	{
		return erase(back());
	}

	// Swaps the binary tree's nodes with another binary tree's nodes
	red_black_tree<data_type>& swap(red_black_tree<data_type>& swapped_data)
	{
		red_black_node<data_type>* data = root;

		int count = node_size;

		root = swapped_data.root;

		node_size = swapped_data.node_size;

		swapped_data.root = data;

		swapped_data.node_size = count;

		return *this;
	}

	// Clears the binary tree's data
	int clear()
	{
		deallocate();

		int total = node_size;

		root = nullptr;

		node_size = 0;

		return total;
	}

	// Creates and inserts a new  node of the given data into the binary tree
	template<typename ... argument_types> red_black_node<data_type>* emplace(argument_types ... arguments)
	{
		red_black_node<data_type>* new_node = new red_black_node<data_type>(data_type(arguments...));

		insert(new_node);

		return new_node;
	}


	// ELEMENT OPERATIONS

	// Finds and an existing node and if successful, removes it and inserts a new node
	red_black_node<data_type>* replace(data_type replaced_data, data_type new_data)
	{
		red_black_node<data_type>* node = find(replaced_data);

		if (node == nullptr)
		{
			return nullptr;
		}

		erase(node);

		insert(new_data);

		return node;
	}

	// Removes the replaced node and inserts the new one
	red_black_tree<data_type>& replace(red_black_node<data_type>* replaced_node, red_black_node<data_type>* new_node)
	{
		erase(replaced_node);

		insert(new_node);

		return *this;
	}


	// OPERATIONS

	// Finds the matching node of the given data if it is present
	red_black_node<data_type>* find(data_type data)
	{
		if (node_size == 0)
		{
			return nullptr;
		}

		red_black_node<data_type>* node = root;

		while (node != nullptr)
		{
			if (node->data == data)
			{
				return node;
			}
			else
			{
				if (node->data > data)
				{
					node = node->left;
				}
				else
				{
					node = node->right;
				}
			}
		}

		return nullptr;
	}

	// Returns whether the binary tree contains the given data
	bool count(data_type contained_data)
	{
		return find(contained_data) != nullptr;
	}

	// Returns whether the binary tree contains the given node
	bool count(red_black_node<data_type>* new_node)
	{
		if (node_size == 0 || new_node == nullptr)
		{
			return false;
		}

		return root == new_node->root();
	}

	// Returns a new tree whose root is of the given node
	static red_black_tree<data_type> subset(red_black_node<data_type>* node)
	{
		red_black_tree<data_type> tree = red_black_tree<data_type>();

		insert_children_recursively(tree, node);

		return tree;
	}

	// Merges the given binary tree into this binary tree
	red_black_tree<data_type>& merge(red_black_tree<data_type>& new_data)
	{
		data_type* array = new_data.to_new_array();

		for (int i = 0; i < new_data.node_size; i++)
		{
			insert(array[i]);
		}

		delete[] array;

		array = nullptr;

		new_data.clear();

		return *this;
	}

	// Returns a copy of the binary tree's data
	red_black_tree<data_type> copy()
	{
		return red_black_tree<data_type>(*this);
	}


	// TO STRING

	// Converts the nodes of the binary tree into a string
	std::string to_string()
	{
		if (node_size == 0)
		{
			return "{ }";
		}

		data_type* data = to_new_array();

		std::string log = "{ ";

		for (int i = 0; i < node_size; i++)
		{
			log += (data[i] + ", ");
		}

		log = log.erase(log.length() - 2, 1);

		log += "}";

		delete[] data;

		data = nullptr;

		return log;
	}

	// Converts the nodes of the linked list into a string
	std::string to_string(std::string(*to_string_function) (data_type))
	{
		if (node_size == 0)
		{
			return "{ }";
		}

		data_type* data = to_new_array();

		std::string log = "{ ";

		for (int i = 0; i < node_size; i++)
		{
			log += (to_string_function(data[i]) + ", ");
		}

		log = log.erase(log.length() - 2, 1);

		log += "}";

		delete[] data;

		data = nullptr;

		return log;
	}
};
