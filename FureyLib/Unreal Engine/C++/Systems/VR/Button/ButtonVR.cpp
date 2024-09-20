
// VR Clickable Button Component Script
// by Kyle Furey

// REQUIREMENT: ButtonVR.h

// Include this heading to use the class
#include "VR/Button/ButtonVR.h"


// CONSTRUCTORS

// Default constructor.
UButtonVR::UButtonVR()
{
	PrimaryComponentTick.bCanEverTick = true;

	PrimaryComponentTick.TickGroup = ETickingGroup::TG_DuringPhysics;

	ButtonModel = nullptr;

	ButtonCollider = nullptr;

	bActive = true;

	bSticky = true;

	bClicked = false;

	UnclickedHeight = 7.5;

	ClickedHeight = 2.5;

	ButtonSpeed = 10;

	ClickedSound = nullptr;

	UnclickedSound = nullptr;

	OnClick = FButtonDelegateVR();

	OnUnclick = FButtonDelegateVR();

	WhileClicked = FButtonDelegateVR();

	bHeld = false;
}

// Object initializer constructor.
UButtonVR::UButtonVR(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;

	PrimaryComponentTick.TickGroup = ETickingGroup::TG_DuringPhysics;

	ButtonModel = nullptr;

	ButtonCollider = nullptr;

	bActive = true;

	bSticky = true;

	bClicked = false;

	UnclickedHeight = 7.5;

	ClickedHeight = 2.5;

	ButtonSpeed = 10;

	ClickedSound = nullptr;

	UnclickedSound = nullptr;

	OnClick = FButtonDelegateVR();

	OnUnclick = FButtonDelegateVR();

	WhileClicked = FButtonDelegateVR();

	bHeld = false;
}

// ButtonVR constructor.
UButtonVR::UButtonVR(UStaticMeshComponent* _ButtonModel, UPrimitiveComponent* _ButtonCollider, bool Active, bool Sticky, bool Clicked, float _UnclickedHeight, float _ClickedHeight, float _ButtonSpeed, USoundBase* _ClickedSound, USoundBase* _UnclickedSound)
{
	PrimaryComponentTick.bCanEverTick = true;

	PrimaryComponentTick.TickGroup = ETickingGroup::TG_DuringPhysics;

	ButtonModel = _ButtonModel;

	ButtonCollider = _ButtonCollider;

	bActive = Active;

	bSticky = Sticky;

	bClicked = Clicked;

	UnclickedHeight = _UnclickedHeight;

	ClickedHeight = _ClickedHeight;

	ButtonSpeed = _ButtonSpeed;

	ClickedSound = _ClickedSound;

	UnclickedSound = _UnclickedSound;

	OnClick = FButtonDelegateVR();

	OnUnclick = FButtonDelegateVR();

	WhileClicked = FButtonDelegateVR();

	bHeld = false;
}


// UNREAL FUNCTIONS

// Called when the game starts or when spawned.
void UButtonVR::BeginPlay()
{
	// Calls the base class's function.
	Super::BeginPlay();
}

// Called every frame.
void UButtonVR::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// Calls the base class's function.
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bActive)
	{
		UpdateButton(DeltaTime);
	}
	else
	{
		if (!bSticky)
		{
			bClicked = false;
		}

		bHeld = false;
	}
}


// GETTERS

// Returns the model moved with the button.
UStaticMeshComponent* UButtonVR::GetButtonModel()
{
	return ButtonModel;
}

// Returns the collider used to check for player input.
UPrimitiveComponent* UButtonVR::GetButtonCollider()
{
	return ButtonCollider;
}

// Returns whether this button is currently active.
bool UButtonVR::IsButtonActive()
{
	return bActive;
}

// Returns whether this button stays clicked on unclick.
bool UButtonVR::IsSticky()
{
	return bSticky;
}

// Returns whether the button is currently clicked.
bool UButtonVR::IsClicked()
{
	return bClicked;
}

