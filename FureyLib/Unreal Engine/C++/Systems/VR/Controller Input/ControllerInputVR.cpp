
// Static VR Controller Input Component Script
// by Kyle Furey

// REQUIREMENT: ControllerInputVR.h

// Include this heading to use the class
#include "VR/Controller Input/ControllerInputVR.h"


// CONSTRUCTORS

// Default constructor.
UControllerInputVR::UControllerInputVR()
{
	PrimaryComponentTick.bCanEverTick = true;

	PrimaryComponentTick.TickGroup = ETickingGroup::TG_PrePhysics;

	PrimaryComponentTick.bHighPriority = true;

	LeftController = nullptr;

	RightController = nullptr;

	Headset = nullptr;

	MappingContext = nullptr;

	bTrackingLeft = false;

	bTrackingRight = false;

	bInputEnabled = false;

	// Controller input construction should be done in blueprints through the ConstructControllerInputVR() function.
}

// Object initializer constructor.
UControllerInputVR::UControllerInputVR(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;

	PrimaryComponentTick.TickGroup = ETickingGroup::TG_PrePhysics;

	PrimaryComponentTick.bHighPriority = true;

	LeftController = nullptr;

	RightController = nullptr;

	Headset = nullptr;

	MappingContext = nullptr;

	bTrackingLeft = false;

	bTrackingRight = false;

	bInputEnabled = false;

	// Controller input construction should be done in blueprints through the ConstructControllerInputVR() function.
}

// Controller input constructor.
UControllerInputVR::UControllerInputVR(UInputMappingContext* _MappingContext, UCameraComponent* _Headset, UMotionControllerComponent* _LeftControllerComponent, UMotionControllerComponent* _RightControllerComponent, bool bAutoEnable)
{
	PrimaryComponentTick.bCanEverTick = true;

	PrimaryComponentTick.TickGroup = ETickingGroup::TG_PrePhysics;

	PrimaryComponentTick.bHighPriority = true;

	LeftController = _LeftControllerComponent;

	RightController = _RightControllerComponent;

	Headset = _Headset;

	MappingContext = _MappingContext;

	bTrackingLeft = false;

	bTrackingRight = false;

	bInputEnabled = !bAutoEnable;

	if (bAutoEnable)
	{
		ReceiveControllerInput(GetOwner(), DEFAULT_INPUT_PRIORITY);
	}

	// Controller input construction should be done in blueprints through the ConstructControllerInputVR() function.
}


// UNREAL FUNCTIONS

// Initializes controller input.
void UControllerInputVR::BeginPlay()
{
	// Calls the base class's function.
	Super::BeginPlay();

	// Check for existing controller inputs.
	if (Instance == nullptr)
	{
		// Store the current instance of the controller input.
		Instance = this;

		// Marks input as enabled if it is already enabled.
		if (IsInputEnabled(0, MappingContext))
		{
			bInputEnabled = true;
		}
	}
	else
	{
		// Remove this component as it is not needed.
		DestroyComponent();
	}
}

// Disables controller input.
void UControllerInputVR::BeginDestroy()
{
	// Calls the base class's function.
	Super::BeginDestroy();

	// Check for existing controller inputs.
	if (Instance == this)
	{
		// Remove the current instance of the controller input.
		Instance = nullptr;

		// Remove global player input.
		DisableInput(0, MappingContext);
	}
}

// Called every frame.
void UControllerInputVR::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// Calls the base class's function.
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Configures global player input.
	if (!bInputEnabled)
	{
		bInputEnabled = EnableInput(0, MappingContext, DEFAULT_INPUT_PRIORITY);
	}
}


// GLOBAL INPUT

// Returns whether the given mapping context is being broadcast for the given player.
bool UControllerInputVR::IsInputEnabled(int32 PlayerIndex, UInputMappingContext* _MappingContext)
{
	if (PlayerIndex < 0 || _MappingContext == nullptr)
	{
		return false;
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GWorld, PlayerIndex);

	if (PlayerController == nullptr)
	{
		return false;
	}

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	if (InputSubsystem == nullptr)
	{
		return false;
	}

	return InputSubsystem->HasMappingContext(_MappingContext);
}

// Begins broadcasting the given mapping context to the given player and returns if it was successful.
bool UControllerInputVR::EnableInput(int32 PlayerIndex, UInputMappingContext* _MappingContext, int32 Priority)
{
	if (PlayerIndex < 0 || _MappingContext == nullptr)
	{
		return false;
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GWorld, PlayerIndex);

	if (PlayerController == nullptr)
	{
		return false;
	}

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	if (InputSubsystem == nullptr)
	{
		return false;
	}

	bool Success = !InputSubsystem->HasMappingContext(_MappingContext);

	if (Success)
	{
		InputSubsystem->AddMappingContext(_MappingContext, Priority);
	}

	return true;
}

