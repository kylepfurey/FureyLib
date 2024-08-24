
// VR Hand Tracking Interface Script
// by Kyle Furey

// REQUIREMENT: HandInteractableVR.h

// Include this heading to use the interface
#include "VR/Hand Tracking/HandInteractableVR.h"


// IHANDINTERACTABLEVR FUNCTIONS

// Returns whether this object is currently receiving hand tracking input.
bool IHandInteractableVR::IsHandTrackingImplemented()
{
	return Implementations.Contains(_getUObject());
}

// Call this function when this object is created to enable hand tracking.
// Make sure to call RemoveHandTracking() when this object is destroyed.
void IHandInteractableVR::ImplementHandTracking()
{
	Implementations.Add(_getUObject());

	if (HandsSet)
	{
		Execute_OnSetHands(_getUObject());
	}
}

// Call this function when this object is destroyed to remove hand tracking.
// Make sure to call ImplementHandTracking() when this object is created.
void IHandInteractableVR::RemoveHandTracking()
{
	Implementations.Remove(_getUObject());

	if (Implementations.Num() <= 0)
	{
		HandsSet = false;
	}
}


// IHANDINTERACTABLEVR EVENTS

// Automatically called when VR hands are successfully initialized on the implemented interface.
// ImplementHandTracking() must have been called during this object's creation.
// RemoveHandTracking() must be called when this object is destroyed.
void IHandInteractableVR::OnSetHands_Implementation() { }

// Automatically called when VR hands are tracked.
// ImplementHandTracking() must have been called during this object's creation.
// RemoveHandTracking() must be called when this object is destroyed.
void IHandInteractableVR::OnHandTracked_Implementation(bool bIsRight) { }

// Automatically called when VR hands are lost.
// ImplementHandTracking() must have been called during this object's creation.
// RemoveHandTracking() must be called when this object is destroyed.
void IHandInteractableVR::OnHandLost_Implementation(bool bIsRight) { }

// Automatically called when VR hands detect a new gesture.
// Use a switch statement on EGestureVR to write logic for each gesture.
// ImplementHandTracking() must have been called during this object's creation.
// RemoveHandTracking() must be called when this object is destroyed.
void IHandInteractableVR::OnNewGesture_Implementation(bool bIsRight, EHandGestureVR NewGesture) { }

// Automatically called each tick while VR hands detect a gesture.
// Use a switch statement on EGestureVR to write logic for each gesture.
// ImplementHandTracking() must have been called during this object's creation.
// RemoveHandTracking() must be called when this object is destroyed.
void IHandInteractableVR::OnGestureTick_Implementation(bool bIsRight, EHandGestureVR NewGesture) { }

// Automatically called when VR hands no longer detect a gesture.
// Use a switch statement on EGestureVR to write logic for each gesture.
// ImplementHandTracking() must have been called during this object's creation.
// RemoveHandTracking() must be called when this object is destroyed.
void IHandInteractableVR::OnStopGesture_Implementation(bool bIsRight, EHandGestureVR NewGesture) { }


// STATIC VARIABLE INITIALIZATION

// A list of all objects that implement this interface. Each new implemented interface should be added to this.
// OnSetHands() is automatically called when hands are initialized.
// Call ImplementHandTracking() to initialize an IHandInteractableVR object.
// Call RemoveHandTracking() to remove an IHandInteractableVR object.
TSet<UObject*> IHandInteractableVR::Implementations = TSet<UObject*>();

// Whether or not hands have been set in the world.
bool IHandInteractableVR::HandsSet = false;
