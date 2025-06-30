// .h
// Simulated Qubit Type
// by Kyle Furey
// REFERENCES:	https://azure.microsoft.com/en-us/resources/cloud-computing-dictionary/what-is-a-qubit
//				https://en.wikipedia.org/wiki/Qubit
//				https://en.wikipedia.org/wiki/Quantum_logic_gate

#pragma once
#include <unordered_set>
#include <utility>
#include <complex>
#include <cstdlib>
#include <cmath>


// QUANTUM

#ifdef QUANTUM_DLL_EXPORTS
#define QUANTUM_API __declspec(dllexport)
#else
#define QUANTUM_API __declspec(dllimport)
#endif

/** Classes used to simulate quantum computing. */
namespace Quantum {

	// COMPLEX

	/** A complex number. */
	using Complex = std::complex<double>;


	// RESULT

	/** The result of a collapsed qubit. */
	enum class Result {
		ZERO,
		ONE,
	};


	// QUBIT

	/** Simulates a single quantum bit that holds a state of 0, 1, or a superposition. */
	class QUANTUM_API Qubit final {
	public:

		// CONSTANTS

		/** The reciprocal of the square root of 2. */
		static constexpr double INV_SQRT2 = 0.7071067811865475244;

	private:

		// VARIABLES

		/** The probability amplitude of the qubit being in a 0 state. */
		Complex alpha;

		/** The probability amplitude of the qubit being in a 1 state. */
		Complex beta;

		/** Each entangled qubit that shares the same state. */
		std::unordered_set<Qubit*> entanglements;


		// METHODS

		/** Normalizes this qubit. */
		void Normalize();

		/** Synchronizes all entangled qubits. */
		void Sync();

		/** Entangles this qubit with another qubit. */
		void Entangle(Qubit& other);

		/** Separates this qubit from other qubits. */
		void Separate();

	public:

		// CONSTRUCTORS AND DESTRUCTOR

		/** Default constructor. */
		Qubit();

		/** Delete copy constructor. */
		Qubit(const Qubit& copied) = delete;

		/** Move constructor. */
		Qubit(Qubit&& moved) noexcept;

		/** Destructor. */
		~Qubit();


		// OPERATORS

		/** Delete copy assignment operator. */
		Qubit& operator=(const Qubit& copied) = delete;

		/** Move assignment operator. */
		Qubit& operator=(Qubit&& moved) noexcept;


		// METHODS

		/** Simulated Pauli-X gate. */
		Qubit& X();

		/** Simulated Pauli-Y gate. */
		Qubit& Y();

		/** Simulated Pauli-Z gate. */
		Qubit& Z();

		/** Simulated Hadamard gate. */
		Qubit& H();

		/** Simulated Phase PI / 2 gate. */
		Qubit& S();

		/** Simulated Phase PI / 4 gate. */
		Qubit& T();

		/** Simulated X Rotation gate. */
		Qubit& Rx(const double theta);

		/** Simulated Y Rotation gate. */
		Qubit& Ry(const double theta);

		/** Simulated Z Rotation gate. */
		Qubit& Rz(const double theta);

		/** Simulated Controlled Not gate. */
		Qubit& CNOT(Qubit& control);

		/** Simulated Controlled Z gate. */
		Qubit& CZ(Qubit& control);

		/** Simulated Swap gate. */
		Qubit& SWAP(Qubit& other);

		/** Simulated Toffoli gate. */
		Qubit& CCNOT(Qubit& control1, Qubit& control2);

		/** Collapses this and all entangled qubits. */
		Result Measure();

		/** Resets this qubit to the 0 state. */
		Qubit& Reset();
	};
}
