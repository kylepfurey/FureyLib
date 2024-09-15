
// VR Movable Lever Actor Script
// by Kyle Furey

// REQUIREMENTS: GrabbableVR.h, LeverVR.cpp

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/Vector.h"
#include "Math/Vector2D.h"
#include "Math/Rotator.h"
#include "Math/Quat.h"
#include "Math/Transform.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "VR/Grabbable/GrabbableVR.h"
#include "LeverVR.generated.h"

// Include this heading to use the class
// #include "VR/Lever/LeverVR.h"

/** Different types of directions a VR lever can move. */
UENUM(BlueprintType, Category = "LeverVR")
enum class ELeverModeVR : uint8
{
	BACKWARD_FORWARD = 0    UMETA(DisplayName = "Forward Backward"),
	LEFT_RIGHT = 1		    UMETA(DisplayName = "Left Right"),
	BIDIRECTIONAL = 2		UMETA(DisplayName = "Bidirectional"),
	JOYSTICK = 3			UMETA(DisplayName = "Joystick"),
	ANY_DIRECTION = 4		UMETA(DisplayName = "Any Direction"),
	MAX						UMETA(Hidden)
};

// Delegate declaration.
DECLARE_DYNAMIC_DELEGATE(FLeverDelegateVR);

/** Different axes a lever can move. */
UENUM(BlueprintType, meta = (Bitflags), Category = "LeverVR")
enum class ELeverAxisVR : uint8
{
	NONE = 0					UMETA(Hidden),
	BACKWARD = 1				UMETA(DisplayName = "Backward"),
	FORWARD = 2					UMETA(DisplayName = "Forward"),
	LEFT = 4					UMETA(DisplayName = "Left"),
	RIGHT = 8					UMETA(DisplayName = "Right"),
	MAX							UMETA(Hidden)
};

/** An actor with a knob the can be moved from a fixed point with a VR hand to trigger events. */
UCLASS(Blueprintable, BlueprintType, Abstract)
class MYGAME_API ALeverVR : public AActor
{
	GENERATED_BODY()

protected:

	// LEVER VARIABLES

	/** This lever's grab component. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LeverVR")
	UGrabbableVR* GrabComponent = nullptr;

	/** The pivot of this lever that will always face the knob. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LeverVR")
	USceneComponent* LeverPivot = nullptr;

	/** Whether this lever is active. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LeverVR")
	bool bActive = true;

	/** The directions this lever may be pushed or pulled. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), EditAnywhere, Category = "LeverVR")
	ELeverModeVR LeverMode = ELeverModeVR::BACKWARD_FORWARD;

	/** The minimum backward and maximum forward rotation value on the Y axis. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), EditAnywhere, Category = "LeverVR")
	FVector2D BackwardForwardClamp = FVector2D(-45, 45);

	/** The minimum left and maximum right rotation value on the X axis. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), EditAnywhere, Category = "LeverVR")
	FVector2D LeftRightClamp = FVector2D(-45, 45);

	/** Whether to reset the lever when it is not grabbed. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), EditAnywhere, Category = "LeverVR")
	bool bResetLever = true;

	/** The speed to reset the lever when it is not grabbed. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), EditAnywhere, Category = "LeverVR")
	float ResetSpeed = 5;

	/** The percentage the lever must be at to be considered down. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), EditAnywhere, Category = "LeverVR")
	float LeverDownPercent = 0.9;

	/** Events fired when the lever is backward. */
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn), Category = "LeverVR")
	FLeverDelegateVR OnLeverBackward = FLeverDelegateVR();

	/** Events fired when the lever is forward. */
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn), Category = "LeverVR")
	FLeverDelegateVR OnLeverForward = FLeverDelegateVR();

	/** Events fired when the lever is left. */
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn), Category = "LeverVR")
	FLeverDelegateVR OnLeverLeft = FLeverDelegateVR();

	/** Events fired when the lever is right. */
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn), Category = "LeverVR")
	FLeverDelegateVR OnLeverRight = FLeverDelegateVR();

	/** The position of this actor before it was grabbed. This is used to lock the actor in place. */
	FVector GrabbedPosition = FVector();

	/** The rotation of this actor before it was grabbed. This is used to lock the actor in place. */
	FRotator GrabbedRotation = FRotator();


	// UNREAL FUNCTIONS

	/** Called when the game starts or when spawned. */
	virtual void BeginPlay() override;


	// LEVER FUNCTIONS

	/** Gets a float rotation in degrees from the angle of the given start point to the given end point. */
	virtual float GetDegreesRotation(FVector2D Start, FVector2D End);

