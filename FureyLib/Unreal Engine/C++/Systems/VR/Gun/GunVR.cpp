
// VR Gun Base Class Script
// by Kyle Furey

// REQUIREMENT: GunVR.h

// Include this heading to use the class
#include "VR/Gun/GunVR.h"


// ISHOOTABLEVR FUNCTIONS

// Automatically called when this actor is hit with a GunVR projectile.
void IShootableVR::OnHit_Implementation(AActor* Shooter, AGunVR* Gun, float Damage, FHitResult Hit) { }


// CONSTRUCTORS

// Default constructor.
AGunVR::AGunVR()
{
	PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.TickGroup = ETickingGroup::TG_StartPhysics;

	PrimaryActorTick.bHighPriority = true;

	GrabComponent = nullptr;

	Muzzle = nullptr;

	TriggerPivot = nullptr;

	TriggerRotations = FVector2D(-45, 45);

	AmmoClass = nullptr;

	AmmoPivot = nullptr;

	AmmoCollider = nullptr;

	CurrentMagazine = nullptr;

	EmptyMagazineClass = nullptr;

	bSafety = false;

	TriggerFirePercentage = 0.75;

	bFireProjectiles = false;

	ProjectileClass = nullptr;

	bPenetrate = false;

	BulletMaxDistance = 10000;

	Damage = 100;

	bAutomatic = false;

	TapFireRate = 0;

	FireRate = 0.3;

	ShotsFired = 1;

	bFirstShotAccuracy = true;

	FirstShotDelay = 1;

	bRandomSpread = true;

	Spread = FVector2D(2.5, 2.5);

	FixedSpreadPattern = TArray<FVector2D>();

	bBurstFire = false;

	BurstsFired = 3;

	BurstRate = 0.1;

	bInfiniteAmmo = false;

	CurrentAmmo = 12;

	MaxAmmo = 12;

	bAutoEjectMagazine = true;

	FiringSound = nullptr;

	EmptySound = nullptr;

	EjectSound = nullptr;

	ReloadSound = nullptr;

	SafetySound = nullptr;

	OnFire = FGunDelegateVR();

	OnShoot = FGunDelegateVR();

	OnReload = FGunDelegateVR();

	FireLingerTime = 0.05;

	BeamClass = nullptr;

	MuzzleFlashClass = nullptr;

	MuzzleFlashTransform = FTransform();

	LaserSight = nullptr;

	Flashlight = nullptr;

	AmmoDisplayText = nullptr;

	GunColor = FLinearColor::Red;

	Delay = 0;

	bFirstShot = false;

	CurrentSpreadIndex = 0;

	bBurstFiring = false;

	bAwaitTriggerRelease = false;

	LaserSightStart = FVector();

	bLeftDown = 0;

	bRightDown = 0;

	LeftPress = nullptr;

	RightPress = nullptr;

	LeftRelease = nullptr;

	RightRelease = nullptr;
}

// Object initializer constructor.
AGunVR::AGunVR(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.TickGroup = ETickingGroup::TG_StartPhysics;

	PrimaryActorTick.bHighPriority = true;

	GrabComponent = nullptr;

	Muzzle = nullptr;

	TriggerPivot = nullptr;

	TriggerRotations = FVector2D(-45, 45);

	AmmoClass = nullptr;

	AmmoPivot = nullptr;

	AmmoCollider = nullptr;

	CurrentMagazine = nullptr;

	EmptyMagazineClass = nullptr;

	IA_Shoot_Button_Left = nullptr;

	IA_Shoot_Button_Right = nullptr;

	bSafety = false;

	TriggerFirePercentage = 0.75;

	bFireProjectiles = false;

	ProjectileClass = nullptr;

	bPenetrate = false;

	BulletMaxDistance = 10000;

	Damage = 100;

	bAutomatic = false;

	TapFireRate = 0;

	FireRate = 0.3;

	ShotsFired = 1;

	bFirstShotAccuracy = true;

	FirstShotDelay = 1;

	bRandomSpread = true;

	Spread = FVector2D(2.5, 2.5);

	FixedSpreadPattern = TArray<FVector2D>();

	bBurstFire = false;

	BurstsFired = 3;

	BurstRate = 0.1;

	bInfiniteAmmo = false;

	CurrentAmmo = 12;

	MaxAmmo = 12;

	bAutoEjectMagazine = true;

	FiringSound = nullptr;

	EmptySound = nullptr;

	EjectSound = nullptr;

	ReloadSound = nullptr;

	SafetySound = nullptr;

	OnFire = FGunDelegateVR();

	OnShoot = FGunDelegateVR();

	OnReload = FGunDelegateVR();

	FireLingerTime = 0.05;

	BeamClass = nullptr;

	MuzzleFlashClass = nullptr;

	MuzzleFlashTransform = FTransform();

	LaserSight = nullptr;

	Flashlight = nullptr;

	AmmoDisplayText = nullptr;

	GunColor = FLinearColor::Red;

	Delay = 0;

	bFirstShot = false;

	CurrentSpreadIndex = 0;

	bBurstFiring = false;

	bAwaitTriggerRelease = false;

	LaserSightStart = FVector();

	bLeftDown = 0;

	bRightDown = 0;

	LeftPress = nullptr;

	RightPress = nullptr;

	LeftRelease = nullptr;

	RightRelease = nullptr;
}

// GunVR constructor.
AGunVR::AGunVR(
	FVector2D _TriggerRotations, UClass* _AmmoClass, UGrabbableVR* _CurrentMagazine, UClass* _EmptyMagazineClass, UInputAction* LeftShootButton,
	UInputAction* RightShootButton, bool Safety, float _TriggerFirePercentage, bool FireProjectiles, UClass* _ProjectileClass, bool Penetrate,
	float _BulletMaxDistance, float _Damage, bool Automatic, float _TapFireRate, float _FireRate, int32 _ShotsFired, bool FirstShotAccuracy,
	float _FirstShotDelay, bool RandomSpread, FVector2D _Spread, bool BurstFire, int32 _BurstsFired, float _BurstRate, bool InfiniteAmmo,
	int32 _CurrentAmmo, int32 _MaxAmmo, bool AutoEjectMagazine, USoundBase* _FiringSound, USoundBase* _EmptySound, USoundBase* _EjectSound,
	USoundBase* _ReloadSound, USoundBase* _SafetySound, float _FireLingerTime, UClass* _BeamClass, UClass* _MuzzleFlashClass,
	FTransform _MuzzleFlashTransform, UClass* _DecalClass, FLinearColor _GunColor)
{
	PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.TickGroup = ETickingGroup::TG_StartPhysics;

	PrimaryActorTick.bHighPriority = true;

	GrabComponent = nullptr;

	Muzzle = nullptr;

	TriggerPivot = nullptr;

	TriggerRotations = _TriggerRotations;

	AmmoClass = _AmmoClass;

	AmmoPivot = nullptr;

	AmmoCollider = nullptr;

	CurrentMagazine = _CurrentMagazine;

	EmptyMagazineClass = _EmptyMagazineClass;

	IA_Shoot_Button_Left = LeftShootButton;

	IA_Shoot_Button_Right = RightShootButton;

	bSafety = Safety;

	TriggerFirePercentage = _TriggerFirePercentage;

	bFireProjectiles = FireProjectiles;

	ProjectileClass = _ProjectileClass;

	bPenetrate = Penetrate;

	BulletMaxDistance = _BulletMaxDistance;

	Damage = _Damage;

	bAutomatic = Automatic;

	TapFireRate = _TapFireRate;

	FireRate = _FireRate;

	ShotsFired = _ShotsFired;

	bFirstShotAccuracy = FirstShotAccuracy;

	FirstShotDelay = _FirstShotDelay;

	bRandomSpread = RandomSpread;

	Spread = _Spread;

	FixedSpreadPattern = TArray<FVector2D>();

	bBurstFire = BurstFire;

	BurstsFired = _BurstsFired;

	BurstRate = _BurstRate;

	bInfiniteAmmo = InfiniteAmmo;

	CurrentAmmo = _CurrentAmmo;

	MaxAmmo = _MaxAmmo;

	bAutoEjectMagazine = AutoEjectMagazine;

	FiringSound = _FiringSound;

	EmptySound = _EmptySound;

	EjectSound = _EjectSound;

	ReloadSound = _ReloadSound;

	SafetySound = _SafetySound;

	OnFire = FGunDelegateVR();

	OnShoot = FGunDelegateVR();

	OnReload = FGunDelegateVR();

	FireLingerTime = _FireLingerTime;

	BeamClass = _BeamClass;

	MuzzleFlashClass = _MuzzleFlashClass;

	MuzzleFlashTransform = _MuzzleFlashTransform;

	DecalClass = _DecalClass;

	LaserSight = nullptr;

	Flashlight = nullptr;

	AmmoDisplayText = nullptr;

	GunColor = _GunColor;

	Delay = 0;

	bFirstShot = false;

	CurrentSpreadIndex = 0;

	bBurstFiring = false;

	bAwaitTriggerRelease = false;

	LaserSightStart = FVector();

	bLeftDown = 0;

	bRightDown = 0;

	LeftPress = nullptr;

	RightPress = nullptr;

	LeftRelease = nullptr;

	RightRelease = nullptr;
}


