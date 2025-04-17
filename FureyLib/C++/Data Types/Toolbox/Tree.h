// .h
// Tree Type
// by Kyle Furey

#pragma once
#include "Vector.h"
#include "Math.h"
#include "Box.h"

// The maximum number of pairs a tree with N total dimensions can store before dividing.
#define TREE_CAPACITY(N) (N * 2)

// The maximum possible distance value.
#define DISTANCE_MAX DBL_MAX

/** A collection of useful collection types in C++. */
namespace Toolbox {

	// TREE

	/** A collection of elements assigned a location and stored within a partition to be easily found and stored with other elements. */
	template<typename Type, size_t DIMENSIONS = 2, typename PrecisionType = double>
	class Tree final {
	public:

		// POINT AND BOX

		/** Represents a point in space with variable dimensions. */
		using Point = Point<DIMENSIONS, PrecisionType>;

		/** Represents an axis-aligned bounding box with a center point and extensions used for collisions and intersections. */
		using Box = Box<DIMENSIONS, PrecisionType>;


		// PAIR

		/** Arbitrary data and a position value placed into a partition. */
		struct Pair final {

			// DATA

			/** This pair's owned data. */
			Type Data;

		private:

			// DATA

			/** The position of this data used to assign a parition. */
			Point position;

		public:

			// CONSTRUCTOR

			/** Default constructor. */
			Pair(const Type& Data = Type(), const Point& Position = Point()) : Data(Data), position(Position) {
			}


			// GETTERS

			/** Returns the position of this data. */
			const Point& Position() const {
				return position;
			}


			// OPERATORS

			/** Returns whether the given pair is equal to this pair. */
			bool operator==(const Pair& Other) {
				return this == &Other;
			}

			/** Returns whether the given pair is not equal to this pair. */
			bool operator!=(const Pair& Other) {
				return this != &Other;
			}
		};

	private:

		// NODE

		/** Represents a partition with child nodes representing smaller parititons. */
		struct Node final {
		private:

			// DATA

			/** The data this node owns and where it is located. */
			Vector<Pair> pairs;

			/** The area this node covers, as well as the area all its children are in. */
			Box bounds;

			/** Whether this node has been divided and has children. */
			bool divided;

			/** Each child node of this node. */
			Node* children[1 << DIMENSIONS];


			// PARTITION

			/** Divides the node partition into child nodes. */
			bool Divide() {
				if (!divided) {
					for (size_t Index = 0; Index < (1 << DIMENSIONS); ++Index) {
						Point NewOrigin;
						for (size_t Component = 0; Component < DIMENSIONS; ++Component) {
							// SOURCE: ChatGPT - "How can I divide a templated N dimensional quadtree in C++?"
							NewOrigin[Component] = bounds.Origin[Component] + ((Index & (1 << Component)) ? (bounds.HalfSize / 2) : -(bounds.HalfSize / 2));
						}
						children[Index] = new Node(Box(NewOrigin, bounds.HalfSize / 2));
					}
					divided = true;
					return true;
				}
				return false;
			}


			// GETTERS

			/** Recursively counts each pair. */
			void RecursiveCount(size_t& Count) const {
				if (divided) {
					for (size_t Index = 0; Index < (1 << DIMENSIONS); ++Index) {
						children[Index]->RecursiveCount(Count);
					}
				}
				for (auto& Pair : pairs) {
					++Count;
				}
			}

			/** Recursively traverses as deep as possible into the node's children. */
			void RecursiveDepth(size_t CurrentDepth, size_t& Depth) const {
				if (divided) {
					for (size_t Index = 0; Index < (1 << DIMENSIONS); ++Index) {
						children[Index]->RecursiveDepth(CurrentDepth + 1, Depth);
					}
				}
				if (CurrentDepth > Depth) {
					++Depth;
				}
			}

			/** Recursively searches the node's children for points nearby the given position. */
			void RecursiveFindAll(const Point& Position, Vector<Pair*>& Query) {
				if (divided) {
					for (size_t Index = 0; Index < (1 << DIMENSIONS); ++Index) {
						if (children[Index]->Bounds().Contains(Position)) {
							children[Index]->RecursiveFindAll(Position, Query);
						}
					}
				}
				for (auto& Pair : pairs) {
					Query.PushBack(&Pair);
				}
			}

