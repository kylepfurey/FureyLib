
// Game Manager Template Script
// by Kyle Furey

// REQUIREMENT: GameManager.cpp

#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameManager.generated.h"

// Include this heading to use the class
// #include "Game Manager/GameManager.h"

/** A singleton object that allows easy access to other objects. */
UCLASS(Blueprintable, BlueprintType)
class MYGAME_API UGameManager : public UGameInstance
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
	UGameManager();

	/** Object initializer constructor. */
	UGameManager(const FObjectInitializer& ObjectInitializer);

	// New constructors here


	// UNREAL FUNCTIONS

	/** Called when the game is first initialized. */
	virtual void Init() override;

	/** Called when the game's current world changes. */
	virtual void OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld) override;

	/** Called when the game is closed. */
	virtual void Shutdown() override;


	// GAME MANAGER EVENTS

	/** Automatically called when the game's current world changes. */
	UFUNCTION(BlueprintNativeEvent, Category = "HandInteractableVR")
	void OnWorldChangedEvent(UWorld* OldWorld, UWorld* NewWorld);
	virtual void OnWorldChangedEvent_Implementation(UWorld* OldWorld, UWorld* NewWorld);

	// New events here


	// GAME MANAGER FUNCTIONS

	/** Retrieves the global instance of the game manager. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GameManager")
	static UGameManager* GetGameManager();

	/** Retrieves the current world. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GameManager")
	static UWorld* GetWorld();

	/** Retrieves the time in seconds since the last game tick. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GameManager")
	static float GetDeltaTime();

	// New functions here
};
