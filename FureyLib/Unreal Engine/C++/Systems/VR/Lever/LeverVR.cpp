
// VR Movable Lever Actor Script
// by Kyle Furey

// REQUIREMENT: LeverVR.h

// Include this heading to use the class
#include "VR/Lever/LeverVR.h"


// CONSTRUCTORS

// Default constructor.
ALeverVR::ALeverVR()
{
	PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.TickGroup = ETickingGroup::TG_DuringPhysics;

	GrabComponent = nullptr;

	LeverPivot = nullptr;

	bActive = true;

	LeverMode = ELeverModeVR::BACKWARD_FORWARD;

	BackwardForwardClamp = FVector2D(-45, 45);

	LeftRightClamp = FVector2D(-45, 45);

	bResetLever = true;

	ResetSpeed = 5;

	LeverDownPercent = 0.9;

	OnLeverForward = FLeverDelegateVR();

	OnLeverBackward = FLeverDelegateVR();

	OnLeverLeft = FLeverDelegateVR();

	OnLeverRight = FLeverDelegateVR();

	GrabbedPosition = FVector();

	GrabbedRotation = FRotator();
}

// Object initializer constructor.
ALeverVR::ALeverVR(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.TickGroup = ETickingGroup::TG_DuringPhysics;

	GrabComponent = nullptr;

	LeverPivot = nullptr;

	bActive = true;

	LeverMode = ELeverModeVR::BACKWARD_FORWARD;

	BackwardForwardClamp = FVector2D(-45, 45);

	LeftRightClamp = FVector2D(-45, 45);

	bResetLever = true;

	ResetSpeed = 5;

	LeverDownPercent = 0.9;

	OnLeverForward = FLeverDelegateVR();

	OnLeverBackward = FLeverDelegateVR();

	OnLeverLeft = FLeverDelegateVR();

	OnLeverRight = FLeverDelegateVR();

	GrabbedPosition = FVector();

	GrabbedRotation = FRotator();
}

// LeverVR constructor.
ALeverVR::ALeverVR(bool Active, ELeverModeVR _LeverMode, FVector2D _BackwardForwardClamp, FVector2D _LeftRightClamp, bool ResetLever, float _ResetSpeed, float _LeverDownPercent)
{
	PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.TickGroup = ETickingGroup::TG_DuringPhysics;

	GrabComponent = nullptr;

	LeverPivot = nullptr;

	bActive = Active;

	LeverMode = _LeverMode;

	BackwardForwardClamp = _BackwardForwardClamp;

	LeftRightClamp = _LeftRightClamp;

	bResetLever = ResetLever;

	ResetSpeed = _ResetSpeed;

	LeverDownPercent = _LeverDownPercent;

	OnLeverForward = FLeverDelegateVR();

	OnLeverBackward = FLeverDelegateVR();

	OnLeverLeft = FLeverDelegateVR();

	OnLeverRight = FLeverDelegateVR();

	GrabbedPosition = FVector();

	GrabbedRotation = FRotator();
}


// UNREAL FUNCTIONS

// Called when the game starts or when spawned.
void ALeverVR::BeginPlay()
{
	// Calls the base class's function.
	Super::BeginPlay();
}

// Called every frame.
void ALeverVR::Tick(float DeltaTime)
{
	// Calls the base class's function.
	Super::Tick(DeltaTime);

	if (IsValid(GrabComponent))
	{
		GrabComponent->SetGrabActive(bActive);

		GrabComponent->SetUseGrabPhysics(false);

		GrabComponent->SetThrowable(false);

		if (GrabComponent->IsGrabbed())
		{
			FVector Position = GetActorLocation();

			FRotator Rotation = GetActorRotation();

			SetActorLocationAndRotation(GrabbedPosition, GrabbedRotation);
		}
		else
		{
			GrabbedPosition = GetActorLocation();

			GrabbedRotation = GetActorRotation();
		}
	}

	if (bActive)
	{
		UpdateLever(DeltaTime);
	}
}


// GETTERS

// Returns the lever's grab component.
UGrabbableVR* ALeverVR::GetGrabComponent()
{
	return GrabComponent;
}

// Returns the pivot of this lever that will always face the knob.
USceneComponent* ALeverVR::GetLeverPivot()
{
	return LeverPivot;
}

