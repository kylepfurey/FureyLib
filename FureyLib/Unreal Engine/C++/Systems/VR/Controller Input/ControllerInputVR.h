
// Static VR Controller Input Component Script
// by Kyle Furey

// REQUIREMENT: ControllerInputVR.cpp

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MotionControllerComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Math/Vector.h"
#include "Math/Rotator.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ControllerInputVR.generated.h"

// Include this heading to use the class
// #include "VR/Controller Input/ControllerInput.h"

// The default priority for input.
#define DEFAULT_INPUT_PRIORITY 0

/** Each button input from standard VR controllers. */
UENUM(BlueprintType, Category = "ControllerInputVR")
enum class EControllerInputVR : uint8
{
	X_BUTTON				UMETA(DisplayName = "X Button"),
	Y_BUTTON				UMETA(DisplayName = "Y Button"),
	B_BUTTON				UMETA(DisplayName = "B Button"),
	A_BUTTON				UMETA(DisplayName = "A Button"),
	TRIGGER_LEFT			UMETA(DisplayName = "Left Trigger"),
	TRIGGER_RIGHT			UMETA(DisplayName = "Right Trigger"),
	SHOULDER_LEFT			UMETA(DisplayName = "Left Shoulder"),
	SHOULDER_RIGHT			UMETA(DisplayName = "Right Shoulder"),
	JOYSTICK_LEFT			UMETA(DisplayName = "Left Joystick"),
	JOYSTICK_RIGHT			UMETA(DisplayName = "Left Joystick"),
	JOYSTICK_BUTTON_LEFT	UMETA(DisplayName = "Left Joystick Button"),
	JOYSTICK_BUTTON_RIGHT	UMETA(DisplayName = "Right Joystick Button"),
	SPECIAL_BUTTON_LEFT		UMETA(DisplayName = "Left Special Button"),
	SPECIAL_BUTTON_RIGHT	UMETA(DisplayName = "Right Special Button"),
	MAX						UMETA(Hidden)
};

/**
* Singleton controller input component class.
* Provides static functions for easy access to VR controller input.
*/
UCLASS(Blueprintable, BlueprintType, ClassGroup = (ControllerInputVR), meta = (BlueprintSpawnableComponent))
class MYGAME_API UControllerInputVR : public UActorComponent
{
	GENERATED_BODY()

protected:

	// CONTROLLER OBJECTS

	/** The headset camera object. */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, BlueprintGetter = "GetHeadset", meta = (ExposeOnSpawn), Category = "ControllerInputVR")
	UCameraComponent* Headset = nullptr;

	/** The left controller object. */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, BlueprintGetter = "GetLeftController", meta = (ExposeOnSpawn), Category = "ControllerInputVR")
	UMotionControllerComponent* LeftController = nullptr;

	/** The right controller object. */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, BlueprintGetter = "GetRightController", meta = (ExposeOnSpawn), Category = "ControllerInputVR")
	UMotionControllerComponent* RightController = nullptr;


	// CONTROLLER INPUT STATE

	/** Whether input was successfully configured. */
	UPROPERTY(BlueprintReadOnly, BlueprintGetter = "IsControllerInputEnabled", Category = "ControllerInputVR")
	bool bInputEnabled = false;

	/** The mapping context of global VR input. */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, BlueprintGetter = "GetMappingContext", meta = (ExposeOnSpawn), Category = "ControllerInputVR")
	UInputMappingContext* MappingContext = nullptr;

	/** Whether the left controller is currently being tracked (used for blueprint support). */
	UPROPERTY(BlueprintReadOnly, BlueprintGetter = "IsTrackingLeftController", Category = "ControllerInputVR")
	bool bTrackingLeft = false;

	/** Whether the right controller is currently being tracked (used for blueprint support).. */
	UPROPERTY(BlueprintReadOnly, BlueprintGetter = "IsTrackingRightController", Category = "ControllerInputVR")
	bool bTrackingRight = false;


	// STATIC INSTANCE

	/** The global instance of the world's controller input used to call controller input functions anywhere. */
	static UControllerInputVR* Instance;


	// UNREAL FUNCTIONS

	/** Initializes controller input. */
	virtual void BeginPlay() override;

	/** Disables controller input. */
	virtual void BeginDestroy() override;

