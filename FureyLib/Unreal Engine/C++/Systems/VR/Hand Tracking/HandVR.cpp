
// VR Hand Object Script
// by Kyle Furey

// REQUIREMENT: HandVR.h

// REFERENCE: https://developer.oculus.com/documentation/unreal/unreal-hand-tracking/

// Include this heading to use the class
#include "VR/Hand Tracking/HandVR.h"


// CONSTRUCTORS

// Default constructor.
UHandVR::UHandVR()
{
	bIsRight = false;

	Hand = nullptr;
}

// Object initializer constructor.
UHandVR::UHandVR(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bIsRight = false;

	Hand = nullptr;
}

// HandVR constructor.
UHandVR::UHandVR(bool bIsRight, UPoseableMeshComponent* Hand)
{
	this->bIsRight = bIsRight;

	this->Hand = Hand;
}


// TYPE OF HAND FUNCTION

// Returns which hand this is.
bool UHandVR::IsRight()
{
	return bIsRight;
}

// Fixes the given rotation relative to a right hand.
FRotator UHandVR::FixRightHandRotation(FRotator RightHandRotation)
{
	return FRotationMatrix::MakeFromX(RightHandRotation.Vector() * -1).Rotator();
}


// HAND OBJECT FUNCTIONS

// Gets the hand component.
UPoseableMeshComponent* UHandVR::GetHandComponent()
{
	return Hand;
}

// Gets the given bone's transform data.
void UHandVR::GetHandBone(FName Bone, FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation)
{
	if (IsValid(Hand))
	{
		int32 BoneIndex = Hand->GetBoneIndex(Bone);

		if (BoneIndex == INDEX_NONE)
		{
			WorldPosition = FVector(0, 0, 0);

			WorldRotation = FRotator(0, 0, 0);

			LocalPosition = FVector(0, 0, 0);

			LocalRotation = FRotator(0, 0, 0);

			return;
		}

		FTransform Transform = Hand->GetBoneTransform(BoneIndex);

		WorldPosition = Transform.GetLocation();

		WorldRotation = Transform.Rotator();

		if (bIsRight)
		{
			WorldRotation = FixRightHandRotation(WorldRotation);
		}

		BoneIndex = Hand->GetBoneIndex(Hand->GetParentBone(Bone));

		if (BoneIndex == INDEX_NONE)
		{
			LocalPosition = WorldPosition;

			LocalRotation = WorldRotation;

			return;
		}

		Transform = Transform.GetRelativeTransform(Hand->GetBoneTransform(BoneIndex));

		LocalPosition = Transform.GetLocation();

		LocalRotation = Transform.Rotator();

		return;
	}

	WorldPosition = FVector(0, 0, 0);

	WorldRotation = FRotator(0, 0, 0);

	LocalPosition = FVector(0, 0, 0);

	LocalRotation = FRotator(0, 0, 0);
}

// Calculates the object the index finger is currently pointing at.
bool UHandVR::GetPointedAtObject(FHitResult& Result, float MaxDistance, bool HitComplex)
{
	FVector WorldPosition;

	FRotator WorldRotation;

	FVector LocalPosition;

	FRotator LocalRotation;

	GetIndexFingerTip(WorldPosition, WorldRotation, LocalPosition, LocalRotation);

	return UKismetSystemLibrary::LineTraceSingle(Hand, WorldPosition, WorldPosition + WorldRotation.Vector() * MaxDistance, ETraceTypeQuery::TraceTypeQuery1, HitComplex, TArray<AActor*>(), EDrawDebugTrace::None, Result, true);
}

// Constructs a new HandVR object.
UHandVR* UHandVR::ConstructHandVR(bool IsRight, UPoseableMeshComponent* HandComponent)
{
	UHandVR* NewHand = NewObject<UHandVR>();

	NewHand->bIsRight = IsRight;

	NewHand->Hand = HandComponent;

	return NewHand;
}


// WRIST AND PALM FUNCTIONS

// Gets the wrist transform data.
void UHandVR::GetWrist(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation)
{
	GetHandBone("Wrist Root", WorldPosition, WorldRotation, LocalPosition, LocalRotation);
}

