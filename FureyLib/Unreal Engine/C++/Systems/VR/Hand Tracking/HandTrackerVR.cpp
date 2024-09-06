
// Static VR Hand Tracking Component Script
// by Kyle Furey

// REQUIREMENT: HandTrackerVR.h

// Include this heading to use the class
#include "VR/Hand Tracking/HandTrackerVR.h"


// CONSTRUCTORS

// Default constructor.
UHandTrackerVR::UHandTrackerVR()
{
	PrimaryComponentTick.bCanEverTick = true;

	PrimaryComponentTick.TickGroup = ETickingGroup::TG_PrePhysics;

	PrimaryComponentTick.bHighPriority = true;

	LeftHand = nullptr;

	RightHand = nullptr;

	bDominantHandIsRight = true;

	Headset = nullptr;

	LeftHandMotionController = nullptr;

	RightHandMotionController = nullptr;

	LeftGestures = TMap<EHandGestureVR, bool>();

	RightGestures = TMap<EHandGestureVR, bool>();

	for (int32 Index = 0; Index < (int32)EHandGestureVR::MAX; Index++)
	{
		LeftGestures.Add((EHandGestureVR)Index, false);

		RightGestures.Add((EHandGestureVR)Index, false);
	}

	State = EHandTrackingStateVR::BOTH;

	bTrackingLeft = false;

	bTrackingRight = false;

	PreviousLeftGestures = TSet<EHandGestureVR>();

	PreviousRightGestures = TSet<EHandGestureVR>();
}

// Object initializer constructor.
UHandTrackerVR::UHandTrackerVR(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;

	PrimaryComponentTick.TickGroup = ETickingGroup::TG_PrePhysics;

	PrimaryComponentTick.bHighPriority = true;

	LeftHand = nullptr;

	RightHand = nullptr;

	bDominantHandIsRight = true;

	Headset = nullptr;

	LeftHandMotionController = nullptr;

	RightHandMotionController = nullptr;

	LeftGestures = TMap<EHandGestureVR, bool>();

	RightGestures = TMap<EHandGestureVR, bool>();

	for (int32 Index = 0; Index < (int32)EHandGestureVR::MAX; Index++)
	{
		LeftGestures.Add((EHandGestureVR)Index, false);

		RightGestures.Add((EHandGestureVR)Index, false);
	}

	State = EHandTrackingStateVR::BOTH;

	bTrackingLeft = false;

	bTrackingRight = false;

	PreviousLeftGestures = TSet<EHandGestureVR>();

	PreviousRightGestures = TSet<EHandGestureVR>();
}

// Hand tracker constructor.
UHandTrackerVR::UHandTrackerVR(UCameraComponent* _Headset, UPoseableMeshComponent* _LeftHandComponent, UPoseableMeshComponent* _RightHandComponent, bool _DominantHandIsRight, EHandTrackingStateVR TrackingState)
{
	PrimaryComponentTick.bCanEverTick = true;

	PrimaryComponentTick.TickGroup = ETickingGroup::TG_PrePhysics;

	PrimaryComponentTick.bHighPriority = true;

	LeftHand = UHandVR::ConstructHandVR(false, _LeftHandComponent);

	RightHand = UHandVR::ConstructHandVR(true, _RightHandComponent);

	bDominantHandIsRight = _DominantHandIsRight;

	Headset = _Headset;

	LeftHandMotionController = nullptr;

	RightHandMotionController = nullptr;

	LeftGestures = TMap<EHandGestureVR, bool>();

	RightGestures = TMap<EHandGestureVR, bool>();

	for (int32 Index = 0; Index < (int32)EHandGestureVR::MAX; Index++)
	{
		LeftGestures.Add((EHandGestureVR)Index, false);

		RightGestures.Add((EHandGestureVR)Index, false);
	}

	State = TrackingState;

	bTrackingLeft = false;

	bTrackingRight = false;

	PreviousLeftGestures = TSet<EHandGestureVR>();

	PreviousRightGestures = TSet<EHandGestureVR>();
}