// Returns the directions this lever may be pushed or pulled.
ELeverModeVR ALeverVR::GetLeverMode()
{
	return LeverMode;
}

// Returns whether this lever is active.
bool ALeverVR::IsActive()
{
	return bActive;
}

// Returns the minimum backward and maximum forward rotation value on the Y axis.
FVector2D ALeverVR::GetBackwardForwardClamp()
{
	return BackwardForwardClamp;
}

// Returns the minimum left and maximum right rotation value on the X axis.
FVector2D ALeverVR::GetLeftRightClamp()
{
	return LeftRightClamp;
}

// Returns whether to reset the lever when it is not grabbed.
bool ALeverVR::IsResettingLever()
{
	return bResetLever;
}

// Returns the speed to reset the lever when it is not grabbed.
float ALeverVR::GetResetSpeed()
{
	return ResetSpeed;
}

// Returns the percentage the lever must be at to be considered down.
float ALeverVR::GetLeverDownPercent()
{
	return LeverDownPercent;
}

// Returns the events fired when the lever is backward.
FLeverDelegateVR& ALeverVR::GetOnLeverBackwardEvent()
{
	return OnLeverBackward;
}

// Returns the events fired when the lever is forward.
FLeverDelegateVR& ALeverVR::GetOnLeverForwardEvent()
{
	return OnLeverForward;
}

// Returns the events fired when the lever is left.
FLeverDelegateVR& ALeverVR::GetOnLeverLeftEvent()
{
	return OnLeverLeft;
}

// Returns the events fired when the lever is right.
FLeverDelegateVR& ALeverVR::GetOnLeverRightEvent()
{
	return OnLeverRight;
}


// SETTERS

// Sets the lever's grab component.
void ALeverVR::SetGrabComponent(UGrabbableVR* _GrabComponent)
{
	GrabComponent = _GrabComponent;
}

// Sets the pivot of this lever that will always face the knob.
void ALeverVR::SetLeverPivot(USceneComponent* _LeverPivot)
{
	LeverPivot = _LeverPivot;
}

// Sets whether this lever is active.
void ALeverVR::SetActive(bool Active)
{
	bActive = Active;
}

// Sets the directions this lever may be pushed or pulled.
void ALeverVR::SetLeverMode(ELeverModeVR _LeverMode)
{
	LeverMode = _LeverMode;
}

// Sets the minimum backward and maximum forward rotation value on the Y axis.
void ALeverVR::SetBackwardForwardClamp(FVector2D _BackwardForwardClamp)
{
	BackwardForwardClamp = _BackwardForwardClamp;
}

// Sets the minimum left and maximum right rotation value on the X axis.
void ALeverVR::SetLeftRightClamp(FVector2D _LeftRightClamp)
{
	LeftRightClamp = _LeftRightClamp;
}

// Sets whether to reset the lever when it is not grabbed.
void ALeverVR::SetResetLever(bool ResetLever)
{
	bResetLever = ResetLever;
}

// Sets the speed to reset the lever when it is not grabbed.
void ALeverVR::SetResetSpeed(float _ResetSpeed)
{
	ResetSpeed = _ResetSpeed;
}

// Sets the percentage the lever must be at to be considered down.
void ALeverVR::SetLeverDownPercent(float _LeverDownPercent)
{
	LeverDownPercent = _LeverDownPercent;
}

// Binds an event to be fired when the lever is backward.
void ALeverVR::BindOnLeverBackwardEvent(const FLeverDelegateVR& Event)
{
	OnLeverBackward = Event;
}

// Binds an event to be fired when the lever is forward.
void ALeverVR::BindOnLeverForwardEvent(const FLeverDelegateVR& Event)
{
	OnLeverForward = Event;
}

// Binds an event to be fired when the lever is left.
void ALeverVR::BindOnLeverLeftEvent(const FLeverDelegateVR& Event)
{
	OnLeverLeft = Event;
}

// Binds an event to be fired when the lever is right.
void ALeverVR::BindOnLeverRightEvent(const FLeverDelegateVR& Event)
{
	OnLeverRight = Event;
}


// LEVER FUNCTIONS

// Gets a float rotation in degrees from the angle of the given start point to the given end point.
float ALeverVR::GetDegreesRotation(FVector2D Start, FVector2D End)
{
	FVector2D Direction = (End - Start).GetSafeNormal();

	return FMath::RadiansToDegrees(FMath::Atan2(Direction.Y, Direction.X));
}

