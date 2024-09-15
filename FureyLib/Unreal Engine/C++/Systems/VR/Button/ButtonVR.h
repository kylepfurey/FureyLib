
// VR Clickable Button Component Script
// by Kyle Furey

// REQUIREMENT: GrabbableVR.h, ButtonVR.cpp

#pragma once
#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Sound/SoundBase.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "VR/Grabbable/GrabbableVR.h"
#include "ButtonVR.generated.h"

// Include this heading to use the class
// #include "VR/Button/ButtonVR.h"

// Delegate declaration.
DECLARE_DYNAMIC_DELEGATE(FButtonDelegateVR);

/** A component attached to an actor that can be clicked with a VR hand to trigger events. */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (ButtonVR), meta = (BlueprintSpawnableComponent))
class MYGAME_API UButtonVR : public USceneComponent
{
	GENERATED_BODY()

protected:

	// BUTTON VARIABLES

	/** The model moved with the button. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), EditAnywhere, Category = "ButtonVR")
	UStaticMeshComponent* ButtonModel = nullptr;

	/** The collider used to check for player input. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), EditAnywhere, Category = "ButtonVR")
	UPrimitiveComponent* ButtonCollider = nullptr;

	/** Whether this button is currently active. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "ButtonVR")
	bool bActive = true;

	/** Whether this button stays clicked on unclick. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "ButtonVR")
	bool bSticky = true;

	/** Whether the button is currently clicked. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "ButtonVR")
	bool bClicked = false;

	/** The relative height of the button when its not clicked down. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "ButtonVR")
	float UnclickedHeight = 7.5;

	/** The relative height of the button when its clicked down. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "ButtonVR")
	float ClickedHeight = 2.5;

	/** The speed the button moves to its next state. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "ButtonVR")
	float ButtonSpeed = 10;

	/** The sound to play when the button is clicked. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "ButtonVR")
	USoundBase* ClickedSound = nullptr;

	/** The sound to play when the button is unclicked. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "ButtonVR")
	USoundBase* UnclickedSound = nullptr;

	/** An event called when the button is clicked or first held down. */
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn), Category = "ButtonVR")
	FButtonDelegateVR OnClick = FButtonDelegateVR();

	/** An event called when the button is unclicked or released. */
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn), Category = "ButtonVR")
	FButtonDelegateVR OnUnclick = FButtonDelegateVR();

	/** An event called while the button is clicked or held down. */
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn), Category = "ButtonVR")
	FButtonDelegateVR WhileClicked = FButtonDelegateVR();

	/** Whether the button is currently in contact with the player. */
	UPROPERTY(BlueprintReadOnly, Category = "ButtonVR")
	bool bHeld = false;


	// UNREAL FUNCTIONS

	/** Called when the game starts or when spawned. */
	virtual void BeginPlay() override;

