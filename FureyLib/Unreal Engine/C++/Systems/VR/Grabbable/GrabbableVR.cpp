
// VR Grabbable Actor Component Script
// by Kyle Furey

// REQUIREMENT: GrabbableVR.h

// Include this heading to use the class
#include "VR/Grabbable/GrabbableVR.h"


// GRAB POINT CONSTRUCTORS

// Default constructor.
FGrabPointVR::FGrabPointVR()
{
	Gestures = { EHandGestureVR::FIST };

	GrabPointName = "New Grab Point";

	Collider = nullptr;

	HandOffset = FVector(0, 0, 0);

	bUseRotationOffset = true;

	RotationOffset = FRotator(0, 0, 0);

	Priority = EGrabPointPriorityVR::NORMAL;
}

// Grab point constructor
FGrabPointVR::FGrabPointVR(TArray<EHandGestureVR> _Gestures, FName _GrabPointName, UPrimitiveComponent* _Collider, FVector _HandOffset, bool UseRotationOffset, FRotator _RotationOffset, EGrabPointPriorityVR _Priority)
{
	Gestures = _Gestures;

	GrabPointName = _GrabPointName;

	Collider = _Collider;

	HandOffset = _HandOffset;

	bUseRotationOffset = UseRotationOffset;

	RotationOffset = _RotationOffset;

	Priority = _Priority;
}


// GRABBABLE CONSTRUCTORS

// Default constructor.
UGrabbableVR::UGrabbableVR()
{
	PrimaryComponentTick.bCanEverTick = true;

	PrimaryComponentTick.bHighPriority = true;

	GrabPoints = TArray<FGrabPointVR>();

	bActive = true;

	bHandTracking = true;

	IA_Grab_Button_Left = nullptr;

	IA_Grab_Button_Right = nullptr;

	GrabMode = EGrabModeVR::BOTH;

	GrabBuffer = 0.5f;

	PrimaryCollider = nullptr;

	bGrabPhysics = true;

	GravitySetting = EGravitySettingVR::UNCHANGED;

	bLocked = false;

	bThrowable = true;

	ThrowScale = 200;

	MinimumThrowDistance = 1;

	ThrowCalculation = EThrowCalculationVR::DIRECTION;

	ThrowRotationOffset = FRotator(0, 0, -10);

	CollisionDelay = 0.5f;

	OnGrab = FGrabDelegateVR();

	OnDrop = FGrabDelegateVR();

	OnThrow = FGrabDelegateVR();

	LeftGrabTime = 0;

	RightGrabTime = 0;

	bPreviousGravitySetting = false;

	PreviousPosition = FVector(0, 0, 0);

	GrabbedRotation = FRotator(0, 0, 0);

	PreviousPawnCollision = ECollisionResponse::ECR_Block;

	GrabbedHand = nullptr;

	HandRotation = FRotator(0, 0, 0);

	bIsGrabbedRight = false;

	GrabbedPoint = FGrabPointVR();

	bLeftDown = false;

	bRightDown = false;

	LeftPress = nullptr;

	RightPress = nullptr;

	LeftRelease = nullptr;

	RightRelease = nullptr;
}

// Object initializer constructor.
UGrabbableVR::UGrabbableVR(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;

	PrimaryComponentTick.bHighPriority = true;

	GrabPoints = TArray<FGrabPointVR>();

	bActive = true;

	bHandTracking = true;

	IA_Grab_Button_Left = nullptr;

	IA_Grab_Button_Right = nullptr;

	GrabMode = EGrabModeVR::BOTH;

	GrabBuffer = 0.5f;

	PrimaryCollider = nullptr;

	bGrabPhysics = true;

	GravitySetting = EGravitySettingVR::UNCHANGED;

	bLocked = false;

	bThrowable = true;

	ThrowScale = 200;

	MinimumThrowDistance = 1;

	ThrowCalculation = EThrowCalculationVR::DIRECTION;

	ThrowRotationOffset = FRotator(0, 0, -10);

	CollisionDelay = 0.5f;

	OnGrab = FGrabDelegateVR();

	OnDrop = FGrabDelegateVR();

	OnThrow = FGrabDelegateVR();

	LeftGrabTime = 0;

	RightGrabTime = 0;

	bPreviousGravitySetting = false;

	PreviousPosition = FVector(0, 0, 0);

	GrabbedRotation = FRotator(0, 0, 0);

	PreviousPawnCollision = ECollisionResponse::ECR_Block;

	GrabbedHand = nullptr;

	HandRotation = FRotator(0, 0, 0);

	bIsGrabbedRight = false;

	GrabbedPoint = FGrabPointVR();

	bLeftDown = false;

	bRightDown = false;

	LeftPress = nullptr;

	RightPress = nullptr;

	LeftRelease = nullptr;

	RightRelease = nullptr;
}

