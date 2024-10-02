
// VR Grabbable Actor Component Script
// by Kyle Furey

// REQUIREMENT: HandTrackerVR.h, ControllerInputVR.h, GrabbableVR.cpp

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Containers/Array.h"
#include "Containers/Set.h"
#include "Math/Vector.h"
#include "Math/Rotator.h"
#include "Math/Quat.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "VR/Hand Tracking/HandTrackerVR.h"
#include "VR/Controller Input/ControllerInputVR.h"
#include "GrabbableVR.generated.h"

// Include this heading to use the class
// #include "VR/Grabbable/GrabbableVR.h"

// The percentage a grab input should be at least at to grab an object.
#define GRAB_TRIGGER_PERCENT 0.5

// The delay in seconds before completing a throw (used for easier aiming).
#define THROW_DELAY 0.01

/** The priority of a grab point being chosen over another nearby grab point. */
UENUM(BlueprintType, Category = "GrabbableVR")
enum class EGrabPointPriorityVR : uint8
{
	LOW = 0			UMETA(DisplayName = "Low Priority"),
	NORMAL = 1		UMETA(DisplayName = "Normal Priority"),
	HIGH = 2		UMETA(DisplayName = "High Priority"),
	MAX				UMETA(Hidden)
};

/**
* Represents a single grab point on an actor.
* This structure is used for GrabbableVR components.
*/
USTRUCT(BlueprintType)
struct MYGAME_API FGrabPointVR
{
	GENERATED_BODY()

public:

	// GRAB VARIABLES

	/** The allowed gestures for this grab point. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GrabPointVR")
	TArray<EHandGestureVR> Gestures = { EHandGestureVR::FIST };

	/** The name of this grab point. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GrabPointVR")
	FName GrabPointName = TEXT("New Grab Point");

	/**
	* The collider used in collision detection for this grab point.
	* This collider is used as the origin and optionally as the rotation of this grab point.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GrabPointVR")
	UPrimitiveComponent* Collider = nullptr;

	/** The offset applied to the grab point's location from the palm of the player's hand when grabbed. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GrabPointVR")
	FVector HandOffset = FVector(0, 0, 0);

	/** Whether to use the set offset rotation value (true) or the rotation of the object relative to when it was grabbed (false). */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GrabPointVR")
	bool bUseRotationOffset = true;

	/** The offset applied to the grab point's rotation when grabbed. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GrabPointVR")
	FRotator RotationOffset = FRotator(0, 0, 0);

	/** The priority value of this grab point. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GrabPointVR")
	EGrabPointPriorityVR Priority = EGrabPointPriorityVR::NORMAL;


	// GRAB POINT CONSTRUCTORS

	/** Default constructor. */
	FGrabPointVR();

	/** Grab point constructor. */
	FGrabPointVR(TArray<EHandGestureVR> _Gestures, FName _GrabPointName = TEXT("New Grab Point"), UPrimitiveComponent* _Collider = nullptr, FVector _HandOffset = FVector(0, 0, 0), bool UseRotationOffset = true, FRotator _RotationOffset = FRotator(0, 0, 0), EGrabPointPriorityVR _Priority = EGrabPointPriorityVR::NORMAL);


	// GRAB POINT EQUALITY

	/** Returns if this grab point is equal to the given grab point are equal. */
	bool operator==(const FGrabPointVR& GrabPoint) const;
};

// Returns a hash code for this grab point.
FORCEINLINE uint32 GetTypeHash(const FGrabPointVR& GrabPoint)
{
	return ::GetTypeHash(GrabPoint.Collider);
}

/** Which hands can be used to grab a grabbable object in VR. */
UENUM(BlueprintType, Category = "GrabbableVR")
enum class EGrabModeVR : uint8
{
	NONE = 0			UMETA(DisplayName = "None"),
	LEFT_ONLY = 1		UMETA(DisplayName = "Left Hand Only"),
	RIGHT_ONLY = 2		UMETA(DisplayName = "Right Hand Only"),
	DOMINANT = 3		UMETA(DisplayName = "Dominant Hand Only"),
	NON_DOMINANT = 4	UMETA(DisplayName = "Non-Dominant Hand Only"),
	BOTH = 5			UMETA(DisplayName = "Both Hands"),
	MAX					UMETA(Hidden)
};

