
// Name
// Creator

// REQUIREMENT: MyInterface.cpp

#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MyInterface.generated.h"

// Include this heading to use the interface
// #include "Boilerplate/MyInterface.h"

// This class does not need to be modified. Do not inherit from this class.
UINTERFACE(Blueprintable, BlueprintType, MinimalAPI)
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
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Category", meta = (Keywords = "Keywords"))
	void Function(bool Input, bool& Output);
	virtual void Function_Implementation(bool Input, bool& Output);

	// New functions here
};