// Grabbable constructor.
UGrabbableVR::UGrabbableVR(TArray<FGrabPointVR> _GrabPoints, bool Active, bool HandTracking, UInputAction* LeftGrabButton, UInputAction* RightGrabButton, EGrabModeVR _GrabMode, float _GrabBuffer, UPrimitiveComponent* _Collider, bool GrabPhysics, EGravitySettingVR _GravitySetting, bool Locked, bool Throwable, float _ThrowScale, float _MinimumThrowDistance, EThrowCalculationVR _ThrowCalculation, FRotator _ThrowRotationOffset, float _CollisionDelay)
{
	PrimaryComponentTick.bCanEverTick = true;

	PrimaryComponentTick.bHighPriority = true;

	GrabPoints = _GrabPoints;

	bActive = Active;

	bHandTracking = HandTracking;

	IA_Grab_Button_Left = LeftGrabButton;

	IA_Grab_Button_Right = RightGrabButton;

	GrabMode = _GrabMode;

	GrabBuffer = _GrabBuffer;

	PrimaryCollider = _Collider;

	bGrabPhysics = GrabPhysics;

	GravitySetting = _GravitySetting;

	bLocked = Locked;

	bThrowable = Throwable;

	ThrowScale = _ThrowScale;

	MinimumThrowDistance = _MinimumThrowDistance;

	ThrowCalculation = _ThrowCalculation;

	ThrowRotationOffset = _ThrowRotationOffset;

	CollisionDelay = _CollisionDelay;

	OnGrab = FGrabDelegateVR();

	OnDrop = FGrabDelegateVR();

	OnThrow = FGrabDelegateVR();

	LeftGrabTime = 0;

	RightGrabTime = 0;

	bPreviousGravitySetting = false;

	PreviousPosition = FVector(0, 0, 0);

	GrabbedRotation = FRotator(0, 0, 0);

	PreviousPawnCollision = ECollisionResponse::ECR_Block;

	GrabbedHand = nullptr;

	HandRotation = FRotator(0, 0, 0);

	bIsGrabbedRight = false;

	GrabbedPoint = FGrabPointVR();

	bLeftDown = false;

	bRightDown = false;

	LeftPress = nullptr;

	RightPress = nullptr;

	LeftRelease = nullptr;

	RightRelease = nullptr;
}


// UNREAL FUNCTIONS

// Called when the game starts.
void UGrabbableVR::BeginPlay()
{
	// Calls the base class's function.
	Super::BeginPlay();

	if (IsValid(PrimaryCollider))
	{
		PreviousPawnCollision = PrimaryCollider->GetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn);
	}

	if (bActive)
	{
		if (bHandTracking)
		{
			ImplementHandTracking();
		}
		else
		{
			UControllerInputVR::ReceiveControllerInput(GetOwner(), 0);

			BindInput(false);

			BindInput(true);
		}
	}
}

// Called when this component is destroyed.
void UGrabbableVR::BeginDestroy()
{
	// Calls the base class's function.
	Super::BeginDestroy();

	if (IsGrabbedRight())
	{
		RightGrabbedObject = nullptr;
	}
	else if (IsGrabbedLeft())
	{
		LeftGrabbedObject = nullptr;
	}

	if (bActive)
	{
		if (bHandTracking)
		{
			RemoveHandTracking();
		}
		else
		{
			UControllerInputVR::StopReceivingControllerInput(GetOwner(), 0);

			UnbindInput(false);

			UnbindInput(true);
		}
	}
}

// Called every frame.
void UGrabbableVR::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// Calls the base class's function.
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateGrab(DeltaTime);
}


// CONTROLLERINPUTVR FUNCTIONS

// Called when the left grab button is pressed down.
void UGrabbableVR::OnLeftGrabButtonPressed()
{
	bLeftDown = true;
}

// Called when the right grab button is pressed down.
void UGrabbableVR::OnRightGrabButtonPressed()
{
	bRightDown = true;
}

// Called when the left grab button is released.
void UGrabbableVR::OnLeftGrabButtonReleased()
{
	bLeftDown = false;
}

// Called when the right grab button is released.
void UGrabbableVR::OnRightGrabButtonReleased()
{
	bRightDown = false;
}


// GETTERS

// Returns this grabbable component's grab points.
TArray<FGrabPointVR>& UGrabbableVR::GetGrabPoints()
{
	return GrabPoints;
}

// Returns whether the grabbable component is active.
bool UGrabbableVR::IsGrabActive()
{
	return bActive;
}

// Returns whether the grabbable component is using hand tracking for grab detection.
bool UGrabbableVR::IsUsingHandTracking()
{
	return bHandTracking;
}

// Returns this grabbable component's given grab button.
UInputAction* UGrabbableVR::GetGrabButton(bool bIsRight)
{
	return bIsRight ? IA_Grab_Button_Right : IA_Grab_Button_Left;
}

// Returns this grabbable component's grab buttons.
void UGrabbableVR::GetGrabButtons(UInputAction*& Left, UInputAction*& Right)
{
	Left = IA_Grab_Button_Left;

	Right = IA_Grab_Button_Right;
}

// Returns this grabbable component's left grab button.
UInputAction* UGrabbableVR::GetLeftGrabButton()
{
	return IA_Grab_Button_Left;
}

// Returns this grabbable component's grab mode setting.
UInputAction* UGrabbableVR::GetRightGrabButton()
{
	return IA_Grab_Button_Right;
}

// Returns this grabbable component's grab mode setting.
EGrabModeVR UGrabbableVR::GetGrabMode()
{
	return GrabMode;
}

// Returns this grabbable component's grab buffer time.
float UGrabbableVR::GetGrabBuffer()
{
	return GrabBuffer;
}

// Returns the primary collider component for this grabbable component.
UPrimitiveComponent* UGrabbableVR::GetPrimaryCollider()
{
	return PrimaryCollider;
}

// Returns whether this grabbable component is using physics when grabbed.
bool UGrabbableVR::IsUsingGrabPhysics()
{
	return bGrabPhysics;
}

// Returns the gravity behaviour setting for this grabbable component.
EGravitySettingVR UGrabbableVR::GetGravitySetting()
{
	return GravitySetting;
}

// Returns whether this grabbable component is locked to a player's hand when grabbed.
bool UGrabbableVR::IsLocked()
{
	return bLocked;
}

// Returns whether this grabbable component is currently grabbed and locked to a player's hand.
bool UGrabbableVR::IsCurrentlyLocked()
{
	return bLocked && IsGrabbed();
}

// Returns whether this object can be thrown.
bool UGrabbableVR::IsThrowable()
{
	return bThrowable;
}

// Returns the scale applied to the force added to this object when thrown.
float UGrabbableVR::GetThrowScale()
{
	return ThrowScale;
}

// Returns the minimum distance to consider this object as thrown when released.
float UGrabbableVR::GetMinimumThrowDistance()
{
	return MinimumThrowDistance;
}

// Returns the distance calculation used for throwing objects.
EThrowCalculationVR UGrabbableVR::GetThrowCalculation()
{
	return ThrowCalculation;
}

