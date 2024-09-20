
// VR Torso, Shoulders, and Elbows Component Script
// by Kyle Furey

// REQUIREMENT: BodyVR.h

// Include this heading to use the class
#include "VR/Body/BodyVR.h"


// CONSTRUCTORS

// Default constructor.
UBodyVR::UBodyVR()
{
	PrimaryComponentTick.bCanEverTick = true;

	PrimaryComponentTick.TickGroup = ETickingGroup::TG_PrePhysics;

	bActive = true;

	bHandTracking = true;

	Torso = nullptr;

	TorsoOffset = -50;

	TorsoRotateSpeed = 10;

	LeftShoulder = nullptr;

	RightShoulder = nullptr;

	ShoulderOffset = FVector(0, 15, 35);

	LeftElbow = nullptr;

	RightElbow = nullptr;

	ElbowOffset = FVector(0, -5, 25);
}

// Object initializer constructor.
UBodyVR::UBodyVR(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;

	PrimaryComponentTick.TickGroup = ETickingGroup::TG_PrePhysics;

	bActive = true;

	bHandTracking = true;

	Torso = nullptr;

	TorsoOffset = -50;

	TorsoRotateSpeed = 10;

	LeftShoulder = nullptr;

	RightShoulder = nullptr;

	ShoulderOffset = FVector(0, 15, 35);

	LeftElbow = nullptr;

	RightElbow = nullptr;

	ElbowOffset = FVector(0, -5, 25);
}

// Body constructor
UBodyVR::UBodyVR(bool Active, bool HandTracking, USceneComponent* _Torso, float _TorsoOffset, float _TorsoRotateSpeed, USceneComponent* _LeftShoulder, USceneComponent* _RightShoulder, FVector _ShoulderOffset, USceneComponent* _LeftElbow, USceneComponent* _RightElbow, FVector _ElbowOffset)
{
	PrimaryComponentTick.bCanEverTick = true;

	PrimaryComponentTick.TickGroup = ETickingGroup::TG_PrePhysics;

	bActive = Active;

	bHandTracking = HandTracking;

	Torso = _Torso;

	TorsoOffset = _TorsoOffset;

	TorsoRotateSpeed = _TorsoRotateSpeed;

	LeftShoulder = _LeftShoulder;

	RightShoulder = _RightShoulder;

	ShoulderOffset = _ShoulderOffset;

	LeftElbow = _LeftElbow;

	RightElbow = _RightElbow;

	ElbowOffset = _ElbowOffset;
}


// UNREAL FUNCTIONS

// Called when the game starts.
void UBodyVR::BeginPlay()
{
	// Calls the base class's function.
	Super::BeginPlay();

	if (!IsValid(Instance))
	{
		Instance = this;

		UpdateBodyVR();
	}
	else
	{
		DestroyComponent();
	}
}

// Called when this object is destroyed.
void UBodyVR::BeginDestroy()
{
	// Calls the base class's function.
	Super::BeginDestroy();

	if (Instance == this)
	{
		Instance = nullptr;
	}
}

// Called every frame.
void UBodyVR::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// Calls the base class's function.
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bActive)
	{
		UpdateBodyVR(DeltaTime);
	}
}


// GETTERS

// Returns whether a VR body is present with the player.
bool UBodyVR::VRBodyExist()
{
	return IsValid(Instance);
}

// Returns the current instance of the player's VR body.
UBodyVR* UBodyVR::GetBodyVR()
{
	return Instance;
}

// Returns whether the VR body is currently active.
bool UBodyVR::IsBodyActive()
{
	if (!IsValid(Instance))
	{
		return false;
	}

	return Instance->bActive;
}

// Returns whether the VR body is tracking hands (true) or controllers (false).
bool UBodyVR::DoesBodyUseHandTracking()
{
	if (!IsValid(Instance))
	{
		return false;
	}

	return Instance->bHandTracking;
}

// Returns the VR torso object.
USceneComponent* UBodyVR::GetTorso()
{
	if (!IsValid(Instance))
	{
		return nullptr;
	}

	return Instance->Torso;
}

// Returns the VR torso offset.
float UBodyVR::GetTorsoOffset()
{
	if (!IsValid(Instance))
	{
		return 0;
	}

	return Instance->TorsoOffset;
}

// Returns the speed the VR body's torso will automatically rotate to face the camera.
float UBodyVR::GetTorsoRotateSpeed()
{
	if (!IsValid(Instance))
	{
		return 0;
	}

	return Instance->TorsoRotateSpeed;
}

// Returns the VR shoulder objects.
void UBodyVR::GetShoulders(USceneComponent*& Left, USceneComponent*& Right)
{
	if (!IsValid(Instance))
	{
		Left = nullptr;

		Right = nullptr;

		return;
	}

	Left = Instance->LeftShoulder;

	Right = Instance->RightShoulder;
}