/** VR grabbable object gravity settings. */
UENUM(BlueprintType, Category = "GrabbableVR")
enum class EGravitySettingVR : uint8
{
	UNCHANGED = 0		UMETA(DisplayName = "Keep Gravity Setting"),
	APPLY_GRAVITY = 1	UMETA(DisplayName = "Apply Gravity On Drop"),
	NO_GRAVITY = 2		UMETA(DisplayName = "No Gravity On Drop"),
	MAX					UMETA(Hidden)
};

/** VR grabbable object throw calculation settings. */
UENUM(BlueprintType, Category = "GrabbableVR")
enum class EThrowCalculationVR : uint8
{
	DIRECTION = 0			UMETA(DisplayName = "Calculate With Subtraction"),
	DISTANCE = 1			UMETA(DisplayName = "Calculate With Distance"),
	DISTANCE_SQUARED = 2	UMETA(DisplayName = "Calculate With Squared Distance"),
	MAX						UMETA(Hidden)
};

// Delegate declaration.
DECLARE_DYNAMIC_DELEGATE(FGrabDelegateVR);

/** Allows an actor to be picked up and possibly thrown by VR hands. */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (GrabbableVR), meta = (BlueprintSpawnableComponent))
class MYGAME_API UGrabbableVR : public UActorComponent, public IHandInteractableVR
{
	GENERATED_BODY()

protected:

	/** Each individual grab point on the actor used to check for grab collision. */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (ExposeOnSpawn), Category = "GrabbableVR")
	TArray<FGrabPointVR> GrabPoints = TArray<FGrabPointVR>();

	/** Whether this grabbed object is active. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintGetter = "IsGrabActive", BlueprintSetter = "SetGrabActive", meta = (ExposeOnSpawn), Category = "GrabbableVR")
	bool bActive = true;

	/** Whether this grabbed object uses hand tracking (true) or controller input (false) for the player's hands. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintGetter = "IsUsingHandTracking", BlueprintSetter = "SetUseHandTracking", meta = (ExposeOnSpawn), Category = "GrabbableVR")
	bool bHandTracking = true;

	/** The left grab button (used for controller input). */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (ExposeOnSpawn), Category = "GrabbableVR")
	UInputAction* IA_Grab_Button_Left = nullptr;

	/** The right grab button (used for controller input). */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (ExposeOnSpawn), Category = "GrabbableVR")
	UInputAction* IA_Grab_Button_Right = nullptr;

	/** What hands are allowed to be used for grabbing this object. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GrabbableVR")
	EGrabModeVR GrabMode = EGrabModeVR::BOTH;

	/** The maximum delay in seconds the player can grab an object when gesturing within range. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GrabbableVR")
	float GrabBuffer = 0.5f;

	/** The primary collider for this object. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GrabbableVR")
	UPrimitiveComponent* PrimaryCollider = nullptr;

	/** Whether physics are applied to this object while grabbed (true) or this object just jumps to the hand's next location (false). */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GrabbableVR")
	bool bGrabPhysics = true;

	/** The change in gravity to apply to the object when dropped. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GrabbableVR")
	EGravitySettingVR GravitySetting = EGravitySettingVR::UNCHANGED;

	/** Whether this grabbed object is locked to the player's hand when grabbed until unlocked. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GrabbableVR")
	bool bLocked = false;

	/** Whether this grabbed object can be thrown. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GrabbableVR")
	bool bThrowable = true;

	/** The scale applied to the calculated thrown direction and force. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GrabbableVR")
	float ThrowScale = 200;

	/** The minimum distance to check for throwing when releasing an object from the player's hand. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GrabbableVR")
	float MinimumThrowDistance = 1;

	/** The type of calculation used to determine the force applied to a thrown object. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GrabbableVR")
	EThrowCalculationVR ThrowCalculation = EThrowCalculationVR::DIRECTION;

	/** The offset applied to a thrown object's direction. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GrabbableVR")
	FRotator ThrowRotationOffset = FRotator(0, 0, -10);

	/** The delay before enabling hand collision when dropping or throwing an object. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GrabbableVR")
	float CollisionDelay = 0.5f;

	/** An event called when the object is grabbed. */
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn), Category = "GrabbableVR")
	FGrabDelegateVR OnGrab = FGrabDelegateVR();

	/** An event called when the object is dropped. */
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn), Category = "GrabbableVR")
	FGrabDelegateVR OnDrop = FGrabDelegateVR();

	/** An event called when the object is thrown. */
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn), Category = "GrabbableVR")
	FGrabDelegateVR OnThrow = FGrabDelegateVR();

	/** The current held object in the left hand. */
	static UGrabbableVR* LeftGrabbedObject;

	/** The current held object in the right hand. */
	static UGrabbableVR* RightGrabbedObject;

	/** The object used for checking left hand collisions. */
	static UPrimitiveComponent* LeftHandCollider;

	/** The object used for checking right hand collisions. */
	static UPrimitiveComponent* RightHandCollider;

	/** All currently valid grab points in the left hand. */
	static TSet<FGrabPointVR> LeftGrabbablePoints;

	/** All currently valid grab points in the right hand. */
	static TSet<FGrabPointVR> RightGrabbablePoints;

	/** The time in seconds since the left hand initiated a grab gesture. */
	float LeftGrabTime = 0;

	/** The time in seconds since the right hand initiated a grab gesture. */
	float RightGrabTime = 0;

	/** The previous gravity setting when an object is grabbed. */
	bool bPreviousGravitySetting = false;

	/** The location of this object before it is about to be thrown. */
	FVector PreviousPosition = FVector(0, 0, 0);

	/** The rotation of this object when it was grabbed. */
	FRotator GrabbedRotation = FRotator(0, 0, 0);

	/** The previous response to pawn collisions. */
	ECollisionResponse PreviousPawnCollision = ECollisionResponse::ECR_Block;

	/** The hand that is grabbing this object. */
	USceneComponent* GrabbedHand = nullptr;

	/** The rotation of the grabbed hand when this object is grabbed. */
	FRotator HandRotation = FRotator(0, 0, 0);

	/** The type of hand that is grabbing this object. */
	bool bIsGrabbedRight = false;

	/** The current grabbed point. */
	FGrabPointVR GrabbedPoint = FGrabPointVR();

	/** The percentage of how much the left grab button is currently down. */
	float LeftDown = 0;

	/** The percentage of how much the right grab button is currently down.*/
	float RightDown = 0;

	/** The event binding for the left grab button being pressed. */
	FEnhancedInputActionEventBinding* LeftPress = nullptr;

	/** The event binding for the right grab button being pressed. */
	FEnhancedInputActionEventBinding* RightPress = nullptr;

	/** The event binding for the left grab button being released. */
	FEnhancedInputActionEventBinding* LeftRelease = nullptr;

	/** The event binding for the right grab button being released. */
	FEnhancedInputActionEventBinding* RightRelease = nullptr;


	// UNREAL FUNCTIONS

	/** Called when the game starts. */
	virtual void BeginPlay() override;

	/** Called when this component is destroyed. */
	virtual void BeginDestroy() override;


	// GRABBABLE FUNCTIONS

	/**
	* Binds controller input to grab events.
	* Returns whether the bind was successful.
	*/
	virtual bool BindInput(bool bIsRight);

	/**
	* Unbinds controller input to grab events.
	* Returns whether the unbind was successful.
	*/
	virtual bool UnbindInput(bool bIsRight);

	/** Reenables collision with pawns (used for delays). */
	virtual void ReenablePawnCollision();

	/** Completes a throw motion (used for delays). */
	virtual void CompleteThrow();

	/** Gets the proper offset vector. */
	virtual FVector GetOffset();

