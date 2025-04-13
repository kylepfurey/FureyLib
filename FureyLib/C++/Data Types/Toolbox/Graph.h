// .h
// Node Graph Type
// by Kyle Furey

#pragma once
#include <cfloat>
#include "Stack.h"
#include "PriorityQueue.h"
#include "Map.h"

// Represents an invalid node code.
#define INVALID_NODE_CODE 0

// The default unsigned weight of each graph node.
#define DEFAULT_WEIGHT 100

// The maximum possible value of a heuristic.
#define HEURISTIC_MAX DBL_MAX

// The maximum number of loops when building a path in a graph.
#define MAX_LOOPS 300

/** A collection of useful collection types in C++. */
namespace Toolbox {

	// STRUCTURES

	/** Private namespace. */
	namespace {

		// NODE

		/**
		 * An unsigned number used to represent an individual node.<br/>
		 * A code of INVALID_NODE_CODE is an invalid node.
		 */
		using NodeCode = size_t;

		/** An unsigned number used to represent the weight of traversing a node. */
		using NodeWeight = size_t;


		// CONNECTION

		/** Represents an individual graph node with its own data and connections. */
		template <typename Type>
		struct Node;

		/** Represents a link between two graph nodes. */
		template <typename Type>
		struct Connection final {
		private:

			// DATA

			/** The code of the node this connection is linked towards within its graph. */
			NodeCode to;

			/** The code of the node that owns this connection within its graph. */
			NodeCode from;

		public:

			// DATA

			/** The weight of traversing this connection. */
			NodeWeight Weight;

			/** Whether this connection is currently active. */
			bool Active;


			// CONSTRUCTORS

			/** Default constructor. */
			Connection(const NodeCode To = INVALID_NODE_CODE, const NodeCode From = INVALID_NODE_CODE, const NodeWeight Weight = DEFAULT_WEIGHT, const bool Active = true) : to(To), from(From), Weight(Weight), Active(Active) {
			}


			// GETTERS

			/** Returns the code of the node this connection is linked towards within its graph. */
			NodeCode To() const {
				return to;
			}

			/** Returns the code of the node that owns this connection within its graph. */
			NodeCode From() const {
				return from;
			}

			/** Returns whether this connection is a valid connection for a node. */
			bool IsValidConnection() const {
				return to != INVALID_NODE_CODE && from != INVALID_NODE_CODE;
			}
		};


		// NODE

		/** Represents an individual graph node with its own data and connections. */
		template <typename Type>
		struct Node final {

			// CONNECTION

			/** Represents a link between two graph nodes. */
			using Connection = Connection<Type>;

		private:

			// DATA

			/** The unique code used to identify this node in its graph. */
			NodeCode code;

		public:

			// DATA

			/** The data this node owns. */
			Type Data;

		private:

			// DATA

			/** Each of this node's connections within its graph by their node codes. */
			Map<NodeCode, Connection> connections;

		public:

			// DATA

			/** The weight of this individual node. */
			NodeWeight Weight;

			/** Whether this node is currently active. */
			bool Active;


			// CONSTRUCTOR

			/** Default constructor. */
			Node(const NodeCode Code = INVALID_NODE_CODE, const Type& Data = Type(), const NodeWeight Weight = DEFAULT_WEIGHT, const bool Active = true) : code(Code), Data(Data), connections(), Weight(Weight), Active(Active) {
			}


			// GETTERS

			/** Returns this node's unique code used to identify itself within its graph. */
			NodeCode Code() const {
				return code;
			}

			/** Returns whether the node's code is valid. */
			bool IsValidNode() const {
				return code != INVALID_NODE_CODE;
			}


			// CONNECTIONS

			/** Returns this node's neighboring connections. */
			const Map<NodeCode, Connection>& Connections() const {
				return connections;
			}

			/** Connects this node to the given node and returns a pointer to the connection. */
			Connection* Connect(const NodeCode Node, const NodeWeight Weight = DEFAULT_WEIGHT, const bool Active = true) {
				if (Node == INVALID_NODE_CODE || Node == code) {
					return nullptr;
				}
				return &connections.Insert(Node, Connection(Node, code, Weight, Active));
			}