// Stops broadcasting the given mapping context to the given player and returns if it was successful.
bool UControllerInputVR::DisableInput(int32 PlayerIndex, UInputMappingContext* _MappingContext)
{
	if (PlayerIndex < 0 || _MappingContext == nullptr)
	{
		return false;
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GWorld, PlayerIndex);

	if (PlayerController == nullptr)
	{
		return false;
	}

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	if (InputSubsystem == nullptr)
	{
		return false;
	}

	bool Success = InputSubsystem->HasMappingContext(_MappingContext);

	if (Success)
	{
		InputSubsystem->RemoveMappingContext(_MappingContext);
	}

	return Success;
}


// CONTROLLER INPUT FUNCTIONS

// Returns whether global input has been enabled.
bool UControllerInputVR::IsControllerInputEnabled()
{
	if (Instance == nullptr)
	{
		return false;
	}

	return IsInputEnabled(0, Instance->MappingContext);
}

// Sets the global inputs status and returns if it was successful.
bool UControllerInputVR::SetControllerInput(bool bEnabled)
{
	if (Instance == nullptr)
	{
		return false;
	}

	Instance->bInputEnabled = !bEnabled;

	return bEnabled ? EnableInput(0, Instance->MappingContext, DEFAULT_INPUT_PRIORITY) : DisableInput(0, Instance->MappingContext);
}

// Enables global input and returns if it was successful.
bool UControllerInputVR::EnableControllerInput()
{
	if (Instance == nullptr)
	{
		return false;
	}

	Instance->bInputEnabled = false;

	return EnableInput(0, Instance->MappingContext, DEFAULT_INPUT_PRIORITY);
}

// Disables global input and returns if it was successful.
bool UControllerInputVR::DisableControllerInput()
{
	if (Instance == nullptr)
	{
		return false;
	}

	Instance->bInputEnabled = true;

	return DisableInput(0, Instance->MappingContext);
}

// Receives input from the given player.
// EnableControllerInput() must have been called somewhere for the given player index for this actor to receive input.
bool UControllerInputVR::ReceiveControllerInput(AActor* Actor, int32 PlayerIndex)
{
	if (Actor == nullptr)
	{
		return false;
	}

	Actor->EnableInput(UGameplayStatics::GetPlayerController(GWorld, PlayerIndex));

	return true;
}

// Stops receiving input from the given player.
// EnableControllerInput() must have been called somewhere for the given player index for this actor to receive input.
bool UControllerInputVR::StopReceivingControllerInput(AActor* Actor, int32 PlayerIndex)
{
	if (Actor == nullptr)
	{
		return false;
	}

	Actor->DisableInput(UGameplayStatics::GetPlayerController(GWorld, PlayerIndex));

	return true;
}

// Returns the global input mapping context.
UInputMappingContext* UControllerInputVR::GetMappingContext()
{
	if (Instance == nullptr)
	{
		return nullptr;
	}

	return Instance->MappingContext;
}

// Returns the current instance of the controller input component.
UControllerInputVR* UControllerInputVR::GetControllerInputVR()
{
	return Instance;
}

// Constructs a new ControllerInputVR component.
UControllerInputVR* UControllerInputVR::ConstructControllerInputVR(AActor* Parent, UInputMappingContext* _MappingContext, UCameraComponent* _Headset, UMotionControllerComponent* _LeftControllerComponent, UMotionControllerComponent* _RightControllerComponent, bool bAutoEnable)
{
	if (Instance != nullptr)
	{
		return nullptr;
	}

	UControllerInputVR* NewControllerInput = Cast<UControllerInputVR>(Parent->AddComponentByClass(UControllerInputVR::StaticClass(), true, FTransform(), true));

	NewControllerInput->RegisterComponent();

	Parent->AddInstanceComponent(NewControllerInput);

	NewControllerInput->PrimaryComponentTick.bCanEverTick = true;

	NewControllerInput->PrimaryComponentTick.TickGroup = ETickingGroup::TG_PrePhysics;

	NewControllerInput->PrimaryComponentTick.bHighPriority = true;

	NewControllerInput->LeftController = _LeftControllerComponent;

	NewControllerInput->RightController = _RightControllerComponent;

	NewControllerInput->Headset = _Headset;

	NewControllerInput->MappingContext = _MappingContext;

	NewControllerInput->bTrackingLeft = false;

	NewControllerInput->bTrackingRight = false;

	NewControllerInput->bInputEnabled = !bAutoEnable;

	if (bAutoEnable)
	{
		ReceiveControllerInput(NewControllerInput->GetOwner(), DEFAULT_INPUT_PRIORITY);
	}

	return NewControllerInput;
}


// TRACKING FUNCTIONS

// Returns whether the given VR controller is currently found and being tracked.
bool UControllerInputVR::IsTrackingController(bool bIsRight)
{
	return Instance != nullptr && (bIsRight ? Instance->RightController->IsTracked() : Instance->LeftController->IsTracked());
}

