
// VR Gun Base Class Script
// by Kyle Furey

// REQUIREMENT: GrabbableVR.h, GunVR.cpp

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/LightComponent.h"
#include "Components/TextRenderComponent.h"
#include "Sound/SoundBase.h"
#include "Containers/Array.h"
#include "Math/Vector.h"
#include "Math/Vector2D.h"
#include "Math/Rotator.h"
#include "Math/Quat.h"
#include "Math/Transform.h"
#include "Math/UnrealMathUtility.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "VR/Grabbable/GrabbableVR.h"
#include "GunVR.generated.h"

// Include this heading to use the class
// #include "VR/Gun/GunVR.h"

// Returns a value relative to a percentage of a minimum and maximum.
#define VALUE(percentage, min, max) ((max - min) * percentage + min)

// Forward declaration of AGunVR.
class AGunVR;

// This class does not need to be modified. Do not inherit from this class.
UINTERFACE(Blueprintable, BlueprintType, MinimalAPI)
class UShootableVR : public UInterface
{
	GENERATED_BODY()
};

// Inherit from the following interface to implement it.

/** Indicates an object can be fired at by a GunVR actor. */
class MYGAME_API IShootableVR
{
	GENERATED_BODY()

public:

	// ISHOOTABLEVR FUNCTIONS

	/** Automatically called when this actor is hit with a GunVR projectile. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ShootableVR")
	void OnHit(AActor* Shooter, AGunVR* Gun, float Damage, FHitResult Hit);
	virtual void OnHit_Implementation(AActor* Shooter, AGunVR* Gun, float Damage, FHitResult Hit);
};

// Delegate declaration.
DECLARE_DYNAMIC_DELEGATE(FGunDelegateVR);

/** An actor that is able to be picked up and fired at other objects in VR. */
UCLASS(Blueprintable, BlueprintType, Abstract)
class MYGAME_API AGunVR : public AActor, public IHandInteractableVR
{
	GENERATED_BODY()

protected:

	// GUN VARIABLES

	/** This gun's grab component. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GunVR")
	UGrabbableVR* GrabComponent = nullptr;

	/** This gun's muzzle object used to fire the projectile in its forward direction. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GunVR")
	USceneComponent* Muzzle = nullptr;

	/** A pivot object used to represent the gun's pullable trigger. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GunVR")
	USceneComponent* TriggerPivot = nullptr;

	/** The rotation values used to pull the trigger (X is unpulled, Y is pulled). */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	FVector2D TriggerRotations = FVector2D(-45, 45);

	/** The class type this gun uses for loading in ammo. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	UClass* AmmoClass = nullptr;

	/** A pivot object used to place ammo that is currently stored in the gun. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GunVR")
	USceneComponent* AmmoPivot = nullptr;

	/** The collider used to insert ammo into the gun. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GunVR")
	UPrimitiveComponent* AmmoCollider = nullptr;

	/** The current magazine loaded into the gun. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	UGrabbableVR* CurrentMagazine = nullptr;

	/** The class this gun uses to spawn empty magazines. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	UClass* EmptyMagazineClass = nullptr;

	/** The left shoot button (used for controller input). */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	UInputAction* IA_Shoot_Button_Left = nullptr;

	/** The right shoot button (used for controller input). */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	UInputAction* IA_Shoot_Button_Right = nullptr;

	/** Whether this gun's safety is on (and therefore cannot currently be fired). */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	bool bSafety = false;

	/** The percentage the gun's trigger needs to be at in order to fire. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	float TriggerFirePercentage = 0.75;

	/** Whether to shoot projectile actors (true) or bullets via a raycast (false). */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	bool bFireProjectiles = false;