			/** Recursively searches the node's children for points nearby the given position. */
			void RecursiveFindAll(const Point& Position, Vector<const Pair*>& Query) const {
				if (divided) {
					for (size_t Index = 0; Index < (1 << DIMENSIONS); ++Index) {
						if (children[Index]->Bounds().Contains(Position)) {
							children[Index]->RecursiveFindAll(Position, Query);
						}
					}
				}
				for (auto& Pair : pairs) {
					Query.PushBack(&Pair);
				}
			}

			/** Recursively searches the node's children for points within the given area. */
			void RecursiveQuery(const Box& Area, Vector<Pair*>& Query) {
				if (!bounds.Intersects(Area)) {
					return;
				}
				if (divided) {
					for (size_t Index = 0; Index < (1 << DIMENSIONS); ++Index) {
						children[Index]->RecursiveQuery(Area, Query);
					}
				}
				for (auto& Pair : pairs) {
					if (Area.Contains(Pair.Position())) {
						Query.PushBack(&Pair);
					}
				}
			}

			/** Recursively searches the node's children for points within the given area. */
			void RecursiveQuery(const Box& Area, Vector<const Pair*>& Query) const {
				if (!bounds.Intersects(Area)) {
					return;
				}
				if (divided) {
					for (size_t Index = 0; Index < (1 << DIMENSIONS); ++Index) {
						children[Index]->RecursiveQuery(Area, Query);
					}
				}
				for (auto& Pair : pairs) {
					if (Area.Contains(Pair.Position())) {
						Query.PushBack(&Pair);
					}
				}
			}

			/** Recursively appends pointers to this node's and its children's pairs to a vector. */
			void RecursiveAllPairs(Vector<Pair*>& Pairs) {
				if (divided) {
					for (size_t Index = 0; Index < (1 << DIMENSIONS); ++Index) {
						children[Index]->RecursivePairs(Pairs);
					}
				}
				for (auto& Pair : pairs) {
					Pairs.PushBack(&Pair);
				}
			}

			/** Recursively appends constant pointers to this node's and its children's pairs to a vector. */
			void RecursiveAllPairs(Vector<const Pair*>& Pairs) const {
				if (divided) {
					for (size_t Index = 0; Index < (1 << DIMENSIONS); ++Index) {
						children[Index]->RecursivePairs(Pairs);
					}
				}
				for (auto& Pair : pairs) {
					Pairs.PushBack(&Pair);
				}
			}


			// EXPANSION

			/** Recursively inserts a new node into its child nodes. */
			Pair* RecursiveInsert(const Type& Data, const Point& Position) {
				if (!bounds.Contains(Position)) {
					return nullptr;
				}
				if (pairs.Size() < pairs.Capacity()) {
					return &pairs.PushBack(Pair(Data, Position));
				}
				if (!divided) {
					Divide();
				}
				for (size_t Index = 0; Index < (1 << DIMENSIONS); ++Index) {
					Pair* Result = children[Index]->RecursiveInsert(Data, Position);
					if (Result != nullptr) {
						return Result;
					}
				}
				return nullptr;
			}


			// TO STRING

			/** Recursively appends the string representations of this node's children. */
			void RecursiveToString(const size_t Depth, std::string& String) const {
				for (auto& Pair : pairs) {
					for (size_t Index = 0; Index <= Depth; ++Index) {
						String += '\t';
					}
					String += "( " + std::to_string(Pair.Data) + " : " + Pair.Position().ToString() + " ),\n";
				}
				if (String[String.length() - 2] == ',') {
					String.erase(String.length() - 2, 1);
					String += '\n';
				}
				if (divided) {
					for (size_t Index = 0; Index < (1 << DIMENSIONS); ++Index) {
						children[Index]->RecursiveToString(Depth + 1, String);
					}
				}
			}

		public:

			// CONSTRUCTORS AND DESTRUCTOR

