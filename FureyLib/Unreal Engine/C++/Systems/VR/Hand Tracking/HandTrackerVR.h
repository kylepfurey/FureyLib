
// Static VR Hand Tracking Component Script
// by Kyle Furey

// REQUIREMENTS: HandInteractableVR.h, HandVR.h, HandTrackerVR.cpp

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MotionControllerComponent.h"
#include "Camera/CameraComponent.h"
#include "VR/Hand Tracking/HandInteractableVR.h"
#include "VR/Hand Tracking/HandVR.h"
#include "HandTrackerVR.generated.h"

// Include this heading to use the class
// #include "VR/Hand Tracking/HandTrackerVR.h"

/** Each possible state for hand tracking. */
UENUM(BlueprintType, meta = (Bitflags), Category = "HandTrackerVR")
enum class EHandTrackingStateVR : uint8
{
	NONE = 0	UMETA(DisplayName = "No Hands Tracked"),
	LEFT = 1	UMETA(DisplayName = "Left Hand Tracked"),
	RIGHT = 2	UMETA(DisplayName = "Right Hand Tracked"),
	BOTH = 3	UMETA(DisplayName = "Both Hands Tracked"),
	MAX			UMETA(Hidden)
};

/**
* Singleton hand tracking component class.
* Tracks a player's hands in VR through the hand's joints.
* Provides static functions for easy access and validation of data from the player's hands.
*/
UCLASS(Blueprintable, BlueprintType, ClassGroup = (HandTrackerVR))
class MYGAME_API UHandTrackerVR : public UActorComponent, public IHandInteractableVR
{
	GENERATED_BODY()

protected:

	// HAND OBJECTS

	/** The headset camera object. */
	UPROPERTY(BlueprintReadOnly, BlueprintGetter = "GetHeadset", meta = (ExposeOnSpawn), Category = "HandTrackerVR")
	UCameraComponent* Headset = nullptr;

	/** The left hand object. */
	UPROPERTY(BlueprintReadOnly, BlueprintGetter = "GetLeftHand", meta = (ExposeOnSpawn), Category = "HandTrackerVR")
	UHandVR* LeftHand = nullptr;

	/** The right hand object. */
	UPROPERTY(BlueprintReadOnly, BlueprintGetter = "GetRightHand", meta = (ExposeOnSpawn), Category = "HandTrackerVR")
	UHandVR* RightHand = nullptr;


	// MOTION CONTROLLERS

	/** The motion controller component being used to represent the left hand. */
	UPROPERTY(BlueprintReadOnly, BlueprintGetter = "GetLeftMotionController", meta = (ExposeOnSpawn), Category = "HandTrackerVR")
	UMotionControllerComponent* LeftHandMotionController = nullptr;

	/** The motion controller component being used to represent the right hand. */
	UPROPERTY(BlueprintReadOnly, BlueprintGetter = "GetRightMotionController", meta = (ExposeOnSpawn), Category = "HandTrackerVR")
	UMotionControllerComponent* RightHandMotionController = nullptr;


	// GESTURE MAPS

	/** Each gesture and whether it is currently active in the left hand. */
	UPROPERTY(BlueprintReadOnly, BlueprintGetter = "GetLeftGestureMap", Category = "HandTrackerVR")
	TMap<EHandGestureVR, bool> LeftGestures = TMap<EHandGestureVR, bool>();

	/** Each gesture and whether it is currently active in the right hand. */
	UPROPERTY(BlueprintReadOnly, BlueprintGetter = "GetRightGestureMap", Category = "HandTrackerVR")
	TMap<EHandGestureVR, bool> RightGestures = TMap<EHandGestureVR, bool>();


	// HAND TRACKING STATE

	/** The global state of hand tracking input. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintGetter = "GetHandTrackingState", BlueprintSetter = "SetHandTrackingState", meta = (ExposeOnSpawn), Category = "HandTrackerVR")
	EHandTrackingStateVR State = EHandTrackingStateVR::BOTH;

	/** Whether the left hand is currently being tracked. */
	UPROPERTY(BlueprintReadOnly, BlueprintGetter = "IsTrackingLeftHand", Category = "HandTrackerVR")
	bool bTrackingLeft = false;

	/** Whether the right hand is currently being tracked. */
	UPROPERTY(BlueprintReadOnly, BlueprintGetter = "IsTrackingRightHand", Category = "HandTrackerVR")
	bool bTrackingRight = false;

	/** The previous set of active left gestures. */
	TSet<EHandGestureVR> PreviousLeftGestures = TSet<EHandGestureVR>();