// Returns the relative height of the button when its not clicked down.
float UButtonVR::GetUnclickedHeight()
{
	return UnclickedHeight;
}

// Returns the relative height of the button when its clicked down.
float UButtonVR::GetClickedHeight()
{
	return ClickedHeight;
}

// Returns the speed the button moves to its next state.
float UButtonVR::GetButtonSpeed()
{
	return ButtonSpeed;
}

// Returns the sound to play when the button is clicked.
USoundBase* UButtonVR::GetClickedSound()
{
	return ClickedSound;
}

// Returns the sound to play when the button is unclicked.
USoundBase* UButtonVR::GetUnclickedSound()
{
	return UnclickedSound;
}

// Returns the event called when the button is clicked or first held down.
FButtonDelegateVR& UButtonVR::GetOnClickEvent()
{
	return OnClick;
}

// Returns the event called when the button is unclicked or released.
FButtonDelegateVR& UButtonVR::GetOnUnclickEvent()
{
	return OnUnclick;
}

// Returns the event called while the button is clicked or held down.
FButtonDelegateVR& UButtonVR::GetWhileClickedEvent()
{
	return WhileClicked;
}

// Returns whether the button is currently held down.
bool UButtonVR::IsHeld()
{
	return bHeld;
}


// SETTERS

// Sets the model moved with the button.
void UButtonVR::SetButtonModel(UStaticMeshComponent* _ButtonModel)
{
	ButtonModel = _ButtonModel;
}

// Sets the collider used to check for player input.
void UButtonVR::SetButtonCollider(UPrimitiveComponent* _ButtonCollider)
{
	ButtonCollider = _ButtonCollider;
}

// Sets whether this button is currently active.
void UButtonVR::SetButtonActive(bool Active)
{
	bActive = Active;
}

// Sets whether this button stays clicked on unclick.
void UButtonVR::SetSticky(bool Sticky)
{
	bSticky = Sticky;
}

// Sets whether the button is currently clicked.
void UButtonVR::SetClicked(bool Clicked)
{
	bClicked = Clicked;
}

// Sets the relative height of the button when it’s not clicked down.
void UButtonVR::SetUnclickedHeight(float _UnclickedHeight)
{
	UnclickedHeight = _UnclickedHeight;
}

// Sets the relative height of the button when it’s clicked down.
void UButtonVR::SetClickedHeight(float _ClickedHeight)
{
	ClickedHeight = _ClickedHeight;
}

// Sets the speed the button moves to its next state.
void UButtonVR::SetButtonSpeed(float _ButtonSpeed)
{
	ButtonSpeed = _ButtonSpeed;
}

// Sets the sound to play when the button is clicked.
void UButtonVR::SetClickedSound(USoundBase* _ClickedSound)
{
	ClickedSound = _ClickedSound;
}

// Sets the sound to play when the button is unclicked.
void UButtonVR::SetUnclickedSound(USoundBase* _UnclickedSound)
{
	UnclickedSound = _UnclickedSound;
}

// Sets the event called when the button is clicked or first held down.
void UButtonVR::BindOnClickEvent(const FButtonDelegateVR& Event)
{
	OnClick = Event;
}

// Sets the event called when the button is unclicked or released.
void UButtonVR::BindOnUnclickEvent(const FButtonDelegateVR& Event)
{
	OnUnclick = Event;
}

// Sets the event called while the button is clicked or held down.
void UButtonVR::BindWhileClickedEvent(const FButtonDelegateVR& Event)
{
	WhileClicked = Event;
}


// BUTTON FUNCTIONS

