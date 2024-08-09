
// Function Pointer Object Script
// by Kyle Furey

// REQUIREMENT: FunctionPointer.h

// SOURCE: https://blog.jamie.holdings/2022/04/14/unreal-engine-4-23-accept-delegates-as-arguments-in-blueprint-functions/

// Include this heading to use the class
#include "FunctionPointer.h"


// CONSTRUCTORS

// Default constructor.
UFunctionPointer::UFunctionPointer()
{
	Delegate = FFunctionPointerDelegate();
}

// Delegate constructor.
UFunctionPointer::UFunctionPointer(const FFunctionPointerDelegate& Event)
{
	Delegate = Event;
}


// FUNCTIONS

// Binds or rebinds the given delegate to this function pointer.
void UFunctionPointer::Bind(const FFunctionPointerDelegate& Event, bool& Overwrite)
{
	Overwrite = Delegate.IsBound();

	Delegate = Event;
}

// Unbinds this function pointer's delegate if possible.
void UFunctionPointer::Unbind(bool& Success)
{
	Success = Delegate.IsBound();

	Delegate.Unbind();
}

// Invokes the underlying delegate stored to this function pointer if possible.
void UFunctionPointer::Invoke(bool& Success)
{
	Success = Delegate.IsBound();

	if (Success)
	{
		Delegate.Execute();
	}
}

// Returns whether this function pointer is current bound to an delegate.
void UFunctionPointer::IsBound(bool& Bound)
{
	Bound = Delegate.IsBound();
}

// Returns the underlying delegate. 
FFunctionPointerDelegate& UFunctionPointer::GetDelegate()
{
	return Delegate;
}

// Constructs a function pointer with the given delegate.
UFunctionPointer* UFunctionPointer::ConstructFunctionPointer(const FFunctionPointerDelegate& Event)
{
	UFunctionPointer* FunctionPointer = NewObject<UFunctionPointer>();

	FunctionPointer->Delegate = Event;

	return FunctionPointer;
}
