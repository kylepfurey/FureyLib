// .h
// Singleton Subsystem Base Class
// by Kyle Furey

#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Singleton.generated.h"


// SINGLETON

/** Allows a derived class or blueprint to have a single global instance via USingleton::Instance<T>(). */
UCLASS(Blueprintable, BlueprintType, Abstract, meta = (Category = "Singleton"))
class MYGAME_API USingleton : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	// EVENTS

	/** Returns whether the subsystem should be instantiated. */
	bool ShouldCreateSubsystem(UObject* Outer) const override;

	/** Returns whether the singleton should be instantiated. */
	UFUNCTION(BlueprintNativeEvent, Category = "Singleton")
	bool ShouldCreateSingleton() const;
	virtual bool ShouldCreateSingleton_Implementation() const;

	/** Initializes the subsystem. */
	void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Initializes the singleton. */
	UFUNCTION(BlueprintNativeEvent, Category = "Singleton")
	void OnInitialize();
	virtual void OnInitialize_Implementation();

	/** Cleans up the subsystem. */
	void Deinitialize() override;

	/** Cleans up the singleton. */
	UFUNCTION(BlueprintNativeEvent, Category = "Singleton")
	void OnDeinitialize();
	virtual void OnDeinitialize_Implementation();


	// METHODS

	/** Returns the singleton instance of this class or blueprint. */
	template<typename T>
	static T* Instance() {
		return GetSubsystem<T>();
	}
};
