
// VR Controller Input Interface Script
// by Kyle Furey

// REQUIREMENT: InputVR.h

// Include this heading to use the interface
#include "InputVR.h"


// IINPUTVR FUNCTIONS

// Call this function when this object is created to start receive controller input.
// Make sure to call StopControllerInput() when this object is destroyed.
void IInputVR::ReceiveControllerInput()
{
	Implementations.Add(_getUObject());

	if (FoundControllers)
	{
		Execute_OnFoundControllers(_getUObject());
	}
}

// Call this function when this object is destroyed to stop receiving controller input.
// Make sure to call ReceiveControllerInput() when this object is created.
void IInputVR::StopControllerInput()
{
	Implementations.Remove(_getUObject());

	if (Implementations.Num() <= 0)
	{
		FoundControllers = false;
	}
}


// IINPUTVR EVENTS

// Automatically called when VR controllers are successfully found.
// ReceiveControllerInput() must have been called during this object's creation.
// StopControllerInput() must be called when this object is destroyed.
void IInputVR::OnFoundControllers_Implementation() { }

// Automatically called when VR controllers are tracked.
// ReceiveControllerInput() must have been called during this object's creation.
// StopControllerInput() must be called when this object is destroyed.
void IInputVR::OnControllerTracked_Implementation(bool bIsRight) { }

// Automatically called when VR controllers are lost.
// ReceiveControllerInput() must have been called during this object's creation.
// StopControllerInput() must be called when this object is destroyed.
void IInputVR::OnControllerLost_Implementation(bool bIsRight) { }

// Automatically called when a button(s) is pressed on a VR controller.
// For Oculus controllers: X (bottom) and Y (top) are on the left, and B (top) and A (bottom) are on the right.
// ReceiveControllerInput() must have been called during this object's creation.
// StopControllerInput() must be called when this object is destroyed.
void IInputVR::OnButtonPressed_Implementation(bool X, bool Y, bool B, bool A) { }

// Automatically called when a button(s) is held down on a VR controller.
// For Oculus controllers: X (bottom) and Y (top) are on the left, and B (top) and A (bottom) are on the right.
// ReceiveControllerInput() must have been called during this object's creation.
// StopControllerInput() must be called when this object is destroyed.
void IInputVR::OnButtonHeld_Implementation(bool X, bool Y, bool B, bool A) { }

// Automatically called when a button(s) is released on a VR controller.
// For Oculus controllers: X (bottom) and Y (top) are on the left, and B (top) and A (bottom) are on the right.
// ReceiveControllerInput() must have been called during this object's creation.
// StopControllerInput() must be called when this object is destroyed.
void IInputVR::OnButtonReleased_Implementation(bool X, bool Y, bool B, bool A) { }

// Automatically called when a trigger(s) is pressed on a VR controller.
// ReceiveControllerInput() must have been called during this object's creation.
// StopControllerInput() must be called when this object is destroyed.
void IInputVR::OnTriggerPressed_Implementation(bool Left, float LeftAnalog, bool Right, float RightAnalog) { }

// Automatically called when a trigger(s) is held down on a VR controller.
// ReceiveControllerInput() must have been called during this object's creation.
// StopControllerInput() must be called when this object is destroyed.
void IInputVR::OnTriggerHeld_Implementation(bool Left, float LeftAnalog, bool Right, float RightAnalog) { }

// Automatically called when a trigger(s) is released on a VR controller.
// ReceiveControllerInput() must have been called during this object's creation.
// StopControllerInput() must be called when this object is destroyed.
void IInputVR::OnTriggerReleased_Implementation(bool Left, float LeftAnalog, bool Right, float RightAnalog) { }

// Automatically called when a shoulder(s) is pressed on a VR controller.
// ReceiveControllerInput() must have been called during this object's creation.
// StopControllerInput() must be called when this object is destroyed.
void IInputVR::OnShoulderPressed_Implementation(bool Left, float LeftAnalog, bool Right, float RightAnalog) { }

// Automatically called when a shoulder(s) is held down on a VR controller.
// ReceiveControllerInput() must have been called during this object's creation.
// StopControllerInput() must be called when this object is destroyed.
void IInputVR::OnShoulderHeld_Implementation(bool Left, float LeftAnalog, bool Right, float RightAnalog) { }

// Automatically called when a shoulder(s) is released on a VR controller.
// ReceiveControllerInput() must have been called during this object's creation.
// StopControllerInput() must be called when this object is destroyed.
void IInputVR::OnShoulderReleased_Implementation(bool Left, float LeftAnalog, bool Right, float RightAnalog) { }

// Automatically called when the left joystick is moved or pressed on a VR controller.
// ReceiveControllerInput() must have been called during this object's creation.
// StopControllerInput() must be called when this object is destroyed.
void IInputVR::OnLeftJoystickMoved_Implementation(FVector2D Direction, float Magnitude, bool bIsPressed) { }

// Automatically called when the right joystick is moved or pressed on a VR controller.
// ReceiveControllerInput() must have been called during this object's creation.
// StopControllerInput() must be called when this object is destroyed.
void IInputVR::OnRightJoystickMoved_Implementation(FVector2D Direction, float Magnitude, bool bIsPressed) { }

// Automatically called when a special button is pressed on a VR controller.
// On Oculus controllers: the Options button is on the left and the Meta button is on the right.
// ReceiveControllerInput() must have been called during this object's creation.
// StopControllerInput() must be called when this object is destroyed.
void IInputVR::OnSpecialButtonPressed_Implementation(bool bIsRight) { }

// Automatically called when a special button is held down on a VR controller.
// On Oculus controllers: the Options button is on the left and the Meta button is on the right.
// ReceiveControllerInput() must have been called during this object's creation.
// StopControllerInput() must be called when this object is destroyed.
void IInputVR::OnSpecialButtonHeld_Implementation(bool bIsRight) { }

// Automatically called when a special button is released on a VR controller.
// On Oculus controllers: the Options button is on the left and the Meta button is on the right.
// ReceiveControllerInput() must have been called during this object's creation.
// StopControllerInput() must be called when this object is destroyed.
void IInputVR::OnSpecialButtonReleased_Implementation(bool bIsRight) { }


// STATIC VARIABLE INITIALIZATION

// A list of all objects that implement this interface.Each new implemented interface should be added to this.
// OnFoundControllers() is automatically called when the controllers are first found.
// Call ReceiveControllerInput() to initialize an IInputVR object.
// Call StopControllerInput() to remove an IInputVR object.
TSet<UObject*> IInputVR::Implementations = TSet<UObject*>();

// Whether or not controllers have been found in the world.
bool IInputVR::FoundControllers = false;