// UNREAL FUNCTIONS

// Initializes hand tracking.
void UHandTrackerVR::BeginPlay()
{
	// Calls the base class's function.
	Super::BeginPlay();

	// Check for existing hand trackers.
	if (Instance == nullptr)
	{
		// Store the current instance of the hand tracker.
		Instance = this;

		// Implement IHandInteractableVR implementation.
		ImplementHandTracking();
	}
	else
	{
		// Remove this component as it is not needed.
		DestroyComponent();
	}
}

// Disables hand tracking.
void UHandTrackerVR::BeginDestroy()
{
	// Calls the base class's function.
	Super::BeginDestroy();

	// Check for existing hand trackers.
	if (Instance == this)
	{
		// Clean up tracking and gestures.
		bTrackingLeft = false;

		bTrackingRight = false;

		if (bTrackingLeft)
		{
			for (UObject* Object : Implementations)
			{
				if (Object == this)
				{
					continue;
				}

				if (IsValid(Object))
				{
					Execute_OnHandLost(Object, false);
				}
			}
		}

		if (bTrackingRight)
		{
			for (UObject* Object : Implementations)
			{
				if (Object == this)
				{
					continue;
				}

				if (IsValid(Object))
				{
					Execute_OnHandLost(Object, true);
				}
			}
		}

		// Remove IHandInteractableVR implementation.
		Implementations.Remove(this);

		if (Implementations.Num() <= 0)
		{
			HandsSet = false;
		}

		// Clean up implementations.
		Implementations.Empty();

		HandsSet = false;

		// Remove the current instance of the hand tracker.
		Instance = nullptr;
	}
}

// Called every frame.
void UHandTrackerVR::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// Calls the base class's function.
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	LocateMotionControllers();

	bool bLeft = LeftHandMotionController != nullptr && LeftHandMotionController->IsTracked() && EnumHasAnyFlags(State, EHandTrackingStateVR::LEFT);

	bool bRight = RightHandMotionController != nullptr && RightHandMotionController->IsTracked() && EnumHasAnyFlags(State, EHandTrackingStateVR::RIGHT);

	if (!HandsSet && State != EHandTrackingStateVR::NONE && (bLeft || !EnumHasAnyFlags(State, EHandTrackingStateVR::LEFT)) && (bRight || !EnumHasAnyFlags(State, EHandTrackingStateVR::RIGHT)))
	{
		Execute_OnSetHands(this);
	}

	if (HandsSet)
	{
		if (bLeft)
		{
			if (!bTrackingLeft)
			{
				Execute_OnHandTracked(this, false);
			}

			for (int32 Index = 0; Index < (int32)EHandGestureVR::MAX; Index++)
			{
				LeftGestures[(EHandGestureVR)Index] = LeftHand->GetGesture((EHandGestureVR)Index);
			}

			for (int32 Index = 0; Index < (int32)EHandGestureVR::MAX; Index++)
			{
				if (LeftGestures[(EHandGestureVR)Index])
				{
					if (PreviousLeftGestures.Contains((EHandGestureVR)Index))
					{
						Execute_OnGestureTick(this, false, (EHandGestureVR)Index);
					}
					else
					{
						Execute_OnNewGesture(this, false, (EHandGestureVR)Index);
					}
				}
				else
				{
					if (PreviousLeftGestures.Contains((EHandGestureVR)Index))
					{
						Execute_OnStopGesture(this, false, (EHandGestureVR)Index);
					}
				}
			}

			PreviousLeftGestures.Empty();

			for (int32 Index = 0; Index < (int32)EHandGestureVR::MAX; Index++)
			{
				if (LeftGestures[(EHandGestureVR)Index])
				{
					PreviousLeftGestures.Add((EHandGestureVR)Index);
				}
			}
		}
		else
		{
			if (bTrackingLeft)
			{
				Execute_OnHandLost(this, false);
			}
		}

		if (bRight)
		{
			if (!bTrackingRight)
			{
				Execute_OnHandTracked(this, true);
			}

			for (int32 Index = 0; Index < (int32)EHandGestureVR::MAX; Index++)
			{
				RightGestures[(EHandGestureVR)Index] = RightHand->GetGesture((EHandGestureVR)Index);
			}

			for (int32 Index = 0; Index < (int32)EHandGestureVR::MAX; Index++)
			{
				if (RightGestures[(EHandGestureVR)Index])
				{
					if (PreviousRightGestures.Contains((EHandGestureVR)Index))
					{
						Execute_OnGestureTick(this, true, (EHandGestureVR)Index);
					}
					else
					{
						Execute_OnNewGesture(this, true, (EHandGestureVR)Index);
					}
				}
				else
				{
					if (PreviousRightGestures.Contains((EHandGestureVR)Index))
					{
						Execute_OnStopGesture(this, true, (EHandGestureVR)Index);
					}
				}
			}

			PreviousRightGestures.Empty();

			for (int32 Index = 0; Index < (int32)EHandGestureVR::MAX; Index++)
			{
				if (RightGestures[(EHandGestureVR)Index])
				{
					PreviousRightGestures.Add((EHandGestureVR)Index);
				}
			}
		}
		else
		{
			if (bTrackingRight)
			{
				Execute_OnHandLost(this, true);
			}
		}
	}
}