			/** Default constructor. */
			Node(const Box& Bounds = Box()) : pairs(), bounds(Bounds), divided(false), children() {
				pairs.Resize(TREE_CAPACITY(DIMENSIONS));
				for (size_t Index = 0; Index < (1 << DIMENSIONS); ++Index) {
					children[Index] = nullptr;
				}
			}

			/** Delete copy constructor. */
			Node(const Node&) = delete;

			/** Delete move constructor. */
			Node(Node&&) noexcept = delete;

			/** Destructor. */
			~Node() {
				for (size_t Index = 0; Index < (1 << DIMENSIONS); ++Index) {
					delete children[Index];
					children[Index] = nullptr;
				}
			}


			// OPERATORS

			/** Delete copy assignment operator. */
			Node& operator=(const Node&) = delete;

			/** Delete move assignment operator. */
			Node& operator=(Node&&) noexcept = delete;


			// GETTERS

			/** Returns the total number of pairs of this node and its children. */
			size_t Count() const {
				size_t Count = 0;
				RecursiveCount(Count);
				return Count;
			}

			/** Returns the current depth of this node's children. */
			size_t Depth() const {
				size_t Depth = 0;
				RecursiveDepth(0, Depth);
				return Depth;
			}

			/** Returns each of this node's stored pairs. */
			const Vector<Pair>& Pairs() const {
				return pairs;
			}

			/** Returns the bounds of this node. */
			const Box& Bounds() {
				return bounds;
			}

			/** Returns whether this node is divided and has children. */
			bool IsDivided() const {
				return divided;
			}

			/** Returns the total number of children of this node. */
			size_t ChildCount() const {
				return 1 << DIMENSIONS;
			}

			/** Returns a constant pointer to all of the node's children. */
			const Node** Children() const {
				return divided ? children : nullptr;
			}

			/** Returns a pointer to the child node at the given index, or nullptr if it has not been divided. */
			Node* GetChild(const size_t Index) {
				if (Index >= (1 << DIMENSIONS)) {
					throw std::runtime_error(std::string("ERROR: Index was out of bounds of the tree's maximum child count of ") + std::to_string(1 << DIMENSIONS) + "!");
				}
				if (!divided) {
					return nullptr;
				}
				return children[Index];
			}

			/** Returns a constant pointer to the child node at the given index, or nullptr if it has not been divided. */
			const Node* GetChild(const size_t Index) const {
				if (Index >= (1 << DIMENSIONS)) {
					throw std::runtime_error(std::string("ERROR: Index was out of bounds of the tree's maximum child count of ") + std::to_string(1 << DIMENSIONS) + "!");
				}
				if (!divided) {
					return nullptr;
				}
				return children[Index];
			}

			/** Returns a pointer to the child node at the given corner of the partition, or nullptr if it has not been divided. */
			Node* GetChild(const bool PositiveDimensions[DIMENSIONS]) {
				if (!divided) {
					return nullptr;
				}
				size_t Child = 0;
				for (size_t Index = 0; Index < DIMENSIONS; ++Index) {
					if (PositiveDimensions[Index]) {
						Child |= (1 << Index);
					}
				}
				return children[Child];
			}

			/** Returns a constant pointer to the child node at the given corner of the partition, or nullptr if it has not been divided. */
			const Node* GetChild(const bool PositiveDimensions[DIMENSIONS]) const {
				if (!divided) {
					return nullptr;
				}
				size_t Child = 0;
				for (size_t Index = 0; Index < DIMENSIONS; ++Index) {
					if (PositiveDimensions[Index]) {
						Child |= (1 << Index);
					}
				}
				return children[Child];
			}

			/** Returns a vector of pointers to the pairs within the same quadrant of the given position within this node and its children. */
			Vector<Pair*> FindAll(const Point& Position) {
				Vector<Pair*> Query;
				RecursiveFindAll(Position, Query);
				return Query;
			}

			/** Returns a vector of constant pointers to the pairs within the same quadrant of the given position within this node and its children. */
			Vector<const Pair*> FindAll(const Point& Position) const {
				Vector<const Pair*> Query;
				RecursiveFindAll(Position, Query);
				return Query;
			}

