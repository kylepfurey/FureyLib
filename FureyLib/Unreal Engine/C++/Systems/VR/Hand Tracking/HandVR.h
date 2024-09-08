
// VR Hand Object Script
// by Kyle Furey

// REQUIREMENT: HandVR.cpp

// REFERENCE: https://developer.oculus.com/documentation/unreal/unreal-hand-tracking/

#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/PoseableMeshComponent.h"
#include "Math/Vector.h"
#include "Math/Rotator.h"
#include "Math/Transform.h"
#include "Kismet/KismetSystemLibrary.h"
#include "HandVR.generated.h"

// Include this heading to use the class
// #include "VR/Hand Tracking/HandVR.h"

// Returns a percentage relative to a value of a minimum and maximum.
#define PERCENTAGE(value, min, max) ((value - min) / (max - min))

// Finger rotation percentages.

#define THUMB_MIN -2.0
#define THUMB_MAX 7.0
#define INDEX_FINGER_MIN -2.5
#define INDEX_FINGER_MAX 0.5
#define MIDDLE_FINGER_MIN -1.5
#define MIDDLE_FINGER_MAX 0.5
#define RING_FINGER_MIN -5.0
#define RING_FINGER_MAX 0.3
#define PINKY_FINGER_MIN -5.5
#define PINKY_FINGER_MAX 4.5

/** Each of the five fingers used in accessing VR hand tracking data. */
UENUM(BlueprintType, meta = (Bitflags), Category = "HandVR")
enum class EFingerVR : uint8
{
	NONE = 0	UMETA(Hidden),
	THUMB = 1	UMETA(DisplayName = "Thumb"),
	INDEX = 2	UMETA(DisplayName = "Index"),
	MIDDLE = 4	UMETA(DisplayName = "Middle"),
	RING = 8	UMETA(DisplayName = "Ring"),
	PINKY = 16	UMETA(DisplayName = "Pinky"),
	MAX			UMETA(Hidden)
};

/** Different joints in each finger. */
UENUM(BlueprintType, Category = "HandVR")
enum class EFingerJointVR : uint8
{
	BASE	UMETA(DisplayName = "Base"),
	MIDDLE	UMETA(DisplayName = "Middle"),
	TIP		UMETA(DisplayName = "Tip"),
	MAX		UMETA(Hidden)
};

/** Each defined gesture that can be detected in VR (add more if needed). */
UENUM(BlueprintType, Category = "HandVR")
enum class EHandGestureVR : uint8
{
	OPEN			UMETA(DisplayName = "Open"),
	FIST			UMETA(DisplayName = "Fist"),
	GRIP			UMETA(DisplayName = "Grip"),
	POINT			UMETA(DisplayName = "Point"),
	PINCH			UMETA(DisplayName = "Pinch"),
	PINCH_MIDDLE	UMETA(DisplayName = "Pinch Middle"),
	THUMBS_UP		UMETA(DisplayName = "Thumbs Up"),
	FINGER_GUN		UMETA(DisplayName = "Finger Gun"),
	FLIP_OFF		UMETA(DisplayName = "Flip Off"),

	// New gestures here

	MAX				UMETA(Hidden)
};

/** Data for an individual hand in VR. */
UCLASS(Blueprintable, BlueprintType)
class MYGAME_API UHandVR : public UObject
{
	GENERATED_BODY()

protected:

	// TYPE OF HAND

	/** Whether this hand is a right hand. */
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn), Category = "HandVR")
	bool bIsRight = false;


	// HAND OBJECT

	/** The hand object. */
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn), Category = "HandVR")
	UPoseableMeshComponent* Hand = nullptr;

public:

	// CONSTRUCTORS

	/** Default constructor. */
	UHandVR();

	/** Object initializer constructor. */
	UHandVR(const FObjectInitializer& ObjectInitializer);

	/** HandVR constructor. */
	UHandVR(bool bIsRight, UPoseableMeshComponent* Hand);


	// TYPE OF HAND FUNCTION

	/** Returns which hand this is. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandVR")
	virtual bool IsRight();

	/** Fixes the given rotation relative to a right hand. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandVR")
	static FRotator FixRightHandRotation(FRotator RightHandRotation);


	// HAND OBJECT FUNCTIONS

	/** Gets the hand component. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandVR")
	virtual UPoseableMeshComponent* GetHandComponent();

	/** Gets the given bone's transform data. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandVR")
	virtual void GetHandBone(FName Bone, FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation);

	/** Calculates the object the index finger is currently pointing at. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandVR")
	virtual bool GetPointedAtObject(FHitResult& Result, float MaxDistance = 10000, bool HitComplex = true);

	/** Constructs a new HandVR object. */
	UFUNCTION(BlueprintCallable, Category = "HandVR")
	static UHandVR* ConstructHandVR(bool IsRight, UPoseableMeshComponent* HandComponent);


	// WRIST AND PALM FUNCTIONS

	/** Gets the wrist transform data. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandVR")
	virtual void GetWrist(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation);

	/** Gets the palm transform data. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandVR")
	virtual void GetPalm(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation);


	// THUMB FUNCTIONS

	/** Gets the thumb transform data. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandVR")
	virtual void GetThumb(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation);

	/** Gets the thumb tip transform data. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandVR")
	virtual void GetThumbTip(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation);


	// INDEX FINGER FUNCTIONS

	/** Gets the index finger transform data. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandVR")
	virtual void GetIndexFinger(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation);

	/** Gets the index finger middle transform data. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandVR")
	virtual void GetIndexFingerMiddle(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation);

	/** Gets the index finger tip transform data. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandVR")
	virtual void GetIndexFingerTip(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation);


	// MIDDLE FINGER FUNCTIONS

	/** Gets the middle finger transform data. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandVR")
	virtual void GetMiddleFinger(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation);

	/** Gets the middle finger middle transform data. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandVR")
	virtual void GetMiddleFingerMiddle(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation);

	/** Gets the middle finger tip transform data. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandVR")
	virtual void GetMiddleFingerTip(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation);


	// RING FINGER FUNCTIONS

	/** Gets the ring finger transform data. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandVR")
	virtual void GetRingFinger(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation);

	/** Gets the ring finger middle transform data. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandVR")
	virtual void GetRingFingerMiddle(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation);

	/** Gets the ring finger tip transform data. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandVR")
	virtual void GetRingFingerTip(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation);


	// PINKY FINGER FUNCTIONS

	/** Gets the pinky finger transform data. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandVR")
	virtual void GetPinkyFinger(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation);

	/** Gets the pinky finger middle transform data. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandVR")
	virtual void GetPinkyFingerMiddle(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation);

	/** Gets the pinky finger tip transform data. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandVR")
	virtual void GetPinkyFingerTip(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation);


	// FINGER AND GESTURE FUNCTIONS

	/** Gets the the transform data of the given finger. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandVR")
	virtual void GetFinger(EFingerVR Finger, EFingerJointVR Joint, FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation);

	/**
	* Returns the percentage of a given finger's position based on their maximums and minimums.
	* 0 = finger pointing inward, 1 = finger pointing outward.
	* Note: You may need to adjust the minimum and maximum constants for accuracy and leniency.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandVR")
	virtual float GetFingerPercentage(EFingerVR Finger);

	/**
	* Returns if the hand matches the given gesture. Add more gestures if needed.
	* Note: You may need to adjust the values that check the gesture for accuracy and leniency.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HandVR")
	virtual bool GetGesture(EHandGestureVR Gesture);
};