// HAND TRACKING STATE FUNCTIONS

// Locates the hand tracker's motion controllers.
void UHandTrackerVR::LocateMotionControllers()
{
	UPoseableMeshComponent* Component;

	USceneComponent* ParentComponent;

	if (LeftHandMotionController == nullptr)
	{
		if (LeftHand != nullptr)
		{
			Component = LeftHand->GetHand();

			if (Component != nullptr)
			{
				ParentComponent = Component->GetAttachParent();

				if (ParentComponent != nullptr)
				{
					LeftHandMotionController = Cast<UMotionControllerComponent>(ParentComponent);
				}
			}
		}
	}

	if (RightHandMotionController == nullptr)
	{
		if (RightHand != nullptr)
		{
			Component = RightHand->GetHand();

			if (Component != nullptr)
			{
				ParentComponent = Component->GetAttachParent();

				if (ParentComponent != nullptr)
				{
					RightHandMotionController = Cast<UMotionControllerComponent>(ParentComponent);
				}
			}
		}
	}
}

// Returns whether this object is currently receiving hand tracking input.
// This is the static version used exclusively for blueprint implementations.
bool UHandTrackerVR::IsHandTrackingVRImplemented(TScriptInterface<IHandInteractableVR> HandInteractableVR)
{
	return Implementations.Contains(HandInteractableVR.GetObject());
}

// Call this function when this object is created to enable hand tracking.
// Make sure to call RemoveHandTrackingVR() when this object is destroyed.
// This is the static version used exclusively for blueprint implementations.
void UHandTrackerVR::ImplementHandTrackingVR(TScriptInterface<IHandInteractableVR> HandInteractableVR)
{
	Implementations.Add(HandInteractableVR.GetObject());

	if (HandsSet)
	{
		Execute_OnSetHands(HandInteractableVR.GetObject());
	}
}

// Call this function when this object is destroyed to remove hand tracking.
// Make sure to call ImplementHandTrackingVR() when this object is created.
// This is the static version used exclusively for blueprint implementations.
void UHandTrackerVR::RemoveHandTrackingVR(TScriptInterface<IHandInteractableVR> HandInteractableVR)
{
	Implementations.Remove(HandInteractableVR.GetObject());

	if (Implementations.Num() <= 0)
	{
		HandsSet = false;
	}
}


// HAND TRACKER FUNCTIONS

// Returns the global state of hand tracking input.
EHandTrackingStateVR UHandTrackerVR::GetHandTrackingState()
{
	if (Instance == nullptr)
	{
		return EHandTrackingStateVR::NONE;
	}

	return Instance->State;
}