// Returns the left VR shoulder object.
USceneComponent* UBodyVR::GetLeftShoulder()
{
	if (!IsValid(Instance))
	{
		return nullptr;
	}

	return Instance->LeftShoulder;
}

// Returns the right VR shoulder object.
USceneComponent* UBodyVR::GetRightShoulder()
{
	if (!IsValid(Instance))
	{
		return nullptr;
	}

	return Instance->RightShoulder;
}

// Returns the VR shoulder offset.
FVector UBodyVR::GetShoulderOffset()
{
	if (!IsValid(Instance))
	{
		return FVector();
	}

	return Instance->ShoulderOffset;
}

// Returns the VR elbow objects.
void UBodyVR::GetElbows(USceneComponent*& Left, USceneComponent*& Right)
{
	if (!IsValid(Instance))
	{
		Left = nullptr;

		Right = nullptr;

		return;
	}

	Left = Instance->LeftElbow;

	Right = Instance->RightElbow;
}

// Returns the left VR elbow object.
USceneComponent* UBodyVR::GetLeftElbow()
{
	if (!IsValid(Instance))
	{
		return nullptr;
	}

	return Instance->LeftElbow;
}

// Returns the right VR elbow object.
USceneComponent* UBodyVR::GetRightElbow()
{
	if (!IsValid(Instance))
	{
		return nullptr;
	}

	return Instance->RightElbow;
}

// Returns the VR elbow offset.
FVector UBodyVR::GetElbowOffset()
{
	if (!IsValid(Instance))
	{
		return FVector();
	}

	return Instance->ElbowOffset;
}

// Returns the torso's Z rotation.
float UBodyVR::GetTorsoRotation()
{
	if (!IsValid(Instance) || !IsValid(Instance->Torso))
	{
		return 0;
	}

	return Instance->Torso->GetComponentRotation().Euler().Z;
}


// SETTERS

// Sets whether the VR body is currently active.
void UBodyVR::SetBodyActive(bool Active)
{
	if (!IsValid(Instance))
	{
		return;
	}

	Instance->bActive = Active;
}

// Sets whether the VR body is tracking hands (true) or controllers (false).
void UBodyVR::SetBodyUsesHandTracking(bool HandTracking)
{
	if (!IsValid(Instance))
	{
		return;
	}

	Instance->bHandTracking = HandTracking;
}

// Sets the VR torso object.
void UBodyVR::SetTorso(USceneComponent* _Torso)
{
	if (!IsValid(Instance))
	{
		return;
	}

	Instance->Torso = _Torso;
}

// Sets the VR torso offset.
void UBodyVR::SetTorsoOffset(float Offset)
{
	if (!IsValid(Instance))
	{
		return;
	}

	Instance->TorsoOffset = Offset;
}

// Sets the speed the VR body's torso will automatically rotate to face the camera.
void UBodyVR::SetTorsoRotateSpeed(float Speed)
{
	if (!IsValid(Instance))
	{
		return;
	}

	Instance->TorsoRotateSpeed = Speed;
}

// Sets the left VR shoulder object.
void UBodyVR::SetLeftShoulder(USceneComponent* Shoulder)
{
	if (!IsValid(Instance))
	{
		return;
	}

	Instance->LeftShoulder = Shoulder;
}

// Sets the right VR shoulder object.
void UBodyVR::SetRightShoulder(USceneComponent* Shoulder)
{
	if (!IsValid(Instance))
	{
		return;
	}

	Instance->RightShoulder = Shoulder;
}

// Sets the VR shoulder offset.
void UBodyVR::SetShoulderOffset(FVector Offset)
{
	if (!IsValid(Instance))
	{
		return;
	}

	Instance->ShoulderOffset = Offset;
}

// Sets the left VR elbow object.
void UBodyVR::SetLeftElbow(USceneComponent* Elbow)
{
	if (!IsValid(Instance))
	{
		return;
	}

	Instance->LeftElbow = Elbow;
}

// Sets the right VR elbow object.
void UBodyVR::SetRightElbow(USceneComponent* Elbow)
{
	if (!IsValid(Instance))
	{
		return;
	}

	Instance->RightElbow = Elbow;
}

// Sets the VR elbow offset.
void UBodyVR::SetElbowOffset(FVector Offset)
{
	if (!IsValid(Instance))
	{
		return;
	}

	Instance->ElbowOffset = Offset;
}