			/**
			 * Disconnects this node from the given node.<br/>
			 * Returns whether the node was successfully disconnected.
			 */
			bool Disconnect(const NodeCode Node) {
				return connections.Erase(Node);
			}

			/** Returns a pointer to the connection to the given node if this node is connected to it, or nullptr if not. */
			Connection* FindConnection(const NodeCode Node) {
				return connections.Find(Node);
			}

			/** Returns a constant pointer to the connection to the given node if this node is connected to it, or nullptr if not. */
			const Connection* FindConnection(const NodeCode Node) const {
				return connections.Find(Node);
			}

			/** Returns whether this node is connected to the given node. */
			bool IsConnected(const NodeCode Node) const {
				return connections.ContainsKey(Node);
			}

			/** Returns the number of connections this node has. */
			size_t TotalConnections() const {
				return connections.Size();
			}


			// OPERATORS

			/** Returns a pointer to this nodes connection to the given node if it exists, otherwise nullptr. */
			Connection* operator[](const NodeCode Node) {
				return FindConnection(Node);
			}

			/** Returns a constant pointer to this nodes connection to the given node if it exists, otherwise nullptr. */
			const Connection* operator[](const NodeCode Node) const {
				return FindConnection(Node);
			}

			/** Returns whether this node is equivilent to the given node. */
			bool operator==(const Node& Node) const {
				return code == Node.code;
			}

			/** Returns whether this node is not equivilent to the given node. */
			bool operator!=(const Node& Node) const {
				return code != Node.code;
			}

			/** Returns whether this node is a valid node. */
			explicit operator bool() const {
				return code != INVALID_NODE_CODE;
			}
		};
	}


	// HEURISTIC FUNCTION

	/** A value used to guess how close a node is to a goal node. */
	using Heuristic = double;

	/** Returns 0 as no heuristic was given. */
	template <typename Type>
	static Heuristic NoHeuristic(const Node<Type>& Current, const Node<Type>& End) {
		return 0;
	}


	// GRAPH

	/** A collection of interconnected nodes that can be traversed based on their weights. */
	template<typename Type, Heuristic(*HEURISTIC_FUNC)(const Node<Type>&, const Node<Type>&) = NoHeuristic>
	class Graph final {
	public:

		// NODE AND CONNECTION

		/**
		 * An unsigned number used to represent an individual node.<br/>
		 * A code of INVALID_NODE_CODE is an invalid node.
		 */
		using NodeCode = size_t;

		/** An unsigned number used to represent the weight of traversing a node. */
		using NodeWeight = size_t;

		/** Represents an individual graph node with its own data and connections. */
		using Node = Node<Type>;

		/** Represents a link between two graph nodes. */
		using Connection = Connection<Type>;

	private:

		// DATA

		/** The current node to distribute a code for. */
		size_t nextCode;

		/** Each of the nodes this graph manages. */
		Map<NodeCode, Node> nodes;

	public:

		// CONSTRUCTORS

		/** Default constructor. */
		Graph(const size_t BucketCount = 16) : nextCode(1), nodes(BucketCount) {
		}

		/** Copy constructor. */
		Graph(const Graph<Type>& Copied) : nextCode(1), nodes(Copied.nodes) {
		}

		/** Move constructor. */
		Graph(Graph<Type>&& Moved) : nextCode(1), nodes(std::move(Moved.nodes)) {
		}


		// OPERATORS

		/** Copy assignment operator. */
		Graph<Type>& operator=(const Graph<Type>& Copied) {
			nextCode = Copied.nextCode;
			nodes = Copied.nodes;
			return *this;
		}

		/** Move assignment operator. */
		Graph<Type>& operator=(Graph<Type>&& Moved) noexcept {
			nextCode = Moved.nextCode;
			nodes = std::move(Moved.nodes);
			return *this;
		}

		/** Returns a pointer to the the given node code's corresponding node, or nullptr if it is not found. */
		Node* operator[](const NodeCode Node) {
			return Find(Node);
		}