// Sets the global state of hand tracking input.
void UHandTrackerVR::SetHandTrackingState(EHandTrackingStateVR TrackingState)
{
	if (Instance == nullptr)
	{
		return;
	}

	Instance->State = TrackingState;
}

// Returns whether hand tracking is enabled for the given hands.
void UHandTrackerVR::IsHandTrackingEnabled(bool& Either, bool& Both, bool& Left, bool& Right)
{
	Left = Instance != nullptr && EnumHasAnyFlags(Instance->State, EHandTrackingStateVR::LEFT);

	Right = Instance != nullptr && EnumHasAnyFlags(Instance->State, EHandTrackingStateVR::RIGHT);

	Both = Left && Right;

	Either = Left || Right;
}

// Returns whether hand tracking is enabled for the left hand.
bool UHandTrackerVR::IsLeftHandTrackingEnabled()
{
	return Instance != nullptr && EnumHasAnyFlags(Instance->State, EHandTrackingStateVR::LEFT);
}

// Returns whether hand tracking is enabled for the right hand.
bool UHandTrackerVR::IsRightHandTrackingEnabled()
{
	return Instance != nullptr && EnumHasAnyFlags(Instance->State, EHandTrackingStateVR::RIGHT);
}

// Returns the current IHandInteractableVR implementations.
TSet<UObject*> UHandTrackerVR::GetHandTrackingImplementations()
{
	return TSet<UObject*>(Implementations);
}

// Returns the current number of IHandInteractableVR implementations.
int32 UHandTrackerVR::NumberOfHandTrackingImplementations()
{
	return Implementations.Num();
}

// Returns the current instance of the hand tracker component.
UHandTrackerVR* UHandTrackerVR::GetHandTrackerVR()
{
	return Instance;
}

// Constructs a new HandTrackerVR component.
UHandTrackerVR* UHandTrackerVR::ConstructHandTrackerVR(AActor* Parent, UCameraComponent* _Headset, UPoseableMeshComponent* _LeftHandComponent, UPoseableMeshComponent* _RightHandComponent, bool _DominantHandIsRight, EHandTrackingStateVR TrackingState)
{
	if (Instance != nullptr)
	{
		return nullptr;
	}

	UHandTrackerVR* NewHandTracker = Cast<UHandTrackerVR>(Parent->AddComponentByClass(UHandTrackerVR::StaticClass(), true, FTransform(), true));

	NewHandTracker->RegisterComponent();

	Parent->AddInstanceComponent(NewHandTracker);

	NewHandTracker->PrimaryComponentTick.bCanEverTick = true;

	NewHandTracker->PrimaryComponentTick.TickGroup = ETickingGroup::TG_PrePhysics;

	NewHandTracker->PrimaryComponentTick.bHighPriority = true;

	NewHandTracker->LeftHand = UHandVR::ConstructHandVR(false, _LeftHandComponent);

	NewHandTracker->RightHand = UHandVR::ConstructHandVR(true, _RightHandComponent);

	NewHandTracker->bDominantHandIsRight = _DominantHandIsRight;

	NewHandTracker->Headset = _Headset;

	NewHandTracker->LeftHandMotionController = nullptr;

	NewHandTracker->RightHandMotionController = nullptr;

	NewHandTracker->LeftGestures = TMap<EHandGestureVR, bool>();

	NewHandTracker->RightGestures = TMap<EHandGestureVR, bool>();

	for (int32 Index = 0; Index < (int32)EHandGestureVR::MAX; Index++)
	{
		NewHandTracker->LeftGestures.Add((EHandGestureVR)Index, false);

		NewHandTracker->RightGestures.Add((EHandGestureVR)Index, false);
	}

	NewHandTracker->bTrackingLeft = false;

	NewHandTracker->bTrackingRight = false;

	NewHandTracker->PreviousLeftGestures = TSet<EHandGestureVR>();

	NewHandTracker->PreviousRightGestures = TSet<EHandGestureVR>();

	NewHandTracker->State = TrackingState;

	return NewHandTracker;
}


// TRACKING FUNCTIONS

