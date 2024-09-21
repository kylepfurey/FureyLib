
// VR Torso, Shoulders, and Elbows Component Script
// by Kyle Furey

// REQUIREMENT: ControllerInputVR.h, HandTrackerVR.h, BodyVR.cpp

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SceneComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Math/Vector.h"
#include "Math/Rotator.h"
#include "Math/Quat.h"
#include "Kismet/KismetMathLibrary.h"
#include "VR/Controller Input/ControllerInputVR.h"
#include "VR/Hand Tracking/HandTrackerVR.h"
#include "BodyVR.generated.h"

// Include this heading to use the class
// #include "VR/Body/BodyVR.h"

/** Provides transform data for the player's body in VR. */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (BodyVR), meta = (BlueprintSpawnableComponent))
class MYGAME_API UBodyVR : public UActorComponent
{
	GENERATED_BODY()

protected:

	// VARIABLES

	/** Whether to update the VR body. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "BodyVR")
	bool bActive = true;

	/** Whether to update the VR body relative to VR hand tracking (true) or VR controllers (false). */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "BodyVR")
	bool bHandTracking = true;

	/** The VR torso object. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "BodyVR")
	USceneComponent* Torso = nullptr;

	/** The offset of the torso relative to the headset. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "BodyVR")
	float TorsoOffset = -50;

	/** The speed to rotate the VR torso towards the headset's direction. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "BodyVR")
	float TorsoRotateSpeed = 10;

	/** The left VR shoulder object. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "BodyVR")
	USceneComponent* LeftShoulder = nullptr;

	/** The right VR shoulder object. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "BodyVR")
	USceneComponent* RightShoulder = nullptr;

	/** The offset of the shoulders relative to the torso. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "BodyVR")
	FVector ShoulderOffset = FVector(0, 15, 35);

	/** The left VR elbow object. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "BodyVR")
	USceneComponent* LeftElbow = nullptr;

	/** The right VR elbow object. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "BodyVR")
	USceneComponent* RightElbow = nullptr;

	/** The offset of the elbows' location relative to the hands / controllers. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "BodyVR")
	FVector ElbowOffset = FVector(0, 0, 0);

	/** The offset of the elbows' rotation to the hands / controllers. */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "BodyVR")
	FRotator ElbowRotation = FRotator(0, 0, 0);

	/** The global instance of the player's body. */
	static UBodyVR* Instance;


	// UNREAL FUNCTIONS

	/** Called when the game starts. */
	virtual void BeginPlay() override;

	/** Called when this object is destroyed. */
	virtual void BeginDestroy() override;