// UNREAL FUNCTIONS

// Called when the game starts or when spawned.
void AGunVR::BeginPlay()
{
	// Calls the base class's function.
	Super::BeginPlay();

	ImplementHandTracking();

	UControllerInputVR::ReceiveControllerInput(this, 0);

	BindInput(false);

	BindInput(true);

	if (IsValid(CurrentMagazine))
	{
		UGrabbableVR* Magazine = CurrentMagazine;

		CurrentMagazine = nullptr;

		InsertMagazine(Magazine);
	}

	ResetLaserSight();

	AmmoDisplayText->SetText(FText::FromString(bInfiniteAmmo ? "" : FString::FromInt(CurrentAmmo)));
}

// Called when this component is destroyed.
void AGunVR::BeginDestroy()
{
	// Calls the base class's function.
	Super::BeginDestroy();

	RemoveHandTracking();

	UControllerInputVR::StopReceivingControllerInput(this, 0);

	UnbindInput(false);

	UnbindInput(true);
}

// Called every frame.
void AGunVR::Tick(float DeltaTime)
{
	// Calls the base class's function.
	Super::Tick(DeltaTime);

	UpdateGun(DeltaTime);
}


// CONTROLLERINPUTVR FUNCTIONS

// Called when the left shoot button is pressed down.
void AGunVR::OnLeftShootButtonPressed(const FInputActionValue& Value)
{
	bLeftDown = Value.Get<float>();
}

// Called when the right shoot button is pressed down.
void AGunVR::OnRightShootButtonPressed(const FInputActionValue& Value)
{
	bRightDown = Value.Get<float>();
}

// Called when the left shoot button is released.
void AGunVR::OnLeftShootButtonReleased(const FInputActionValue& Value)
{
	bLeftDown = 0;
}

// Called when the right shoot button is released.
void AGunVR::OnRightShootButtonReleased(const FInputActionValue& Value)
{
	bRightDown = 0;
}


// GETTERS

// Returns the gun's grab component.
UGrabbableVR* AGunVR::GetGrabComponent()
{
	return GrabComponent;
}

// Returns the gun's muzzle.
USceneComponent* AGunVR::GetMuzzle()
{
	return Muzzle;
}

// Returns the gun's trigger pivot.
USceneComponent* AGunVR::GetTriggerPivot()
{
	return TriggerPivot;
}

// Returns the gun's trigger rotations.
FVector2D AGunVR::GetTriggerRotations()
{
	return TriggerRotations;
}

// Returns the gun's ammo class.
UClass* AGunVR::GetAmmoClass()
{
	return AmmoClass;
}

// Returns the gun's ammo pivot.
USceneComponent* AGunVR::GetAmmoPivot()
{
	return AmmoPivot;
}

// Returns the gun's ammo collider.
UPrimitiveComponent* AGunVR::GetAmmoCollider()
{
	return AmmoCollider;
}

// Returns the gun's current magazine.
UGrabbableVR* AGunVR::GetCurrentMagazine()
{
	return CurrentMagazine;
}

// Returns the gun's empty magazine class.
UClass* AGunVR::GetEmptyMagazineClass()
{
	return EmptyMagazineClass;
}

// Returns this gun's given shoot button.
UInputAction* AGunVR::GetShootButton(bool bIsRight)
{
	return bIsRight ? IA_Shoot_Button_Right : IA_Shoot_Button_Right;
}

// Returns this gun's shoot buttons.
void AGunVR::GetShootButtons(UInputAction*& Left, UInputAction*& Right)
{
	Left = IA_Shoot_Button_Left;

	Right = IA_Shoot_Button_Right;
}

// Returns this gun's left shoot button.
UInputAction* AGunVR::GetLeftShootButton()
{
	return IA_Shoot_Button_Left;
}

// Returns this gun's right shoot button.
UInputAction* AGunVR::GetRightShootButton()
{
	return IA_Shoot_Button_Right;
}

// Returns the gun's safety setting.
bool AGunVR::IsSafetyOn()
{
	return bSafety;
}

// Returns the gun's trigger fire percentage.
float AGunVR::GetTriggerFirePercentage()
{
	return TriggerFirePercentage;
}

// Returns whether this gun is firing projectiles instead of bullets.
bool AGunVR::IsFiringProjectiles()
{
	return bFireProjectiles;
}

// Returns the projectile class used for this gun.
UClass* AGunVR::GetProjectileClass()
{
	return ProjectileClass;
}

// Returns whether the gun's bullets penetrate walls.
bool AGunVR::IsPenetratingWalls()
{
	return bPenetrate;
}

// Returns the maximum distance bullets and projectiles will travel.
float AGunVR::GetBulletMaxDistance()
{
	return BulletMaxDistance;
}

// Returns the damage this gun does when its bullets and projectiles make contact.
float AGunVR::GetDamage()
{
	return Damage;
}

// Returns whether the gun is automatic.
bool AGunVR::IsAutomatic()
{
	return bAutomatic;
}

// Returns the gun's tap fire rate.
float AGunVR::GetTapFireRate()
{
	return TapFireRate;
}

// Returns the gun's fire rate.
float AGunVR::GetFireRate()
{
	return FireRate;
}

// Returns the gun's number of shots fired.
int32 AGunVR::GetShotsFired()
{
	return ShotsFired;
}

// Returns the gun's first shot accuracy setting.
bool AGunVR::IsFirstShotAccurate()
{
	return bFirstShotAccuracy;
}

// Returns the gun's first shot delay.
float AGunVR::GetFirstShotDelay()
{
	return FirstShotDelay;
}

// Returns the gun's random spread setting.
bool AGunVR::IsSpreadRandom()
{
	return bRandomSpread;
}

// Returns the gun's random spread.
FVector2D AGunVR::GetSpread()
{
	return Spread;
}

// Returns the gun's fixed spread pattern.
void AGunVR::GetFixedSpreadPattern(TArray<FVector2D>& _FixedSpreadPattern)
{
	_FixedSpreadPattern = FixedSpreadPattern;
}

// Returns the gun's burst fire setting.
bool AGunVR::IsBurstFire()
{
	return bBurstFire;
}