// Returns whether both VR controllers are currently found and being tracked.
void UControllerInputVR::IsTrackingBothControllers(bool& Both, bool& Left, bool& Right)
{
	Left = Instance != nullptr && Instance->LeftController->IsTracked();

	Right = Instance != nullptr && Instance->RightController->IsTracked();

	Both = Left && Right;
}

// Returns whether the left VR controller is currently found and being tracked.
bool UControllerInputVR::IsTrackingLeftController()
{
	return Instance != nullptr && Instance->LeftController->IsTracked();
}

// Returns whether the right VR controller is currently found and being tracked.
bool UControllerInputVR::IsTrackingRightController()
{
	return Instance != nullptr && Instance->RightController->IsTracked();
}


// CONTROLLER FUNCTIONS

// Returns the given motion controller.
UMotionControllerComponent* UControllerInputVR::GetController(bool bIsRight)
{
	if (Instance == nullptr)
	{
		return nullptr;
	}

	return bIsRight ? Instance->RightController : Instance->LeftController;
}

// Returns both motion controllers.
void UControllerInputVR::GetBothControllers(UMotionControllerComponent*& Left, UMotionControllerComponent*& Right)
{
	if (Instance == nullptr)
	{
		Left = nullptr;

		Right = nullptr;

		return;
	}

	Left = Instance->LeftController;

	Right = Instance->RightController;
}

// Returns the left motion controller.
UMotionControllerComponent* UControllerInputVR::GetLeftController()
{
	if (Instance == nullptr)
	{
		return nullptr;
	}

	return Instance->LeftController;
}

// Returns the right motion controller.
UMotionControllerComponent* UControllerInputVR::GetRightController()
{
	if (Instance == nullptr)
	{
		return nullptr;
	}

	return Instance->RightController;
}

// Gets the given motion controller component's transform data.
void UControllerInputVR::GetControllerTransform(bool bIsRight, FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation)
{
	if (bIsRight)
	{
		GetRightControllerTransform(WorldPosition, WorldRotation, LocalPosition, LocalRotation);
	}
	else
	{
		GetLeftControllerTransform(WorldPosition, WorldRotation, LocalPosition, LocalRotation);
	}
}

// Gets the left motion controller component's transform data.
void UControllerInputVR::GetLeftControllerTransform(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation)
{
	if (Instance == nullptr || Instance->LeftController == nullptr)
	{
		WorldPosition = FVector(0, 0, 0);

		WorldRotation = FRotator(0, 0, 0);

		LocalPosition = FVector(0, 0, 0);

		LocalRotation = FRotator(0, 0, 0);

		return;
	}

	WorldPosition = Instance->LeftController->GetComponentLocation();

	WorldRotation = Instance->LeftController->GetComponentRotation();

	LocalPosition = Instance->LeftController->GetRelativeLocation();

	LocalRotation = Instance->LeftController->GetRelativeRotation();
}

// Gets the right motion controller component's transform data.
void UControllerInputVR::GetRightControllerTransform(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation)
{
	if (Instance == nullptr || Instance->RightController == nullptr)
	{
		WorldPosition = FVector(0, 0, 0);

		WorldRotation = FRotator(0, 0, 0);

		LocalPosition = FVector(0, 0, 0);

		LocalRotation = FRotator(0, 0, 0);

		return;
	}

	WorldPosition = Instance->RightController->GetComponentLocation();

	WorldRotation = Instance->RightController->GetComponentRotation();

	LocalPosition = Instance->RightController->GetRelativeLocation();

	LocalRotation = Instance->RightController->GetRelativeRotation();
}


// HEADSET FUNCTIONS

// Returns the headset camera.
UCameraComponent* UControllerInputVR::GetHeadset()
{
	if (Instance == nullptr)
	{
		return nullptr;
	}

	return Instance->Headset;
}

// Returns the headset camera's transform data.
void UControllerInputVR::GetHeadsetTransform(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation)
{
	if (Instance == nullptr)
	{
		WorldPosition = FVector(0, 0, 0);

		WorldRotation = FRotator(0, 0, 0);

		LocalPosition = FVector(0, 0, 0);

		LocalRotation = FRotator(0, 0, 0);

		return;
	}

	WorldPosition = Instance->Headset->GetComponentLocation();

	WorldRotation = Instance->Headset->GetComponentRotation();

	LocalPosition = Instance->Headset->GetRelativeLocation();

	LocalRotation = Instance->Headset->GetRelativeRotation();
}

// Returns the player actor.
AActor* UControllerInputVR::GetPlayer()
{
	if (Instance == nullptr || Instance->Headset == nullptr)
	{
		return nullptr;
	}

	return Instance->Headset->GetAttachParentActor();
}

// Returns the player's transform data.
void UControllerInputVR::GetPlayerTransform(FVector& WorldPosition, FRotator& WorldRotation, FVector& WorldScale)
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


// STATIC VARIABLE INITIALIZATION

// The global instance of the world's controller input used to call controller input functions anywhere.
UControllerInputVR* UControllerInputVR::Instance = nullptr;