// Returns the offset in direction applied to this object when thrown.
FRotator UGrabbableVR::GetThrowRotationOffset()
{
	return ThrowRotationOffset;
}

// Returns the delay in seconds before hand collision is reenabled for this object when dropped.
float UGrabbableVR::GetCollisionDelay()
{
	return CollisionDelay;
}

// Returns the delegate used for the event when this object is grabbed.
FGrabDelegateVR& UGrabbableVR::GetOnGrabEvent()
{
	return OnGrab;
}

// Returns the delegate used for the event when this object is dropped.
FGrabDelegateVR& UGrabbableVR::GetOnDropEvent()
{
	return OnDrop;
}

// Returns the delegate used for the event when this object is thrown.
FGrabDelegateVR& UGrabbableVR::GetOnThrowEvent()
{
	return OnThrow;
}

// Returns the given hand's collider component.
UPrimitiveComponent* UGrabbableVR::GetHandCollider(bool bIsRight)
{
	return bIsRight ? RightHandCollider : LeftHandCollider;
}

// Returns both hands' collider components.
void UGrabbableVR::GetBothHandColliders(UPrimitiveComponent*& Left, UPrimitiveComponent*& Right)
{
	Left = LeftHandCollider;

	Right = RightHandCollider;
}

// Returns the left hand's collider component.
UPrimitiveComponent* UGrabbableVR::GetLeftHandCollider()
{
	return LeftHandCollider;
}

// Returns the right hand's collider component.
UPrimitiveComponent* UGrabbableVR::GetRightHandCollider()
{
	return RightHandCollider;
}


// SETTERS

// Sets whether the grabbable component is active.
void UGrabbableVR::SetGrabActive(bool Active)
{
	if (Active)
	{
		if (bHandTracking)
		{
			if (!IsHandTrackingImplemented())
			{
				ImplementHandTracking();
			}
		}
		else
		{
			UControllerInputVR::ReceiveControllerInput(GetOwner(), 0);

			UnbindInput(false);

			UnbindInput(true);

			BindInput(false);

			BindInput(true);
		}
	}
	else
	{
		if (bHandTracking)
		{
			if (IsHandTrackingImplemented())
			{
				RemoveHandTracking();
			}
		}
		else
		{
			UControllerInputVR::StopReceivingControllerInput(GetOwner(), 0);

			UnbindInput(false);

			UnbindInput(true);
		}
	}

	bActive = Active;
}

// Sets whether the grabbable component is using hand tracking for grab detection.
void UGrabbableVR::SetUseHandTracking(bool HandTracking)
{
	bHandTracking = HandTracking;

	SetGrabActive(bActive);
}

// Sets this grabbable component's given grab button.
void UGrabbableVR::SetGrabButton(bool bIsRight, UInputAction* Button)
{
	if (bIsRight)
	{
		UnbindInput(true);

		IA_Grab_Button_Right = Button;

		if (bActive && !bHandTracking)
		{
			BindInput(true);
		}
	}
	else
	{
		UnbindInput(false);

		IA_Grab_Button_Left = Button;

		if (bActive && !bHandTracking)
		{
			BindInput(false);
		}
	}
}

// Sets this grabbable component's grab buttons.
void UGrabbableVR::SetGrabButtons(UInputAction* Left, UInputAction* Right)
{
	UnbindInput(false);

	UnbindInput(true);

	IA_Grab_Button_Left = Left;

	IA_Grab_Button_Right = Right;

	if (bActive && !bHandTracking)
	{
		BindInput(false);

		BindInput(true);
	}
}

// Sets this grabbable component's left grab button.
void UGrabbableVR::SetLeftGrabButton(UInputAction* Button)
{
	UnbindInput(false);

	IA_Grab_Button_Left = Button;

	if (bActive && !bHandTracking)
	{
		BindInput(false);
	}
}

// Sets this grabbable component's left grab button.
void UGrabbableVR::SetRightGrabButton(UInputAction* Button)
{
	UnbindInput(true);

	IA_Grab_Button_Right = Button;

	if (bActive && !bHandTracking)
	{
		BindInput(true);
	}
}

// Sets this grabbable component's grab mode setting.
void UGrabbableVR::SetGrabMode(EGrabModeVR _GrabMode)
{
	GrabMode = _GrabMode;
}

// Sets this grabbable component's grab buffer time.
void UGrabbableVR::SetGrabBuffer(float Buffer)
{
	GrabBuffer = Buffer;
}

// Sets the primary collider component for this grabbable component.
void UGrabbableVR::SetPrimaryCollider(UPrimitiveComponent* Collider)
{
	PrimaryCollider = Collider;
}

// Sets whether this grabbable component is using physics when grabbed.
void UGrabbableVR::SetUseGrabPhysics(bool GrabPhysics)
{
	bGrabPhysics = GrabPhysics;
}

// Sets the gravity behaviour setting for this grabbable component.
void UGrabbableVR::SetGravitySetting(EGravitySettingVR _GravitySetting)
{
	GravitySetting = _GravitySetting;
}

// Sets whether this grabbable component is locked to a player's hand when grabbed.
void UGrabbableVR::SetLocked(bool Locked)
{
	bLocked = Locked;
}

// Locks the object so when it is grabbed, it stays grabbed until unlocked.
void UGrabbableVR::Lock()
{
	bLocked = true;
}

// Unlocks the object so when it is let go of, it is dropped or thrown.
void UGrabbableVR::Unlock()
{
	bLocked = false;
}

// Sets whether this object can be thrown.
void UGrabbableVR::SetThrowable(bool Throwable)
{
	bThrowable = Throwable;
}

// Sets the scale applied to the force added to this object when thrown.
void UGrabbableVR::SetThrowScale(float _ThrowScale)
{
	ThrowScale = _ThrowScale;
}