public:

	// CONSTRUCTORS

	/** Default constructor. */
	UButtonVR();

	/** Object initializer constructor. */
	UButtonVR(const FObjectInitializer& ObjectInitializer);

	/** ButtonVR constructor. */
	UButtonVR(UStaticMeshComponent* _ButtonModel, UPrimitiveComponent* _ButtonCollider = nullptr, bool Active = true, bool Sticky = true, bool Clicked = false, float _UnclickedHeight = 7.5, float _ClickedHeight = 2.5, float _ButtonSpeed = 10, USoundBase* _ClickedSound = nullptr, USoundBase* _UnclickedSound = nullptr);


	// UNREAL FUNCTIONS

	/** Called every frame. */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	// GETTERS

	/** Returns the model moved with the button. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ButtonVR")
	virtual UStaticMeshComponent* GetButtonModel();

	/** Returns the collider used to check for player input. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ButtonVR")
	virtual UPrimitiveComponent* GetButtonCollider();

	/** Returns whether this button is currently active. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ButtonVR")
	virtual bool IsButtonActive();

	/** Returns whether this button stays clicked on unclick. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ButtonVR")
	virtual bool IsSticky();

	/** Returns whether the button is currently clicked. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ButtonVR")
	virtual bool IsClicked();

	/** Returns the relative height of the button when its not clicked down. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ButtonVR")
	virtual float GetUnclickedHeight();

	/** Returns the relative height of the button when its clicked down. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ButtonVR")
	virtual float GetClickedHeight();

	/** Returns the speed the button moves to its next state. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ButtonVR")
	virtual float GetButtonSpeed();

	/** Returns the sound to play when the button is clicked. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ButtonVR")
	virtual USoundBase* GetClickedSound();

	/** Returns the sound to play when the button is unclicked. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ButtonVR")
	virtual USoundBase* GetUnclickedSound();

	/** Returns the event called when the button is clicked or first held down. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ButtonVR")
	virtual FButtonDelegateVR& GetOnClickEvent();

	/** Returns the event called when the button is unclicked or released. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ButtonVR")
	virtual FButtonDelegateVR& GetOnUnclickEvent();

	/** Returns the event called while the button is clicked or held down. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ButtonVR")
	virtual FButtonDelegateVR& GetWhileClickedEvent();

	/** Returns whether the button is currently held down. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ButtonVR")
	virtual bool IsHeld();


	// SETTERS

	/** Sets the model moved with the button. */
	UFUNCTION(BlueprintCallable, Category = "ButtonVR")
	virtual void SetButtonModel(UStaticMeshComponent* _ButtonModel);

	/** Sets the collider used to check for player input. */
	UFUNCTION(BlueprintCallable, Category = "ButtonVR")
	virtual void SetButtonCollider(UPrimitiveComponent* _ButtonCollider);

	/** Sets whether this button is currently active. */
	UFUNCTION(BlueprintCallable, Category = "ButtonVR")
	virtual void SetButtonActive(bool Active);

	/** Sets whether this button stays clicked on unclick. */
	UFUNCTION(BlueprintCallable, Category = "ButtonVR")
	virtual void SetSticky(bool Sticky);

	/** Sets whether the button is currently clicked. */
	UFUNCTION(BlueprintCallable, Category = "ButtonVR")
	virtual void SetClicked(bool Clicked);

	/** Sets the relative height of the button when it’s not clicked down. */
	UFUNCTION(BlueprintCallable, Category = "ButtonVR")
	virtual void SetUnclickedHeight(float _UnclickedHeight);

	/** Sets the relative height of the button when it’s clicked down. */
	UFUNCTION(BlueprintCallable, Category = "ButtonVR")
	virtual void SetClickedHeight(float _ClickedHeight);

	/** Sets the speed the button moves to its next state. */
	UFUNCTION(BlueprintCallable, Category = "ButtonVR")
	virtual void SetButtonSpeed(float _ButtonSpeed);

	/** Sets the sound to play when the button is clicked. */
	UFUNCTION(BlueprintCallable, Category = "ButtonVR")
	virtual void SetClickedSound(USoundBase* _ClickedSound);

	/** Sets the sound to play when the button is unclicked. */
	UFUNCTION(BlueprintCallable, Category = "ButtonVR")
	virtual void SetUnclickedSound(USoundBase* _UnclickedSound);

	/** Sets the event called when the button is clicked or first held down. */
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "Event"), Category = "ButtonVR")
	virtual void BindOnClickEvent(const FButtonDelegateVR& Event);

	/** Sets the event called when the button is unclicked or released. */
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "Event"), Category = "ButtonVR")
	virtual void BindOnUnclickEvent(const FButtonDelegateVR& Event);

	/** Sets the event called while the button is clicked or held down. */
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "Event"), Category = "ButtonVR")
	virtual void BindWhileClickedEvent(const FButtonDelegateVR& Event);


	// BUTTON FUNCTIONS

	/**
	* Clicks the button down or back up.
	* Returns the buttons new clicked state.
	*/
	UFUNCTION(BlueprintCallable, Category = "ButtonVR")
	virtual bool Click(bool InvokeEvent = true);

	/**
	* Attempts to unclick the button.
	* Returns if the unclick was successful.
	*/
	UFUNCTION(BlueprintCallable, Category = "ButtonVR")
	virtual bool Unclick(bool InvokeEvent = true);

	/**
	* Updates the button's current state.
	* Automatically called while active.
	*/
	UFUNCTION(BlueprintCallable, Category = "ButtonVR")
	virtual void UpdateButton(float DeltaTime = 0.001);

	/** Constructs a new ButtonVR component. */
	UFUNCTION(BlueprintCallable, Category = "ButtonVR")
	static UButtonVR* ConstructButtonVR(USceneComponent* Parent, UStaticMeshComponent* _ButtonModel, UPrimitiveComponent* _ButtonCollider, bool Active = true, bool Sticky = true, bool Clicked = false, float _UnclickedHeight = 7.5, float _ClickedHeight = 2.5, float _ButtonSpeed = 10, USoundBase* _ClickedSound = nullptr, USoundBase* _UnclickedSound = nullptr);
};