// Returns the number of bursts fired from the gun.
int32 AGunVR::GetBurstsFired()
{
	return BurstsFired;
}

// Returns the gun's burst rate.
float AGunVR::GetBurstRate()
{
	return BurstRate;
}

// Returns the gun's infinite ammo setting.
bool AGunVR::IsAmmoInfinite()
{
	return bInfiniteAmmo;
}

// Returns the gun's current ammo count.
int32 AGunVR::GetCurrentAmmo()
{
	return CurrentAmmo;
}

// Returns if the ammo count is empty.
bool AGunVR::IsEmpty()
{
	return CurrentAmmo <= 0;
}

// Returns the gun's maximum ammo count.
int32 AGunVR::GetMaxAmmo()
{
	return MaxAmmo;
}

// Returns the gun's magazine ejecting setting.
bool AGunVR::IsAutoEjectingMagazine()
{
	return bAutoEjectMagazine;
}

// Returns the gun's firing sound.
USoundBase* AGunVR::GetFiringSound()
{
	return FiringSound;
}

// Returns the gun's empty firing sound.
USoundBase* AGunVR::GetEmptySound()
{
	return EmptySound;
}

// Returns the gun's ejecting sound.
USoundBase* AGunVR::GetEjectSound()
{
	return EjectSound;
}

// Returns the gun's reloading sound.
USoundBase* AGunVR::GetReloadSound()
{
	return ReloadSound;
}

// Returns the gun's safety click sound.
USoundBase* AGunVR::GetSafetySound()
{
	return SafetySound;
}

// Returns the event that is triggered for each bullet and projectile of the gun that is fired.
FGunDelegateVR& AGunVR::GetOnFireEvent()
{
	return OnFire;
}

// Returns the event that is triggered when the gun successfully shoots.
FGunDelegateVR& AGunVR::GetOnShootEvent()
{
	return OnShoot;
}

// Returns the event that is triggered when the gun is reloaded.
FGunDelegateVR& AGunVR::GetOnReloadEvent()
{
	return OnReload;
}

// Returns the time firing effects last per shot.
float AGunVR::GetFireLingerTime()
{
	return FireLingerTime;
}

// Returns the gun's beam class.
UClass* AGunVR::GetBeamClass()
{
	return BeamClass;
}

// Returns the gun's muzzle flash class.
UClass* AGunVR::GetMuzzleFlashClass()
{
	return MuzzleFlashClass;
}

// Returns the gun's muzzle flash transform.
FTransform AGunVR::GetMuzzleFlashTransform()
{
	return MuzzleFlashTransform;
}

// Returns the gun's wall decal class.
UClass* AGunVR::GetDecalClass()
{
	return DecalClass;
}

// Returns the gun's laser sight.
USceneComponent* AGunVR::GetLaserSight()
{
	return LaserSight;
}

// Returns whether the gun's laser sight is on.
// Note: The laser sight is automatically disabled when not picked up, but may still be on.
bool AGunVR::IsLaserSightOn()
{
	return IsValid(LaserSight) && LaserSight->IsVisible();
}

// Returns the gun's flashlight.
ULightComponent* AGunVR::GetFlashlight()
{
	return Flashlight;
}

// Returns whether the gun's flashlight is on.
bool AGunVR::IsFlashlightOn()
{
	return IsValid(Flashlight) && Flashlight->IsVisible();
}

// Returns the gun's ammo display text.
UTextRenderComponent* AGunVR::GetAmmoDisplayText()
{
	return AmmoDisplayText;
}

// Returns the gun's ammo display text's visibility.
bool AGunVR::IsAmmoDisplayTextOn()
{
	return IsValid(AmmoDisplayText) && AmmoDisplayText->IsVisible();
}

// Returns the gun's color setting.
FLinearColor AGunVR::GetGunColor()
{
	return GunColor;
}


// SETTERS

// Sets the gun's grab component.
void AGunVR::SetGrabComponent(UGrabbableVR* _GrabComponent)
{
	GrabComponent = _GrabComponent;
}

// Sets the gun's muzzle.
void AGunVR::SetMuzzle(USceneComponent* _Muzzle)
{
	Muzzle = _Muzzle;
}

// Sets the gun's trigger pivot.
void AGunVR::SetTriggerPivot(USceneComponent* _TriggerPivot)
{
	TriggerPivot = _TriggerPivot;
}

// Sets the gun's trigger rotations.
void AGunVR::SetTriggerRotations(FVector2D _TriggerRotations)
{
	TriggerRotations = _TriggerRotations;
}

// Sets the gun's ammo class.
void AGunVR::SetAmmoClass(UClass* _AmmoClass)
{
	AmmoClass = _AmmoClass;
}

// Sets the gun's ammo pivot.
void AGunVR::SetAmmoPivot(USceneComponent* _AmmoPivot)
{
	AmmoPivot = _AmmoPivot;
}

// Sets the gun's ammo collider.
void AGunVR::SetAmmoCollider(UPrimitiveComponent* _AmmoCollider)
{
	AmmoCollider = _AmmoCollider;
}

// Sets the gun's current magazine.
void AGunVR::SetCurrentMagazine(UGrabbableVR* _CurrentMagazine)
{
	CurrentMagazine = _CurrentMagazine;
}

// Sets the gun's empty magazine class.
void AGunVR::SetEmptyMagazineClass(UClass* _EmptyMagazineClass)
{
	EmptyMagazineClass = _EmptyMagazineClass;
}

// Sets this gun's given shoot button.
void AGunVR::SetShootButton(bool bIsRight, UInputAction* Button)
{
	if (bIsRight)
	{
		UnbindInput(true);

		IA_Shoot_Button_Right = Button;

		BindInput(true);
	}
	else
	{
		UnbindInput(false);

		IA_Shoot_Button_Left = Button;

		BindInput(false);
	}
}

// Sets this gun's shoot buttons.
void AGunVR::SetShootButtons(UInputAction* Left, UInputAction* Right)
{
	UnbindInput(false);

	UnbindInput(true);

	IA_Shoot_Button_Left = Left;

	IA_Shoot_Button_Right = Right;

	BindInput(false);

	BindInput(true);
}

// Sets this gun's left shoot button.
void AGunVR::SetLeftShootButton(UInputAction* Button)
{
	UnbindInput(false);

	IA_Shoot_Button_Left = Button;

	BindInput(false);
}

// Sets this gun's right shoot button.
void AGunVR::SetRightShootButton(UInputAction* Button)
{
	UnbindInput(true);

	IA_Shoot_Button_Right = Button;

	BindInput(true);
}

// Sets the gun's safety setting.
void AGunVR::SetSafety(bool Safety)
{
	bSafety = Safety;
}

// Toggle the gun's safety setting.
bool AGunVR::ToggleSafety()
{
	bSafety = !bSafety;

	return bSafety;
}

// Sets the gun's trigger fire percentage.
void AGunVR::SetTriggerFirePercentage(float _TriggerFirePercentage)
{
	TriggerFirePercentage = _TriggerFirePercentage;
}

// Sets whether this gun is firing projectiles instead of bullets.
void AGunVR::SetFireProjectile(bool FireProjectiles)
{
	bFireProjectiles = FireProjectiles;
}

// Toggle whether this gun is firing projectiles instead of bullets.
bool AGunVR::ToggleProjectile()
{
	bFireProjectiles = !bFireProjectiles;

	return bFireProjectiles;
}

// Sets the projectile class for this gun.
void AGunVR::SetProjectileClass(UClass* _ProjectileClass)
{
	ProjectileClass = _ProjectileClass;
}

// Sets whether the gun's bullets penetrate walls.
void AGunVR::SetBulletPenetration(bool Penetrate)
{
	bPenetrate = Penetrate;
}