// Sets the minimum distance to consider this object as thrown when released.
void UGrabbableVR::SetMinimumThrowDistance(float _MinimumThrowDistance)
{
	MinimumThrowDistance = _MinimumThrowDistance;
}

// Sets the distance calculation used for when this object is thrown.
void UGrabbableVR::SetThrowCalculation(EThrowCalculationVR Calculation)
{
	ThrowCalculation = Calculation;
}

// Sets the offset in direction applied to this object when thrown.
void UGrabbableVR::SetThrowRotationOffset(FRotator Offset)
{
	ThrowRotationOffset = Offset;
}

// Sets the delay in seconds before hand collision is reenabled for this object when dropped.
void UGrabbableVR::SetCollisionDelay(float Delay)
{
	CollisionDelay = Delay;
}

// Binds or rebinds the delegate used for the event when this object is grabbed.
// Note: This event only binds one function, so you will need an event dispatcher for multiple events.
void UGrabbableVR::BindOnGrabEvent(const FGrabDelegateVR& Event)
{
	OnGrab = Event;
}

// Binds or rebinds the delegate used for the event when this object is dropped.
// Note: This event only binds one function, so you will need an event dispatcher for multiple events.
void UGrabbableVR::BindOnDropEvent(const FGrabDelegateVR& Event)
{
	OnDrop = Event;
}

// Binds or rebinds the delegate used for the event when this object is thrown.
// Note: This event only binds one function, so you will need an event dispatcher for multiple events.
void UGrabbableVR::BindOnThrowEvent(const FGrabDelegateVR& Event)
{
	OnThrow = Event;
}

// Sets the given hand's collider component.
void UGrabbableVR::SetHandCollider(bool bIsRight, UPrimitiveComponent* Collider)
{
	if (bIsRight)
	{
		RightHandCollider = Collider;
	}
	else
	{
		LeftHandCollider = Collider;
	}
}

// Sets both hands' collider components.
void UGrabbableVR::SetBothHandColliders(UPrimitiveComponent* Left, UPrimitiveComponent* Right)
{
	LeftHandCollider = Left;

	RightHandCollider = Right;
}

// Sets the left hand's collider component.
void UGrabbableVR::SetLeftHandCollider(UPrimitiveComponent* Collider)
{
	LeftHandCollider = Collider;
}

// Sets the right hand's collider component.
void UGrabbableVR::SetRightHandCollider(UPrimitiveComponent* Collider)
{
	RightHandCollider = Collider;
}

// Simply updates the collision profile so that when this object is dropped, it maintains its proper collision response to pawns.
// This is automatically set at the start of this object's lifetime, but you can call it again if you need to change the collision
void UGrabbableVR::UpdatePawnCollision(ECollisionResponse NewResponse)
{
	PreviousPawnCollision = NewResponse;
}


// GRABBABLE FUNCTIONS

// Binds controller inputs to grab events.
// Returns whether the bind was successful.
bool UGrabbableVR::BindInput(bool bIsRight)
{
	APlayerController* Player = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	if (IsValid(Player))
	{
		UEnhancedInputComponent* InputComponent = Cast<UEnhancedInputComponent>(Player->InputComponent);

		if (IsValid(InputComponent))
		{
			if (bIsRight)
			{
				if (IsValid(IA_Grab_Button_Right))
				{
					RightPress = &InputComponent->BindAction(IA_Grab_Button_Right, ETriggerEvent::Started, this, &UGrabbableVR::OnRightGrabButtonPressed);

					RightRelease = &InputComponent->BindAction(IA_Grab_Button_Right, ETriggerEvent::Completed, this, &UGrabbableVR::OnRightGrabButtonReleased);
				}
			}
			else
			{
				if (IsValid(IA_Grab_Button_Left))
				{
					LeftPress = &InputComponent->BindAction(IA_Grab_Button_Left, ETriggerEvent::Started, this, &UGrabbableVR::OnLeftGrabButtonPressed);

					LeftRelease = &InputComponent->BindAction(IA_Grab_Button_Left, ETriggerEvent::Completed, this, &UGrabbableVR::OnLeftGrabButtonReleased);
				}
			}

			return bIsRight ? IsValid(IA_Grab_Button_Right) : IsValid(IA_Grab_Button_Left);
		}
	}

	return false;
}

// Unbinds controller inputs to grab events.
// Returns whether the unbind was successful.
bool UGrabbableVR::UnbindInput(bool bIsRight)
{
	APlayerController* Player = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	if (IsValid(Player))
	{
		UEnhancedInputComponent* InputComponent = Cast<UEnhancedInputComponent>(Player->InputComponent);

		if (IsValid(InputComponent))
		{
			if (bIsRight)
			{
				if (RightPress != nullptr)
				{
					InputComponent->RemoveBinding(*RightPress);
				}

				if (RightRelease != nullptr)
				{
					InputComponent->RemoveBinding(*RightRelease);
				}
			}
			else
			{
				if (LeftPress != nullptr)
				{
					InputComponent->RemoveBinding(*LeftPress);
				}

				if (LeftRelease != nullptr)
				{
					InputComponent->RemoveBinding(*LeftRelease);
				}
			}

			return true;
		}
	}

	return false;
}

// Reenables collision with pawns (used for delays).
void UGrabbableVR::ReenablePawnCollision()
{
	if (!IsGrabbed() && IsValid(PrimaryCollider))
	{
		PrimaryCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, PreviousPawnCollision);
	}
}

// Completes a throw motion (used for delays).
void UGrabbableVR::CompleteThrow()
{
	if (IsValid(GrabbedHand))
	{
		GetOwner()->SetActorLocation(GrabbedHand->GetComponentLocation() + GrabbedHand->GetComponentQuat() * GetOffset(), bGrabPhysics, nullptr, bGrabPhysics ? ETeleportType::TeleportPhysics : ETeleportType::ResetPhysics);

		Throw(PreviousPosition, GetOwner()->GetActorLocation(), GetWorld()->GetDeltaSeconds());
	}

	PreviousPosition = FVector(0, 0, 0);
}