// Returns whether VR hands have been set yet.
bool UHandTrackerVR::AreHandsSet()
{
	return HandsSet;
}

// Returns whether the given VR hand is currently set and being tracked.
bool UHandTrackerVR::IsTrackingHand(bool bIsRight)
{
	return HandsSet && Instance != nullptr && (bIsRight ? Instance->bTrackingRight : Instance->bTrackingLeft);
}

// Returns whether both VR hands are currently set and being tracked.
void UHandTrackerVR::IsTrackingBothHands(bool& Both, bool& Left, bool& Right)
{
	Left = HandsSet && Instance != nullptr && Instance->bTrackingLeft;

	Right = HandsSet && Instance != nullptr && Instance->bTrackingRight;

	Both = Left && Right;
}

// Returns whether the left VR hand is currently set and being tracked.
bool UHandTrackerVR::IsTrackingLeftHand()
{
	return HandsSet && Instance != nullptr && Instance->bTrackingLeft;
}

// Returns whether the right VR hand is currently set and being tracked.
bool UHandTrackerVR::IsTrackingRightHand()
{
	return HandsSet && Instance != nullptr && Instance->bTrackingRight;
}


// HAND FUNCTIONS

// Returns the given VR hand.
UHandVR* UHandTrackerVR::GetHand(bool bIsRight)
{
	if (Instance == nullptr)
	{
		return nullptr;
	}

	return bIsRight ? Instance->RightHand : Instance->LeftHand;
}

// Returns both VR hands.
void UHandTrackerVR::GetBothHands(UHandVR*& Left, UHandVR*& Right)
{
	if (Instance == nullptr)
	{
		Left = nullptr;

		Right = nullptr;

		return;
	}

	Left = Instance->LeftHand;

	Right = Instance->RightHand;
}

// Returns the left VR hand.
UHandVR* UHandTrackerVR::GetLeftHand()
{
	if (Instance == nullptr)
	{
		return nullptr;
	}

	return Instance->LeftHand;
}

// Returns the right VR hand.
UHandVR* UHandTrackerVR::GetRightHand()
{
	if (Instance == nullptr)
	{
		return nullptr;
	}

	return Instance->RightHand;
}


// DOMINANT HAND FUNCTIONS

// Returns whether the dominant hand is currently the right hand.
bool UHandTrackerVR::IsDominantHandRight()
{
	if (Instance == nullptr)
	{
		return false;
	}

	return Instance->bDominantHandIsRight;
}

// Returns whether the dominant hand is currently the left hand.
bool UHandTrackerVR::IsDominantHandLeft()
{
	if (Instance == nullptr)
	{
		return false;
	}

	return !Instance->bDominantHandIsRight;
}

// Set whether the dominant hand is currently the right hand.
void UHandTrackerVR::SetDominantHand(bool bIsRight)
{
	if (Instance == nullptr)
	{
		return;
	}

	Instance->bDominantHandIsRight = bIsRight;
}

// Returns the dominant hand.
void UHandTrackerVR::GetDominantHand(UHandVR*& Dominant, UHandVR*& NonDominant)
{
	if (Instance == nullptr)
	{
		Dominant = nullptr;

		NonDominant = nullptr;

		return;
	}

	Dominant = Instance->bDominantHandIsRight ? Instance->RightHand : Instance->LeftHand;

	NonDominant = Instance->bDominantHandIsRight ? Instance->LeftHand : Instance->RightHand;
}

// Returns the non-dominant hand.
void UHandTrackerVR::GetNonDominantHand(UHandVR*& NonDominant, UHandVR*& Dominant)
{
	if (Instance == nullptr)
	{
		Dominant = nullptr;

		NonDominant = nullptr;

		return;
	}

	NonDominant = Instance->bDominantHandIsRight ? Instance->LeftHand : Instance->RightHand;

	Dominant = Instance->bDominantHandIsRight ? Instance->RightHand : Instance->LeftHand;
}


// HEADSET FUNCTIONS

