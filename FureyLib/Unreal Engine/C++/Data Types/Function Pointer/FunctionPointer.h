
// Function Pointer Object Script
// by Kyle Furey

// REQUIREMENT: FunctionPointer.cpp

// SOURCE: https://blog.jamie.holdings/2022/04/14/unreal-engine-4-23-accept-delegates-as-arguments-in-blueprint-functions/

#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Delegates/Delegate.h"
#include "FunctionPointer.generated.h"

// Include this heading to use the class
// #include "FunctionPointer.h"

// Delegate declaration.
DECLARE_DYNAMIC_DELEGATE(FFunctionPointerDelegate);

/** A wrapper object that stores and can invoke an Unreal delegate. */
UCLASS(Blueprintable, BlueprintType)
class GAME_API UFunctionPointer : public UObject
{
	GENERATED_BODY()

protected:

	// VARIABLES

	/** The underlying delegate this UFunctionPointer stores. */
	UPROPERTY(BlueprintReadOnly, BlueprintGetter = "GetDelegate", meta = (ExposeOnSpawn), Category = "Function Pointer")
	FFunctionPointerDelegate Delegate = FFunctionPointerDelegate();

public:

	// CONSTRUCTORS

	/** Default constructor. */
	UFunctionPointer();

	/** Delegate constructor. */
	UFunctionPointer(const FFunctionPointerDelegate& Event);


	// FUNCTIONS

	/** Binds or rebinds the given delegate to this function pointer. */
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "Event"), Category = "Function Pointer")
	virtual void Bind(const FFunctionPointerDelegate& Event, bool& Overwrite);

	/** Unbinds this function pointer's delegate if possible. */
	UFUNCTION(BlueprintCallable, Category = "Function Pointer")
	virtual void Unbind(bool& Success);

	/** Invokes the underlying delegate stored to this function pointer if possible. */
	UFUNCTION(BlueprintCallable, Category = "Function Pointer")
	virtual void Invoke(bool& Success);

	/** Returns whether this function pointer is current bound to a delegate. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Function Pointer")
	virtual void IsBound(bool& Bound);

	/** Returns the underlying delegate. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Function Pointer")
	virtual FFunctionPointerDelegate& GetDelegate();

	/** Constructs a function pointer with the given delegate. */
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "Event"), Category = "Function Pointer")
	static UFunctionPointer* ConstructFunctionPointer(const FFunctionPointerDelegate& Event);
};