		/** Returns a constant pointer to the the given node code's corresponding node, or nullptr if it is not found. */
		const Node* operator[](const NodeCode Node) const {
			return Find(Node);
		}


		// GETTERS

		/** Returns the number of nodes in the graph. */
		size_t Size() const {
			return nodes.Size();
		}

		/** Returns the next code given to the next inserted node. */
		size_t NextCode() const {
			return nextCode;
		}

		/** Finds and returns a pointer to the given node in the graph, or nullptr if it does not exist. */
		Node* Find(const NodeCode Node) {
			return nodes.Find(Node);
		}

		/** Finds and returns a constant pointer to the given node in the graph, or nullptr if it does not exist. */
		const Node* Find(const NodeCode Node) const {
			return nodes.Find(Node);
		}

		/** Returns whether the given node is present in the graph. */
		bool Contains(const NodeCode Node) const {
			return nodes.ContainsKey(Node);
		}

		/** Returns whether the graph is empty. */
		bool IsEmpty() const {
			return nodes.IsEmpty();
		}


		// EXPANSION

		/** Deallocates the graph. */
		void Clear() {
			nodes.Clear();
		}

		/** Inserts a new node into the graph with a copy of the given value and returns its code. */
		NodeCode Insert(const Type& Value, const NodeWeight Weight = DEFAULT_WEIGHT, const bool Active = true) {
			NodeCode Next = nextCode;
			++nextCode;
			if (nextCode == INVALID_NODE_CODE) {
				++nextCode;
			}
			return nodes.Insert(Next, Node(Next, Value, Weight, Active)).Code();
		}

		/** Removes the given node from the graph and returns whether it was successful. */
		bool Erase(const NodeCode Node) {
			if (nodes.ContainsKey(Node)) {
				Vector<NodeCode> Codes = nodes.Keys();
				for (auto Code : Codes) {
					struct Node* Current = nodes.Find(Code);
					if (Current != nullptr) {
						Current->Disconnect(Node);
					}
				}
				nodes.Erase(Node);
				return true;
			}
			return false;
		}


		// CONNECTIONS

		/** Connects both of the given nodes together and returns whether it was successful. */
		bool Connect(const NodeCode Node1, const NodeCode Node2, const NodeWeight Weight = DEFAULT_WEIGHT, const bool Active = true) {
			Node* NodeOne = Find(Node1);
			Node* NodeTwo = Find(Node2);
			if (NodeOne == nullptr || NodeTwo == nullptr || (NodeOne->IsConnected(Node2) && NodeTwo->IsConnected(Node1))) {
				return false;
			}
			NodeOne->Connect(Node2, Weight, Active);
			NodeTwo->Connect(Node1, Weight, Active);
			return true;
		}

		/** Disconnects both of the given nodes and returns whether it was successful. */
		bool Disconnect(const NodeCode Node1, const NodeCode Node2) {
			Node* NodeOne = Find(Node1);
			Node* NodeTwo = Find(Node2);
			if (NodeOne == nullptr || NodeTwo == nullptr) {
				return false;
			}
			bool Success1 = NodeOne->Disconnect(Node2);
			bool Success2 = NodeTwo->Disconnect(Node1);
			return Success1 || Success2;
		}

		/** Returns whether both of the given nodes are linked to each other. */
		bool IsConnected(const NodeCode Node1, const NodeCode Node2) const {
			const Node* NodeOne = Find(Node1);
			const Node* NodeTwo = Find(Node2);
			if (NodeOne == nullptr || NodeTwo == nullptr) {
				return false;
			}
			return NodeOne->IsConnected(Node2) && NodeTwo->IsConnected(Node1);
		}


		// NAVIGATION