// Returns the headset camera.
UCameraComponent* UHandTrackerVR::GetHeadset()
{
	if (Instance == nullptr)
	{
		return nullptr;
	}

	return Instance->Headset;
}

// Returns the headset camera's transform data.
void UHandTrackerVR::GetHeadsetTransform(FVector& WorldPosition, FRotator& WorldRotation)
{
	if (Instance == nullptr)
	{
		WorldPosition = FVector(0, 0, 0);

		WorldRotation = FRotator(0, 0, 0);

		return;
	}

	WorldPosition = Instance->Headset->GetComponentLocation();

	WorldRotation = Instance->Headset->GetComponentRotation();
}

// Returns the player actor.
AActor* UHandTrackerVR::GetPlayer()
{
	if (Instance == nullptr || Instance->Headset == nullptr)
	{
		return nullptr;
	}

	return Instance->Headset->GetAttachParentActor();
}

// Returns the player's transform data.
void UHandTrackerVR::GetPlayerTransform(FVector& WorldPosition, FRotator& WorldRotation, FVector& WorldScale)
{
	if (Instance == nullptr || Instance->Headset == nullptr)
	{
		WorldPosition = FVector(0, 0, 0);

		WorldRotation = FRotator(0, 0, 0);

		WorldScale = FVector(1, 1, 1);

		return;
	}

	AActor* Parent = Instance->Headset->GetAttachParentActor();

	if (Parent == nullptr)
	{
		WorldPosition = FVector(0, 0, 0);

		WorldRotation = FRotator(0, 0, 0);

		WorldScale = FVector(1, 1, 1);

		return;
	}

	WorldPosition = Parent->GetActorLocation();

	WorldRotation = Parent->GetActorRotation();

	WorldScale = Parent->GetActorScale();
}


// MOTION CONTROLLER FUNCTIONS

// Returns the given motion controller.
UMotionControllerComponent* UHandTrackerVR::GetMotionController(bool bIsRight)
{
	if (Instance == nullptr)
	{
		return nullptr;
	}

	return bIsRight ? Instance->RightHandMotionController : Instance->LeftHandMotionController;
}

// Returns both motion controllers.
void UHandTrackerVR::GetBothMotionControllers(UMotionControllerComponent*& Left, UMotionControllerComponent*& Right)
{
	if (Instance == nullptr)
	{
		Left = nullptr;

		Right = nullptr;

		return;
	}

	Left = Instance->LeftHandMotionController;

	Right = Instance->RightHandMotionController;
}

// Returns the left motion controller.
UMotionControllerComponent* UHandTrackerVR::GetLeftMotionController()
{
	if (Instance == nullptr)
	{
		return nullptr;
	}

	return Instance->LeftHandMotionController;
}

// Returns the right motion controller.
UMotionControllerComponent* UHandTrackerVR::GetRightMotionController()
{
	if (Instance == nullptr)
	{
		return nullptr;
	}

	return Instance->RightHandMotionController;
}


// GESTURE FUNCTIONS

// Returns whether the given VR hand is making the given gesture.
bool UHandTrackerVR::GetGesture(bool bIsRight, EHandGestureVR Gesture)
{
	if (Instance == nullptr)
	{
		return false;
	}

	return bIsRight ? Instance->RightGestures[Gesture] : Instance->LeftGestures[Gesture];
}

// Returns whether the both VR hands are making the given gestures.
void UHandTrackerVR::GetBothGestures(EHandGestureVR LeftGesture, EHandGestureVR RightGesture, bool& Left, bool& Right)
{
	if (Instance == nullptr)
	{
		Left = false;

		Right = false;

		return;
	}
}

// Returns whether the left VR hand is making the given gesture.
bool UHandTrackerVR::GetLeftGesture(EHandGestureVR Gesture)
{
	if (Instance == nullptr)
	{
		return false;
	}

	return Instance->LeftGestures[Gesture];
}

// Returns whether the right VR hand is making the given gesture.
bool UHandTrackerVR::GetRightGesture(EHandGestureVR Gesture)
{
	if (Instance == nullptr)
	{
		return false;
	}

	return Instance->RightGestures[Gesture];
}