// Toggle whether the gun's bullets penetrate walls.
bool AGunVR::ToggleBulletPenetration()
{
	bPenetrate = !bPenetrate;

	return bPenetrate;
}

// Sets the maximum distance bullets and projectiles will travel.
void AGunVR::SetBulletMaxDistance(float _BulletMaxDistance)
{
	BulletMaxDistance = _BulletMaxDistance;
}

// Sets the damage this gun does when its bullets and projectiles make contact.
void AGunVR::SetDamage(float _Damage)
{
	Damage = _Damage;
}

// Sets whether the gun is automatic.
void AGunVR::SetAutomatic(bool Automatic)
{
	bAutomatic = Automatic;
}

// Toggle whether the gun is automatic.
bool AGunVR::ToggleAutomatic()
{
	bAutomatic = !bAutomatic;

	return bAutomatic;
}

// Sets the gun's tap fire rate.
void AGunVR::SetTapFireRate(float _TapFireRate)
{
	TapFireRate = _TapFireRate;
}

// Sets the gun's fire rate.
void AGunVR::SetFireRate(float _FireRate)
{
	FireRate = _FireRate;
}

// Sets the gun's number of shots fired.
void AGunVR::SetShotsFired(int32 _ShotsFired)
{
	ShotsFired = _ShotsFired;
}

// Sets the gun's first shot accuracy setting.
void AGunVR::SetFirstShotAccuracy(bool FirstShotAccuracy)
{
	bFirstShotAccuracy = FirstShotAccuracy;
}

// Toggle the gun's first shot accuracy setting.
bool AGunVR::ToggleFirstShotAccuracy()
{
	bFirstShotAccuracy = !bFirstShotAccuracy;

	return bFirstShotAccuracy;
}

// Sets the gun's first shot delay.
void AGunVR::SetFirstShotDelay(float _FirstShotDelay)
{
	FirstShotDelay = _FirstShotDelay;
}

// Sets the gun's random spread setting.
void AGunVR::SetRandomSpread(bool RandomSpread)
{
	bRandomSpread = RandomSpread;
}

// Toggle the gun's random spread setting.
bool AGunVR::ToggleRandomSpread()
{
	bRandomSpread = !bRandomSpread;

	return bRandomSpread;
}

// Sets the gun's random spread.
void AGunVR::SetSpread(FVector2D _Spread)
{
	Spread = _Spread;
}

// Sets the gun's burst fire setting.
void AGunVR::SetBurstFire(bool BurstFire)
{
	bBurstFire = BurstFire;
}

// Toggle the gun's burst fire setting.
bool AGunVR::ToggleBurstFire()
{
	bBurstFire = !bBurstFire;

	return bBurstFire;
}

// Sets the number of bursts fired from the gun.
void AGunVR::SetBurstsFired(int32 _BurstsFired)
{
	BurstsFired = _BurstsFired;
}

// Sets the gun's burst rate.
void AGunVR::SetBurstRate(float _BurstRate)
{
	BurstRate = _BurstRate;
}

// Sets the gun's infinite ammo setting.
void AGunVR::SetInfiniteAmmo(bool InfiniteAmmo)
{
	bInfiniteAmmo = InfiniteAmmo;
}

// Toggle the gun's infinite ammo setting.
bool AGunVR::ToggleInfiniteAmmo()
{
	bInfiniteAmmo = !bInfiniteAmmo;

	return bInfiniteAmmo;
}

// Sets the gun's current ammo count.
void AGunVR::SetCurrentAmmo(int32 _CurrentAmmo)
{
	CurrentAmmo = _CurrentAmmo;
}

// Sets the gun's maximum ammo count.
void AGunVR::SetMaxAmmo(int32 _MaxAmmo)
{
	MaxAmmo = _MaxAmmo;
}

// Sets the gun's magazine auto-eject setting.
void AGunVR::SetMagazineAutoEjects(bool AutoEjectMagazine)
{
	bAutoEjectMagazine = AutoEjectMagazine;
}

// Toggle the gun's magazine ejecting setting.
bool AGunVR::ToggleAutoEjectMagazine()
{
	bAutoEjectMagazine = !bAutoEjectMagazine;

	return bAutoEjectMagazine;
}

// Sets the gun's firing sound.
void AGunVR::SetFiringSound(USoundBase* _FiringSound)
{
	FiringSound = _FiringSound;
}

// Sets the gun's empty firing sound.
void AGunVR::SetEmptySound(USoundBase* _EmptySound)
{
	EmptySound = _EmptySound;
}

// Sets the gun's ejecting sound.
void AGunVR::SetEjectSound(USoundBase* _EjectSound)
{
	EjectSound = _EjectSound;
}

// Sets the gun's reloading sound.
void AGunVR::SetReloadSound(USoundBase* _ReloadSound)
{
	ReloadSound = _ReloadSound;
}

// Sets the gun's safety click sound.
void AGunVR::SetSafetySound(USoundBase* _SafetySound)
{
	SafetySound = _SafetySound;
}

// Sets the event that is triggered for each bullet and projectile of the gun that is fired.
void AGunVR::BindOnFireEvent(const FGunDelegateVR& Event)
{
	OnFire = Event;
}

// Sets the event that is triggered when the gun successfully shoots.
void AGunVR::BindOnShootEvent(const FGunDelegateVR& Event)
{
	OnShoot = Event;
}

// Binds the event when the gun is reloaded.
void AGunVR::BindOnReloadEvent(const FGunDelegateVR& Event)
{
	OnReload = Event;
}

// Sets the time firing effects last per shot.
void AGunVR::SetFireLingerTime(float _FireLingerTime)
{
	FireLingerTime = _FireLingerTime;
}

// Sets the gun's beam class.
void AGunVR::SetBeamClass(UClass* _BeamClass)
{
	BeamClass = _BeamClass;
}

// Sets the gun's muzzle flash class.
void AGunVR::SetMuzzleFlashClass(UClass* _MuzzleFlashClass)
{
	MuzzleFlashClass = _MuzzleFlashClass;
}

// Sets the gun's muzzle flash transform.
void AGunVR::SetMuzzleFlashTransform(FTransform _MuzzleFlashTransform)
{
	MuzzleFlashTransform = _MuzzleFlashTransform;
}

// Sets the gun's wall decal class.
void AGunVR::SetDecalClass(UClass* _DecalClass)
{
	DecalClass = _DecalClass;
}

// Sets the gun's laser sight.
void AGunVR::SetLaserSight(USceneComponent* _LaserSight)
{
	LaserSight = _LaserSight;
}

// Sets the gun's laser sight's visibility.
void AGunVR::SetLaserSightOn(bool bOn)
{
	if (IsValid(LaserSight))
	{
		LaserSight->SetVisibility(bOn);
	}
}

// Toggle the gun's laser sight's visibility.
bool AGunVR::ToggleLaserSight()
{
	if (IsValid(LaserSight))
	{
		LaserSight->SetVisibility(!LaserSight->IsVisible());
	}

	return LaserSight->IsVisible();
}

// Sets the gun's laser sight.
void AGunVR::SetFlashlight(ULightComponent* _Flashlight)
{
	Flashlight = _Flashlight;
}

// Sets the gun's flashlight's visibility.
void AGunVR::SetFlashlightOn(bool bOn)
{
	if (IsValid(Flashlight))
	{
		Flashlight->SetVisibility(bOn);
	}
}

// Toggle the gun's flashlight's visibility.
bool AGunVR::ToggleFlashlight()
{
	if (IsValid(Flashlight))
	{
		Flashlight->SetVisibility(!Flashlight->IsVisible());
	}

	return Flashlight->IsVisible();
}

// Sets the gun's ammo display text.
void AGunVR::SetAmmoDisplayText(UTextRenderComponent* _AmmoDisplayText)
{
	AmmoDisplayText = _AmmoDisplayText;
}

