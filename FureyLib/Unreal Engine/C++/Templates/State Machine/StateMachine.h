
// Template State Machine Script
// by Kyle Furey

// REQUIREMENT: StateMachine.cpp

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateMachine.generated.h"

// Include this heading to use the class
// #include "State Machine/StateMachine.h"

// Forward declaration of UStateMachine.
class UStateMachine;

/** The base class for each state. All states should inherit from this class. */
UCLASS(Blueprintable, BlueprintType, Abstract)
class MYGAME_API UStateBase : public UObject
{
	GENERATED_BODY()

protected:

	// STATE BASE VARIABLES

	/** The inherited state machine from the owner. */
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn), Category = "State Machine")
	UStateMachine* StateMachine = nullptr;

public:

	// STATE BASE CONSTRUCTORS

	/** Default constructor. */
	UStateBase();

	/** Object initializer constructor. */
	UStateBase(const FObjectInitializer& ObjectInitializer);

	/** State machine constructor. */
	UStateBase(UStateMachine* _StateMachine);


	// STATE BASE GETTERS

	/** Returns this state's state machine. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "State Machine")
	virtual UStateMachine* GetStateMachine();

	/** Returns this state's class. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "State Machine")
	virtual UClass* GetStateClass();

	/** Returns a new state of the given state class and state machine. */
	UFUNCTION(BlueprintCallable, Category = "State Machine")
	static UStateBase* ConstructState(UClass* StateClass, UStateMachine* _StateMachine);


	// STATE BASE EVENTS

	/** Called when this state is set as the state machine's current state. */
	UFUNCTION(BlueprintNativeEvent, Category = "State Machine")
	void OnStateBegin();
	virtual void OnStateBegin_Implementation();

	/** Called every frame while this state is the state machine's current state. */
	UFUNCTION(BlueprintNativeEvent, Category = "State Machine")
	void OnStateTick(float DeltaTime);
	virtual void OnStateTick_Implementation(float DeltaTime);

	/** Called when this state machine's current state is no longer this state. */
	UFUNCTION(BlueprintNativeEvent, Category = "State Machine")
	void OnStateEnd();
	virtual void OnStateEnd_Implementation();
};

/** Base for building a state machine. */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (StateMachine), meta = (BlueprintSpawnableComponent))
class MYGAME_API UStateMachine : public UActorComponent
{
	GENERATED_BODY()

protected:

	// STATE MACHINE VARIABLES

	/** The current state of this state machine. */
	UPROPERTY(BlueprintReadOnly, Category = "State Machine")
	UStateBase* CurrentState = nullptr;

	/**
	* The state to start this state machine in.
	* Blueprints should set this in the default settings.
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (ExposeOnSpawn), Category = "State Machine")
	UClass* StartingStateClass = nullptr;


	// UNREAL FUNCTIONS

	/** Called when the game starts. */
	virtual void BeginPlay() override;

public:

	// STATE MACHINE CONSTRUCTORS

	/** Default constructor. */
	UStateMachine();

	/** Object initializer constructor. */
	UStateMachine(const FObjectInitializer& ObjectInitializer);

	/** Starting state constructor. */
	UStateMachine(UClass* _StartingStateClass);


	// UNREAL FUNCTIONS

	/** Called every frame. */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	// STATE MACHINE GETTERS

	/** Returns the current state of this state machine. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "State Machine")
	virtual UStateBase* GetCurrentState();

	/** Returns the class of the current state of this state machine. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "State Machine")
	virtual UClass* GetCurrentStateClass();

	/** Returns the starting state class of this state machine. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "State Machine")
	virtual UClass* GetStartingState();

	/** Returns whether the current state is null. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "State Machine")
	virtual bool IsStateNull();

	/** Returns a new state machine component starting with the given state class. */
	UFUNCTION(BlueprintCallable, Category = "State Machine")
	static UStateMachine* ConstructStateMachine(AActor* Parent, UClass* _StartingStateClass = nullptr);


	// STATE MACHINE FUNCTIONS

	/**
	* Properly switches the state machine's current state to the given state type.
	* Returns whether the switch was successful.
	*/
	UFUNCTION(BlueprintCallable, Category = "State Machine")
	virtual bool SwitchState(UClass* NewStateClass);
};