			/** Returns a pointer to the pair closest to the given position within this node or its children. */
			Pair* Find(const Point& Position) {
				Vector<Pair*> Query = FindAll(Position);
				Pair* Closest = nullptr;
				PrecisionType ClosestDistance = DISTANCE_MAX;
				for (auto& Pair : Query) {
					PrecisionType Distance = Math::Distance<DIMENSIONS, PrecisionType>(Position, Pair->Position());
					if (Distance < ClosestDistance) {
						Closest = Pair;
						ClosestDistance = Distance;
					}
				}
				return Closest;
			}

			/** Returns a constant pointer to the pair closest to the given position within this node or its children. */
			const Pair* Find(const Point& Position) const {
				Vector<const Pair*> Query = FindAll(Position);
				const Pair* Closest = nullptr;
				PrecisionType ClosestDistance = DISTANCE_MAX;
				for (auto& Pair : Query) {
					PrecisionType Distance = Math::Distance<DIMENSIONS, PrecisionType>(Position, Pair->Position());
					if (Distance < ClosestDistance) {
						Closest = Pair;
						ClosestDistance = Distance;
					}
				}
				return Closest;
			}

			/** Returns a vector of pointers to each of this node's children's pairs within the given area. */
			Vector<Pair*> Query(const Box& Area) {
				Vector<Pair*> Query;
				RecursiveQuery(Area, Query);
				return Query;
			}

			/** Returns a vector of constant pointers to each of this node's children's pairs within the given area. */
			Vector<const Pair*> Query(const Box& Area) const {
				Vector<const Pair*> Query;
				RecursiveQuery(Area, Query);
				return Query;
			}

			/** Returns whether the given pair is within this node or its children. */
			bool Contains(const Pair* Pair) const {
				if (Pair == nullptr) {
					return false;
				}
				return Find(Pair->Position()) == Pair;
			}

			/** Returns a vector of pointers to each of this node's pairs and its children's pairs. */
			Vector<Pair*> AllPairs() {
				Vector<Pair*> Pairs;
				RecursiveAllPairs(Pairs);
				return Pairs;
			}

			/** Returns a vector of constant pointers to each of this node's pairs and its children's pairs. */
			Vector<const Pair*> AllPairs() const {
				Vector<const Pair*> Pairs;
				RecursiveAllPairs(Pairs);
				return Pairs;
			}


			// EXPANSION

			/** Inserts a new node into the tree and returns a reference to the new data. */
			Pair* Insert(const Type& Data, const Point& Position) {
				return RecursiveInsert(Data, Position);
			}


			// TO STRING

			/** Returns the node and its children as a string. */
			std::string ToString() const {
				if (!divided && pairs.IsEmpty()) {
					return "{ }";
				}
				std::string String = "{\n";
				RecursiveToString(0, String);
				String[String.length() - 1] = '}';
				return String;
			}
		};


		// DATA

		/** The maximum bounds of this tree. */
		Box bounds;

		/** The root node of the tree. */
		Node* root;

	public:

		// CONSTRUCTORS AND DESTRUCTOR

		/** Default constructor. */
		Tree(const Box& Bounds = Box(Point(), 100)) : bounds(Bounds), root(new Node(Bounds)) {
		}

		/** Pair constructor. */
		Tree(const Box& Bounds, const Vector<Pair*>& Pairs) : bounds(Bounds), root(new Node(Bounds)) {
			for (auto& Pair : Pairs) {
				if (Bounds.Contains(Pair->Position())) {
					Insert(Pair->Data, Pair->Position());
				}
			}
		}

		/** Pair constructor. */
		Tree(const Box& Bounds, const Vector<const Pair*>& Pairs) : bounds(Bounds), root(new Node(Bounds)) {
			for (auto& Pair : Pairs) {
				if (Bounds.Contains(Pair->Position())) {
					Insert(Pair->Data, Pair->Position());
				}
			}
		}

