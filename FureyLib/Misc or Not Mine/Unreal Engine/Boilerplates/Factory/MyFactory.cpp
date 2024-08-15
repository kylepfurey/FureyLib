
// Name
// Creator

// REQUIREMENT: MyFactory.h

#if WITH_EDITOR

// Include this heading to use the class
#include "MyFactory.h"


// CONSTRUCTORS

// Default constructor.
UMyFactory::UMyFactory()
{

}

// Object initializer constructor.
UMyFactory::UMyFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

// New constructors here


// UNREAL FUNCTIONS

// Creates a new object of the given class.
UObject* UMyFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	return nullptr;
}

// Exports the given class instance as a file.
UObject* UMyFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	return nullptr;
}

// Imports the given file as a class instance.
UObject* UMyFactory::ImportObject(UClass* InClass, UObject* InOuter, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, bool& OutCanceled)
{
	return nullptr;
}


// FUNCTIONS

// New functions here

#endif