// Gets the proper offset vector.
FVector UGrabbableVR::GetOffset()
{
	FVector Offset;

	if (bHandTracking)
	{
		if (bIsGrabbedRight)
		{
			Offset = FVector(-GrabbedPoint.HandOffset.Z, GrabbedPoint.HandOffset.X, GrabbedPoint.HandOffset.Y) + FVector(-5, 5, 4);

			Offset.Y *= -1;

			Offset.Z *= -1;
		}
		else
		{
			Offset = FVector(GrabbedPoint.HandOffset.Z, GrabbedPoint.HandOffset.X, GrabbedPoint.HandOffset.Y) + FVector(-5, 5, 4);
		}
	}
	else
	{
		Offset = GrabbedPoint.HandOffset + FVector(-7.5, 2.5, -4);

		if (bIsGrabbedRight)
		{
			Offset.Y *= -1;
		}
	}

	return Offset;
}

// Updates the state of this grabbable actor.
// Automatically called each tick to update grabbing logic.
void UGrabbableVR::UpdateGrab(float DeltaSeconds)
{
	if (IsGrabbed())
	{
		bool KeepGrabbing = true;

		if (bActive && IsValid(GrabbedHand))
		{
			if (bHandTracking)
			{
				if (!bLocked)
				{
					KeepGrabbing = false;

					if (bIsGrabbedRight)
					{
						for (EHandGestureVR Gesture : GrabbedPoint.Gestures)
						{
							if (UHandTrackerVR::GetRightGesture(Gesture))
							{
								KeepGrabbing = true;

								break;
							}
						}
					}
					else
					{
						for (EHandGestureVR Gesture : GrabbedPoint.Gestures)
						{
							if (UHandTrackerVR::GetLeftGesture(Gesture))
							{
								KeepGrabbing = true;

								break;
							}
						}
					}
				}
			}
			else
			{
				KeepGrabbing = bLocked || (bIsGrabbedRight ? bRightDown : bLeftDown);
			}
		}
		else
		{
			KeepGrabbing = false;
		}

		if (KeepGrabbing)
		{
			if (GrabbedPoint.bUseRotationOffset)
			{
				if (bHandTracking)
				{
					if (bIsGrabbedRight)
					{
						GetOwner()->SetActorRotation(GrabbedHand->GetComponentQuat() * FRotator(0, -90, -90).Quaternion() * GrabbedPoint.RotationOffset.Quaternion() * FRotator().Quaternion(), bGrabPhysics ? ETeleportType::TeleportPhysics : ETeleportType::ResetPhysics);
					}
					else
					{
						GetOwner()->SetActorRotation(GrabbedHand->GetComponentQuat() * FRotator(0, 90, -90).Quaternion() * GrabbedPoint.RotationOffset.Quaternion(), bGrabPhysics ? ETeleportType::TeleportPhysics : ETeleportType::ResetPhysics);
					}
				}
				else
				{
					GetOwner()->SetActorRotation(GrabbedHand->GetComponentQuat() * GrabbedPoint.RotationOffset.Quaternion(), bGrabPhysics ? ETeleportType::TeleportPhysics : ETeleportType::ResetPhysics);
				}
			}
			else
			{
				GetOwner()->SetActorRotation(GrabbedHand->GetComponentQuat() * HandRotation.Quaternion().Inverse() * GrabbedRotation.Quaternion(), bGrabPhysics ? ETeleportType::TeleportPhysics : ETeleportType::ResetPhysics);
			}

			GetOwner()->SetActorLocation(GrabbedHand->GetComponentLocation() + GrabbedHand->GetComponentQuat() * GetOffset(), bGrabPhysics, nullptr, bGrabPhysics ? ETeleportType::TeleportPhysics : ETeleportType::ResetPhysics);

			if (bIsGrabbedRight)
			{
				RightGrabTime += DeltaSeconds;
			}
			else
			{
				LeftGrabTime += DeltaSeconds;
			}
		}
		else
		{
			if (bThrowable && IsValid(GrabbedHand) && FVector::DistSquared(GetOwner()->GetActorLocation() - GrabbedHand->GetComponentQuat() * GetOffset(), GrabbedHand->GetComponentLocation()) >= MinimumThrowDistance)
			{
				FTimerHandle Timer;

				PreviousPosition = GetOwner()->GetActorLocation();

				GetWorld()->GetTimerManager().SetTimer(Timer, this, &UGrabbableVR::CompleteThrow, THROW_DELAY, false);
			}
			else
			{
				Drop();
			}
		}
	}
	else if (bActive)
	{
		TArray<FGrabPointVR> LeftGrabbablePoints = TArray<FGrabPointVR>();

		TArray<FGrabPointVR> RightGrabbablePoints = TArray<FGrabPointVR>();

		bool LeftTimerUpdated = false;

		bool RightTimerUpdated = false;

		bool LeftGrabbable = false;

		bool RightGrabbable = false;

		switch (GrabMode)
		{
		case EGrabModeVR::LEFT_ONLY:

			LeftGrabbable = true;

			break;

		case EGrabModeVR::RIGHT_ONLY:

			RightGrabbable = true;

			break;

		case EGrabModeVR::DOMINANT:

			if (UHandTrackerVR::IsDominantHandRight())
			{
				RightGrabbable = true;
			}
			else
			{
				LeftGrabbable = true;
			}

			break;

		case EGrabModeVR::NON_DOMINANT:

			if (UHandTrackerVR::IsDominantHandRight())
			{
				LeftGrabbable = true;
			}
			else
			{
				RightGrabbable = true;
			}

			break;

		case EGrabModeVR::BOTH:

			LeftGrabbable = true;

			RightGrabbable = true;

			break;
		}

		if (bHandTracking)
		{
			for (FGrabPointVR GrabPoint : GrabPoints)
			{
				if (IsValid(GrabPoint.Collider))
				{
					if (IsValid(LeftHandCollider))
					{
						for (EHandGestureVR Gesture : GrabPoint.Gestures)
						{
							if (UHandTrackerVR::GetLeftGesture(Gesture))
							{
								if (LeftGrabTime <= GrabBuffer && GrabPoint.Collider->IsOverlappingComponent(LeftHandCollider))
								{
									LeftGrabbablePoints.Add(GrabPoint);
								}

								if (!LeftTimerUpdated)
								{
									LeftTimerUpdated = true;

									LeftGrabTime += DeltaSeconds;
								}

								break;
							}
						}
					}

					if (IsValid(RightHandCollider))
					{
						for (EHandGestureVR Gesture : GrabPoint.Gestures)
						{
							if (UHandTrackerVR::GetRightGesture(Gesture))
							{
								if (RightGrabTime <= GrabBuffer && GrabPoint.Collider->IsOverlappingComponent(RightHandCollider))
								{
									RightGrabbablePoints.Add(GrabPoint);
								}

								if (!RightTimerUpdated)
								{
									RightTimerUpdated = true;

									RightGrabTime += DeltaSeconds;
								}

								break;
							}
						}
					}
				}
			}
		}
		else
		{
			for (FGrabPointVR GrabPoint : GrabPoints)
			{
				if (IsValid(GrabPoint.Collider))
				{
					if (IsValid(LeftHandCollider) && bLeftDown)
					{
						if (LeftGrabTime <= GrabBuffer && GrabPoint.Collider->IsOverlappingComponent(LeftHandCollider))
						{
							LeftGrabbablePoints.Add(GrabPoint);
						}

						if (!LeftTimerUpdated)
						{
							LeftTimerUpdated = true;

							LeftGrabTime += DeltaSeconds;
						}
					}

					if (IsValid(RightHandCollider) && bRightDown)
					{
						if (RightGrabTime <= GrabBuffer && GrabPoint.Collider->IsOverlappingComponent(RightHandCollider))
						{
							RightGrabbablePoints.Add(GrabPoint);
						}

						if (!RightTimerUpdated)
						{
							RightTimerUpdated = true;

							RightGrabTime += DeltaSeconds;
						}
					}
				}
			}
		}

		if (!LeftTimerUpdated)
		{
			LeftGrabTime = 0;
		}

		if (!RightTimerUpdated)
		{
			RightGrabTime = 0;
		}

		FGrabPointVR ClosestGrabPoint = FGrabPointVR();

		ClosestGrabPoint.Priority = (EGrabPointPriorityVR)0;

		float ClosestDistance = FLT_MAX;

		bool bIsRight = false;

		if (!LeftGrabbablePoints.IsEmpty())
		{
			for (FGrabPointVR GrabPoint : LeftGrabbablePoints)
			{
				float NewDistance = FVector::DistSquared(LeftHandCollider->GetComponentLocation(), GrabPoint.Collider->GetComponentLocation());

				if (GrabPoint.Priority > ClosestGrabPoint.Priority || (NewDistance < ClosestDistance && GrabPoint.Priority == ClosestGrabPoint.Priority))
				{
					ClosestGrabPoint = GrabPoint;

					ClosestDistance = NewDistance;

					bIsRight = false;
				}
			}
		}

		if (!RightGrabbablePoints.IsEmpty())
		{
			for (FGrabPointVR GrabPoint : RightGrabbablePoints)
			{
				float NewDistance = FVector::DistSquared(RightHandCollider->GetComponentLocation(), GrabPoint.Collider->GetComponentLocation());

				if (GrabPoint.Priority > ClosestGrabPoint.Priority || (NewDistance < ClosestDistance && GrabPoint.Priority == ClosestGrabPoint.Priority))
				{
					ClosestGrabPoint = GrabPoint;

					ClosestDistance = NewDistance;

					bIsRight = true;
				}
			}
		}

		if (ClosestDistance != FLT_MAX)
		{
			Grab(bIsRight, ClosestGrabPoint);
		}
	}
}