		/**
		 * Calculates the shortest path from the given start node to the given end node using the A Star Search algorithm.<br/>
		 * REFERENCE: https://www.redblobgames.com/pathfinding/a-star/introduction.html
		 */
		Stack<NodeCode> BuildPath(const NodeCode Start, const NodeCode End) const {
			if (Start == INVALID_NODE_CODE || End == INVALID_NODE_CODE || Start == End) {
				return Stack<NodeCode>();
			}
			const Node* CurrentNode = Find(Start);
			const Node* EndNode = Find(End);
			if (CurrentNode == nullptr || EndNode == nullptr) {
				return Stack<NodeCode>();
			}
			PriorityQueue<NodeCode, Heuristic> Frontier;
			Frontier.Push(Start, 0);
			Map<NodeCode, NodeCode> From;
			From.Insert(Start, INVALID_NODE_CODE);
			Map<NodeCode, NodeWeight> Weights;
			Weights.Insert(Start, 0);
			CurrentNode = EndNode;
			size_t LoopCount = 0;
			while (!Frontier.IsEmpty()) {
				++LoopCount;
				if (LoopCount > MAX_LOOPS) {
					break;
				}
				CurrentNode = Find(Frontier.Pop());
				if (CurrentNode == nullptr) {
					continue;
				}
				if (CurrentNode == EndNode) {
					break;
				}
				Vector<Connection> Connections = CurrentNode->Connections().Values();
				for (auto& Connection : Connections) {
					if (!Connection.Active) {
						continue;
					}
					const Node* ToNode = Find(Connection.To());
					if (ToNode == nullptr || !ToNode->Active) {
						continue;
					}
					NodeWeight NewCost = Weights[CurrentNode->Code()] + Connection.Weight + ToNode->Weight;
					if (!From.ContainsKey(Connection.To()) || NewCost < Weights[Connection.To()]) {
						Weights[Connection.To()] = NewCost;
						Frontier.Push(Connection.To(), static_cast<Heuristic>(NewCost) + HEURISTIC_FUNC(*ToNode, *EndNode));
						From[Connection.To()] = CurrentNode->Code();
					}
				}
			}
			Frontier.Clear();
			if (CurrentNode != EndNode) {
				CurrentNode = Find(Start);
				Heuristic CurrentHeuristic = HEURISTIC_MAX;
				Vector<NodeCode> FromTo = From.Keys();
				for (auto& To : FromTo) {
					const Node* ToNode = Find(To);
					if (ToNode == nullptr) {
						continue;
					}
					Heuristic NewHeuristic = HEURISTIC_FUNC(*ToNode, *EndNode);
					if (NewHeuristic < CurrentHeuristic) {
						CurrentNode = ToNode;
						CurrentHeuristic = NewHeuristic;
					}
				}
			}
			Stack<NodeCode> Route;
			NodeCode CurrentCode = CurrentNode->Code();
			while (From[CurrentCode] != INVALID_NODE_CODE) {
				Route.Push(CurrentCode);
				CurrentCode = From[CurrentCode];
			}
			return Route;
		}


		// TO STRING

		/** Returns the graph as a string. */
		std::string ToString(const bool IncludeConnections = false) const {
			if (IncludeConnections) {
				std::string String = "{";
				Vector<Node> Nodes = nodes.Values();
				for (auto& Node : Nodes) {
					String += "\n\t";
					String += std::to_string(Node.Code()) + " -> ( ";
					Vector<Connection> Connections = Node.Connections().Values();
					for (auto& Connection : Connections) {
						String += std::to_string(Connection.To()) + ", ";
					}
					if (Connections.Size() > 0) {
						String.erase(String.length() - 2, 2);
						String += " ), ";
					}
					else {
						String += "), ";
					}
				}
				if (nodes.Size() > 0) {
					String.erase(String.length() - 2, 2);
					String += "\n";
				}
				String += "}";
				return String;
			}
			else {
				std::string String = "{";
				Vector<NodeCode> Nodes = nodes.Keys();
				for (auto& Node : Nodes) {
					String += std::to_string(Node) + ", ";
				}
				if (nodes.Size() > 0) {
					String.erase(String.length() - 2, 2);
				}
				String += " }";
				return String;
			}
		}


		// AS MAP

		/** Returns a reference to this graph's underlying map. */
		Map<NodeCode, Node>& AsMap() {
			return nodes;
		}

		/** Returns a constant reference to this graph's underlying map. */
		const Map<NodeCode, Node>& AsMap() const {
			return nodes;
		}
	};
}