// Gets the palm transform data.
void UHandVR::GetPalm(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation)
{
	if (IsValid(Hand))
	{
		int32 BoneIndex = Hand->GetBoneIndex(TEXT("Wrist Root"));

		if (BoneIndex == INDEX_NONE)
		{
			WorldPosition = FVector(0, 0, 0);

			WorldRotation = FRotator(0, 0, 0);

			LocalPosition = FVector(0, 0, 0);

			LocalRotation = FRotator(0, 0, 0);

			return;
		}

		FTransform Transform = Hand->GetBoneTransform(BoneIndex);

		WorldPosition = Transform.GetLocation();

		WorldRotation = Transform.Rotator();

		WorldPosition += (FRotationMatrix(WorldRotation).GetUnitAxis(EAxis::X) * 6);

		WorldRotation = ((WorldRotation.Quaternion() * FVector::RightVector) * -1).ToOrientationRotator();

		Transform = Transform.GetRelativeTransform(Hand->GetBoneTransform(BoneIndex));

		LocalPosition = Transform.GetLocation();

		LocalRotation = Transform.Rotator();

		return;
	}

	WorldPosition = FVector(0, 0, 0);

	WorldRotation = FRotator(0, 0, 0);

	LocalPosition = FVector(0, 0, 0);

	LocalRotation = FRotator(0, 0, 0);
}


// THUMB FUNCTIONS

// Gets the thumb transform data.
void UHandVR::GetThumb(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation)
{
	GetHandBone("Thumb2", WorldPosition, WorldRotation, LocalPosition, LocalRotation);
}

// Gets the thumb tip transform data.
void UHandVR::GetThumbTip(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation)
{
	GetHandBone("Thumb Tip", WorldPosition, WorldRotation, LocalPosition, LocalRotation);
}


// INDEX FINGER FUNCTIONS

// Gets the index finger transform data.
void UHandVR::GetIndexFinger(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation)
{
	GetHandBone("Index1", WorldPosition, WorldRotation, LocalPosition, LocalRotation);
}

// Gets the index finger middle transform data.
void UHandVR::GetIndexFingerMiddle(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation)
{
	GetHandBone("Index2", WorldPosition, WorldRotation, LocalPosition, LocalRotation);
}

// Gets the index finger tip transform data.
void UHandVR::GetIndexFingerTip(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation)
{
	GetHandBone("Index Tip", WorldPosition, WorldRotation, LocalPosition, LocalRotation);
}


// MIDDLE FINGER FUNCTIONS

// Gets the middle finger transform data.
void UHandVR::GetMiddleFinger(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation)
{
	GetHandBone("Middle1", WorldPosition, WorldRotation, LocalPosition, LocalRotation);
}

// Gets the middle finger middle transform data.
void UHandVR::GetMiddleFingerMiddle(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation)
{
	GetHandBone("Middle2", WorldPosition, WorldRotation, LocalPosition, LocalRotation);
}

// Gets the middle finger tip transform data.
void UHandVR::GetMiddleFingerTip(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation)
{
	GetHandBone("Middle Tip", WorldPosition, WorldRotation, LocalPosition, LocalRotation);
}


// RING FINGER FUNCTIONS

// Gets the ring finger transform data.
void UHandVR::GetRingFinger(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation)
{
	GetHandBone("Ring1", WorldPosition, WorldRotation, LocalPosition, LocalRotation);
}

// Gets the ring finger middle transform data.
void UHandVR::GetRingFingerMiddle(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation)
{
	GetHandBone("Ring2", WorldPosition, WorldRotation, LocalPosition, LocalRotation);
}

// Gets the ring finger tip transform data.
void UHandVR::GetRingFingerTip(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation)
{
	GetHandBone("Ring Tip", WorldPosition, WorldRotation, LocalPosition, LocalRotation);
}


// PINKY FINGER FUNCTIONS

// Gets the pinky finger transform data.
void UHandVR::GetPinkyFinger(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation)
{
	GetHandBone("Pinky1", WorldPosition, WorldRotation, LocalPosition, LocalRotation);
}