// Attempts to attach this object to the given hand at the given grab point.
// Returns if the grab was successful.
bool UGrabbableVR::Grab(bool bIsRight, FGrabPointVR GrabPoint, bool InvokeEvent)
{
	if (bActive && !IsGrabbed() && IsValid(GrabPoint.Collider))
	{
		if (bIsRight)
		{
			if (!IsValid(RightGrabbedObject) && ((GrabMode == EGrabModeVR::BOTH) || (GrabMode == EGrabModeVR::RIGHT_ONLY) || (GrabMode == EGrabModeVR::DOMINANT && UHandTrackerVR::IsDominantHandRight()) || (GrabMode == EGrabModeVR::NON_DOMINANT && UHandTrackerVR::IsDominantHandLeft())))
			{
				RightGrabbedObject = this;

				LeftGrabTime = 0;

				RightGrabTime = 0;

				if (IsValid(PrimaryCollider))
				{
					bPreviousGravitySetting = PrimaryCollider->IsGravityEnabled();

					PrimaryCollider->SetEnableGravity(false);

					PrimaryCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
				}
				else
				{
					bPreviousGravitySetting = false;
				}

				GrabbedRotation = GetOwner()->GetActorRotation();

				if (bHandTracking)
				{
					GrabbedHand = UHandTrackerVR::GetRightMotionController();
				}
				else
				{
					GrabbedHand = UControllerInputVR::GetRightController();
				}

				HandRotation = GrabbedHand->GetComponentRotation();

				bIsGrabbedRight = true;

				GrabbedPoint = GrabPoint;

				if (InvokeEvent)
				{
					OnGrab.ExecuteIfBound();
				}

				return true;
			}
		}
		else
		{
			if (!IsValid(LeftGrabbedObject) && ((GrabMode == EGrabModeVR::BOTH) || (GrabMode == EGrabModeVR::LEFT_ONLY) || (GrabMode == EGrabModeVR::DOMINANT && UHandTrackerVR::IsDominantHandLeft()) || (GrabMode == EGrabModeVR::NON_DOMINANT && UHandTrackerVR::IsDominantHandRight())))
			{
				LeftGrabbedObject = this;

				LeftGrabTime = 0;

				RightGrabTime = 0;

				if (IsValid(PrimaryCollider))
				{
					PrimaryCollider->SetPhysicsLinearVelocity(FVector(0, 0, 0));

					PrimaryCollider->SetPhysicsAngularVelocityInDegrees(FVector(0, 0, 0));

					bPreviousGravitySetting = PrimaryCollider->IsGravityEnabled();

					PrimaryCollider->SetEnableGravity(false);

					PrimaryCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
				}
				else
				{
					bPreviousGravitySetting = false;
				}

				GrabbedRotation = GetOwner()->GetActorRotation();

				if (bHandTracking)
				{
					GrabbedHand = UHandTrackerVR::GetLeftMotionController();
				}
				else
				{
					GrabbedHand = UControllerInputVR::GetLeftController();
				}

				HandRotation = GrabbedHand->GetComponentRotation();

				bIsGrabbedRight = false;

				GrabbedPoint = GrabPoint;

				if (InvokeEvent)
				{
					OnGrab.ExecuteIfBound();
				}

				return true;
			}
		}
	}

	return false;
}

