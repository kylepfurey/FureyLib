
// Name
// Creator

// REQUIREMENT: MyInterface.cpp

#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MyInterface.generated.h"

// Include this heading to use the interface
// #include "MyInterface.h"

// This class does not need to be modified. Do not inherit from this class.
UINTERFACE(NotBlueprintable, BlueprintType, MinimalAPI)
class UMyInterface : public UInterface
{
	GENERATED_BODY()
};

// Inherit from the following interface to implement it.

/** Template Unreal interface script. */
class MYGAME_API IMyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// CONTRACTED FUNCTIONS

	/** Description. */
	UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "Category", meta = (Keywords = "Keywords"))
	virtual void Function(bool Input, bool& Output);

	// New functions here
};
