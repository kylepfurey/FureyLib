// .h
// Singleton Base Class
// by Kyle Furey

#pragma once
#include "CoreMinimal.h"
#include "UObject/UObjectGlobals.h"
#include "Misc/CoreDelegates.h"


// SINGLETON

/** Allows a derived class or blueprint to have a single global instance via T::Instance(). */
template<typename T>
class MYGAME_API TSingleton
{
	// VARIABLES

	/** The underlying singleton instance of this class or blueprint. */
	static T* Instance;

public:

	// CONSTRUCTORS AND DESTRUCTOR

	/** Initializes the singleton. */
	TSingleton()
	{
		static bool Init = false;
		if (!Init)
		{
			FCoreDelegates::OnPreExit.AddStatic([]()
			{
				if (TSingleton<T>::Instance)
				{
					TSingleton<T>::Instance->RemoveFromRoot();
					TSingleton<T>::Instance = nullptr;
				}
			});
			Init = true;
		}
		if (GWorld == nullptr || !GWorld->IsGameWorld() || IsEngineExitRequested())
		{
			return;
		}
		if (Instance == nullptr)
		{
			Instance = static_cast<T*>(this);
		}
	}

	/** Cleans up the singleton. */
	~TSingleton()
	{
		if (Instance == this)
		{
			Instance = nullptr;
		}
	}


	// METHODS

	/** Returns the singleton instance of this class or blueprint. */
	static T* Instance()
	{
		if (GWorld == nullptr || !GWorld->IsGameWorld() || IsEngineExitRequested())
		{
			return nullptr;
		}
		if (!IsValid(Instance))
		{
			for (TObjectIterator<T> Iterator; Iterator; ++Iterator)
			{
				T* Object = *Iterator;
				if (Object != nullptr)
				{
					Instance = Object;
					return Instance;
				}
			}
			Instance = NewObject<T>(GetTransientPackage(), T::StaticClass());
			if (IsValid(Instance))
			{
				Instance->AddToRoot();
				return Instance;
			}
			else
			{
				return nullptr;
			}
		}
		return Instance;
	}
};

#undef DECLARE_BP_SINGLETON
#undef _U
// Shorthand for declaring a static GetInstance(T*&) method for type T that supports blueprint reflection when expanded.
#define DECLARE_BP_SINGLETON(T) _U()FUNCTION(BlueprintPure, Category = #T) static void GetInstance(T*& T) { T = Instance(); }
#define _U() U


// STATIC VARIABLE INITIALIZATION

// The underlying singleton instance of this component.
template<typename T>
static T* TSingleton<T>::Instance = nullptr;