public:

	// CONSTRUCTORS

	/** Default constructor. */
	UBodyVR();

	/** Object initializer constructor. */
	UBodyVR(const FObjectInitializer& ObjectInitializer);

	/** Body constructor. */
	UBodyVR(bool Active, bool HandTracking = true, USceneComponent* _Torso = nullptr, float _TorsoOffset = -50, float _TorsoRotateSpeed = 10, USceneComponent* _LeftShoulder = nullptr, USceneComponent* _RightShoulder = nullptr, FVector _ShoulderOffset = FVector(0, 15, 35), USceneComponent* _LeftElbow = nullptr, USceneComponent* _RightElbow = nullptr, FVector _ElbowOffset = FVector(0, 0, 0), FRotator _ElbowRotation = FRotator(0, 0, 0));


	// UNREAL FUNCTIONS

	/** Called every frame. */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	// GETTERS

	/** Returns whether a VR body is present with the player. */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "VR Body Exist"), Category = "BodyVR")
	static bool BodyVRExists();

	/** Returns the current instance of the player's VR body. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "BodyVR")
	static UBodyVR* GetBodyVR();

	/** Returns whether the VR body is currently active. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "BodyVR")
	static bool IsBodyActive();

	/** Returns whether the VR body is tracking hands (true) or controllers (false). */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "BodyVR")
	static bool DoesBodyUseHandTracking();

	/** Returns the VR torso object. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "BodyVR")
	static USceneComponent* GetTorso();

	/** Returns the VR torso offset. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "BodyVR")
	static float GetTorsoOffset();

	/** Returns the speed the VR body's torso will automatically rotate to face the camera. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "BodyVR")
	static float GetTorsoRotateSpeed();

	/** Returns the given VR shoulder object. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "BodyVR")
	static USceneComponent* GetShoulder(bool bIsRight);

	/** Returns the VR shoulder objects. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "BodyVR")
	static void GetShoulders(USceneComponent*& Left, USceneComponent*& Right);

	/** Returns the left VR shoulder object. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "BodyVR")
	static USceneComponent* GetLeftShoulder();

	/** Returns the right VR shoulder object. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "BodyVR")
	static USceneComponent* GetRightShoulder();

	/** Returns the VR shoulder offset. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "BodyVR")
	static FVector GetShoulderOffset();

	/** Returns the given VR elbow object. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "BodyVR")
	static USceneComponent* GetElbow(bool bIsRight);

	/** Returns the VR elbow objects. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "BodyVR")
	static void GetElbows(USceneComponent*& Left, USceneComponent*& Right);

	/** Returns the left VR elbow object. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "BodyVR")
	static USceneComponent* GetLeftElbow();

	/** Returns the right VR elbow object. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "BodyVR")
	static USceneComponent* GetRightElbow();

	/** Returns the VR elbow offset. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "BodyVR")
	static FVector GetElbowOffset();

	/** Returns the VR elbow rotation. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "BodyVR")
	static FRotator GetElbowRotation();

	/** Returns the torso's Z rotation. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "BodyVR")
	static float GetTorsoRotation();


	// SETTERS

	/** Sets whether the VR body is currently active. */
	UFUNCTION(BlueprintCallable, Category = "BodyVR")
	static void SetBodyActive(bool Active);

	/** Sets whether the VR body is tracking hands (true) or controllers (false). */
	UFUNCTION(BlueprintCallable, Category = "BodyVR")
	static void SetBodyUsesHandTracking(bool HandTracking);

	/** Sets the VR torso object. */
	UFUNCTION(BlueprintCallable, Category = "BodyVR")
	static void SetTorso(USceneComponent* _Torso);

	/** Sets the VR torso offset. */
	UFUNCTION(BlueprintCallable, Category = "BodyVR")
	static void SetTorsoOffset(float Offset);

	/** Sets the speed the VR body's torso will automatically rotate to face the camera. */
	UFUNCTION(BlueprintCallable, Category = "BodyVR")
	static void SetTorsoRotateSpeed(float Speed);

	/** Sets the left VR shoulder object. */
	UFUNCTION(BlueprintCallable, Category = "BodyVR")
	static void SetLeftShoulder(USceneComponent* Shoulder);

	/** Sets the right VR shoulder object. */
	UFUNCTION(BlueprintCallable, Category = "BodyVR")
	static void SetRightShoulder(USceneComponent* Shoulder);

	/** Sets the VR shoulder offset. */
	UFUNCTION(BlueprintCallable, Category = "BodyVR")
	static void SetShoulderOffset(FVector Offset);

	/** Sets the left VR elbow object. */
	UFUNCTION(BlueprintCallable, Category = "BodyVR")
	static void SetLeftElbow(USceneComponent* Elbow);

	/** Sets the right VR elbow object. */
	UFUNCTION(BlueprintCallable, Category = "BodyVR")
	static void SetRightElbow(USceneComponent* Elbow);

	/** Sets the VR elbow offset. */
	UFUNCTION(BlueprintCallable, Category = "BodyVR")
	static void SetElbowOffset(FVector Offset);

	/** Sets the VR elbow rotation. */
	UFUNCTION(BlueprintCallable, Category = "BodyVR")
	static void SetElbowRotation(FRotator Rotation);

	/**
	* Rotates the torso to face the headset's direction.
	* Returns whether the rotation was successful.
	*/
	UFUNCTION(BlueprintCallable, Category = "BodyVR")
	static bool MakeTorsoFaceHeadset();

	/**
	* Sets the torso's rotation to the given degrees.
	* Returns whether the rotation was successful.
	*/
	UFUNCTION(BlueprintCallable, Category = "BodyVR")
	static bool SetTorsoRotation(float NewRotation);

	/**
	* Rotates the torso by the given degrees.
	* Returns whether the rotation was successful.
	*/
	UFUNCTION(BlueprintCallable, Category = "BodyVR")
	static bool AddTorsoRotation(float DeltaRotation);


	// BODY FUNCTIONS

	/**
	* Updates the body of the player.
	* Automatically called while the VR body is present and active.
	* Returns if the update was successful.
	*/
	UFUNCTION(BlueprintCallable, Category = "BodyVR")
	static bool UpdateBodyVR(float DeltaSeconds = 0.001);

	// Shows the player's VR body.
	UFUNCTION(BlueprintCallable, Category = "BodyVR")
	static void ShowBody(bool Show = true);

	// Hides the player's VR body.
	UFUNCTION(BlueprintCallable, Category = "BodyVR")
	static void HideBody(bool Hide = true);

	/** Constructs a new BodyVR component. */
	UFUNCTION(BlueprintCallable, Category = "BodyVR")
	static UBodyVR* ConstructBodyVR(AActor* Parent, bool Active = true, bool HandTracking = true, USceneComponent* _Torso = nullptr, float _TorsoOffset = -50, float _TorsoRotateSpeed = 10, USceneComponent* _LeftShoulder = nullptr, USceneComponent* _RightShoulder = nullptr, FVector _ShoulderOffset = FVector(0, 15, 35), USceneComponent* _LeftElbow = nullptr, USceneComponent* _RightElbow = nullptr, FVector _ElbowOffset = FVector(0, 0, 0), FRotator _ElbowRotation = FRotator(0, 0, 0));
};
