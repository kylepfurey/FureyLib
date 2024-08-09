
// Name
// Creator

// REQUIREMENT: MyObject.cpp

#pragma once
#include "CoreMinimal.h"
#include "UMyObject/NoExportTypes.h"
#include "MyObject.generated.h"

// Include this heading to use the class
// #include "MyObject.h"

/** Template Unreal object script. */
UCLASS(Blueprintable, BlueprintType)
class GAME_API UMyObject : public UObject
{
	GENERATED_BODY()

public:

	// VARIABLES

	// New variables here


	// CONSTRUCTORS AND DESTRUCTOR

	/** Default constructor */
	UMyObject();

	/** Copy constructor */
	UMyObject(const UMyObject& Copied);

	/** Move constructor */
	UMyObject(UMyObject&& Moved) noexcept;

	// New constructors here

	/** Destructor */
	virtual ~UMyObject();


	// FUNCTIONS

	// New functions here


	// OPERATORS

	/** Copy assignment operator */
	UMyObject& operator=(const UMyObject& Copied);

	/** Move assignment operator */
	UMyObject& operator=(UMyObject&& Moved) noexcept;

	// New overloaded operators here
};
