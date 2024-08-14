
// Name
// Creator

// REQUIREMENT: MyFactory.cpp

#pragma once
#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "MyFactory.generated.h"

// Include this heading to use the class
// #include "MyFactory.h"

/** Template Unreal factory script. */
UCLASS(Blueprintable, BlueprintType)
class MYGAME_API UMyFactory : public UFactory
{
	GENERATED_BODY()

protected:

	// VARIABLES

	// New variables here


	// FUNCTIONS

	// New functions here

public:

	// VARIABLES

	// New variables here


	// CONSTRUCTORS

	/** Default constructor. */
	UMyFactory(const FObjectInitializer& ObjectInitializer);

	// New constructors here


	// UNREAL FUNCTIONS

	/** Creates a new object of the given class. */
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;

	/** Exports the given class instance as a file. */
	virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;

	/** Imports the given file as a class instance. */
	virtual UObject* ImportObject(UClass* InClass, UObject* InOuter, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, bool& OutCanceled) override;


	// FUNCTIONS

	// New functions here
};