	/** The previous set of active right gestures. */
	TSet<EHandGestureVR> PreviousRightGestures = TSet<EHandGestureVR>();


	// STATIC INSTANCE

	/** The global instance of the world's hand tracker used to call hand tracker functions anywhere. */
	static UHandTrackerVR* Instance;


	// UNREAL FUNCTIONS

	/** Initializes hand tracking. */
	virtual void BeginPlay() override;

	/** Disables hand tracking. */
	virtual void BeginDestroy() override;


	// HAND TRACKING STATE FUNCTIONS

	/** Locates the hand tracker's motion controllers. */
	virtual void LocateMotionControllers();

	/**
	* Returns whether this object is currently receiving hand tracking input.
	* This is the static version used exclusively for blueprint implementations.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Is Hand Tracking VR Implemented"), Category = "HandInteractableVR")
	static bool IsHandTrackingVRImplemented(TScriptInterface<IHandInteractableVR> HandInteractableVR);

	/**
	* Call this function when this object is created to enable hand tracking.
	* Make sure to call RemoveHandTrackingVR() when this object is destroyed.
	* This is the static version used exclusively for blueprint implementations.
	*/
	UFUNCTION(BlueprintCallable, Category = "HandInteractableVR")
	static void ImplementHandTrackingVR(TScriptInterface<IHandInteractableVR> HandInteractableVR);

	/**
	* Call this function when this object is destroyed to remove hand tracking.
	* Make sure to call ImplementHandTrackingVR() when this object is created.
	* This is the static version used exclusively for blueprint implementations.
	*/
	UFUNCTION(BlueprintCallable, Category = "HandInteractableVR")
	static void RemoveHandTrackingVR(TScriptInterface<IHandInteractableVR> HandInteractableVR);

public:

	// CONSTRUCTORS

	/** Default constructor. */
	UHandTrackerVR();

	/** Object initializer constructor. */
	UHandTrackerVR(const FObjectInitializer& ObjectInitializer);

	/** Hand tracker constructor. */
	UHandTrackerVR(UCameraComponent* _Headset, UPoseableMeshComponent* _LeftHandComponent, UPoseableMeshComponent* _RightHandComponent, EHandTrackingStateVR TrackingState = EHandTrackingStateVR::BOTH);


	// UNREAL FUNCTIONS

	/** Called every frame. */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	// HAND TRACKER FUNCTIONS

	/** Returns the global state of hand tracking input. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static EHandTrackingStateVR GetHandTrackingState();

	/** Sets the global state of hand tracking input. */
	UFUNCTION(BlueprintCallable, Category = "HandTrackerVR")
	static void SetHandTrackingState(EHandTrackingStateVR TrackingState);

	/** Returns whether hand tracking is enabled for the given hands. */
	UFUNCTION(BlueprintCallable, Category = "HandTrackerVR")
	static void IsHandTrackingEnabled(bool& Either, bool& Both, bool& Left, bool& Right);

	/** Returns whether hand tracking is enabled for the left hand. */
	UFUNCTION(BlueprintCallable, Category = "HandTrackerVR")
	static bool IsLeftHandTrackingEnabled();

	/** Returns whether hand tracking is enabled for the right hand. */
	UFUNCTION(BlueprintCallable, Category = "HandTrackerVR")
	static bool IsRightHandTrackingEnabled();

	/** Returns the current IHandInteractableVR implementations. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static TSet<UObject*> GetHandTrackingImplementations();

	/** Returns the current number of IHandInteractableVR implementations. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static int32 NumberOfHandTrackingImplementations();

	/** Returns the current instance of the hand tracker component. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static UHandTrackerVR* GetHandTrackerVR();

	/** Constructs a new HandTrackerVR component. */
	UFUNCTION(BlueprintCallable, Category = "HandTrackerVR")
	static UHandTrackerVR* ConstructHandTrackerVR(AActor* Parent, UCameraComponent* _Headset, UPoseableMeshComponent* _LeftHandComponent, UPoseableMeshComponent* _RightHandComponent, EHandTrackingStateVR TrackingState = EHandTrackingStateVR::BOTH);


	// TRACKING FUNCTIONS

