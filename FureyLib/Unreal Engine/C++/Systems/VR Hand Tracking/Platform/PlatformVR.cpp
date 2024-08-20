
// Static PC and Mobile VR Functions Script
// by Kyle Furey

// REQUIREMENT: PlatformVR.h

// Include this heading to use the library
#include "PlatformVR.h"


// STATIC FUNCTIONS

// Returns the name of the current platform.
FString UPlatformVR::GetPlatform()
{
	return FPlatformProperties::PlatformName();
}

// Returns whether the current platform is a Mobile device (the game is playing on a VR headset).
bool UPlatformVR::IsMobile()
{
#if IS_MOBILE

	return true;

#else

	return false;

#endif
}

// Returns whether the current platform is a PC (the game is playing on Windows, Mac, or Linux).
bool UPlatformVR::IsPC()
{
#if IS_MOBILE

	return false;

#else

	return true;

#endif
}

// Returns whether the game is in editor mode.
bool UPlatformVR::IsEditor()
{
	return GIsEditor;
}

// Multiply this value with a light's intensity value to normalize its brightness between PC and Mobile platforms.
float UPlatformVR::GetLightScalar()
{
	if (GIsEditor)
	{
		return 1;
	}

#if IS_MOBILE

#if MATCH_MOBILE_LIGHTING

	return 1;

#else

	return PC_TO_MOBILE_LIGHT_INTENSITY_SCALAR;

#endif

#else

#if MATCH_MOBILE_LIGHTING

	return MOBILE_TO_PC_LIGHT_INTENSITY_SCALE;

#else

	return 1;

#endif

#endif
}

// Updates the intensity of a light to ensure its brightness is consistent between platforms. Call this once.
ALight* UPlatformVR::NormalizeLight(ALight* Light)
{
	ULightComponent* Component = Light->GetLightComponent();

	Component->SetIntensity(Component->Intensity * GetLightScalar());

	return Light;
}

// Updates the intensity of a world's lights to ensure its brightness is consistent between platforms. Call this once.
TArray<ALight*> UPlatformVR::NormalizeLights(TArray<ALight*> Lights)
{
	for (ALight* Light : Lights)
	{
		ULightComponent* Component = Light->GetLightComponent();

		Component->SetIntensity(Component->Intensity * GetLightScalar());
	}

	return Lights;
}

// •  Updates the intensity of a world's lights to ensure its brightness is consistent between platforms. Call this once.
// •  Returns whether the lights were successfully normalized and all of the lights in the world.
void UPlatformVR::NormalizeLighting(bool& Success, TArray<ALight*>& Lights)
{
	if (!GIsEditor && GWorld != nullptr)
	{
		TArray<AActor*> Actors;

		UGameplayStatics::GetAllActorsOfClass(GWorld, ALight::StaticClass(), Actors);

		for (AActor* Actor : Actors)
		{
			ALight* Light = Cast<ALight>(Actor);

			Lights.Add(Light);

			ULightComponent* Component = Light->GetLightComponent();

			Component->SetIntensity(Component->Intensity * GetLightScalar());

			Success = true;
		}

		if (Success)
		{
			return;
		}
	}

	Success = false;
}