// GESTURE MAP FUNCTIONS

// Returns all of the gestures of the given VR hand.
TMap<EHandGestureVR, bool> UHandTrackerVR::GetGestureMap(bool bIsRight)
{
	if (Instance == nullptr)
	{
		return TMap<EHandGestureVR, bool>();
	}

	return bIsRight ? TMap<EHandGestureVR, bool>(Instance->RightGestures) : TMap<EHandGestureVR, bool>(Instance->LeftGestures);
}

// Returns all of the gestures of both VR hands.
void UHandTrackerVR::GetBothGestureMaps(TMap<EHandGestureVR, bool>& Left, TMap<EHandGestureVR, bool>& Right)
{
	if (Instance == nullptr)
	{
		Left = TMap<EHandGestureVR, bool>();

		Right = TMap<EHandGestureVR, bool>();

		return;
	}

	Left = Instance->LeftGestures;

	Right = Instance->RightGestures;
}

// Returns all of the gestures of the left VR hand.
TMap<EHandGestureVR, bool> UHandTrackerVR::GetLeftGestureMap()
{
	if (Instance == nullptr)
	{
		return TMap<EHandGestureVR, bool>();
	}

	return TMap<EHandGestureVR, bool>(Instance->LeftGestures);
}

// Returns all of the gestures of the right VR hand.
TMap<EHandGestureVR, bool> UHandTrackerVR::GetRightGestureMap()
{
	if (Instance == nullptr)
	{
		return TMap<EHandGestureVR, bool>();
	}

	return TMap<EHandGestureVR, bool>(Instance->RightGestures);
}


// ACTIVE GESTURE FUNCTIONS

// Returns all of the active gestures of the given VR hand.
TSet<EHandGestureVR> UHandTrackerVR::GetActiveGestures(bool bIsRight)
{
	if (Instance == nullptr)
	{
		return TSet<EHandGestureVR>();
	}

	TSet<EHandGestureVR> Gestures = TSet<EHandGestureVR>();

	if (bIsRight)
	{
		for (int32 Index = 0; Index < (int32)EHandGestureVR::MAX; Index++)
		{
			if (Instance->RightGestures[(EHandGestureVR)Index])
			{
				Gestures.Add((EHandGestureVR)Index);
			}
		}
	}
	else
	{
		for (int32 Index = 0; Index < (int32)EHandGestureVR::MAX; Index++)
		{
			if (Instance->LeftGestures[(EHandGestureVR)Index])
			{
				Gestures.Add((EHandGestureVR)Index);
			}
		}
	}

	return Gestures;
}

// Returns all of the active gestures of both VR hands.
void UHandTrackerVR::GetBothActiveGestures(TSet<EHandGestureVR>& Left, TSet<EHandGestureVR>& Right)
{
	if (Instance == nullptr)
	{
		Left = TSet<EHandGestureVR>();

		Right = TSet<EHandGestureVR>();

		return;
	}

	for (int32 Index = 0; Index < (int32)EHandGestureVR::MAX; Index++)
	{
		if (Instance->RightGestures[(EHandGestureVR)Index])
		{
			Left.Add((EHandGestureVR)Index);
		}
	}

	for (int32 Index = 0; Index < (int32)EHandGestureVR::MAX; Index++)
	{
		if (Instance->LeftGestures[(EHandGestureVR)Index])
		{
			Right.Add((EHandGestureVR)Index);
		}
	}

}

// Returns all of the active gestures of the left VR hand.
TSet<EHandGestureVR> UHandTrackerVR::GetActiveLeftGestures()
{
	if (Instance == nullptr)
	{
		return TSet<EHandGestureVR>();
	}

	TSet<EHandGestureVR> Gestures = TSet<EHandGestureVR>();

	for (int32 Index = 0; Index < (int32)EHandGestureVR::MAX; Index++)
	{
		if (Instance->LeftGestures[(EHandGestureVR)Index])
		{
			Gestures.Add((EHandGestureVR)Index);
		}
	}

	return Gestures;
}