// Gets the pinky finger middle transform data.
void UHandVR::GetPinkyFingerMiddle(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation)
{
	GetHandBone("Pinky2", WorldPosition, WorldRotation, LocalPosition, LocalRotation);
}

// Gets the pinky finger tip transform data.
void UHandVR::GetPinkyFingerTip(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation)
{
	GetHandBone("Pinky Tip", WorldPosition, WorldRotation, LocalPosition, LocalRotation);
}


// FINGER AND GESTURE FUNCTIONS

// Gets the the transform data of the given finger.
void UHandVR::GetFinger(EFingerVR Finger, EFingerJointVR Joint, FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation)
{
	switch (Finger)
	{
	case EFingerVR::THUMB:

		switch (Joint)
		{
		case EFingerJointVR::BASE:

			GetThumb(WorldPosition, WorldRotation, LocalPosition, LocalRotation);

			return;

		case EFingerJointVR::MIDDLE:

			GetThumb(WorldPosition, WorldRotation, LocalPosition, LocalRotation);

			return;

		case EFingerJointVR::TIP:

			GetThumbTip(WorldPosition, WorldRotation, LocalPosition, LocalRotation);

			return;
		}

	case EFingerVR::INDEX:

		switch (Joint)
		{
		case EFingerJointVR::BASE:

			GetIndexFinger(WorldPosition, WorldRotation, LocalPosition, LocalRotation);

			return;

		case EFingerJointVR::MIDDLE:

			GetIndexFingerMiddle(WorldPosition, WorldRotation, LocalPosition, LocalRotation);

			return;

		case EFingerJointVR::TIP:

			GetIndexFingerTip(WorldPosition, WorldRotation, LocalPosition, LocalRotation);

			return;
		}

	case EFingerVR::MIDDLE:

		switch (Joint)
		{
		case EFingerJointVR::BASE:

			GetMiddleFinger(WorldPosition, WorldRotation, LocalPosition, LocalRotation);

			return;

		case EFingerJointVR::MIDDLE:

			GetMiddleFingerMiddle(WorldPosition, WorldRotation, LocalPosition, LocalRotation);

			return;

		case EFingerJointVR::TIP:

			GetMiddleFingerTip(WorldPosition, WorldRotation, LocalPosition, LocalRotation);

			return;
		}

	case EFingerVR::RING:

		switch (Joint)
		{
		case EFingerJointVR::BASE:

			GetRingFinger(WorldPosition, WorldRotation, LocalPosition, LocalRotation);

			return;

		case EFingerJointVR::MIDDLE:

			GetRingFingerMiddle(WorldPosition, WorldRotation, LocalPosition, LocalRotation);

			return;

		case EFingerJointVR::TIP:

			GetRingFingerTip(WorldPosition, WorldRotation, LocalPosition, LocalRotation);

			return;
		}

	case EFingerVR::PINKY:

		switch (Joint)
		{
		case EFingerJointVR::BASE:

			GetPinkyFinger(WorldPosition, WorldRotation, LocalPosition, LocalRotation);

			return;

		case EFingerJointVR::MIDDLE:

			GetPinkyFingerMiddle(WorldPosition, WorldRotation, LocalPosition, LocalRotation);

			return;

		case EFingerJointVR::TIP:

			GetPinkyFingerTip(WorldPosition, WorldRotation, LocalPosition, LocalRotation);

			return;
		}
	}
}