public:

	// CONSTRUCTORS

	/** Default constructor. */
	ALeverVR();

	/** Object initializer constructor. */
	ALeverVR(const FObjectInitializer& ObjectInitializer);

	/** LeverVR constructor. */
	ALeverVR(bool Active, ELeverModeVR _LeverMode = ELeverModeVR::BACKWARD_FORWARD, FVector2D _BackwardForwardClamp = FVector2D(-45, 45), FVector2D _LeftRightClamp = FVector2D(-45, 45), bool ResetLever = true, float _ResetSpeed = 5, float _LeverDownPercent = 0.9);


	// UNREAL FUNCTIONS

	/** Called every frame. */
	virtual void Tick(float DeltaTime) override;


	// GETTERS

	/** Returns the lever's grab component. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LeverVR")
	virtual UGrabbableVR* GetGrabComponent();

	/** Returns the pivot of this lever that will always face the knob. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LeverVR")
	virtual USceneComponent* GetLeverPivot();

	/** Returns the directions this lever may be pushed or pulled. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LeverVR")
	virtual ELeverModeVR GetLeverMode();

	/** Returns whether this lever is active. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LeverVR")
	virtual bool IsActive();

	/** Returns the minimum backward and maximum forward rotation value on the Y axis. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LeverVR")
	virtual FVector2D GetBackwardForwardClamp();

	/** Returns the minimum left and maximum right rotation value on the X axis. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LeverVR")
	virtual FVector2D GetLeftRightClamp();

	/** Returns whether to reset the lever when it is not grabbed. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LeverVR")
	virtual bool IsResettingLever();

	/** Returns the speed to reset the lever when it is not grabbed. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LeverVR")
	virtual float GetResetSpeed();

	/** Returns the percentage the lever must be at to be considered down. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LeverVR")
	virtual float GetLeverDownPercent();

	/** Returns the events fired when the lever is backward. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LeverVR")
	virtual FLeverDelegateVR& GetOnLeverBackwardEvent();

	/** Returns the events fired when the lever is forward. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LeverVR")
	virtual FLeverDelegateVR& GetOnLeverForwardEvent();

	/** Returns the events fired when the lever is left. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LeverVR")
	virtual FLeverDelegateVR& GetOnLeverLeftEvent();

	/** Returns the events fired when the lever is right. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LeverVR")
	virtual FLeverDelegateVR& GetOnLeverRightEvent();


	// SETTERS

	/** Sets the lever's grab component. */
	UFUNCTION(BlueprintCallable, Category = "LeverVR")
	virtual void SetGrabComponent(UGrabbableVR* _GrabComponent);

	/** Sets the pivot of this lever that will always face the knob. */
	UFUNCTION(BlueprintCallable, Category = "LeverVR")
	virtual void SetLeverPivot(USceneComponent* _LeverPivot);

	/** Sets whether this lever is active. */
	UFUNCTION(BlueprintCallable, Category = "LeverVR")
	virtual void SetActive(bool Active);

	/** Sets the directions this lever may be pushed or pulled. */
	UFUNCTION(BlueprintCallable, Category = "LeverVR")
	virtual void SetLeverMode(ELeverModeVR _LeverMode);

	/** Sets the minimum backward and maximum forward rotation value on the Y axis. */
	UFUNCTION(BlueprintCallable, Category = "LeverVR")
	virtual void SetBackwardForwardClamp(FVector2D _BackwardForwardClamp);

	/** Sets the minimum left and maximum right rotation value on the X axis. */
	UFUNCTION(BlueprintCallable, Category = "LeverVR")
	virtual void SetLeftRightClamp(FVector2D _LeftRightClamp);

	/** Sets whether to reset the lever when it is not grabbed. */
	UFUNCTION(BlueprintCallable, Category = "LeverVR")
	virtual void SetResetLever(bool ResetLever);

	/** Sets the speed to reset the lever when it is not grabbed. */
	UFUNCTION(BlueprintCallable, Category = "LeverVR")
	virtual void SetResetSpeed(float _ResetSpeed);

	/** Sets the percentage the lever must be at to be considered down. */
	UFUNCTION(BlueprintCallable, Category = "LeverVR")
	virtual void SetLeverDownPercent(float _LeverDownPercent);

	/** Binds an event to be fired when the lever is backward. */
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "Event"), Category = "LeverVR")
	virtual void BindOnLeverBackwardEvent(const FLeverDelegateVR& Event);

	/** Binds an event to be fired when the lever is forward. */
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "Event"), Category = "LeverVR")
	virtual void BindOnLeverForwardEvent(const FLeverDelegateVR& Event);

	/** Binds an event to be fired when the lever is left. */
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "Event"), Category = "LeverVR")
	virtual void BindOnLeverLeftEvent(const FLeverDelegateVR& Event);

	/** Binds an event to be fired when the lever is right. */
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "Event"), Category = "LeverVR")
	virtual void BindOnLeverRightEvent(const FLeverDelegateVR& Event);


	// LEVER FUNCTIONS

	/** Updates the state of this lever. */
	UFUNCTION(BlueprintCallable, Category = "LeverVR")
	virtual void UpdateLever(float DeltaTime = 0.001);

	/** Returns the current percentage of the lever in the given direction. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LeverVR")
	virtual float GetLeverPercentage(ELeverAxisVR Axis);

	/** Returns whether the lever is currently down for the given axis. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LeverVR")
	virtual bool IsLeverDown(ELeverAxisVR Axis);

	/**
	* Returns the percentages of each axis of the lever.
	* Note: Negative axes implies the axis is in the negative direction.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LeverVR")
	virtual FVector2D GetLeverAxes();

	/** Returns the current normalized 2D direction of the lever. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LeverVR")
	virtual FVector2D GetLeverDirection();

	/** Spawns a new ALeverVR into the world. */
	UFUNCTION(BlueprintCallable, Category = "LeverVR")
	static ALeverVR* SpawnLeverVR(UClass* LeverClass, FTransform SpawnTransform, bool Active = true, ELeverModeVR _LeverMode = ELeverModeVR::BACKWARD_FORWARD, FVector2D _BackwardForwardClamp = FVector2D(-45, 45), FVector2D _LeftRightClamp = FVector2D(-45, 45), bool ResetLever = true, float _ResetSpeed = 5, float _LeverDownPercent = 0.9);
};