// Attempts to release this object from the player's hand.
// Returns if the drop was successful.
bool UGrabbableVR::Drop(bool InvokeEvent)
{
	if (IsGrabbed() && !bLocked)
	{
		if (bIsGrabbedRight)
		{
			RightGrabbedObject = nullptr;
		}
		else
		{
			LeftGrabbedObject = nullptr;
		}

		LeftGrabTime = 0;

		RightGrabTime = 0;

		if (IsValid(PrimaryCollider))
		{
			PrimaryCollider->SetPhysicsLinearVelocity(FVector(0, 0, 0));

			PrimaryCollider->SetPhysicsAngularVelocityInDegrees(FVector(0, 0, 0));

			switch (GravitySetting)
			{
			case EGravitySettingVR::UNCHANGED:

				PrimaryCollider->SetEnableGravity(bPreviousGravitySetting);

				break;

			case EGravitySettingVR::APPLY_GRAVITY:

				PrimaryCollider->SetEnableGravity(true);

				break;

			case EGravitySettingVR::NO_GRAVITY:

				PrimaryCollider->SetEnableGravity(false);

				break;
			}

			if (CollisionDelay > 0)
			{
				FTimerHandle Timer;

				GetWorld()->GetTimerManager().SetTimer(Timer, this, &UGrabbableVR::ReenablePawnCollision, CollisionDelay, false);
			}
			else
			{
				PrimaryCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, PreviousPawnCollision);
			}
		}

		bPreviousGravitySetting = false;

		GrabbedRotation = FRotator(0, 0, 0);

		GrabbedHand = nullptr;

		HandRotation = FRotator(0, 0, 0);

		bIsGrabbedRight = false;

		GrabbedPoint = FGrabPointVR();

		if (InvokeEvent)
		{
			OnDrop.ExecuteIfBound();
		}

		return true;
	}

	return false;
}

// Attempts to release and throw this object from the player's hand.
// Returns if the throw was successful.
bool UGrabbableVR::Throw(FVector StartPoint, FVector TargetPoint, float DeltaSeconds, bool InvokeEvent)
{
	if (bThrowable && IsValid(PrimaryCollider) && PrimaryCollider->IsSimulatingPhysics())
	{
		if (Drop(false))
		{
			FVector Direction = (TargetPoint - StartPoint) / DeltaSeconds;

			switch (ThrowCalculation)
			{
			case EThrowCalculationVR::DISTANCE:

				Direction.Normalize();

				Direction *= FVector::Dist(StartPoint, TargetPoint);

				break;

			case EThrowCalculationVR::DISTANCE_SQUARED:

				Direction.Normalize();

				Direction *= FVector::DistSquared(StartPoint, TargetPoint);

				break;
			}

			Direction = ThrowRotationOffset.RotateVector(Direction);

			PrimaryCollider->AddForce(Direction * ThrowScale);

			if (InvokeEvent)
			{
				OnThrow.ExecuteIfBound();
			}

			return true;
		}
	}

	return false;
}

// Returns whether this object is currently grabbed.
bool UGrabbableVR::IsGrabbed()
{
	return LeftGrabbedObject == this || RightGrabbedObject == this;
}

// Returns whether this object is currently grabbed with the left hand.
bool UGrabbableVR::IsGrabbedLeft()
{
	return LeftGrabbedObject == this;
}

// Returns whether this object is currently grabbed with right left hand.
bool UGrabbableVR::IsGrabbedRight()
{
	return RightGrabbedObject == this;
}

// Returns whether the given hand is empty.
bool UGrabbableVR::IsHandEmpty(bool bIsRight)
{
	return bIsRight ? !IsValid(RightGrabbedObject) : !IsValid(LeftGrabbedObject);
}

// Returns whether both hands are empty.
void UGrabbableVR::AreBothHandsEmpty(bool& BothHandsAreEmpty, bool& LeftHandIsEmpty, bool& RightHandIsEmpty)
{
	BothHandsAreEmpty = !IsValid(LeftGrabbedObject) && !IsValid(RightGrabbedObject);

	LeftHandIsEmpty = !IsValid(LeftGrabbedObject);

	RightHandIsEmpty = !IsValid(RightGrabbedObject);
}

// Returns whether the left hand is empty.
bool UGrabbableVR::IsLeftHandEmpty()
{
	return !IsValid(LeftGrabbedObject);
}

// Returns whether the right hand is empty.
bool UGrabbableVR::IsRightHandEmpty()
{
	return !IsValid(RightGrabbedObject);
}