// Sets the gun's ammo display text's visibility.
void AGunVR::SetAmmoDisplayTextOn(bool bOn)
{
	if (IsValid(AmmoDisplayText))
	{
		AmmoDisplayText->SetVisibility(bOn);
	}
}

// Toggle the gun's ammo display text's visibility.
bool AGunVR::ToggleAmmoDisplayText()
{
	if (IsValid(AmmoDisplayText))
	{
		AmmoDisplayText->SetVisibility(!AmmoDisplayText->IsVisible());
	}

	return AmmoDisplayText->IsVisible();
}

// Sets the gun's color setting.
void AGunVR::SetGunColor(FLinearColor _GunColor)
{
	GunColor = _GunColor;
}


// GUN FUNCTIONS

// Binds controller input to grab events.
// Returns whether the bind was successful.
bool AGunVR::BindInput(bool bIsRight)
{
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);

	if (IsValid(Input))
	{
		if (bIsRight)
		{
			if (IsValid(IA_Shoot_Button_Right))
			{
				RightPress = &Input->BindAction(IA_Shoot_Button_Right, ETriggerEvent::Triggered, this, &AGunVR::OnRightShootButtonPressed);

				RightRelease = &Input->BindAction(IA_Shoot_Button_Right, ETriggerEvent::Completed, this, &AGunVR::OnRightShootButtonReleased);
			}
		}
		else
		{
			if (IsValid(IA_Shoot_Button_Left))
			{
				LeftPress = &Input->BindAction(IA_Shoot_Button_Left, ETriggerEvent::Triggered, this, &AGunVR::OnLeftShootButtonPressed);

				LeftRelease = &Input->BindAction(IA_Shoot_Button_Left, ETriggerEvent::Completed, this, &AGunVR::OnLeftShootButtonReleased);
			}
		}

		return bIsRight ? IsValid(IA_Shoot_Button_Right) : IsValid(IA_Shoot_Button_Left);
	}

	return false;
}

// Unbinds controller input to grab events.
// Returns whether the unbind was successful.
bool AGunVR::UnbindInput(bool bIsRight)
{
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);

	if (IsValid(Input))
	{
		if (bIsRight)
		{
			if (RightPress != nullptr)
			{
				Input->RemoveBinding(*RightPress);
			}

			if (RightRelease != nullptr)
			{
				Input->RemoveBinding(*RightRelease);
			}
		}
		else
		{
			if (LeftPress != nullptr)
			{
				Input->RemoveBinding(*LeftPress);
			}

			if (LeftRelease != nullptr)
			{
				Input->RemoveBinding(*LeftRelease);
			}
		}

		return true;
	}

	return false;
}

// Destroys the given actor after the given number of seconds.
void AGunVR::DestroyActorAfterSeconds(AActor* ActorToDestroy, float Seconds)
{
	FTimerDelegate TimerDelegate = FTimerDelegate();

	TimerDelegate.BindLambda([=]() { if (IsValid(ActorToDestroy)) { ActorToDestroy->Destroy(); } });

	FTimerHandle Timer;

	GetWorld()->GetTimerManager().SetTimer(Timer, TimerDelegate, Seconds, false);
}

// Attempts to fire a single bullet from this weapon.
// Returns whether a hit was successful and the hit result.
bool AGunVR::Fire(FHitResult& Hit)
{
	if (IsValid(Muzzle))
	{
		if (!bSafety && (bInfiniteAmmo || CurrentAmmo > 0))
		{
			FVector Direction = Muzzle->GetForwardVector();

			if (!bFirstShot || !bFirstShotAccuracy || ShotsFired > 1 || Delay > -FMath::Abs(FirstShotDelay))
			{
				if (bRandomSpread)
				{
					Direction = FRotator(FMath::RandRange(-FMath::Abs(Spread.Y), FMath::Abs(Spread.Y)), FMath::RandRange(-FMath::Abs(Spread.X), FMath::Abs(Spread.X)), 0).Quaternion() * Direction;
				}
				else if (!FixedSpreadPattern.IsEmpty())
				{
					Direction = FRotator(FixedSpreadPattern[CurrentSpreadIndex].Y, FixedSpreadPattern[CurrentSpreadIndex].X, 0).Quaternion() * Direction;

					CurrentSpreadIndex++;

					CurrentSpreadIndex %= FixedSpreadPattern.Num();
				}
			}

			bFirstShot = false;

			if (IsValid(MuzzleFlashClass))
			{
				AActor* Flash = GetWorld()->SpawnActor<AActor>(MuzzleFlashClass, FTransform(Muzzle->GetComponentRotation(), Muzzle->GetComponentLocation(), FVector(1, 1, 1)));

				Flash->AddActorWorldOffset(Flash->GetActorQuat() * MuzzleFlashTransform.GetLocation());

				Flash->SetActorRotation(Flash->GetActorQuat() * MuzzleFlashTransform.GetRotation() * FRotator(0, 0, FMath::RandRange(-180, 180)).Quaternion());

				FVector Scale = Flash->GetActorScale3D();

				FVector Scale2 = MuzzleFlashTransform.GetScale3D();

				Flash->SetActorScale3D(FVector(Scale.X * Scale2.X, Scale.Y * Scale2.Y, Scale.Z * Scale2.Z));

				DestroyActorAfterSeconds(Flash, FireLingerTime);
			}

			if (bPenetrate)
			{
				if (IsValid(BeamClass))
				{
					AActor* Beam = GetWorld()->SpawnActor<AActor>(BeamClass, FTransform(Direction.Rotation(), Muzzle->GetComponentLocation(), FVector(1, 1, 1)));

					Beam->AddActorWorldOffset(Beam->GetActorForwardVector() * (BulletMaxDistance / 2));

					FVector Scale = Beam->GetActorScale3D();

					Scale.X = BulletMaxDistance / 100;

					Beam->SetActorScale3D(Scale);

					DestroyActorAfterSeconds(Beam, FireLingerTime);
				}

				TArray<FHitResult> Hits;

				if (UKismetSystemLibrary::LineTraceMulti(this, Muzzle->GetComponentLocation(), Muzzle->GetComponentLocation() + Direction * BulletMaxDistance, ETraceTypeQuery::TraceTypeQuery1, true, { this, GetOwner() }, EDrawDebugTrace::None, Hits, true))
				{
					Hit = Hits[0];

					for (const FHitResult& Contact : Hits)
					{
						if (IsValid(Contact.GetComponent()) && Contact.GetComponent()->Implements<UShootableVR>())
						{
							IShootableVR::Execute_OnHit(Contact.GetComponent(), Owner, this, Damage, Contact);
						}

						if (IsValid(Contact.GetActor()) && Contact.GetActor()->Implements<UShootableVR>())
						{
							IShootableVR::Execute_OnHit(Contact.GetActor(), Owner, this, Damage, Contact);
						}

						SpawnDecal(Contact);
					}
				}
				else
				{
					Hit = FHitResult();
				}
			}
			else
			{
				if (UKismetSystemLibrary::LineTraceSingle(this, Muzzle->GetComponentLocation(), Muzzle->GetComponentLocation() + Direction * BulletMaxDistance, ETraceTypeQuery::TraceTypeQuery1, true, { this, GetOwner() }, EDrawDebugTrace::None, Hit, true))
				{
					if (IsValid(BeamClass))
					{
						AActor* Beam = GetWorld()->SpawnActor<AActor>(BeamClass, FTransform(Direction.Rotation(), Muzzle->GetComponentLocation(), FVector(1, 1, 1)));

						Beam->AddActorWorldOffset(Beam->GetActorForwardVector() * (Hit.Distance / 2));

						FVector Scale = Beam->GetActorScale3D();

						Scale.X = Hit.Distance / 100;

						Beam->SetActorScale3D(Scale);

						DestroyActorAfterSeconds(Beam, FireLingerTime);
					}

					if (IsValid(Hit.GetComponent()) && Hit.GetComponent()->Implements<UShootableVR>())
					{
						IShootableVR::Execute_OnHit(Hit.GetComponent(), Owner, this, Damage, Hit);
					}

					if (IsValid(Hit.GetActor()) && Hit.GetActor()->Implements<UShootableVR>())
					{
						IShootableVR::Execute_OnHit(Hit.GetActor(), Owner, this, Damage, Hit);
					}

					SpawnDecal(Hit);
				}
				else
				{
					if (IsValid(BeamClass))
					{
						AActor* Beam = GetWorld()->SpawnActor<AActor>(BeamClass, FTransform(Direction.Rotation(), Muzzle->GetComponentLocation(), FVector(1, 1, 1)));

						Beam->AddActorWorldOffset(Beam->GetActorForwardVector() * (BulletMaxDistance / 2));

						FVector Scale = Beam->GetActorScale3D();

						Scale.X = BulletMaxDistance / 100;

						Beam->SetActorScale3D(Scale);

						DestroyActorAfterSeconds(Beam, FireLingerTime);
					}
				}
			}

			if (!bInfiniteAmmo)
			{
				CurrentAmmo--;
			}

			if (IsValid(FiringSound))
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), FiringSound, Muzzle->GetComponentLocation());
			}

			OnFire.ExecuteIfBound();

			return Hit.bBlockingHit;
		}
		else if (bFirstShot || bAutomatic)
		{
			bFirstShot = false;

			if (bSafety && IsValid(SafetySound))
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), SafetySound, Muzzle->GetComponentLocation());
			}
			else if (IsValid(EmptySound))
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), EmptySound, Muzzle->GetComponentLocation());
			}
		}
	}

	Hit = FHitResult();

	return false;
}

