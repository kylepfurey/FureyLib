// .cpp
// Simulated Qubit Type
// by Kyle Furey
// REFERENCES:	https://azure.microsoft.com/en-us/resources/cloud-computing-dictionary/what-is-a-qubit
//				https://en.wikipedia.org/wiki/Qubit
//				https://en.wikipedia.org/wiki/Quantum_logic_gate

#include "Qubit.h"

// Classes used to simulate quantum computing.
namespace Quantum {

	// CONSTRUCTORS AND DESTRUCTOR

	// Default constructor.
	Qubit::Qubit() : alpha(1.0, 0.0), beta(0.0, 0.0), entanglements() {
	}

	// Move constructor.
	Qubit::Qubit(Qubit&& moved) noexcept : alpha(moved.alpha), beta(moved.beta), entanglements(std::move(moved.entanglements)) {
		for (auto current : entanglements) {
			current->entanglements.erase(&moved);
			current->entanglements.insert(this);
		}
		moved.alpha = 1.0;
		moved.beta = 0.0;
		moved.entanglements.clear();
	}

	// Destructor.
	Qubit::~Qubit() {
		for (auto current : entanglements) {
			current->entanglements.erase(this);
		}
		entanglements.clear();
	}


	// OPERATORS

	// Move assignment operator.
	Qubit& Qubit::operator=(Qubit&& moved) noexcept {
		if (this == &moved) {
			return *this;
		}
		Separate();
		alpha = moved.alpha;
		beta = moved.beta;
		entanglements = std::move(moved.entanglements);
		for (auto current : entanglements) {
			current->entanglements.erase(&moved);
			current->entanglements.insert(this);
		}
		moved.alpha = 1.0;
		moved.beta = 0.0;
		moved.entanglements.clear();
		return *this;
	}


	// METHODS

	// Normalizes this qubit.
	void Qubit::Normalize() {
		const double c = std::sqrt(std::norm(alpha) + std::norm(beta));
		if (c < 1e-12) {
			alpha = 1.0;
			beta = 0.0;
		}
		else {
			alpha /= c;
			beta /= c;
		}
	}

	// Synchronizes all entangled qubits.
	void Qubit::Sync() {
		Normalize();
		for (auto current : entanglements) {
			current->alpha = alpha;
			current->beta = beta;
		}
	}

	// Entangles this qubit with another qubit.
	void Qubit::Entangle(Qubit& other) {
		if (this == &other) {
			return;
		}
		for (auto current : entanglements) {
			current->entanglements.insert(&other);
		}
		for (auto current : other.entanglements) {
			current->entanglements.insert(this);
		}
		entanglements.insert(&other);
		other.entanglements.insert(this);
		Sync();
	}

	// Separates this qubit from other qubits.
	void Qubit::Separate() {
		for (auto current : entanglements) {
			current->entanglements.erase(this);
		}
		entanglements.clear();
	}

	// Simulated Pauli-X gate.
	Qubit& Qubit::X() {
		Complex temp = alpha;
		alpha = beta;
		beta = temp;
		Sync();
		return *this;
	}

	// Simulated Pauli-Y gate.
	Qubit& Qubit::Y() {
		Complex a = alpha;
		Complex b = beta;
		alpha = Complex(0, 1) * b;
		beta = Complex(0, -1) * a;
		Sync();
		return *this;
	}

	// Simulated Pauli-Z gate.
	Qubit& Qubit::Z() {
		beta *= -1.0;
		Sync();
		return *this;
	}

	// Simulated Hadamard gate.
	Qubit& Qubit::H() {
		Complex a = (alpha + beta) * INV_SQRT2;
		Complex b = (alpha - beta) * INV_SQRT2;
		alpha = a;
		beta = b;
		Sync();
		return *this;
	}

	// Simulated Phase PI / 2 gate.
	Qubit& Qubit::S() {
		beta *= Complex(0, 1);
		Sync();
		return *this;
	}

	// Simulated Phase PI / 4 gate.
	Qubit& Qubit::T() {
		beta *= Complex(INV_SQRT2, INV_SQRT2);
		Sync();
		return *this;
	}

	// Simulated X Rotation gate.
	Qubit& Qubit::Rx(const double theta) {
		const double c = std::cos(theta / 2);
		const double s = std::sin(theta / 2);
		Complex a = alpha;
		Complex b = beta;
		alpha = (c * a) - (Complex(0, 1) * s * b);
		beta = (c * b) - (Complex(0, 1) * s * a);
		Sync();
		return *this;
	}

	// Simulated Y Rotation gate.
	Qubit& Qubit::Ry(const double theta) {
		const double c = std::cos(theta / 2);
		const double s = std::sin(theta / 2);
		Complex a = alpha;
		Complex b = beta;
		alpha = (c * a) - (s * b);
		beta = (s * a) + (c * b);
		Sync();
		return *this;
	}

	// Simulated Z Rotation gate.
	Qubit& Qubit::Rz(const double theta) {
		alpha *= std::exp(Complex(0, -theta / 2));
		beta *= std::exp(Complex(0, theta / 2));
		Sync();
		return *this;
	}

	// Simulated Controlled Not gate.
	Qubit& Qubit::CNOT(Qubit& control) {
		if (this == &control) {
			return *this;
		}
		if (std::norm(control.beta) == 1.0) {
			Entangle(control);
			X();
		}
		return *this;
	}

	// Simulated Controlled Z gate.
	Qubit& Qubit::CZ(Qubit& control) {
		if (this == &control) {
			return *this;
		}
		if (std::norm(control.beta) == 1.0) {
			Entangle(control);
			Z();
		}
		return *this;
	}

	// Simulated Swap gate.
	Qubit& Qubit::SWAP(Qubit& other) {
		if (this == &other) return *this;
		Complex temp = alpha;
		alpha = other.alpha;
		other.alpha = temp;
		temp = beta;
		beta = other.beta;
		other.beta = temp;
		std::unordered_set<Qubit*> copy = entanglements;
		entanglements = other.entanglements;
		other.entanglements = std::move(copy);
		for (auto current : entanglements) {
			current->entanglements.erase(&other);
			current->entanglements.insert(this);
		}
		for (auto current : other.entanglements) {
			current->entanglements.erase(this);
			current->entanglements.insert(&other);
		}
		Sync();
		other.Sync();
		return *this;
	}

	// Simulated Toffoli gate.
	Qubit& Qubit::CCNOT(Qubit& control1, Qubit& control2) {
		if (this == &control1 || this == &control2 || &control1 == &control2) {
			return *this;
		}
		if (std::norm(control1.beta) == 1.0 && std::norm(control2.beta) == 1.0) {
			Entangle(control1);
			Entangle(control2);
			X();
		}
		return *this;
	}

	// Collapses this and all entangled qubits.
	Result Qubit::Measure() {
		const double random = static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX);
		const double alphaChance = std::norm(alpha);
		if (random > alphaChance) {
			alpha = 0.0;
			beta = 1.0;
			Sync();
			return Result::ONE;
		}
		else {
			alpha = 1.0;
			beta = 0.0;
			Sync();
			return Result::ZERO;
		}
	}

	// Resets this qubit to the 0 state.
	Qubit& Qubit::Reset() {
		alpha = 1.0;
		beta = 0.0;
		Separate();
		return *this;
	}
}