	/** The class this gun uses to spawn projectiles launched from the gun. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	UClass* ProjectileClass = nullptr;

	/** Whether bullets penetrate walls. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	bool bPenetrate = false;

	/** The maximum distance bullets can travel. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	float BulletMaxDistance = 10000;

	/** The damage this gun does per hit. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	float Damage = 100;

	/** Whether this gun can be fired continuously. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	bool bAutomatic = false;

	/** The delay for firing again when the trigger is pulled and then released. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	float TapFireRate = 0;

	/** The delay for firing again while the trigger is pulled. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	float FireRate = 0.3;

	/** The number of shots fired from this gun at one time. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	int32 ShotsFired = 1;

	/** Whether the first shot fired in a series is 100% accurate. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	bool bFirstShotAccuracy = true;

	/** The delay before allowing first shot accuracy again. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	float FirstShotDelay = 1;

	/** Whether the spread of bullets from firing this weapon is random. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	bool bRandomSpread = true;

	/** The minimum and maximum random spread. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	FVector2D Spread = FVector2D(2.5, 2.5);

	/** The pattern of bullet spread to follow if the spread is not random. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	TArray<FVector2D> FixedSpreadPattern = TArray<FVector2D>();

	/** Whether to fire a burst of shots when the gun is fired. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	bool bBurstFire = false;

	/** The number of shots fired when the gun is bursting. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	int32 BurstsFired = 3;

	/** The delay of each shot in a burst. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	float BurstRate = 0.1;

	/** Whether this gun has infinite ammo. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	bool bInfiniteAmmo = false;

	/** The remaining ammo in the magazine. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	int32 CurrentAmmo = 12;

	/** The maximum ammo in a magazine. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	int32 MaxAmmo = 12;

	/** Whether to auto eject the magazine from the weapon when ammo is expended. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	bool bAutoEjectMagazine = true;

	/** The sound to play when the gun is fired. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	USoundBase* FiringSound = nullptr;

	/** The sound to play when the gun is fired while being empty. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	USoundBase* EmptySound = nullptr;

	/** The sound to play when the magazine is ejected. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	USoundBase* EjectSound = nullptr;

	/** The sound to play when the gun is reloaded. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	USoundBase* ReloadSound = nullptr;

	/** The sound to play when the gun is fired while safety is on. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	USoundBase* SafetySound = nullptr;

	/** An event to trigger for each bullet or projectile of the gun that is fired. */
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn), Category = "GunVR")
	FGunDelegateVR OnFire = FGunDelegateVR();

	/** An event to trigger when the gun successfully shoots. */
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn), Category = "GunVR")
	FGunDelegateVR OnShoot = FGunDelegateVR();

	/** An event to trigger when the gun is reloaded. */
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn), Category = "GunVR")
	FGunDelegateVR OnReload = FGunDelegateVR();

	/** The time for firing effects to linger after being shot. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	float FireLingerTime = 0.05;

	/** The class this gun uses to spawn beams from the muzzle to the hit point32 when firing the weapon. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	UClass* BeamClass = nullptr;

	/** The class this gun uses to spawn flashes at the muzzle when firing the weapon. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	UClass* MuzzleFlashClass = nullptr;

	/** The transform applied to the muzzle flash when it is spawned. After this transform is applied, the X rotation is randomized. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	FTransform MuzzleFlashTransform = FTransform();

	/** The class this gun uses to spawn decals on a contacted wall. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	UClass* DecalClass = nullptr;

	/** The object used as this gun's laser sight. The X scale is used to trace the beam's length. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GunVR")
	USceneComponent* LaserSight = nullptr;

	/** The flashlight attached to this gun. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GunVR")
	ULightComponent* Flashlight = nullptr;

	/** The text render used to display the gun's current ammo. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GunVR")
	UTextRenderComponent* AmmoDisplayText = nullptr;

	/** The color associated with this instance of a gun. The gun may use this to update its materials' colors. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "GunVR")
	FLinearColor GunColor = FLinearColor::Red;

	/** The delay used before reenabling shooting. */
	float Delay = 0;

	/** Whether the current bullet or projectile is a first shot. */
	bool bFirstShot = false;

	/** The index of the current fixed spread pattern. */
	int32 CurrentSpreadIndex = 0;

	/** Whether the gun is currently in a burst of shots. */
	bool bBurstFiring = false;

	/** Whether to await a trigger release before firing (to prevent misfires). */
	bool bAwaitTriggerRelease = false;

	/** The starting relative location of the laser sight. */
	FVector LaserSightStart = FVector();

	/** The percentage of how much the left shoot button is currently down. */
	float LeftDown = 0;

	/** The percentage of how much the right shoot button is currently down. */
	float RightDown = 0;

	/** The event binding for the left shoot button being pressed. */
	FEnhancedInputActionEventBinding* LeftPress = nullptr;

	/** The event binding for the right shoot button being pressed. */
	FEnhancedInputActionEventBinding* RightPress = nullptr;

	/** The event binding for the left shoot button being released. */
	FEnhancedInputActionEventBinding* LeftRelease = nullptr;

	/** The event binding for the right shoot button being released. */
	FEnhancedInputActionEventBinding* RightRelease = nullptr;


	// UNREAL FUNCTIONS

	/** Called when the game starts or when spawned. */
	virtual void BeginPlay() override;

	/** Called when this actor is destroyed. */
	virtual void BeginDestroy() override;


	// GUN FUNCTIONS

	/**
	* Binds controller input to grab events.
	* Returns whether the bind was successful.
	*/
	virtual bool BindInput(bool bIsRight);

	/**
	* Unbinds controller input to grab events.
	* Returns whether the unbind was successful.
	*/
	virtual bool UnbindInput(bool bIsRight);

	/** Destroys the given actor after the given number of seconds. */
	void DestroyActorAfterSeconds(AActor* ActorToDestroy, float Seconds);

	/**
	* Attempts to fire a single bullet from this weapon.
	* Returns whether a hit was successful and the hit result.
	*/
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual bool Fire(FHitResult& Hit);

	/**
	* Attempts to launch a single projectile from this weapon.
	* Returns whether the launch was successful and the actor being used as a projectile.
	*/
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual bool Launch(AActor*& Projectile);

	/** Recursively fires over time until all bursts are expended. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void Burst(int32 RemainingBursts);

	/** Inserts a magazine into the reload chamber. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual bool InsertMagazine(UGrabbableVR* Magazine);

	/** Removes the magazine from the reload chamber. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual bool EjectMagazine();

	/**
	* Disables firing until the trigger is released.
	* This is useful for preventing misfires when the player grabs the gun.
	* Bind it to OnGrab().
	*/
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void AwaitTriggerRelease();

	/** Resets and returns the laser sight's location. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual FVector ResetLaserSight();

public:

	// CONSTRUCTORS

	/** Default constructor. */
	AGunVR();

	/** Object initializer constructor. */
	AGunVR(const FObjectInitializer& ObjectInitializer);

	/** GunVR constructor. */
	AGunVR(
		FVector2D _TriggerRotations, UClass* _AmmoClass = nullptr, UGrabbableVR* _CurrentMagazine = nullptr, UClass* _EmptyMagazineClass = nullptr, UInputAction* LeftShootButton = nullptr,
		UInputAction* RightShootButton = nullptr, bool Safety = false, float _TriggerFirePercentage = 0.75, bool FireProjectiles = false, UClass* _ProjectileClass = nullptr, bool Penetrate = false,
		float _BulletMaxDistance = 10000, float _Damage = 100, bool Automatic = false, float _TapFireRate = 0, float _FireRate = 0.3, int32 _ShotsFired = 1, bool FirstShotAccuracy = true,
		float _FirstShotDelay = 1, bool RandomSpread = true, FVector2D _Spread = FVector2D(2.5, 2.5), bool BurstFire = false, int32 _BurstsFired = 3, float _BurstRate = 0.1, bool InfiniteAmmo = false,
		int32 _CurrentAmmo = 12, int32 _MaxAmmo = 12, bool AutoEjectMagazine = true, USoundBase* _FiringSound = nullptr, USoundBase* _EmptySound = nullptr, USoundBase* _EjectSound = nullptr,
		USoundBase* _ReloadSound = nullptr, USoundBase* _SafetySound = nullptr, float _FireLingerTime = 0, UClass* _BeamClass = nullptr, UClass* _MuzzleFlashClass = nullptr,
		FTransform _MuzzleFlashTransform = FTransform(), UClass* _DecalClass = nullptr, FLinearColor _GunColor = FLinearColor::Red);


	// UNREAL FUNCTIONS

	/** Called every frame. */
	virtual void Tick(float DeltaTime) override;


	// CONTROLLERINPUTVR FUNCTIONS

	/** Called when the left shoot button is pressed down. */
	virtual void OnLeftShootButtonPressed(const FInputActionValue& Value);

	/** Called when the right shoot button is pressed down. */
	virtual void OnRightShootButtonPressed(const FInputActionValue& Value);

	/** Called when the left shoot button is released. */
	virtual void OnLeftShootButtonReleased(const FInputActionValue& Value);

	/** Called when the right shoot button is released. */
	virtual void OnRightShootButtonReleased(const FInputActionValue& Value);


	// GETTERS

	/** Returns the gun's grab component. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual UGrabbableVR* GetGrabComponent();

	/** Returns the gun's muzzle. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual USceneComponent* GetMuzzle();

	/** Returns the gun's trigger pivot. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual USceneComponent* GetTriggerPivot();

	/** Returns the gun's trigger rotations. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual FVector2D GetTriggerRotations();

	/** Returns the gun's ammo class. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual UClass* GetAmmoClass();

	/** Returns the gun's ammo pivot. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual USceneComponent* GetAmmoPivot();

	/** Returns the gun's ammo collider. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual UPrimitiveComponent* GetAmmoCollider();

	/** Returns the gun's current magazine. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual UGrabbableVR* GetCurrentMagazine();

	/** Returns the gun's empty magazine class. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual UClass* GetEmptyMagazineClass();

	/** Returns this gun's given shoot button. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual UInputAction* GetShootButton(bool bIsRight);

	/** Returns this gun's shoot buttons. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual void GetShootButtons(UInputAction*& Left, UInputAction*& Right);

	/** Returns this gun's left shoot button. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual UInputAction* GetLeftShootButton();

	/** Returns this gun's right shoot button. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual UInputAction* GetRightShootButton();

	/** Returns the gun's safety setting. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual bool IsSafetyOn();

	/** Returns the gun's trigger fire percentage. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual float GetTriggerFirePercentage();

	/** Returns whether this gun is firing projectiles instead of bullets. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual bool IsFiringProjectiles();

	/** Returns the projectile class used for this gun. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual UClass* GetProjectileClass();

	/** Returns whether the gun's bullets penetrate walls. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual bool IsPenetratingWalls();

	/** Returns the maximum distance bullets and projectiles will travel. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual float GetBulletMaxDistance();

	/** Returns the damage this gun does when its bullets and projectiles make contact. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual float GetDamage();

	/** Returns whether the gun is automatic. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual bool IsAutomatic();

	/** Returns the gun's tap fire rate. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual float GetTapFireRate();

	/** Returns the gun's fire rate. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual float GetFireRate();

	/** Returns the gun's number of shots fired. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual int32 GetShotsFired();

	/** Returns the gun's first shot accuracy setting. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual bool IsFirstShotAccurate();

	/** Returns the gun's first shot delay. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual float GetFirstShotDelay();

	/** Returns the gun's random spread setting. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual bool IsSpreadRandom();

	/** Returns the gun's random spread. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual FVector2D GetSpread();

	/** Returns the gun's fixed spread pattern. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual void GetFixedSpreadPattern(TArray<FVector2D>& _FixedSpreadPattern);

	/** Returns the gun's burst fire setting. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual bool IsBurstFire();

	/** Returns the number of bursts fired from the gun. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual int32 GetBurstsFired();

	/** Returns the gun's burst rate. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual float GetBurstRate();

	/** Returns the gun's infinite ammo setting. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual bool IsAmmoInfinite();

	/** Returns the gun's current ammo count. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual int32 GetCurrentAmmo();

	/** Returns if the ammo count is empty. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual bool IsEmpty();

	/** Returns the gun's maximum ammo count. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual int32 GetMaxAmmo();

	/** Returns the gun's magazine ejecting setting. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual bool IsAutoEjectingMagazine();

	/** Returns the gun's firing sound. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual USoundBase* GetFiringSound();

	/** Returns the gun's empty firing sound. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual USoundBase* GetEmptySound();

	/** Returns the gun's ejecting sound. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual USoundBase* GetEjectSound();

	/** Returns the gun's reloading sound. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual USoundBase* GetReloadSound();

	/** Returns the gun's safety click sound. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual USoundBase* GetSafetySound();

	/** Returns the event that is triggered for each bullet and projectile of the gun that is fired. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual FGunDelegateVR& GetOnFireEvent();

	/** Returns the event that is triggered when the gun successfully shoots. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual FGunDelegateVR& GetOnShootEvent();

	/** Returns the event that is triggered when the gun is reloaded. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual FGunDelegateVR& GetOnReloadEvent();

	/** Returns the time firing effects last per shot. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual float GetFireLingerTime();

	/** Returns the gun's beam class. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual UClass* GetBeamClass();

	/** Returns the gun's muzzle flash class. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual UClass* GetMuzzleFlashClass();

	/** Returns the gun's muzzle flash transform. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual FTransform GetMuzzleFlashTransform();

	/** Returns the gun's wall decal class. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual UClass* GetDecalClass();

	/** Returns the gun's laser sight. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual USceneComponent* GetLaserSight();

	/**
	* Returns whether the gun's laser sight is on.
	* Note: The laser sight is automatically disabled when not picked up, but may still be on.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual bool IsLaserSightOn();

	/** Returns the gun's flashlight. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual ULightComponent* GetFlashlight();

	/** Returns whether the gun's flashlight is on. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual bool IsFlashlightOn();

	/** Returns the gun's ammo display text. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual UTextRenderComponent* GetAmmoDisplayText();

	/** Returns the gun's ammo display text's visibility. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual bool IsAmmoDisplayTextOn();

	/** Returns the gun's color setting. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual FLinearColor GetGunColor();


	// SETTERS

	/** Sets the gun's grab component. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetGrabComponent(UGrabbableVR* _GrabComponent);

	/** Sets the gun's muzzle. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetMuzzle(USceneComponent* _Muzzle);

	/** Sets the gun's trigger pivot. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetTriggerPivot(USceneComponent* _TriggerPivot);

	/** Sets the gun's trigger rotations. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetTriggerRotations(FVector2D _TriggerRotations);

	/** Sets the gun's ammo class. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetAmmoClass(UClass* _AmmoClass);

	/** Sets the gun's ammo pivot. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetAmmoPivot(USceneComponent* _AmmoPivot);

	/** Sets the gun's ammo collider. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetAmmoCollider(UPrimitiveComponent* _AmmoCollider);

	/** Sets the gun's current magazine. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetCurrentMagazine(UGrabbableVR* _CurrentMagazine);

	/** Sets the gun's empty magazine class. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetEmptyMagazineClass(UClass* _EmptyMagazineClass);

	/** Sets this gun's given shoot button. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetShootButton(bool bIsRight, UInputAction* Button);

	/** Sets this gun's shoot buttons. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetShootButtons(UInputAction* Left, UInputAction* Right);

	/** Sets this gun's left shoot button. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetLeftShootButton(UInputAction* Button);

	/** Sets this gun's right shoot button. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetRightShootButton(UInputAction* Button);

	/** Sets the gun's safety setting. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetSafety(bool Safety);

	/** Toggle the gun's safety setting. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual bool ToggleSafety();

	/** Sets the gun's trigger fire percentage. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetTriggerFirePercentage(float _TriggerFirePercentage);

	/** Sets whether this gun is firing projectiles instead of bullets. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetFireProjectile(bool FireProjectiles);

	/** Toggle whether this gun is firing projectiles instead of bullets. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual bool ToggleProjectile();

	/** Sets the projectile class for this gun. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetProjectileClass(UClass* _ProjectileClass);

	/** Sets whether the gun's bullets penetrate walls. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetBulletPenetration(bool Penetrate);

	/** Toggle whether the gun's bullets penetrate walls. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual bool ToggleBulletPenetration();

	/** Sets the maximum distance bullets and projectiles will travel. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetBulletMaxDistance(float _BulletMaxDistance);

	/** Sets the damage this gun does when its bullets and projectiles make contact. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetDamage(float _Damage);

	/** Sets whether the gun is automatic. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetAutomatic(bool Automatic);

	/** Toggle whether the gun is automatic. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual bool ToggleAutomatic();

	/** Sets the gun's tap fire rate. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetTapFireRate(float _TapFireRate);

	/** Sets the gun's fire rate. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetFireRate(float _FireRate);

	/** Sets the gun's number of shots fired. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetShotsFired(int32 _ShotsFired);

	/** Sets the gun's first shot accuracy setting. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetFirstShotAccuracy(bool FirstShotAccuracy);

	/** Toggle the gun's first shot accuracy setting. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual bool ToggleFirstShotAccuracy();

	/** Sets the gun's first shot delay. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetFirstShotDelay(float _FirstShotDelay);

	/** Sets the gun's random spread setting. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetRandomSpread(bool RandomSpread);

	/** Toggle the gun's random spread setting. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual bool ToggleRandomSpread();

	/** Sets the gun's random spread. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetSpread(FVector2D _Spread);

	/** Sets the gun's burst fire setting. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetBurstFire(bool BurstFire);

	/** Toggle the gun's burst fire setting. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual bool ToggleBurstFire();

	/** Sets the number of bursts fired from the gun. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetBurstsFired(int32 _BurstsFired);

	/** Sets the gun's burst rate. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetBurstRate(float _BurstRate);

	/** Sets the gun's infinite ammo setting. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetInfiniteAmmo(bool InfiniteAmmo);

	/** Toggle the gun's infinite ammo setting. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual bool ToggleInfiniteAmmo();

	/** Sets the gun's current ammo count. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetCurrentAmmo(int32 _CurrentAmmo);

	/** Sets the gun's maximum ammo count. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetMaxAmmo(int32 _MaxAmmo);

	/** Sets the gun's magazine ejecting setting. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetMagazineAutoEjects(bool AutoEjectMagazine);

	/** Toggle the gun's magazine ejecting setting. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual bool ToggleAutoEjectMagazine();

	/** Sets the gun's firing sound. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetFiringSound(USoundBase* _FiringSound);

	/** Sets the gun's empty firing sound. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetEmptySound(USoundBase* _EmptySound);

	/** Sets the gun's ejecting sound. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetEjectSound(USoundBase* _EjectSound);

	/** Sets the gun's reloading sound. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetReloadSound(USoundBase* _ReloadSound);

	/** Sets the gun's safety click sound. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetSafetySound(USoundBase* _SafetySound);

	/** Sets the event that is triggered for each bullet and projectile of the gun that is fired. */
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "Event"), Category = "GunVR")
	virtual void BindOnFireEvent(const FGunDelegateVR& Event);

	/** Sets the event that is triggered when the gun successfully shoots. */
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "Event"), Category = "GunVR")
	virtual void BindOnShootEvent(const FGunDelegateVR& Event);

	/** Sets the event that is triggered when the gun is reloaded. */
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "Event"), Category = "GunVR")
	virtual void BindOnReloadEvent(const FGunDelegateVR& Event);

	/** Sets the time firing effects last per shot. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetFireLingerTime(float _FireLingerTime);

	/** Sets the gun's beam class. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetBeamClass(UClass* _BeamClass);

	/** Sets the gun's muzzle flash class. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetMuzzleFlashClass(UClass* _MuzzleFlashClass);

	/** Sets the gun's muzzle flash transform. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetMuzzleFlashTransform(FTransform _MuzzleFlashTransform);

	/** Sets the gun's wall decal class. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetDecalClass(UClass* _DecalClass);

	/** Sets the gun's laser sight. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetLaserSight(USceneComponent* _LaserSight);

	/** Sets the gun's laser sight's visibility. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetLaserSightOn(bool bOn);

	/** Toggle the gun's laser sight's visibility. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual bool ToggleLaserSight();

	/** Sets the gun's flashlight. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetFlashlight(ULightComponent* _Flashlight);

	/** Sets the gun's flashlight's visibility. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetFlashlightOn(bool bOn);

	/** Toggle the gun's flashlight's visibility. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual bool ToggleFlashlight();

	/** Sets the gun's ammo display text. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetAmmoDisplayText(UTextRenderComponent* _AmmoDisplayText);

	/** Sets the gun's ammo display text's visibility. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetAmmoDisplayTextOn(bool bOn);

	/** Toggle the gun's ammo display text's visibility. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual bool ToggleAmmoDisplayText();

	/** Sets the gun's color setting. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void SetGunColor(FLinearColor _GunColor);


	// GUN FUNCTIONS

	/** Gets the current percentage of the trigger (0 = unpulled, 1 = pulled). */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual float GetTriggerPercentage();

	/** Returns whether the trigger is currently pulled. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual bool IsTriggerPulled();

	/** Returns whether the gun is currently firing. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual bool IsFiring();

	/** Returns whether the gun is currently firing in a burst. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GunVR")
	virtual bool IsBurstFiring();

	/**
	* Attempts to shoot the weapon.
	* This is called when the trigger is pulled.
	* Note: Hits and projectiles will be empty if this weapon burst fires.
	*/
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual bool Shoot(TArray<FHitResult>& Hits, TArray<AActor*>& Projectiles);

	/** Loads the given magazine into the gun. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual bool Reload(UGrabbableVR* Magazine);

	/** Updates the current state of the gun. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual void UpdateGun(float DeltaSeconds = 0.001);

	/** Spawns a decal at the given hit point. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	virtual AActor* SpawnDecal(FHitResult Hit);

	/** Spawns a new AGunVR actor into the world. */
	UFUNCTION(BlueprintCallable, Category = "GunVR")
	static AGunVR* SpawnGunVR(UClass* GunClass, FTransform SpawnTransform,
		FVector2D _TriggerRotations = FVector2D(-45, 45), UClass* _AmmoClass = nullptr, UGrabbableVR* _CurrentMagazine = nullptr, UClass* _EmptyMagazineClass = nullptr, UInputAction* LeftShootButton = nullptr,
		UInputAction* RightShootButton = nullptr, bool Safety = false, float _TriggerFirePercentage = 0.75, bool FireProjectiles = false, UClass* _ProjectileClass = nullptr, bool Penetrate = false,
		float _BulletMaxDistance = 10000, float _Damage = 100, bool Automatic = false, float _TapFireRate = 0, float _FireRate = 0.3, int32 _ShotsFired = 1, bool FirstShotAccuracy = true,
		float _FirstShotDelay = 1, bool RandomSpread = true, FVector2D _Spread = FVector2D(2.5, 2.5), bool BurstFire = false, int32 _BurstsFired = 3, float _BurstRate = 0.1, bool InfiniteAmmo = false,
		int32 _CurrentAmmo = 12, int32 _MaxAmmo = 12, bool AutoEjectMagazine = true, USoundBase* _FiringSound = nullptr, USoundBase* _EmptySound = nullptr, USoundBase* _EjectSound = nullptr,
		USoundBase* _ReloadSound = nullptr, USoundBase* _SafetySound = nullptr, float _FireLingerTime = 0, UClass* _BeamClass = nullptr, UClass* _MuzzleFlashClass = nullptr,
		FTransform _MuzzleFlashTransform = FTransform(), UClass* _DecalClass = nullptr, FLinearColor _GunColor = FLinearColor::Red);
};

// This class does not need to be modified. Do not inherit from this class.
UINTERFACE(Blueprintable, BlueprintType, MinimalAPI)
class UProjectileVR : public UInterface
{
	GENERATED_BODY()
};

// Inherit from the following interface to implement it.

/** Indicates an object is a projectile fired by a GunVR actor. */
class MYGAME_API IProjectileVR
{
	GENERATED_BODY()

public:

	// IPROJECTILEVR FUNCTIONS

	/** Automatically called when this actor is spawned from a GunVR class. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ProjectileVR")
	void InitializeProjectile(AGunVR* FiredFrom);
	virtual void InitializeProjectile_Implementation(AGunVR* FiredFrom);
};
