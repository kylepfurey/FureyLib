
// Name
// Creator

// REQUIREMENT: MyBlueprintFunctionLibrary.cpp

#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

// Include this heading to use the library
// #include "MyBlueprintFunctionLibrary.h"

/** Template Unreal static function library script. */
UCLASS(Blueprintable, BlueprintType)
class GAME_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	// STATIC FUNCTIONS

	/** Description. */
	UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "Category", meta = (Keywords = "Keywords"))
	static void Function(bool Input, UObject* __WorldContext, bool& Output);

	// New functions here
};