// Attempts to launch a single projectile from this weapon.
// Returns whether the launch was successful and the actor being used as a projectile.
bool AGunVR::Launch(AActor*& Projectile)
{
	if (IsValid(Muzzle) && IsValid(ProjectileClass))
	{
		if (!bSafety && (bInfiniteAmmo || CurrentAmmo > 0))
		{
			FVector Direction = Muzzle->GetForwardVector();

			if (!bFirstShot || !bFirstShotAccuracy || ShotsFired > 1 || Delay > -FMath::Abs(FirstShotDelay))
			{
				if (bRandomSpread)
				{
					Direction = FRotator(FMath::RandRange(-FMath::Abs(Spread.Y), FMath::Abs(Spread.Y)), FMath::RandRange(-FMath::Abs(Spread.X), FMath::Abs(Spread.X)), 0).Quaternion() * Direction;
				}
				else if (!FixedSpreadPattern.IsEmpty())
				{
					Direction = FRotator(FixedSpreadPattern[CurrentSpreadIndex].Y, FixedSpreadPattern[CurrentSpreadIndex].X, 0).Quaternion() * Direction;

					CurrentSpreadIndex++;

					CurrentSpreadIndex %= FixedSpreadPattern.Num();
				}
			}

			bFirstShot = false;

			if (IsValid(MuzzleFlashClass))
			{
				AActor* Flash = GetWorld()->SpawnActor<AActor>(MuzzleFlashClass, FTransform(Muzzle->GetComponentRotation(), Muzzle->GetComponentLocation(), FVector(1, 1, 1)));

				Flash->AddActorWorldOffset(Flash->GetActorQuat() * MuzzleFlashTransform.GetLocation());

				Flash->SetActorRotation(Flash->GetActorQuat() * MuzzleFlashTransform.GetRotation() * FRotator(0, 0, FMath::RandRange(-180, 180)).Quaternion());

				FVector Scale = Flash->GetActorScale3D();

				FVector Scale2 = MuzzleFlashTransform.GetScale3D();

				Flash->SetActorScale3D(FVector(Scale.X * Scale2.X, Scale.Y * Scale2.Y, Scale.Z * Scale2.Z));

				DestroyActorAfterSeconds(Flash, FireLingerTime);
			}

			Projectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, FTransform(Direction.Rotation(), Muzzle->GetComponentLocation(), FVector(1, 1, 1)));

			if (IsValid(Projectile) && Projectile->Implements<UProjectileVR>())
			{
				IProjectileVR::Execute_InitializeProjectile(Projectile, this);
			}

			if (!bInfiniteAmmo)
			{
				CurrentAmmo--;
			}

			if (IsValid(FiringSound))
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), FiringSound, Muzzle->GetComponentLocation());
			}

			OnFire.ExecuteIfBound();

			return IsValid(Projectile);
		}
		else if (bFirstShot || bAutomatic)
		{
			bFirstShot = false;

			if (bSafety && IsValid(SafetySound))
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), SafetySound, Muzzle->GetComponentLocation());
			}
			else if (IsValid(EmptySound))
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), EmptySound, Muzzle->GetComponentLocation());
			}
		}
	}

	Projectile = nullptr;

	return false;
}

// Recursively fires over time until all bursts are expended.
void AGunVR::Burst(int32 RemainingBursts)
{
	if (RemainingBursts > 0)
	{
		bBurstFiring = true;

		int Count = bInfiniteAmmo ? ShotsFired : FMath::Min(ShotsFired, CurrentAmmo);

		if (bFireProjectiles)
		{
			AActor* Projectile;

			for (int j = 0; j < Count; j++)
			{
				Launch(Projectile);
			}

			if (Count == 0)
			{
				Launch(Projectile);
			}
		}
		else
		{
			FHitResult Hit;

			for (int j = 0; j < Count; j++)
			{
				Fire(Hit);
			}

			if (Count == 0)
			{
				Fire(Hit);
			}
		}

		FTimerDelegate TimerDelegate = FTimerDelegate();

		TimerDelegate.BindLambda([=, this]() { Burst(RemainingBursts - 1); });

		FTimerHandle Timer;

		GetWorld()->GetTimerManager().SetTimer(Timer, TimerDelegate, BurstRate, false);
	}
	else
	{
		bBurstFiring = false;
	}
}

// Inserts a magazine into the reload chamber.
bool AGunVR::InsertMagazine(UGrabbableVR* Magazine)
{
	if (!IsValid(CurrentMagazine) && IsValid(Magazine) && IsValid(AmmoClass) && Magazine->GetOwner()->IsA(AmmoClass) && (!IsValid(EmptyMagazineClass) || !Magazine->GetOwner()->IsA(EmptyMagazineClass)))
	{
		CurrentMagazine = Magazine;

		CurrentMagazine->SetGrabActive(false);

		CurrentMagazine->Drop(false);

		CurrentMagazine->GetPrimaryCollider()->SetSimulatePhysics(false);

		CurrentMagazine->GetPrimaryCollider()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		CurrentMagazine->GetPrimaryCollider()->SetEnableGravity(false);

		CurrentMagazine->GetOwner()->SetActorEnableCollision(false);

		if (IsValid(AmmoPivot))
		{
			CurrentMagazine->GetOwner()->SetActorLocationAndRotation(AmmoPivot->GetComponentLocation(), AmmoPivot->GetComponentQuat());

			CurrentMagazine->GetOwner()->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}

		return true;
	}

	return false;
}