// Rotates the torso to face the headset's direction.
// Returns whether the rotation was successful.
bool UBodyVR::MakeTorsoFaceHeadset()
{
	if (!IsValid(Instance) || !IsValid(Instance->Torso))
	{
		return false;
	}

	UCameraComponent* Headset = Instance->bHandTracking ? UHandTrackerVR::GetHeadset() : UControllerInputVR::GetHeadset();

	if (IsValid(Headset))
	{
		FVector Rotation = Instance->Torso->GetComponentRotation().Euler();

		Instance->Torso->SetWorldRotation(FRotator::MakeFromEuler(FVector(Rotation.X, Rotation.Y, Headset->GetComponentRotation().Euler().Z)));

		return true;
	}

	return false;
}

// Sets the torso's rotation to the given degrees.
// Returns whether the rotation was successful.
bool UBodyVR::SetTorsoRotation(float NewRotation)
{
	if (!IsValid(Instance) || !IsValid(Instance->Torso))
	{
		return false;
	}

	FVector Rotation = Instance->Torso->GetComponentRotation().Euler();

	Instance->Torso->SetWorldRotation(FRotator::MakeFromEuler(FVector(Rotation.X, Rotation.Y, NewRotation)));

	return true;
}

// Rotates the torso by the given degrees.
// Returns whether the rotation was successful.
bool UBodyVR::AddTorsoRotation(float DeltaRotation)
{
	if (!IsValid(Instance) || !IsValid(Instance->Torso))
	{
		return false;
	}

	FVector Rotation = Instance->Torso->GetComponentRotation().Euler();

	Instance->Torso->SetWorldRotation(FRotator::MakeFromEuler(FVector(Rotation.X, Rotation.Y, Rotation.Z + DeltaRotation)));

	return true;
}


// BODY FUNCTIONS

// Updates the body of the player.
// Automatically called while the VR body is present and active.
// Returns if the update was successful.
bool UBodyVR::UpdateBodyVR(float DeltaTime)
{
	if (!IsValid(Instance))
	{
		return false;
	}

	UCameraComponent* Headset = Instance->bHandTracking ? UHandTrackerVR::GetHeadset() : UControllerInputVR::GetHeadset();

	if (IsValid(Instance->Torso) && IsValid(Headset))
	{
		Instance->Torso->SetWorldLocation(Headset->GetComponentLocation() + (FVector(0, 0, Instance->TorsoOffset)));

		FVector Rotation = Instance->Torso->GetComponentRotation().Euler();

		Instance->Torso->SetWorldRotation(FMath::QInterpTo(Instance->Torso->GetComponentQuat(), FQuat::MakeFromEuler(FVector(Rotation.X, Rotation.Y, Headset->GetComponentRotation().Euler().Z)), DeltaTime, Instance->TorsoRotateSpeed));

		if (IsValid(Instance->LeftShoulder) && IsValid(Instance->RightShoulder))
		{
			FVector LeftOffset = FVector(Instance->ShoulderOffset.X, -Instance->ShoulderOffset.Y, Instance->ShoulderOffset.Z);

			FVector RightOffset = FVector(Instance->ShoulderOffset.X, Instance->ShoulderOffset.Y, Instance->ShoulderOffset.Z);

			Instance->LeftShoulder->SetWorldLocation(Instance->Torso->GetComponentLocation() + Instance->Torso->GetComponentQuat() * LeftOffset);

			Instance->RightShoulder->SetWorldLocation(Instance->Torso->GetComponentLocation() + Instance->Torso->GetComponentQuat() * RightOffset);

			if (IsValid(Instance->LeftElbow) && IsValid(Instance->RightElbow))
			{
				USceneComponent* LeftHand;

				USceneComponent* RightHand;

				if (Instance->bHandTracking)
				{
					LeftHand = UHandTrackerVR::GetLeftMotionController();

					RightHand = UHandTrackerVR::GetRightMotionController();
				}
				else
				{
					LeftHand = UControllerInputVR::GetLeftController();

					RightHand = UControllerInputVR::GetRightController();
				}

				if (IsValid(LeftHand) && IsValid(RightHand))
				{
					if (Instance->bHandTracking)
					{
						LeftOffset = FVector(Instance->ElbowOffset.X, -Instance->ElbowOffset.Y, Instance->ElbowOffset.Z);

						RightOffset = FVector(Instance->ElbowOffset.X, Instance->ElbowOffset.Y, Instance->ElbowOffset.Z);
					}
					else
					{
						LeftOffset = FVector(Instance->ElbowOffset.X - 35, -Instance->ElbowOffset.Y + 20, Instance->ElbowOffset.Z);

						RightOffset = FVector(Instance->ElbowOffset.X - 35, Instance->ElbowOffset.Y - 20, Instance->ElbowOffset.Z);
					}

					Instance->LeftElbow->SetWorldLocation(LeftHand->GetComponentLocation() + LeftHand->GetComponentQuat() * LeftOffset);

					Instance->RightElbow->SetWorldLocation(RightHand->GetComponentLocation() + RightHand->GetComponentQuat() * RightOffset);

					Instance->LeftElbow->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(Instance->LeftShoulder->GetComponentLocation(), Instance->LeftElbow->GetComponentLocation()));

					Instance->LeftShoulder->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(Instance->LeftShoulder->GetComponentLocation(), Instance->LeftElbow->GetComponentLocation()));

					Instance->RightShoulder->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(Instance->RightShoulder->GetComponentLocation(), Instance->RightElbow->GetComponentLocation()));

					if (Instance->bHandTracking)
					{
						LeftOffset = LeftHand->GetComponentQuat() * FVector(-5, 0, 0);

						RightOffset = RightHand->GetComponentQuat() * FVector(-5, 0, 0);
					}
					else
					{
						LeftOffset = LeftHand->GetComponentQuat() * FVector(0, -3, -5);

						RightOffset = RightHand->GetComponentQuat() * FVector(0, 3, -5);
					}

					Instance->LeftElbow->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(Instance->LeftElbow->GetComponentLocation(), LeftHand->GetComponentLocation() + LeftOffset));

					Instance->RightElbow->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(Instance->RightElbow->GetComponentLocation(), RightHand->GetComponentLocation() + RightOffset));
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}

