
// Name
// Creator

// REQUIREMENT: MyInterface.h

// Include this heading to use the interface
#include "MyInterface.h"

// Add default functionality here for any interface functions that are not pure virtual ("MyFunction() = 0").
// BlueprintNativeEvents can be implemented in C++ via overriding "MyFunction_Implementation()".
// BlueprintNativeEvents can be invoked in C++ via calling "Execute_MyFunction(Target)".


// CONTRACTED FUNCTIONS

// Description.
void IMyInterface::Function_Implementation(bool Input, bool& Output)
{
	Output = Input;
}

// New functions here