// Returns the hand that is currently grabbing this object.
void UGrabbableVR::GetGrabbedHand(bool& bIsGrabbed, USceneComponent*& Hand, bool& bIsRight, FGrabPointVR& GrabPoint)
{
	bIsGrabbed = IsGrabbed();

	Hand = GrabbedHand;

	bIsRight = bIsGrabbedRight;

	GrabPoint = GrabbedPoint;
}

// Returns the given hand's grabbed object.
UGrabbableVR* UGrabbableVR::GetGrabbedObject(bool bIsRight)
{
	return bIsRight ? RightGrabbedObject : LeftGrabbedObject;
}

// Returns both hands' grabbed object.
void UGrabbableVR::GetBothGrabbedObjects(UGrabbableVR*& Left, UGrabbableVR*& Right)
{
	Left = LeftGrabbedObject;

	Right = RightGrabbedObject;
}

// Returns the left hand's grabbed object.
UGrabbableVR* UGrabbableVR::GetLeftGrabbedObject()
{
	return LeftGrabbedObject;
}

// Returns the right hand's grabbed object.
UGrabbableVR* UGrabbableVR::GetRightGrabbedObject()
{
	return RightGrabbedObject;
}

// Gets the index of the given grab point by name.
// Returns -1 if the grab point does not exist.
int UGrabbableVR::GetGrabPoint(FName Name, FGrabPointVR& GrabPoint)
{
	int Index = 0;

	for (FGrabPointVR Current : GrabPoints)
	{
		if (Current.GrabPointName == Name)
		{
			GrabPoint = Current;

			return Index;
		}

		Index++;
	}

	GrabPoint = FGrabPointVR();

	return -1;
}

// Returns the elapsed grab time for this object.
float UGrabbableVR::GetElapsedGrabTime()
{
	if (!IsGrabbed())
	{
		return 0;
	}

	return IsGrabbedRight() ? RightGrabTime : LeftGrabTime;
}

// Constructs a new GrabbableVR component.
UGrabbableVR* UGrabbableVR::ConstructGrabbableVR(AActor* Parent, TArray<FGrabPointVR> _GrabPoints, bool Active, bool HandTracking, UInputAction* LeftGrabButton, UInputAction* RightGrabButton, EGrabModeVR _GrabMode, float _GrabBuffer, UPrimitiveComponent* _Collider, bool GrabPhysics, EGravitySettingVR _GravitySetting, bool Locked, bool Throwable, float _ThrowScale, float _MinimumThrowDistance, EThrowCalculationVR _ThrowCalculation, FRotator _ThrowRotationOffset, float _CollisionDelay)
{
	UGrabbableVR* NewGrabbableVR = Cast<UGrabbableVR>(Parent->AddComponentByClass(UGrabbableVR::StaticClass(), true, FTransform(), true));

	NewGrabbableVR->RegisterComponent();

	Parent->AddInstanceComponent(NewGrabbableVR);

	NewGrabbableVR->PrimaryComponentTick.bCanEverTick = true;

	NewGrabbableVR->PrimaryComponentTick.bHighPriority = true;

	NewGrabbableVR->GrabPoints = _GrabPoints;

	NewGrabbableVR->bActive = Active;

	NewGrabbableVR->bHandTracking = HandTracking;

	NewGrabbableVR->IA_Grab_Button_Left = LeftGrabButton;

	NewGrabbableVR->IA_Grab_Button_Right = RightGrabButton;

	NewGrabbableVR->GrabMode = _GrabMode;

	NewGrabbableVR->GrabBuffer = _GrabBuffer;

	NewGrabbableVR->PrimaryCollider = _Collider;

	NewGrabbableVR->bGrabPhysics = GrabPhysics;

	NewGrabbableVR->GravitySetting = _GravitySetting;

	NewGrabbableVR->bLocked = Locked;

	NewGrabbableVR->bThrowable = Throwable;

	NewGrabbableVR->ThrowScale = _ThrowScale;

	NewGrabbableVR->MinimumThrowDistance = _MinimumThrowDistance;

	NewGrabbableVR->ThrowCalculation = _ThrowCalculation;

	NewGrabbableVR->ThrowRotationOffset = _ThrowRotationOffset;

	NewGrabbableVR->CollisionDelay = _CollisionDelay;

	NewGrabbableVR->OnGrab = FGrabDelegateVR();

	NewGrabbableVR->OnDrop = FGrabDelegateVR();

	NewGrabbableVR->OnThrow = FGrabDelegateVR();

	NewGrabbableVR->LeftGrabTime = 0;

	NewGrabbableVR->RightGrabTime = 0;

	NewGrabbableVR->bPreviousGravitySetting = false;

	NewGrabbableVR->GrabbedRotation = FRotator(0, 0, 0);

	NewGrabbableVR->PreviousPawnCollision = ECollisionResponse::ECR_Block;

	NewGrabbableVR->GrabbedHand = nullptr;

	NewGrabbableVR->HandRotation = FRotator(0, 0, 0);

	NewGrabbableVR->bIsGrabbedRight = false;

	NewGrabbableVR->GrabbedPoint = FGrabPointVR();

	NewGrabbableVR->bLeftDown = false;

	NewGrabbableVR->bRightDown = false;

	NewGrabbableVR->LeftPress = nullptr;

	NewGrabbableVR->RightPress = nullptr;

	NewGrabbableVR->LeftRelease = nullptr;

	NewGrabbableVR->RightRelease = nullptr;

	return NewGrabbableVR;
}


// STATIC VARIABLE INITIALIZATION

// The current held object in the left hand.
UGrabbableVR* UGrabbableVR::LeftGrabbedObject = nullptr;

// The current held object in the right hand.
UGrabbableVR* UGrabbableVR::RightGrabbedObject = nullptr;

// The object used for checking left hand collisions.
UPrimitiveComponent* UGrabbableVR::LeftHandCollider = nullptr;

// The object used for checking right hand collisions.
UPrimitiveComponent* UGrabbableVR::RightHandCollider = nullptr;