// Returns all of the active gestures of the right VR hand.
TSet<EHandGestureVR> UHandTrackerVR::GetActiveRightGestures()
{
	if (Instance == nullptr)
	{
		return TSet<EHandGestureVR>();
	}

	TSet<EHandGestureVR> Gestures = TSet<EHandGestureVR>();

	for (int32 Index = 0; Index < (int32)EHandGestureVR::MAX; Index++)
	{
		if (Instance->RightGestures[(EHandGestureVR)Index])
		{
			Gestures.Add((EHandGestureVR)Index);
		}
	}

	return Gestures;
}


// IHANDINTERACTABLEVR IMPLEMENTATION

// Calls OnSetHands() for each IHandInteractableVR implementation.
void UHandTrackerVR::OnSetHands_Implementation()
{
	HandsSet = true;

	for (UObject* Object : Implementations)
	{
		if (Object == this)
		{
			continue;
		}

		if (IsValid(Object))
		{
			Execute_OnSetHands(Object);
		}
	}
}

// Calls OnHandTracked() for each IHandInteractableVR implementation.
void UHandTrackerVR::OnHandTracked_Implementation(bool bIsRight)
{
	if (bIsRight)
	{
		bTrackingRight = true;
	}
	else
	{
		bTrackingLeft = true;
	}

	for (UObject* Object : Implementations)
	{
		if (Object == this)
		{
			continue;
		}

		if (IsValid(Object))
		{
			Execute_OnHandTracked(Object, bIsRight);
		}
	}
}

// Calls OnHandLost() for each IHandInteractableVR implementation.
void UHandTrackerVR::OnHandLost_Implementation(bool bIsRight)
{
	if (bIsRight)
	{
		bTrackingRight = false;

		for (UObject* Object : Implementations)
		{
			if (Object == this)
			{
				continue;
			}

			if (IsValid(Object))
			{
				Execute_OnHandLost(Object, true);

				for (EHandGestureVR Gesture : PreviousRightGestures)
				{
					Execute_OnStopGesture(Object, true, Gesture);
				}
			}
		}
	}
	else
	{
		bTrackingLeft = false;

		for (UObject* Object : Implementations)
		{
			if (Object == this)
			{
				continue;
			}

			if (IsValid(Object))
			{
				Execute_OnHandLost(Object, false);

				for (EHandGestureVR Gesture : PreviousLeftGestures)
				{
					Execute_OnStopGesture(Object, false, Gesture);
				}
			}
		}
	}
}

// Calls OnNewGesture() for each IHandInteractableVR implementation.
void UHandTrackerVR::OnNewGesture_Implementation(bool bIsRight, EHandGestureVR NewGesture)
{
	for (UObject* Object : Implementations)
	{
		if (Object == this)
		{
			continue;
		}

		if (IsValid(Object))
		{
			Execute_OnNewGesture(Object, bIsRight, NewGesture);
		}
	}
}

// Calls OnGestureTick() for each IHandInteractableVR implementation.
void UHandTrackerVR::OnGestureTick_Implementation(bool bIsRight, EHandGestureVR Gesture)
{
	for (UObject* Object : Implementations)
	{
		if (Object == this)
		{
			continue;
		}

		if (IsValid(Object))
		{
			Execute_OnGestureTick(Object, bIsRight, Gesture);
		}
	}
}

// Calls OnStopGesture() for each IHandInteractableVR implementation.
void UHandTrackerVR::OnStopGesture_Implementation(bool bIsRight, EHandGestureVR StoppedGesture)
{
	for (UObject* Object : Implementations)
	{
		if (Object == this)
		{
			continue;
		}

		if (IsValid(Object))
		{
			Execute_OnStopGesture(Object, bIsRight, StoppedGesture);
		}
	}
}


// STATIC VARIABLE INITIALIZATION

// The global instance of the world's hand tracker used to call hand tracker functions anywhere.
UHandTrackerVR* UHandTrackerVR::Instance = nullptr;