// Removes the magazine from the reload chamber.
bool AGunVR::EjectMagazine()
{
	if (IsValid(CurrentMagazine))
	{
		CurrentAmmo = 0;

		if (IsValid(EmptyMagazineClass))
		{
			GetWorld()->SpawnActor<AActor>(EmptyMagazineClass, FTransform(CurrentMagazine->GetOwner()->GetActorRotation(), CurrentMagazine->GetOwner()->GetActorLocation(), CurrentMagazine->GetOwner()->GetActorScale3D()));
		}

		CurrentMagazine->GetOwner()->Destroy();

		CurrentMagazine = nullptr;

		if (IsValid(EjectSound) && IsValid(AmmoPivot))
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), EjectSound, AmmoPivot->GetComponentLocation());
		}

		return true;
	}

	return false;
}

// Disables firing until the trigger is released.
// This is useful for preventing misfires when the player grabs the gun.
// Bind it to OnGrab().
void AGunVR::AwaitTriggerRelease()
{
	bAwaitTriggerRelease = true;
}

// Resets and returns the laser sight's location.
FVector AGunVR::ResetLaserSight()
{
	if (IsValid(LaserSight))
	{
		LaserSightStart = LaserSight->GetRelativeLocation();
	}

	return LaserSightStart;
}

// Gets the current percentage of the trigger (0 = unpulled, 1 = pulled).
float AGunVR::GetTriggerPercentage()
{
	float TriggerPercent = 0;

	if (IsValid(GrabComponent))
	{
		if (GrabComponent->IsGrabbedRight())
		{
			if (UHandTrackerVR::IsTrackingLeftHand())
			{
				TriggerPercent = 1 - UHandTrackerVR::GetRightHand()->GetFingerPercentage(EFingerVR::INDEX);
			}
			else
			{
				TriggerPercent = bRightDown;
			}
		}
		else
		{
			if (UHandTrackerVR::IsTrackingRightHand())
			{
				TriggerPercent = 1 - UHandTrackerVR::GetLeftHand()->GetFingerPercentage(EFingerVR::INDEX);
			}
			else
			{
				TriggerPercent = bLeftDown;
			}
		}
	}

	return TriggerPercent;
}

// Returns whether the trigger is currently pulled.
bool AGunVR::IsTriggerPulled()
{
	return GetTriggerPercentage() >= TriggerFirePercentage;
}

// Returns whether the gun is currently firing.
bool AGunVR::IsFiring()
{
	return !bFirstShot;
}

// Returns whether the gun is currently firing in a burst.
bool AGunVR::IsBurstFiring()
{
	return bBurstFiring;
}