// Returns the percentage of a given finger's position based on their maximums and minimums.
// 0 = finger pointing inward, 1 = finger pointing outward.
// Note: You may need to adjust the minimum and maximum constants for accuracy and leniency.
float UHandVR::GetFingerPercentage(EFingerVR Finger)
{
	FVector WorldPosition;

	FRotator WorldRotation;

	FVector LocalPosition;

	FRotator LocalRotation;

	switch (Finger)
	{
	default:

		return 0;

	case EFingerVR::THUMB:

		GetThumb(WorldPosition, WorldRotation, LocalPosition, LocalRotation);

		return PERCENTAGE(LocalRotation.Euler().Y, THUMB_MIN, THUMB_MAX);

	case EFingerVR::INDEX:

		GetIndexFingerMiddle(WorldPosition, WorldRotation, LocalPosition, LocalRotation);

		return PERCENTAGE(LocalRotation.Euler().Y, INDEX_FINGER_MIN, INDEX_FINGER_MAX);

	case EFingerVR::MIDDLE:

		GetMiddleFingerMiddle(WorldPosition, WorldRotation, LocalPosition, LocalRotation);

		return PERCENTAGE(LocalRotation.Euler().Y, MIDDLE_FINGER_MIN, MIDDLE_FINGER_MAX);

	case EFingerVR::RING:

		GetRingFingerMiddle(WorldPosition, WorldRotation, LocalPosition, LocalRotation);

		return PERCENTAGE(LocalRotation.Euler().Y, RING_FINGER_MIN, RING_FINGER_MAX);

	case EFingerVR::PINKY:

		GetPinkyFingerMiddle(WorldPosition, WorldRotation, LocalPosition, LocalRotation);

		return PERCENTAGE(LocalRotation.Euler().Y, PINKY_FINGER_MIN, PINKY_FINGER_MAX);
	}
}

// Returns if the hand matches the given gesture. Add more gestures if needed.
// Note: You may need to adjust the values that check the gesture for accuracy and leniency.
bool UHandVR::GetGesture(EHandGestureVR Gesture)
{
	float Thumb = GetFingerPercentage(EFingerVR::THUMB);

	float Index = GetFingerPercentage(EFingerVR::INDEX);

	float Middle = GetFingerPercentage(EFingerVR::MIDDLE);

	float Ring = GetFingerPercentage(EFingerVR::RING);

	float Pinky = GetFingerPercentage(EFingerVR::PINKY);

	FVector WorldPosition;

	FRotator WorldRotation;

	FVector LocalPosition;

	FRotator LocalRotation;

	FVector WorldPosition2;

	FRotator WorldRotation2;

	FVector LocalPosition2;

	FRotator LocalRotation2;

	switch (Gesture)
	{
	default:

		return false;

	case EHandGestureVR::OPEN:

		return (Thumb >= 0.65) && (Index >= 0.65) && (Middle >= 0.65) && (Ring >= 0.65) && (Pinky >= 0.65);

	case EHandGestureVR::FIST:

		return (Thumb < 0.65) && (Index < 0.25) && (Middle < 0.25) && (Ring < 0.25) && (Pinky < 0.25);

	case EHandGestureVR::POINT:

		return (Index >= 0.65) && (Middle < 0.25) && (Ring < 0.25) && (Pinky < 0.25);

	case EHandGestureVR::PINCH:

		GetThumbTip(WorldPosition, WorldRotation, LocalPosition, LocalRotation);

		GetIndexFingerTip(WorldPosition2, WorldRotation2, LocalPosition2, LocalRotation2);

		return FVector::DistSquared(WorldPosition, WorldPosition2) <= 3;

	case EHandGestureVR::PINCH_MIDDLE:

		GetThumbTip(WorldPosition, WorldRotation, LocalPosition, LocalRotation);

		GetMiddleFingerTip(WorldPosition2, WorldRotation2, LocalPosition2, LocalRotation2);

		return FVector::DistSquared(WorldPosition, WorldPosition2) <= 3;

	case EHandGestureVR::GRIP:

		return (Middle < 0.25) && (Ring < 0.25) && (Pinky < 0.25);

	case EHandGestureVR::THUMBS_UP:

		return (Thumb >= 0.65) && (Index < 0.25) && (Middle < 0.25) && (Ring < 0.25) && (Pinky < 0.25);

	case EHandGestureVR::FINGER_GUN:

		return (Thumb >= 0.65) && (Index >= 0.65) && (Middle < 0.25) && (Ring < 0.25) && (Pinky < 0.25);

	case EHandGestureVR::FLIP_OFF:

		return (Index < 0.25) && (Middle >= 0.65) && (Ring < 0.25) && (Pinky < 0.25);

	case EHandGestureVR::PEACE:

		return (Thumb < 0.65) && (Index >= 0.65) && (Middle >= 0.65) && (Ring < 0.25) && (Pinky < 0.25);

		// New gestures here
	}
}
