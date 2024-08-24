
// Static PC and Mobile VR Functions Script
// by Kyle Furey

// REQUIREMENT: PlatformVR.cpp

#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/Light.h"
#include "Components/LightComponent.h"
#include "PlatformVR.generated.h"

// Include this heading to use the library
// #include "PlatformVR.h"

// Whether the platform is a mobile platform.
#define IS_MOBILE PLATFORM_ANDROID

// Whether worlds are lit based on the Mobile preview and should be corrected accordingly.
#define MATCH_MOBILE_LIGHTING 1

// The scalar applied to a light's intensity in a scene lit in the PC preview to match the Mobile preview.
#define PC_TO_MOBILE_LIGHT_INTENSITY_SCALAR 3.0

// The scalar applied to a light's intensity in a scene lit in the Mobile preview to match the PC preview.
#define MOBILE_TO_PC_LIGHT_INTENSITY_SCALE (1.0 / PC_TO_MOBILE_LIGHT_INTENSITY_SCALAR)

/** Provides a library of functions used to match a VR game between PC and Android. */
UCLASS(Blueprintable, BlueprintType)
class MYGAME_API UPlatformVR : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	// PLATFORM FUNCTIONS

	/** Returns the name of the current platform. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlatformVR")
	static FString GetPlatform();

	/** Returns whether the current platform is a Mobile device (the game is playing on a VR headset). */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlatformVR", meta = (Keywords = "Is, Mobile, Oculus, Android, VR, Headset"))
	static bool IsMobile();

	/** Returns whether the current platform is a PC (the game is playing on Windows, Mac, or Linux). */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlatformVR", meta = (Keywords = "Is, PC, Windows, Mac, Linux"))
	static bool IsPC();

	/** Returns whether the game is in editor mode. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlatformVR", meta = (Keywords = "Is, Editor, Edit, Mode"))
	static bool IsEditor();


	// LIGHT NORMALIZATION

	/** Multiply this value with a light's intensity value to normalize its brightness between PC and Mobile platforms. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlatformVR")
	static float GetLightScalar();

	/** Updates the intensity of a light to ensure its brightness is consistent between platforms. Call this once. */
	UFUNCTION(BlueprintCallable, Category = "PlatformVR", meta = (Keywords = "Normalize, Light, Lighting"))
	static ALight* NormalizeLight(ALight* Light);

	/** Updates the intensity of a world's lights to ensure its brightness is consistent between platforms. Call this once. */
	UFUNCTION(BlueprintCallable, Category = "PlatformVR", meta = (Keywords = "Normalize, Lights, Lighting"))
	static TArray<ALight*> NormalizeLights(TArray<ALight*> Lights);

	/**
	* Updates the intensity of a world's lights to ensure its brightness is consistent between platforms. Call this once.
	* Returns whether the lights were successfully normalized and all of the lights in the world.
	*/
	UFUNCTION(BlueprintCallable, Category = "PlatformVR")
	static void NormalizeLighting(bool& Success, TArray<ALight*>& Lights);
};