		/** Copy constructor. */
		Tree(const Tree& Copied) : bounds(Copied.bounds), root(new Node(Copied.bounds)) {
			Vector<Pair> Pairs = Copied.Pairs();
			for (auto& Pair : Pairs) {
				Insert(Pair.Data, Pair.Position());
			}
		}

		/** Move constructor. */
		Tree(Tree&& Moved) noexcept : bounds(Moved.bounds), root(new Node(Moved.bounds)) {
			Vector<Pair> Pairs = Moved.Pairs();
			for (auto& Pair : Pairs) {
				Insert(Pair.Data, Pair.Position());
			}
			Moved.Clear();
		}

		/** Destructor. */
		~Tree() {
			delete root;
			root = nullptr;
		}


		// OPERATORS

		/** Copy assignment operator. */
		Tree& operator=(const Tree& Copied) {
			bounds = Copied.bounds;
			Clear();
			Vector<Pair> Pairs = Copied.Pairs();
			for (auto& Pair : Pairs) {
				Insert(Pair.Data, Pair.Position());
			}
			return *this;
		}

		/** Move assignment operator. */
		Tree& operator=(Tree&& Moved) noexcept {
			bounds = Moved.bounds;
			Clear();
			Vector<Pair> Pairs = Moved.Pairs();
			for (auto& Pair : Pairs) {
				Insert(Pair.Data, Pair.Position());
			}
			Moved.Clear();
			return *this;
		}


		// GETTERS

		/** Calculates and returns the current size of the tree. */
		size_t Size() const {
			return root->Count();
		}

		/** Returns the current depth of the tree. */
		size_t Depth() const {
			return root->Depth();
		}

		/** Returns the bounds of this tree. */
		const Box& Bounds() const {
			return bounds;
		}

		/** Returns a constant pointer to the root node of this tree. */
		const Node* Root() const {
			return root;
		}

		/** Returns a pointer to the pair closest to the given position. */
		Pair* Find(const Point& Position) {
			return root->Find(Position);
		}

		/** Returns a constant pointer to the pair closest to the given position. */
		const Pair* Find(const Point& Position) const {
			return root->Find(Position);
		}

		/** Returns a vector of pointers to the pairs within the matching quadrant of the given position. */
		Vector<Pair*> FindAll(const Point& Position) {
			return root->FindAll(Position);
		}

		/** Returns a vector of constant pointers to the pairs within the matching quadrant of the given position. */
		Vector<const Pair*> FindAll(const Point& Position) const {
			return root->FindAll(Position);
		}

		/** Returns a vector of pointers to each of the pairs within the given area. */
		Vector<Pair*> Query(const Box& Area) {
			return root->Query(Area);
		}

		/** Returns a vector of constant pointers to each of the pairs within the given area. */
		Vector<const Pair*> Query(const Box& Area) const {
			return root->Query(Area);
		}

		/** Returns whether the given pair is within the tree. */
		bool Contains(const Pair* Pair) const {
			return root->Contains(Pair);
		}

		/** Returns a vector of pointers to each of the pairs in this tree. */
		Vector<Pair*> Pairs() {
			return root->AllPairs();
		}

		/** Returns a vector of constant pointers to each of the pairs in this tree. */
		Vector<const Pair*> Pairs() const {
			return root->AllPairs();
		}


		// EXPANSION

		/** Deallocates the tree. */
		void Clear() {
			delete root;
			root = new Node(bounds);
		}

		/** Inserts a new pair into the tree and returns a pointer to it. */
		Pair* Insert(const Type& Data, const Point& Position) {
			return root->Insert(Data, Position);
		}


		// TO STRING

		/** Returns the tree as a string. */
		std::string ToString() const {
			return root->ToString();
		}
	};


	// TREE TYPES

	/** A collection of elements that are sorted based on neighboring elements that are greater or smaller. */
	template<typename Type>
	using BinaryTree = Tree<Type, 1, double>;

	/** A collection of elements that are organized based on their location in 2D space. */
	template<typename Type>
	using Quadtree = Tree<Type, 2, double>;

	/** A collection of elements that are organized based on their location in 3D space. */
	template<typename Type>
	using Octree = Tree<Type, 3, double>;
}