// Updates the state of this lever.
void ALeverVR::UpdateLever(float DeltaTime)
{
	if (IsValid(GrabComponent) && GrabComponent->IsGrabbed())
	{
		if (IsValid(LeverPivot))
		{
			FVector Start = LeverPivot->GetComponentLocation();

			FVector End = UGrabbableVR::GetHandCollider(GrabComponent->IsGrabbedRight())->GetComponentLocation();

			float Pitch = GetDegreesRotation(FVector2D(Start.X, Start.Z), FVector2D(End.X, End.Z)) - 90;

			Pitch -= GetActorRotation().Pitch;

			float Roll = -GetDegreesRotation(FVector2D(Start.Y, Start.Z), FVector2D(End.Y, End.Z)) + 90;

			Roll -= GetActorRotation().Roll;

			FVector2D Axes;

			FVector2D Direction;

			switch (LeverMode)
			{
			case ELeverModeVR::BACKWARD_FORWARD:

				Roll = 0;

				break;

			case ELeverModeVR::LEFT_RIGHT:

				Pitch = 0;

				break;

			case ELeverModeVR::BIDIRECTIONAL:

				LeverPivot->SetRelativeRotation(FRotator(Pitch, LeverPivot->GetRelativeRotation().Yaw, Roll));

				Axes = GetLeverAxes();

				if (FMath::Abs(Axes.X) > FMath::Abs(Axes.Y))
				{
					Pitch = 0;
				}
				else
				{
					Roll = 0;
				}

				break;

			case ELeverModeVR::JOYSTICK:

				LeverPivot->SetRelativeRotation(FRotator(Pitch, LeverPivot->GetRelativeRotation().Yaw, Roll));

				Direction = FVector2D(LeverPivot->GetRelativeRotation().Roll, LeverPivot->GetRelativeRotation().Pitch);

				Direction = Direction.GetSafeNormal() * FMath::Min(Direction.Length(), (FMath::Abs(BackwardForwardClamp.X) + FMath::Abs(BackwardForwardClamp.Y) + FMath::Abs(LeftRightClamp.X) + FMath::Abs(LeftRightClamp.Y)) / 4);

				Roll = Direction.X;

				Pitch = Direction.Y;

				break;
			}

			LeverPivot->SetRelativeRotation(FRotator(Pitch, LeverPivot->GetRelativeRotation().Yaw, Roll));

			LeverPivot->SetRelativeRotation(FRotator(FMath::Clamp(LeverPivot->GetRelativeRotation().Pitch, -FMath::Abs(BackwardForwardClamp.X), FMath::Abs(BackwardForwardClamp.Y)), LeverPivot->GetRelativeRotation().Yaw, FMath::Clamp(LeverPivot->GetRelativeRotation().Roll, -FMath::Abs(LeftRightClamp.X), FMath::Abs(LeftRightClamp.Y))));

			Axes = GetLeverAxes();

			if (Axes.X > FMath::Abs(LeverDownPercent))
			{
				OnLeverRight.ExecuteIfBound();
			}
			else
			{
				OnLeverLeft.ExecuteIfBound();
			}

			if (Axes.Y > FMath::Abs(LeverDownPercent))
			{
				OnLeverForward.ExecuteIfBound();
			}
			else
			{
				OnLeverBackward.ExecuteIfBound();
			}
		}
	}
	else if (bResetLever && IsValid(LeverPivot))
	{
		LeverPivot->SetRelativeRotation(FQuat::FastLerp(LeverPivot->GetRelativeRotation().Quaternion(), FQuat::Identity, DeltaTime * ResetSpeed));

		FVector2D Axes = GetLeverAxes();

		if (Axes.X > FMath::Abs(LeverDownPercent))
		{
			OnLeverRight.ExecuteIfBound();
		}
		else
		{
			OnLeverLeft.ExecuteIfBound();
		}

		if (Axes.Y > FMath::Abs(LeverDownPercent))
		{
			OnLeverForward.ExecuteIfBound();
		}
		else
		{
			OnLeverBackward.ExecuteIfBound();
		}
	}
}