// Clicks or unclicks the button.
// Returns the buttons new clicked state.
bool UButtonVR::Click(bool InvokeEvent)
{
	if (bSticky)
	{
		bClicked = !bClicked;

		if (bClicked)
		{
			if (IsValid(ClickedSound))
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), ClickedSound, GetComponentLocation());
			}

			if (InvokeEvent)
			{
				OnClick.ExecuteIfBound();
			}
		}
		else
		{
			if (IsValid(UnclickedSound))
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), UnclickedSound, GetComponentLocation());
			}

			if (InvokeEvent)
			{
				OnUnclick.ExecuteIfBound();
			}
		}
	}
	else
	{
		bClicked = true;

		if (IsValid(ClickedSound))
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ClickedSound, GetComponentLocation());
		}

		if (InvokeEvent)
		{
			OnClick.ExecuteIfBound();
		}
	}

	return bClicked;
}

// Attempts to unclick the button.
// Returns if the unclick was successful.
bool UButtonVR::Unclick(bool InvokeEvent)
{
	if (!bClicked)
	{
		return false;
	}

	bClicked = false;

	if (IsValid(UnclickedSound))
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), UnclickedSound, GetComponentLocation());
	}

	if (InvokeEvent)
	{
		OnUnclick.ExecuteIfBound();
	}

	return true;
}

// Updates the button's current state.
// Automatically called while active.
void UButtonVR::UpdateButton(float DeltaTime)
{
	if (IsValid(ButtonCollider))
	{
		if (ButtonCollider->IsOverlappingComponent(UGrabbableVR::GetLeftHandCollider()) || ButtonCollider->IsOverlappingComponent(UGrabbableVR::GetRightHandCollider()))
		{
			if (bHeld)
			{
				WhileClicked.ExecuteIfBound();
			}
			else
			{
				Click();
			}

			bHeld = true;
		}
		else
		{
			if (bSticky)
			{
				if (bClicked)
				{
					WhileClicked.ExecuteIfBound();
				}
			}
			else
			{
				if (bHeld)
				{
					Unclick();
				}
			}

			bHeld = false;
		}
	}

	if (IsValid(ButtonModel))
	{
		FVector Relative = ButtonModel->GetRelativeLocation();

		ButtonModel->SetRelativeLocation(FVector(Relative.X, Relative.Y, FMath::Lerp(Relative.Z, bClicked ? ClickedHeight : UnclickedHeight, DeltaTime * ButtonSpeed)));
	}
}

// Constructs a new ButtonVR component.
UButtonVR* UButtonVR::ConstructButtonVR(USceneComponent* Parent, UStaticMeshComponent* _ButtonModel, UPrimitiveComponent* _ButtonCollider, bool Active, bool Sticky, bool Clicked, float _UnclickedHeight, float _ClickedHeight, float _ButtonSpeed, USoundBase* _ClickedSound, USoundBase* _UnclickedSound)
{
	if (!IsValid(Parent))
	{
		return nullptr;
	}

	UButtonVR* NewButtonVR = NewObject<UButtonVR>();

	NewButtonVR->RegisterComponent();

	Parent->GetOwner()->AddInstanceComponent(NewButtonVR);

	NewButtonVR->AttachToComponent(Parent, FAttachmentTransformRules::SnapToTargetIncludingScale);

	NewButtonVR->PrimaryComponentTick.bCanEverTick = true;

	NewButtonVR->PrimaryComponentTick.TickGroup = ETickingGroup::TG_DuringPhysics;

	NewButtonVR->ButtonModel = nullptr;

	NewButtonVR->ButtonCollider = nullptr;

	NewButtonVR->bActive = Active;

	NewButtonVR->bSticky = Sticky;

	NewButtonVR->bClicked = Clicked;

	NewButtonVR->UnclickedHeight = _UnclickedHeight;

	NewButtonVR->ClickedHeight = _ClickedHeight;

	NewButtonVR->ButtonSpeed = _ButtonSpeed;

	NewButtonVR->ClickedSound = _ClickedSound;

	NewButtonVR->UnclickedSound = _UnclickedSound;

	NewButtonVR->OnClick = FButtonDelegateVR();

	NewButtonVR->OnUnclick = FButtonDelegateVR();

	NewButtonVR->WhileClicked = FButtonDelegateVR();

	NewButtonVR->bHeld = false;

	return NewButtonVR;
}