public:

	// GRABBABLE CONSTRUCTORS

	/** Default constructor. */
	UGrabbableVR();

	/** Object initializer constructor. */
	UGrabbableVR(const FObjectInitializer& ObjectInitializer);

	/** Grabbable constructor. */
	UGrabbableVR(TArray<FGrabPointVR> _GrabPoints, bool Active = true, bool HandTracking = true, UInputAction* LeftGrabButton = nullptr, UInputAction* RightGrabButton = nullptr, EGrabModeVR _GrabMode = EGrabModeVR::BOTH, float _GrabBuffer = 0.5f, UPrimitiveComponent* _Collider = nullptr, bool GrabPhysics = true, EGravitySettingVR _GravitySetting = EGravitySettingVR::UNCHANGED, bool Locked = false, bool Throwable = true, float _ThrowScale = 200, float _MinimumThrowDistance = 1, EThrowCalculationVR _ThrowCalculation = EThrowCalculationVR::DIRECTION, FRotator _ThrowRotationOffset = FRotator(-10, 0, 0), float _CollisionDelay = 0.5f);


	// UNREAL FUNCTIONS

	/** Called every frame. */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	// CONTROLLERINPUTVR FUNCTIONS

	/** Called when the left grab button is pressed down. */
	virtual void OnLeftGrabButtonPressed(const FInputActionValue& Value);

	/** Called when the right grab button is pressed down. */
	virtual void OnRightGrabButtonPressed(const FInputActionValue& Value);

	/** Called when the left grab button is released. */
	virtual void OnLeftGrabButtonReleased(const FInputActionValue& Value);

	/** Called when the right grab button is released. */
	virtual void OnRightGrabButtonReleased(const FInputActionValue& Value);


	// GETTERS

	/** Returns this grabbable component's grab points. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual void GetGrabPoints(TArray<FGrabPointVR>& _GrabPoints);

	/**
	* Gets the index of the given grab point by name.
	* Returns -1 if the grab point does not exist.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual int FindGrabPoint(FName Name, FGrabPointVR& GrabPoint);

	/** Returns the first grab point of this object. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual bool GetPrimaryGrabPoint(FGrabPointVR& GrabPoint);

	/** Returns whether the grabbable component is active. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual bool IsGrabActive();

	/** Returns whether the grabbable component is using hand tracking for grab detection. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual bool IsUsingHandTracking();

	/** Returns this grabbable component's given grab button. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual UInputAction* GetGrabButton(bool bIsRight);

	/** Returns this grabbable component's grab buttons. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual void GetGrabButtons(UInputAction*& Left, UInputAction*& Right);

	/** Returns this grabbable component's left grab button. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual UInputAction* GetLeftGrabButton();

	/** Returns this grabbable component's right grab button. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual UInputAction* GetRightGrabButton();

	/** Returns this grabbable component's grab mode setting. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual EGrabModeVR GetGrabMode();

	/** Returns this grabbable component's grab buffer time. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual float GetGrabBuffer();

	/** Returns the primary collider component for this grabbable component. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual UPrimitiveComponent* GetPrimaryCollider();

	/** Returns whether this grabbable component is using physics when grabbed. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual bool IsUsingGrabPhysics();

	/** Returns the gravity behaviour setting for this grabbable component. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual EGravitySettingVR GetGravitySetting();

	/** Returns whether this grabbable component is locked to a player's hand when grabbed. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual bool IsLocked();

	/** Returns whether this grabbable component is currently grabbed and locked to a player's hand. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual bool IsCurrentlyLocked();

	/** Returns whether this object can be thrown. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual bool IsThrowable();

	/** Returns the scale applied to the force added to this object when thrown. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual float GetThrowScale();

	/** Returns the minimum distance to consider this object as thrown when released. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual float GetMinimumThrowDistance();

	/** Returns the distance calculation used for when this object is thrown. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual EThrowCalculationVR GetThrowCalculation();

	/** Returns the offset in direction applied to this object when thrown. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual FRotator GetThrowRotationOffset();

	/** Returns the delay in seconds before hand collision is reenabled for this object when dropped. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual float GetCollisionDelay();

	/** Returns the delegate used for the event when this object is grabbed. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual FGrabDelegateVR& GetOnGrabEvent();

	/** Returns the delegate used for the event when this object is dropped. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual FGrabDelegateVR& GetOnDropEvent();

	/** Returns the delegate used for the event when this object is thrown. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual FGrabDelegateVR& GetOnThrowEvent();

	/** Returns the given hand's collider component. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	static UPrimitiveComponent* GetHandCollider(bool bIsRight);

	/** Returns both hands' collider components. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	static void GetBothHandColliders(UPrimitiveComponent*& Left, UPrimitiveComponent*& Right);

	/** Returns the left hand's collider component. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	static UPrimitiveComponent* GetLeftHandCollider();

	/** Returns the right hand's collider component. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	static UPrimitiveComponent* GetRightHandCollider();


	// SETTERS

	/** Sets whether the grabbable component is active. */
	UFUNCTION(BlueprintCallable, Category = "GrabbableVR")
	virtual void SetGrabActive(bool Active);

	/** Sets whether the grabbable component is using hand tracking for grab detection. */
	UFUNCTION(BlueprintCallable, Category = "GrabbableVR")
	virtual void SetUseHandTracking(bool HandTracking);

	/** Sets this grabbable component's given grab button. */
	UFUNCTION(BlueprintCallable, Category = "GrabbableVR")
	virtual void SetGrabButton(bool bIsRight, UInputAction* Button);

	/** Sets this grabbable component's grab buttons. */
	UFUNCTION(BlueprintCallable, Category = "GrabbableVR")
	virtual void SetGrabButtons(UInputAction* Left, UInputAction* Right);

	/** Sets this grabbable component's left grab button. */
	UFUNCTION(BlueprintCallable, Category = "GrabbableVR")
	virtual void SetLeftGrabButton(UInputAction* Button);

	/** Sets this grabbable component's right grab button. */
	UFUNCTION(BlueprintCallable, Category = "GrabbableVR")
	virtual void SetRightGrabButton(UInputAction* Button);

	/** Sets this grabbable component's grab mode setting. */
	UFUNCTION(BlueprintCallable, Category = "GrabbableVR")
	virtual void SetGrabMode(EGrabModeVR _GrabMode);

	/** Sets this grabbable component's grab buffer time. */
	UFUNCTION(BlueprintCallable, Category = "GrabbableVR")
	virtual void SetGrabBuffer(float Buffer);

	/** Sets the primary collider component for this grabbable component. */
	UFUNCTION(BlueprintCallable, Category = "GrabbableVR")
	virtual void SetPrimaryCollider(UPrimitiveComponent* Collider);

	/** Sets whether this grabbable component is using physics when grabbed. */
	UFUNCTION(BlueprintCallable, Category = "GrabbableVR")
	virtual void SetUseGrabPhysics(bool GrabPhysics);

	/** Sets the gravity behaviour setting for this grabbable component. */
	UFUNCTION(BlueprintCallable, Category = "GrabbableVR")
	virtual void SetGravitySetting(EGravitySettingVR _GravitySetting);

	/** Sets whether this grabbable component is locked to a player's hand when grabbed. */
	UFUNCTION(BlueprintCallable, Category = "GrabbableVR")
	virtual void SetLocked(bool Locked);

	/** Locks the object so when it is grabbed, it stays grabbed until unlocked. */
	UFUNCTION(BlueprintCallable, Category = "GrabbableVR")
	virtual void Lock();

	/** Unlocks the object so when it is let go of, it is dropped or thrown. */
	UFUNCTION(BlueprintCallable, Category = "GrabbableVR")
	virtual void Unlock();

	/** Sets whether this object can be thrown. */
	UFUNCTION(BlueprintCallable, Category = "GrabbableVR")
	virtual void SetThrowable(bool Throwable);

	/** Sets the scale applied to the force added to this object when thrown. */
	UFUNCTION(BlueprintCallable, Category = "GrabbableVR")
	virtual void SetThrowScale(float _ThrowScale);

	/** Sets the minimum distance to consider this object as thrown when released. */
	UFUNCTION(BlueprintCallable, Category = "GrabbableVR")
	virtual void SetMinimumThrowDistance(float _MinimumThrowDistance);

	/** Sets the distance calculation used for when this object is thrown. */
	UFUNCTION(BlueprintCallable, Category = "GrabbableVR")
	virtual void SetThrowCalculation(EThrowCalculationVR Calculation);

	/** Sets the offset in direction applied to this object when thrown. */
	UFUNCTION(BlueprintCallable, Category = "GrabbableVR")
	virtual void SetThrowRotationOffset(FRotator Offset);

	/** Sets the delay in seconds before hand collision is reenabled for this object when dropped. */
	UFUNCTION(BlueprintCallable, Category = "GrabbableVR")
	virtual void SetCollisionDelay(float Delay);

	/**
	* Binds or rebinds the delegate used for the event when this object is grabbed.
	* Note: This event only binds one function, so you will need an event dispatcher for multiple events.
	*/
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "Event"), Category = "GrabbableVR")
	virtual void BindOnGrabEvent(const FGrabDelegateVR& Event);

	/**
	* Binds or rebinds the delegate used for the event when this object is dropped.
	* Note: This event only binds one function, so you will need an event dispatcher for multiple events.
	*/
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "Event"), Category = "GrabbableVR")
	virtual void BindOnDropEvent(const FGrabDelegateVR& Event);

	/**
	* Binds or rebinds the delegate used for the event when this object is thrown.
	* Note: This event only binds one function, so you will need an event dispatcher for multiple events.
	*/
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "Event"), Category = "GrabbableVR")
	virtual void BindOnThrowEvent(const FGrabDelegateVR& Event);

	/** Sets the given hand's collider component. */
	UFUNCTION(BlueprintCallable, Category = "GrabbableVR")
	static void SetHandCollider(bool bIsRight, UPrimitiveComponent* Collider);

	/** Sets both hands' collider components. */
	UFUNCTION(BlueprintCallable, Category = "GrabbableVR")
	static void SetBothHandColliders(UPrimitiveComponent* Left, UPrimitiveComponent* Right);

	/** Sets the left hand's collider component. */
	UFUNCTION(BlueprintCallable, Category = "GrabbableVR")
	static void SetLeftHandCollider(UPrimitiveComponent* Collider);

	/** Sets the right hand's collider component. */
	UFUNCTION(BlueprintCallable, Category = "GrabbableVR")
	static void SetRightHandCollider(UPrimitiveComponent* Collider);

	/**
	* Simply updates the collision profile so that when this object is dropped, it maintains its proper collision response to pawns.
	* This is automatically set at the start of this object's lifetime, but you can call it again if you need to change the collision.
	*/
	virtual void UpdatePawnCollision(ECollisionResponse NewResponse);


	// GRABBABLE FUNCTIONS

	/**
	* Updates the state of this grabbable actor.
	* Automatically called each tick to update grabbing logic.
	*/
	UFUNCTION(BlueprintCallable, Category = "GrabbableVR")
	virtual void UpdateGrab(float DeltaSeconds = 0.001f);

	/**
	* Attempts to forcefully attach this object to the given hand at the given grab point.
	* Returns if the grab was successful.
	*/
	UFUNCTION(BlueprintCallable, Category = "GrabbableVR")
	virtual bool Grab(bool bIsRight, FGrabPointVR GrabPoint, bool InvokeEvent = true);

	/**
	* Attempts to forcefully release this object from the player's hand.
	* Returns if the drop was successful.
	*/
	UFUNCTION(BlueprintCallable, Category = "GrabbableVR")
	virtual bool Drop(bool InvokeEvent = true);

	/**
	* Attempts to forcefully release and throw this object from the player's hand.
	* Returns if the throw was successful.
	*/
	UFUNCTION(BlueprintCallable, Category = "GrabbableVR")
	virtual bool Throw(FVector StartPoint, FVector TargetPoint, float DeltaSeconds = 0.001f, bool InvokeEvent = true);

	/** Returns whether this object is currently grabbed. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual bool IsGrabbed();

	/** Returns whether this object is currently grabbed with the given hand. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual bool IsGrabbedWith(bool bIsRight);

	/** Returns whether this object is currently grabbed with the left hand. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual bool IsGrabbedLeft();

	/** Returns whether this object is currently grabbed with the right hand. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual bool IsGrabbedRight();

	/** Returns whether the given hand is empty. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	static bool IsHandEmpty(bool bIsRight);

	/** Returns whether both hands are empty. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	static void AreBothHandsEmpty(bool& BothHandsAreEmpty, bool& LeftHandIsEmpty, bool& RightHandIsEmpty);

	/** Returns whether the left hand is empty. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	static bool IsLeftHandEmpty();

	/** Returns whether the right hand is empty. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	static bool IsRightHandEmpty();

	/** Returns the hand that is currently grabbing this object. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual void GetGrabbedHand(bool& bIsGrabbed, USceneComponent*& Hand, bool& bIsRight, FGrabPointVR& GrabPoint);

	/** Returns the given hand's grabbed object. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	static UGrabbableVR* GetGrabbedObject(bool bIsRight);

	/** Returns both hands' grabbed object. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	static void GetBothGrabbedObjects(UGrabbableVR*& Left, UGrabbableVR*& Right);

	/** Returns the left hand's grabbed object. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	static UGrabbableVR* GetLeftGrabbedObject();

	/** Returns the right hand's grabbed object. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	static UGrabbableVR* GetRightGrabbedObject();

	/** Returns the elapsed grab time for this object. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GrabbableVR")
	virtual float GetElapsedGrabTime();

	/** Constructs a new GrabbableVR component. */
	UFUNCTION(BlueprintCallable, Category = "GrabbableVR")
	static UGrabbableVR* ConstructGrabbableVR(AActor* Parent, TArray<FGrabPointVR> _GrabPoints, bool Active = true, bool HandTracking = true, UInputAction* LeftGrabButton = nullptr, UInputAction* RightGrabButton = nullptr, EGrabModeVR _GrabMode = EGrabModeVR::BOTH, float _GrabBuffer = 0.5f, UPrimitiveComponent* _Collider = nullptr, bool GrabPhysics = true, EGravitySettingVR _GravitySetting = EGravitySettingVR::UNCHANGED, bool Locked = false, bool Throwable = true, float _ThrowScale = 200, float _MinimumThrowDistance = 1, EThrowCalculationVR _ThrowCalculation = EThrowCalculationVR::DIRECTION, FRotator _ThrowRotationOffset = FRotator(-10, 0, 0), float _CollisionDelay = 0.5f);
};