// Shows the player's VR body.
void UBodyVR::ShowBody(bool Show)
{
	if (!IsValid(Instance))
	{
		return;
	}

	if (IsValid(Instance->Torso))
	{
		Instance->Torso->SetVisibility(Show, true);
	}

	if (IsValid(Instance->LeftShoulder))
	{
		Instance->LeftShoulder->SetVisibility(Show, true);
	}

	if (IsValid(Instance->RightShoulder))
	{
		Instance->RightShoulder->SetVisibility(Show, true);
	}

	if (IsValid(Instance->LeftElbow))
	{
		Instance->LeftElbow->SetVisibility(Show, true);
	}

	if (IsValid(Instance->RightElbow))
	{
		Instance->RightElbow->SetVisibility(Show, true);
	}
}

// Hides the player's VR body.
void UBodyVR::HideBody(bool Hide)
{
	if (!IsValid(Instance))
	{
		return;
	}

	if (IsValid(Instance->Torso))
	{
		Instance->Torso->SetVisibility(!Hide, true);
	}

	if (IsValid(Instance->LeftShoulder))
	{
		Instance->LeftShoulder->SetVisibility(!Hide, true);
	}

	if (IsValid(Instance->RightShoulder))
	{
		Instance->RightShoulder->SetVisibility(!Hide, true);
	}

	if (IsValid(Instance->LeftElbow))
	{
		Instance->LeftElbow->SetVisibility(!Hide, true);
	}

	if (IsValid(Instance->RightElbow))
	{
		Instance->RightElbow->SetVisibility(!Hide, true);
	}
}

// Constructs a new BodyVR component.
UBodyVR* UBodyVR::ConstructBodyVR(AActor* Parent, bool Active, bool HandTracking, USceneComponent* _Torso, float _TorsoOffset, float _TorsoRotateSpeed, USceneComponent* _LeftShoulder, USceneComponent* _RightShoulder, FVector _ShoulderOffset, USceneComponent* _LeftElbow, USceneComponent* _RightElbow, FVector _ElbowOffset)
{
	if (IsValid(Instance) || !IsValid(Parent))
	{
		return nullptr;
	}

	UBodyVR* NewBodyVR = Cast<UBodyVR>(Parent->AddComponentByClass(UBodyVR::StaticClass(), true, FTransform(), true));

	NewBodyVR->RegisterComponent();

	Parent->AddInstanceComponent(NewBodyVR);

	NewBodyVR->PrimaryComponentTick.bCanEverTick = true;

	NewBodyVR->PrimaryComponentTick.TickGroup = ETickingGroup::TG_PrePhysics;

	NewBodyVR->bActive = Active;

	NewBodyVR->bHandTracking = HandTracking;

	NewBodyVR->Torso = _Torso;

	NewBodyVR->TorsoOffset = _TorsoOffset;

	NewBodyVR->TorsoRotateSpeed = _TorsoRotateSpeed;

	NewBodyVR->LeftShoulder = _LeftShoulder;

	NewBodyVR->RightShoulder = _RightShoulder;

	NewBodyVR->ShoulderOffset = _ShoulderOffset;

	NewBodyVR->LeftElbow = _LeftElbow;

	NewBodyVR->RightElbow = _RightElbow;

	NewBodyVR->ElbowOffset = _ElbowOffset;

	return NewBodyVR;
}


// STATIC VARIABLE INITIALIZATION

// The global instance of the player's body.
UBodyVR* UBodyVR::Instance = nullptr;