// Attempts to shoot the weapon.
// This is called when the trigger is pulled.
// Note: Hits and projectiles will be empty if this weapon burst fires.
bool AGunVR::Shoot(TArray<FHitResult>& Hits, TArray<AActor*>& Projectiles)
{
	bool HasAmmo = CurrentAmmo > 0 || bInfiniteAmmo;

	bool Success = Delay <= 0 && (bFirstShot || bAutomatic);

	if (Success)
	{
		if (ShotsFired > 1 || bBurstFire)
		{
			CurrentSpreadIndex = 0;
		}

		if (bBurstFire)
		{
			Burst(BurstsFired);

			Delay = BurstRate * BurstsFired + FireRate;
		}
		else
		{
			int32 Count = bInfiniteAmmo ? ShotsFired : FMath::Min(ShotsFired, CurrentAmmo);

			if (bFireProjectiles)
			{
				AActor* Projectile;

				for (int i = 0; i < Count; i++)
				{
					if (Launch(Projectile))
					{
						Projectiles.Add(Projectile);
					}
				}

				if (Count == 0)
				{
					if (Launch(Projectile))
					{
						Projectiles.Add(Projectile);
					}
				}
			}
			else
			{
				FHitResult Hit;

				for (int i = 0; i < Count; i++)
				{
					if (Fire(Hit))
					{
						Hits.Add(Hit);
					}
				}

				if (Count == 0)
				{
					if (Fire(Hit))
					{
						Hits.Add(Hit);
					}
				}
			}

			Delay = FireRate;
		}

		if (HasAmmo)
		{
			OnShoot.ExecuteIfBound();

			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

// Loads the given magazine into the gun.
bool AGunVR::Reload(UGrabbableVR* Magazine)
{
	if (!IsValid(CurrentMagazine) && IsValid(Magazine) && IsValid(AmmoClass) && Magazine->GetOwner()->IsA(AmmoClass) && (!IsValid(EmptyMagazineClass) || !Magazine->GetOwner()->IsA(EmptyMagazineClass)))
	{
		bAwaitTriggerRelease = true;

		CurrentAmmo = MaxAmmo;

		InsertMagazine(Magazine);

		if (IsValid(ReloadSound) && IsValid(AmmoPivot))
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ReloadSound, AmmoPivot->GetComponentLocation());
		}

		OnReload.ExecuteIfBound();

		return true;
	}

	return false;
}

// Updates the current state of the gun.
void AGunVR::UpdateGun(float DeltaSeconds)
{
	if (IsValid(GrabComponent) && GrabComponent->IsGrabbed())
	{
		float TriggerPercent = GetTriggerPercentage();

		float Pitch = bSafety ? FMath::Min(VALUE(TriggerPercent, TriggerRotations.X, TriggerRotations.Y), VALUE(0.5, TriggerRotations.X, TriggerRotations.Y)) : VALUE(TriggerPercent, TriggerRotations.Y, TriggerRotations.X);

		if (IsValid(TriggerPivot))
		{
			FRotator TriggerRotation = TriggerPivot->GetRelativeRotation();

			TriggerPivot->SetRelativeRotation(FRotator(Pitch, TriggerRotation.Yaw, TriggerRotation.Roll));
		}

		if (IsValid(LaserSight))
		{
			LaserSight->SetHiddenInGame(false);

			LaserSight->SetRelativeLocation(LaserSightStart);

			FHitResult Hit;

			float Distance = BulletMaxDistance;

			if (UKismetSystemLibrary::LineTraceSingle(this, LaserSight->GetComponentLocation(), LaserSight->GetComponentLocation() + LaserSight->GetForwardVector() * BulletMaxDistance, ETraceTypeQuery::TraceTypeQuery1, true, { this, GetOwner() }, EDrawDebugTrace::None, Hit, true))
			{
				Distance = Hit.Distance;
			}

			LaserSight->SetWorldLocation(LaserSight->GetComponentLocation() + LaserSight->GetForwardVector() * (Distance / 2));

			FVector Scale = LaserSight->GetComponentScale();

			Scale.X = Distance / 100;

			LaserSight->SetWorldScale3D(Scale);
		}

		if (CurrentAmmo <= 0 && bAutoEjectMagazine)
		{
			EjectMagazine();
		}

		if (IsTriggerPulled())
		{
			if (!bAwaitTriggerRelease)
			{
				TArray<FHitResult> Hits;

				TArray<AActor*> Projectiles;

				Shoot(Hits, Projectiles);
			}
		}
		else if (!bBurstFiring)
		{
			bAwaitTriggerRelease = false;

			bFirstShot = true;

			Delay = FMath::Min(Delay, TapFireRate);
		}

		if (CurrentAmmo <= 0 && !bInfiniteAmmo && IsValid(AmmoClass) && IsValid(AmmoCollider))
		{
			if (IsValid(UGrabbableVR::GetRightGrabbedObject()) && UGrabbableVR::GetRightGrabbedObject()->GetOwner()->IsA(AmmoClass) && (!IsValid(EmptyMagazineClass) || !UGrabbableVR::GetRightGrabbedObject()->GetOwner()->IsA(EmptyMagazineClass)))
			{
				if (AmmoCollider->IsOverlappingActor(UGrabbableVR::GetRightGrabbedObject()->GetOwner()))
				{
					Reload(UGrabbableVR::GetRightGrabbedObject());
				}
			}
			else if (IsValid(UGrabbableVR::GetLeftGrabbedObject()) && UGrabbableVR::GetLeftGrabbedObject()->GetOwner()->IsA(AmmoClass) && (!IsValid(EmptyMagazineClass) || !UGrabbableVR::GetLeftGrabbedObject()->GetOwner()->IsA(EmptyMagazineClass)))
			{
				if (AmmoCollider->IsOverlappingActor(UGrabbableVR::GetLeftGrabbedObject()->GetOwner()))
				{
					Reload(UGrabbableVR::GetLeftGrabbedObject());
				}
			}
		}

		if (IsValid(AmmoDisplayText))
		{
			AmmoDisplayText->SetText(FText::FromString(bInfiniteAmmo ? "" : FString::FromInt(CurrentAmmo)));
		}
	}
	else
	{
		if (IsValid(TriggerPivot))
		{
			FRotator TriggerRotation = TriggerPivot->GetRelativeRotation();

			TriggerPivot->SetRelativeRotation(FRotator(VALUE(0.5, TriggerRotations.X, TriggerRotations.Y), TriggerRotation.Yaw, TriggerRotation.Roll));
		}

		if (IsValid(LaserSight))
		{
			LaserSight->SetHiddenInGame(true);
		}

		if (!bBurstFiring)
		{
			bFirstShot = true;

			Delay = FMath::Min(Delay, TapFireRate);
		}
	}

	Delay -= DeltaSeconds;
}

// Spawns a decal at the given hit point.
AActor* AGunVR::SpawnDecal(FHitResult Hit)
{
	if (IsValid(DecalClass))
	{
		AActor* Decal = GetWorld()->SpawnActor<AActor>(DecalClass, FTransform(Hit.ImpactNormal.Rotation(), Hit.ImpactPoint, FVector(1, 1, 1)));

		if (IsValid(Hit.GetComponent()))
		{
			Decal->AttachToComponent(Hit.GetComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
		else if (IsValid(Hit.GetActor()))
		{
			Decal->AttachToActor(Hit.GetActor(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}

		Decal->SetActorLocationAndRotation(Hit.ImpactPoint, Hit.ImpactNormal.Rotation());

		return Decal;
	}

	return nullptr;
}

// Spawns a new AGunVR actor into the world.
AGunVR* AGunVR::SpawnGunVR(UClass* GunClass, FTransform SpawnTransform,
	FVector2D _TriggerRotations, UClass* _AmmoClass, UGrabbableVR* _CurrentMagazine, UClass* _EmptyMagazineClass, UInputAction* LeftShootButton,
	UInputAction* RightShootButton, bool Safety, float _TriggerFirePercentage, bool FireProjectiles, UClass* _ProjectileClass, bool Penetrate,
	float _BulletMaxDistance, float _Damage, bool Automatic, float _TapFireRate, float _FireRate, int32 _ShotsFired, bool FirstShotAccuracy,
	float _FirstShotDelay, bool RandomSpread, FVector2D _Spread, bool BurstFire, int32 _BurstsFired, float _BurstRate, bool InfiniteAmmo,
	int32 _CurrentAmmo, int32 _MaxAmmo, bool AutoEjectMagazine, USoundBase* _FiringSound, USoundBase* _EmptySound, USoundBase* _EjectSound,
	USoundBase* _ReloadSound, USoundBase* _SafetySound, float _FireLingerTime, UClass* _BeamClass, UClass* _MuzzleFlashClass,
	FTransform _MuzzleFlashTransform, UClass* _DecalClass, FLinearColor _GunColor)
{
	if (!IsValid(GWorld))
	{
		return nullptr;
	}

	AGunVR* NewGunVR = GWorld->SpawnActor<AGunVR>(GunClass, SpawnTransform);

	NewGunVR->PrimaryActorTick.bCanEverTick = true;

	NewGunVR->PrimaryActorTick.TickGroup = ETickingGroup::TG_StartPhysics;

	NewGunVR->PrimaryActorTick.bHighPriority = true;

	NewGunVR->GrabComponent = nullptr;

	NewGunVR->Muzzle = nullptr;

	NewGunVR->TriggerPivot = nullptr;

	NewGunVR->TriggerRotations = _TriggerRotations;

	NewGunVR->AmmoClass = _AmmoClass;

	NewGunVR->AmmoPivot = nullptr;

	NewGunVR->AmmoCollider = nullptr;

	NewGunVR->CurrentMagazine = _CurrentMagazine;

	NewGunVR->EmptyMagazineClass = _EmptyMagazineClass;

	NewGunVR->IA_Shoot_Button_Left = LeftShootButton;

	NewGunVR->IA_Shoot_Button_Right = RightShootButton;

	NewGunVR->bSafety = Safety;

	NewGunVR->TriggerFirePercentage = _TriggerFirePercentage;

	NewGunVR->bFireProjectiles = FireProjectiles;

	NewGunVR->ProjectileClass = _ProjectileClass;

	NewGunVR->bPenetrate = Penetrate;

	NewGunVR->BulletMaxDistance = _BulletMaxDistance;

	NewGunVR->Damage = 100;

	NewGunVR->bAutomatic = Automatic;

	NewGunVR->TapFireRate = _TapFireRate;

	NewGunVR->FireRate = _FireRate;

	NewGunVR->ShotsFired = _ShotsFired;

	NewGunVR->bFirstShotAccuracy = FirstShotAccuracy;

	NewGunVR->FirstShotDelay = _FirstShotDelay;

	NewGunVR->bRandomSpread = RandomSpread;

	NewGunVR->Spread = _Spread;

	NewGunVR->FixedSpreadPattern = TArray<FVector2D>();

	NewGunVR->bBurstFire = BurstFire;

	NewGunVR->BurstsFired = _BurstsFired;

	NewGunVR->BurstRate = _BurstRate;

	NewGunVR->bInfiniteAmmo = InfiniteAmmo;

	NewGunVR->CurrentAmmo = _CurrentAmmo;

	NewGunVR->MaxAmmo = _MaxAmmo;

	NewGunVR->bAutoEjectMagazine = AutoEjectMagazine;

	NewGunVR->FiringSound = _FiringSound;

	NewGunVR->EmptySound = _EmptySound;

	NewGunVR->EjectSound = _EjectSound;

	NewGunVR->ReloadSound = _ReloadSound;

	NewGunVR->SafetySound = _SafetySound;

	NewGunVR->OnFire = FGunDelegateVR();

	NewGunVR->OnShoot = FGunDelegateVR();

	NewGunVR->OnReload = FGunDelegateVR();

	NewGunVR->FireLingerTime = _FireLingerTime;

	NewGunVR->BeamClass = _BeamClass;

	NewGunVR->MuzzleFlashClass = _MuzzleFlashClass;

	NewGunVR->MuzzleFlashTransform = _MuzzleFlashTransform;

	NewGunVR->DecalClass = _DecalClass;

	NewGunVR->LaserSight = nullptr;

	NewGunVR->Flashlight = nullptr;

	NewGunVR->AmmoDisplayText = nullptr;

	NewGunVR->GunColor = _GunColor;

	NewGunVR->Delay = 0;

	NewGunVR->bFirstShot = false;

	NewGunVR->CurrentSpreadIndex = 0;

	NewGunVR->bBurstFiring = false;

	NewGunVR->bAwaitTriggerRelease = false;

	NewGunVR->LaserSightStart = FVector();

	NewGunVR->bLeftDown = 0;

	NewGunVR->bRightDown = 0;

	NewGunVR->LeftPress = nullptr;

	NewGunVR->RightPress = nullptr;

	NewGunVR->LeftRelease = nullptr;

	NewGunVR->RightRelease = nullptr;

	return NewGunVR;
}

// Automatically called when this actor is spawned from a GunVR class.
void IProjectileVR::InitializeProjectile_Implementation(AGunVR* FiredFrom) { }
