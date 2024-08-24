
// VR Hand Tracking Interface Script
// by Kyle Furey

// REQUIREMENT: HandInteractableVR.cpp

#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HandInteractableVR.generated.h"

// Include this heading to use the interface
// #include "HandInteractableVR.h"

// Forward declaration of EGestureVR.
enum class EHandGestureVR : uint8;

// This class does not need to be modified. Do not inherit from this class.
UINTERFACE(Blueprintable, BlueprintType, MinimalAPI)
class UHandInteractableVR : public UInterface
{
	GENERATED_BODY()
};

// Inherit from the following interface to implement it.

/**
* Indicates interaction with VR hands.
* Inherit from this interface to configure hand tracking functionality with a object.
*/
class MYGAME_API IHandInteractableVR
{
	GENERATED_BODY()

protected:

	// IHANDINTERACTABLEVR VARIABLES

	/**
	* A list of all objects that implement this interface. Each new implemented interface should be added to this.
	* OnSetHands() is automatically called when hands are initialized.
	* Call ImplementHandTracking() to initialize an IHandInteractableVR object.
	* Call RemoveHandTracking() to remove an IHandInteractableVR object.
	*/
	static TSet<UObject*> Implementations;

	/** Whether or not hands have been set in the world. */
	static bool HandsSet;

public:

	// IHANDINTERACTABLEVR FUNCTIONS

	/**
	* Call this function when this object is created to enable hand tracking.
	* Make sure to call RemoveHandTracking() when this object is destroyed.
	*/
	void ImplementHandTracking();

	/**
	* Call this function when this object is destroyed to remove hand tracking.
	* Make sure to call ImplementHandTracking() when this object is created.
	*/
	void RemoveHandTracking();


	// IHANDINTERACTABLEVR EVENTS

	/**
	* Automatically called when VR hands are successfully initialized on the implemented interface.
	* ImplementHandTracking() must have been called during this object's creation.
	* RemoveHandTracking() must be called when this object is destroyed.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "HandInteractableVR")
	void OnSetHands();
	virtual void OnSetHands_Implementation();

	/**
	* Automatically called when VR hands are tracked.
	* ImplementHandTracking() must have been called during this object's creation.
	* RemoveHandTracking() must be called when this object is destroyed.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "HandInteractableVR")
	void OnHandTracked(bool bIsRight);
	virtual void OnHandTracked_Implementation(bool bIsRight);

	/**
	* Automatically called when VR hands are lost.
	* ImplementHandTracking() must have been called during this object's creation.
	* RemoveHandTracking() must be called when this object is destroyed.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "HandInteractableVR")
	void OnHandLost(bool bIsRight);
	virtual void OnHandLost_Implementation(bool bIsRight);

	/**
	* Automatically called when VR hands detect a new gesture.
	* Use a switch statement on EGestureVR to write logic for each gesture.
	* ImplementHandTracking() must have been called during this object's creation.
	* RemoveHandTracking() must be called when this object is destroyed.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "HandInteractableVR")
	void OnNewGesture(bool bIsRight, EHandGestureVR NewGesture);
	virtual void OnNewGesture_Implementation(bool bIsRight, EHandGestureVR NewGesture);

	/**
	* Automatically called each tick while VR hands detect a gesture.
	* Use a switch statement on EGestureVR to write logic for each gesture.
	* ImplementHandTracking() must have been called during this object's creation.
	* RemoveHandTracking() must be called when this object is destroyed.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "HandInteractableVR")
	void OnGestureTick(bool bIsRight, EHandGestureVR Gesture);
	virtual void OnGestureTick_Implementation(bool bIsRight, EHandGestureVR NewGesture);

	/**
	* Automatically called when VR hands no longer detect a gesture.
	* Use a switch statement on EGestureVR to write logic for each gesture.
	* ImplementHandTracking() must have been called during this object's creation.
	* RemoveHandTracking() must be called when this object is destroyed.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "HandInteractableVR")
	void OnStopGesture(bool bIsRight, EHandGestureVR StoppedGesture);
	virtual void OnStopGesture_Implementation(bool bIsRight, EHandGestureVR NewGesture);
};