public:

	// CONSTRUCTORS

	/** Default constructor. */
	UControllerInputVR();

	/** Object initializer constructor. */
	UControllerInputVR(const FObjectInitializer& ObjectInitializer);

	/** Controller input constructor. */
	UControllerInputVR(UInputMappingContext* _MappingContext, UCameraComponent* _Headset, UMotionControllerComponent* _LeftControllerComponent, UMotionControllerComponent* _RightControllerComponent, bool bAutoEnable = true);


	// UNREAL FUNCTIONS

	/** Called every frame. */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	// GLOBAL INPUT FUNCTIONS

	/** Returns whether the given mapping context is being broadcast for the given player. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ControllerInputVR")
	static bool IsInputEnabled(int32 PlayerIndex, UInputMappingContext* _MappingContext);

	/** Begins broadcasting the given mapping context to the given player and returns if it was successful. */
	UFUNCTION(BlueprintCallable, Category = "ControllerInputVR")
	static bool EnableInput(int32 PlayerIndex, UInputMappingContext* _MappingContext, int32 Priority = 0);

	/** Stops broadcasting the given mapping context to the given player and returns if it was successful. */
	UFUNCTION(BlueprintCallable, Category = "ControllerInputVR")
	static bool DisableInput(int32 PlayerIndex, UInputMappingContext* _MappingContext);


	// CONTROLLER INPUT FUNCTIONS

	/** Returns whether global input has been enabled. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ControllerInputVR")
	static bool IsControllerInputEnabled();

	/** Sets the global inputs status and returns if it was successful. */
	UFUNCTION(BlueprintCallable, Category = "ControllerInputVR")
	static bool SetControllerInput(bool bEnabled);

	/** Enables global input and returns if it was successful. */
	UFUNCTION(BlueprintCallable, Category = "ControllerInputVR")
	static bool EnableControllerInput();

	/** Disables global input and returns if it was successful. */
	UFUNCTION(BlueprintCallable, Category = "ControllerInputVR")
	static bool DisableControllerInput();

	/**
	* Receives input from the given player.
	* EnableControllerInput() must have been called somewhere for the given player index for this actor to receive input.
	*/
	UFUNCTION(BlueprintCallable, Category = "ControllerInputVR")
	static bool ReceiveControllerInput(AActor* Actor, int32 PlayerIndex);

	/**
	* Stops receiving input from the given player.
	* EnableControllerInput() must have been called somewhere for the given player index for this actor to receive input.
	*/
	UFUNCTION(BlueprintCallable, Category = "ControllerInputVR")
	static bool StopReceivingControllerInput(AActor* Actor, int32 PlayerIndex);

	/** Returns the global input mapping context. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ControllerInputVR")
	static UInputMappingContext* GetMappingContext();

	/** Returns the current instance of the controller input component. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ControllerInputVR")
	static UControllerInputVR* GetControllerInputVR();

	/** Constructs a new ControllerInputVR component. */
	UFUNCTION(BlueprintCallable, Category = "ControllerInputVR")
	static UControllerInputVR* ConstructControllerInputVR(AActor* Parent, UInputMappingContext* _MappingContext, UCameraComponent* _Headset, UMotionControllerComponent* _LeftControllerComponent, UMotionControllerComponent* _RightControllerComponent, bool bAutoEnable = true);


	// TRACKING FUNCTIONS

	/** Returns whether the given VR controller is currently found and being tracked. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ControllerInputVR")
	static bool IsTrackingController(bool bIsRight);

	/** Returns whether both VR controllers are currently found and being tracked. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ControllerInputVR")
	static void IsTrackingBothControllers(bool& Both, bool& Left, bool& Right);

	/** Returns whether the left VR controller is currently found and being tracked. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ControllerInputVR")
	static bool IsTrackingLeftController();

	/** Returns whether the right VR controller is currently found and being tracked. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ControllerInputVR")
	static bool IsTrackingRightController();


	// CONTROLLER FUNCTIONS

	/** Returns the given motion controller. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ControllerInputVR")
	static UMotionControllerComponent* GetController(bool bIsRight);

	/** Returns both motion controllers. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ControllerInputVR")
	static void GetBothControllers(UMotionControllerComponent*& Left, UMotionControllerComponent*& Right);

	/** Returns the left motion controller. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ControllerInputVR")
	static UMotionControllerComponent* GetLeftController();

	/** Returns the right motion controller. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ControllerInputVR")
	static UMotionControllerComponent* GetRightController();

	/** Gets the given motion controller component's transform data. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ControllerInputVR")
	static void GetControllerTransform(bool bIsRight, FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation);

	/** Gets the left motion controller component's transform data. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ControllerInputVR")
	static void GetLeftControllerTransform(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation);

	/** Gets the right motion controller component's transform data. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ControllerInputVR")
	static void GetRightControllerTransform(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation);

	/** Calculates the objects both controllers are currently aiming at. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ControllerInputVR")
	static void GetBothAimedAtObjects(bool& LeftHit, FHitResult& LeftResult, bool& RightHit, FHitResult& RightResult, float MaxDistance = 10000, bool HitComplex = true);

	/** Calculates the object the given controller is currently aiming at. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ControllerInputVR")
	static bool GetAimedAtObject(bool bIsRight, FHitResult& Result, float MaxDistance = 10000, bool HitComplex = true);

	/** Calculates the object the left controller is currently aiming at. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ControllerInputVR")
	static bool GetLeftAimedAtObject(FHitResult& Result, float MaxDistance = 10000, bool HitComplex = true);

	/** Calculates the object the right controller is currently aiming at. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ControllerInputVR")
	static bool GetRightAimedAtObject(FHitResult& Result, float MaxDistance = 10000, bool HitComplex = true);


	// HEADSET FUNCTIONS

	/** Returns the headset camera. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ControllerInputVR")
	static UCameraComponent* GetHeadset();

	/** Returns the headset camera's transform data. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ControllerInputVR")
	static void GetHeadsetTransform(FVector& WorldPosition, FRotator& WorldRotation, FVector& LocalPosition, FRotator& LocalRotation);

	/** Returns the player actor. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ControllerInputVR")
	static AActor* GetPlayer();

	/** Returns the player's transform data. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ControllerInputVR")
	static void GetPlayerTransform(FVector& WorldPosition, FRotator& WorldRotation, FVector& WorldScale);
};
