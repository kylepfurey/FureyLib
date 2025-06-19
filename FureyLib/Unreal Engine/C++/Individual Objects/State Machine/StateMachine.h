// .h
// State Machine Actor Component Script
// by Kyle Furey

#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Components/ActorComponent.h"
#include "StateMachine.generated.h"


// STATE

/** Forward declaration of UStateMachine. */
class UStateMachine;

UINTERFACE(Blueprintable, BlueprintType, MinimalAPI)
class UState : public UInterface
{
	GENERATED_BODY()
};

/** An optional interface used to help define a state machine component's events. */
class MYGAME_API IState
{
	GENERATED_BODY()

public:

	// INTERFACE

	/** Returns the UStateMachine component that owns this state. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State Machine", meta = (Keywords = "Get, State, Machine"))
	UStateMachine* GetStateMachine() const;
	virtual UStateMachine* GetStateMachine_Implementation() const;

	/** Sets the UStateMachine component that owns this state. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State Machine", meta = (Keywords = "Set, State, Machine"))
	void SetStateMachine(UStateMachine* StateMachine);
	virtual void SetStateMachine_Implementation(UStateMachine* StateMachine);
};


// STATE MACHINE

/** How destroying is handled with state components. */
UENUM(BlueprintType, Category = "State Machine")
enum class EStateDestroyBehaviour : uint8
{
	NEVER				UMETA(DisplayName = "NEVER"),
	MY_COMPONENTS		UMETA(DisplayName = "My Components"),
	OTHER_COMPONENTS	UMETA(DisplayName = "Other Components"),
	ALWAYS				UMETA(DisplayName = "Always"),
	MAX					UMETA(Hidden)
};

/** Events to call when the current state component is switched. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSwitchState, UActorComponent*, NewState);

/** A component used to manage an actor's state through switching a single component. */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (StateMachine), meta = (BlueprintSpawnableComponent), Category = "State Machine")
class MYGAME_API UStateMachine : public UActorComponent
{
	GENERATED_BODY()

protected:

	// VARIABLES

	/** The state machine's current state component. */
	UPROPERTY(Instanced, BlueprintReadOnly, EditAnywhere, BlueprintGetter = "GetState", Category = "State Machine")
	UActorComponent* State = nullptr;

	/** The class of the state machine's starting state component. */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, BlueprintGetter = "GetStartingStateClass", meta = (ExposeOnSpawn), Category = "State Machine")
	TSubclassOf<UActorComponent> StartingStateClass;

	/** Events to call when the current state component is switched. */
	UPROPERTY(BlueprintAssignable, Category = "State Machine")
	FOnSwitchState OnSwitchState;

	/** When components are destroyed by this state machine. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintGetter = "GetDestroyBehaviour", BlueprintSetter = "SetDestroyBehaviour", meta = (ExposeOnSpawn), Category = "State Machine")
	EStateDestroyBehaviour DestroyBehaviour = EStateDestroyBehaviour::ALWAYS;


	// EVENTS

	/** Initializes the starting state component. */
	virtual void BeginPlay() override;

	/** Cleans up the state machine's current state component. */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:

	// CONSTRUCTORS

	/** Default constructor. */
	UStateMachine();

	/** Object initializer constructor. */
	UStateMachine(const FObjectInitializer& ObjectInitializer);


	// GETTERS

	/** Returns the state machine's current state component. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "State Machine")
	virtual UActorComponent* GetState() const;

	/** Returns the class of the state machine's current state component. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "State Machine")
	virtual TSubclassOf<UActorComponent> GetStateClass() const;

	/** Returns the class of the state machine's starting state component. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "State Machine")
	virtual TSubclassOf<UActorComponent> GetStartingStateClass() const;

	/** Returns the behaviour set for when components are destroyed by this state machine. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "State Machine")
	virtual EStateDestroyBehaviour GetDestroyBehaviour() const;

	/** Returns whether the state machine's current state component is valid. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "State Machine")
	virtual bool IsStateValid() const;

	/** Returns whether the state machine's current state component is the given component class. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "State Machine")
	virtual bool StateIs(TSubclassOf<UActorComponent> StateClass) const;

	/** Returns whether the state machine's current state component is the given component class. */
	template<typename UStateClass>
	bool StateIs() const {
		return Cast<UStateClass>(State) != nullptr;
	}

	/** Returns the state machine's current state component as the given component class. */
	template<typename UStateClass>
	UStateClass* StateAs() const {
		return Cast<UStateClass>(State);
	}


	// SETTERS

	/** Sets the behaviour set for when components are destroyed by this state machine. */
	UFUNCTION(BlueprintCallable, Category = "State Machine")
	virtual void SetDestroyBehaviour(const EStateDestroyBehaviour _DestroyBehaviour);

	/** Switches the state machine's state component to the given state component. */
	UFUNCTION(BlueprintCallable, Category = "State Machine")
	virtual UActorComponent* SwitchStateTo(UActorComponent* NewState);

	/** Switches the state machine's state component to a new state component of the given class. */
	UFUNCTION(BlueprintCallable, Category = "State Machine")
	virtual UActorComponent* SwitchState(TSubclassOf<UActorComponent> StateClass);

	/** Switches the state machine's state component to a new state component of the given class. */
	template<typename UStateClass>
	UStateClass* SwitchState() {
		return Cast<UStateClass>(SwitchState(UStateClass::StaticClass()));
	}

	/**
	 * Destroys this state machine's current state component based on its destroy behaviour.
	 * Returns whether the component was successfully destroyed.
	 */
	UFUNCTION(BlueprintCallable, Category = "State Machine")
	virtual bool DestroyState();
};