	/** Returns whether VR hands have been set yet. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static bool AreHandsSet();

	/** Returns whether the given VR hand is currently set and being tracked. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static bool IsTrackingHand(bool bIsRight);

	/** Returns whether both VR hands are currently set and being tracked. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static void IsTrackingBothHands(bool& Both, bool& Left, bool& Right);

	/** Returns whether the left VR hand is currently set and being tracked. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static bool IsTrackingLeftHand();

	/** Returns whether the right VR hand is currently set and being tracked. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static bool IsTrackingRightHand();


	// HAND FUNCTIONS

	/** Returns the given VR hand. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static UHandVR* GetHand(bool bIsRight);

	/** Returns both VR hands. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static void GetBothHands(UHandVR*& Left, UHandVR*& Right);

	/** Returns the left VR hand. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static UHandVR* GetLeftHand();

	/** Returns the right VR hand. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static UHandVR* GetRightHand();


	// HEADSET FUNCTIONS

	/** Returns the headset camera. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static UCameraComponent* GetHeadset();

	/** Returns the headset camera's transform data. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static void GetHeadsetTransform(FVector& WorldPosition, FRotator& WorldRotation);

	/** Returns the player actor. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static AActor* GetPlayer();

	/** Returns the player's transform data. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static void GetPlayerTransform(FVector& WorldPosition, FRotator& WorldRotation, FVector& WorldScale);


	// MOTION CONTROLLER FUNCTIONS

	/** Returns the given motion controller. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static UMotionControllerComponent* GetMotionController(bool bIsRight);

	/** Returns both motion controllers. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static void GetBothMotionControllers(UMotionControllerComponent*& Left, UMotionControllerComponent*& Right);

	/** Returns the left motion controller. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static UMotionControllerComponent* GetLeftMotionController();

	/** Returns the right motion controller. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static UMotionControllerComponent* GetRightMotionController();


	// GESTURE FUNCTIONS

	/** Returns whether the given VR hand is making the given gesture. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static bool GetGesture(bool bIsRight, EHandGestureVR Gesture);

	/** Returns whether the both VR hands are making the given gestures. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static void GetBothGestures(EHandGestureVR LeftGesture, EHandGestureVR RightGesture, bool& Left, bool& Right);

	/** Returns whether the left VR hand is making the given gesture. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static bool GetLeftGesture(EHandGestureVR Gesture);

	/** Returns whether the right VR hand is making the given gesture. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static bool GetRightGesture(EHandGestureVR Gesture);


	// GESTURE MAP FUNCTIONS

	/** Returns all of the gestures of the given VR hand. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static TMap<EHandGestureVR, bool> GetGestureMap(bool bIsRight);

	/** Returns all of the gestures of both VR hands. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static void GetBothGestureMaps(TMap<EHandGestureVR, bool>& Left, TMap<EHandGestureVR, bool>& Right);

	/** Returns all of the gestures of the left VR hand. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static TMap<EHandGestureVR, bool> GetLeftGestureMap();

	/** Returns all of the gestures of the right VR hand. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static TMap<EHandGestureVR, bool> GetRightGestureMap();


	// ACTIVE GESTURE FUNCTIONS

	/** Returns all of the active gestures of the given VR hand. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static TSet<EHandGestureVR> GetActiveGestures(bool bIsRight);

	/** Returns all of the active gestures of both VR hands. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static void GetBothActiveGestures(TSet<EHandGestureVR>& Left, TSet<EHandGestureVR>& Right);

	/** Returns all of the active gestures of the left VR hand. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static TSet<EHandGestureVR> GetActiveLeftGestures();

	/** Returns all of the active gestures of the right VR hand. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandTrackerVR")
	static TSet<EHandGestureVR> GetActiveRightGestures();


	// IHANDINTERACTABLEVR IMPLEMENTATION

	/** Calls OnSetHands() for each IHandInteractableVR implementation. */
	virtual void OnSetHands_Implementation() override;

	/** Calls OnHandTracked() for each IHandInteractableVR implementation. */
	virtual void OnHandTracked_Implementation(bool bIsRight) override;

	/** Calls OnHandLost() for each IHandInteractableVR implementation. */
	virtual void OnHandLost_Implementation(bool bIsRight) override;

	/** Calls OnNewGesture() for each IHandInteractableVR implementation. */
	virtual void OnNewGesture_Implementation(bool bIsRight, EHandGestureVR NewGesture) override;

	/** Calls OnGestureTick() for each IHandInteractableVR implementation. */
	virtual void OnGestureTick_Implementation(bool bIsRight, EHandGestureVR Gesture) override;

	/** Calls OnStopGesture() for each IHandInteractableVR implementation. */
	virtual void OnStopGesture_Implementation(bool bIsRight, EHandGestureVR StoppedGesture) override;
};