// Returns the current percentage of the lever in the given direction.
float ALeverVR::GetLeverPercentage(ELeverAxisVR Axis)
{
	if (!IsValid(LeverPivot))
	{
		return 0;
	}

	FRotator Rotation = LeverPivot->GetRelativeRotation();

	float Percentage;

	switch (Axis)
	{
	default:

		Percentage = 0;

		break;

	case ELeverAxisVR::BACKWARD:

		if (LeverMode == ELeverModeVR::LEFT_RIGHT)
		{
			return 0;
		}

		Percentage = -(1 - PERCENTAGE(Rotation.Pitch, -FMath::Abs(BackwardForwardClamp.X), 0));

		break;

	case ELeverAxisVR::FORWARD:

		if (LeverMode == ELeverModeVR::LEFT_RIGHT)
		{
			return 0;
		}

		Percentage = -PERCENTAGE(Rotation.Pitch, 0, FMath::Abs(BackwardForwardClamp.Y));

		break;

	case ELeverAxisVR::LEFT:

		if (LeverMode == ELeverModeVR::BACKWARD_FORWARD)
		{
			return 0;
		}

		Percentage = 1 - PERCENTAGE(Rotation.Roll, -FMath::Abs(LeftRightClamp.X), 0);

		break;

	case ELeverAxisVR::RIGHT:

		if (LeverMode == ELeverModeVR::BACKWARD_FORWARD)
		{
			return 0;
		}

		Percentage = PERCENTAGE(Rotation.Roll, 0, FMath::Abs(LeftRightClamp.Y));

		break;
	}

	return Percentage;
}

// Returns whether the lever is currently down for the given axis.
bool ALeverVR::IsLeverDown(ELeverAxisVR Axis)
{
	return GetLeverPercentage(Axis) >= FMath::Abs(LeverDownPercent);
}

// Returns the percentages of each axis of the lever.
// Note: Negative axes implies the axis is in the negative direction.
FVector2D ALeverVR::GetLeverAxes()
{
	if (!IsValid(LeverPivot))
	{
		return FVector2D(0, 0);
	}

	FVector Rotation = LeverPivot->GetRelativeRotation().Euler();

	return FVector2D(Rotation.Y > 0 ? GetLeverPercentage(ELeverAxisVR::RIGHT) : -GetLeverPercentage(ELeverAxisVR::LEFT), Rotation.X > 0 ? GetLeverPercentage(ELeverAxisVR::FORWARD) : -GetLeverPercentage(ELeverAxisVR::BACKWARD));
}

// Returns the current normalized 2D direction of the lever.
FVector2D ALeverVR::GetLeverDirection()
{
	return GetLeverAxes().GetSafeNormal();
}

// Spawns a new ALeverVR into the world.
ALeverVR* ALeverVR::SpawnLeverVR(UClass* LeverClass, FTransform SpawnTransform, bool Active, ELeverModeVR _LeverMode, FVector2D _BackwardForwardClamp, FVector2D _LeftRightClamp, bool ResetLever, float _ResetSpeed, float _LeverDownPercent)
{
	if (!IsValid(GWorld))
	{
		return nullptr;
	}

	ALeverVR* LeverVR = GWorld->SpawnActor<ALeverVR>(LeverClass->StaticClass(), SpawnTransform);

	LeverVR->PrimaryActorTick.bCanEverTick = true;

	LeverVR->PrimaryActorTick.TickGroup = ETickingGroup::TG_DuringPhysics;

	LeverVR->GrabComponent = nullptr;

	LeverVR->LeverPivot = nullptr;

	LeverVR->bActive = Active;

	LeverVR->LeverMode = _LeverMode;

	LeverVR->BackwardForwardClamp = _BackwardForwardClamp;

	LeverVR->LeftRightClamp = _LeftRightClamp;

	LeverVR->bResetLever = ResetLever;

	LeverVR->ResetSpeed = _ResetSpeed;

	LeverVR->LeverDownPercent = _LeverDownPercent;

	LeverVR->OnLeverForward = FLeverDelegateVR();

	LeverVR->OnLeverBackward = FLeverDelegateVR();

	LeverVR->OnLeverLeft = FLeverDelegateVR();

	LeverVR->OnLeverRight = FLeverDelegateVR();

	LeverVR->GrabbedPosition = FVector();

	LeverVR->GrabbedRotation = FRotator();

	return LeverVR;
}
