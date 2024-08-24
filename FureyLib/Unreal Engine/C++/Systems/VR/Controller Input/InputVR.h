
// VR Controller Input Interface Script
// by Kyle Furey

// REQUIREMENT: InputVR.cpp

#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Math/Vector2D.h"
#include "InputVR.generated.h"

// Include this heading to use the interface
// #include "InputVR.h"

/** Each button input from standard VR controllers. */
UENUM(BlueprintType, Category = "InputVR")
enum class EButtonVR : uint8
{
	X_BUTTON				UMETA(DisplayName = "X Button"),
	Y_BUTTON				UMETA(DisplayName = "Y Button"),
	B_BUTTON				UMETA(DisplayName = "B Button"),
	A_BUTTON				UMETA(DisplayName = "A Button"),
	TRIGGER_LEFT			UMETA(DisplayName = "Left Trigger"),
	TRIGGER_RIGHT			UMETA(DisplayName = "Right Trigger"),
	SHOULDER_LEFT			UMETA(DisplayName = "Left Shoulder"),
	SHOULDER_RIGHT			UMETA(DisplayName = "Right Shoulder"),
	JOYSTICK_BUTTON_LEFT	UMETA(DisplayName = "Left Joystick Button"),
	JOYSTICK_BUTTON_RIGHT	UMETA(DisplayName = "Right Joystick Button"),
	SPECIAL_BUTTON_LEFT		UMETA(DisplayName = "Left Special Button"),
	SPECIAL_BUTTON_RIGHT	UMETA(DisplayName = "Right Special Button"),
	MAX						UMETA(Hidden)
};

// This class does not need to be modified. Do not inherit from this class.
UINTERFACE(Blueprintable, BlueprintType, MinimalAPI)
class UInputVR : public UInterface
{
	GENERATED_BODY()
};

// Inherit from the following interface to implement it.

/**
* Indicates interaction with VR controller input.
* Inherit from this interface to configure controller input events with a object.
*/
class MYGAME_API IInputVR
{
	GENERATED_BODY()

protected:

	// IINPUTVR VARIABLES

	/**
	* A list of all objects that implement this interface. Each new implemented interface should be added to this.
	* OnFoundControllers() is automatically called when the controllers are first found.
	* Call ReceiveControllerInput() to initialize an IInputVR object.
	* Call StopControllerInput() to remove an IInputVR object.
	*/
	static TSet<UObject*> Implementations;

	/** Whether or not controllers have been found in the world. */
	static bool FoundControllers;

public:

	// IINPUTVR FUNCTIONS

	/**
	* Call this function when this object is created to start receive controller input.
	* Make sure to call StopControllerInput() when this object is destroyed.
	*/
	void ReceiveControllerInput();

	/**
	* Call this function when this object is destroyed to stop receiving controller input.
	* Make sure to call ReceiveControllerInput() when this object is created.
	*/
	void StopControllerInput();


	// IINPUTVR EVENTS

	/**
	* Automatically called when VR controllers are successfully found.
	* ReceiveControllerInput() must have been called during this object's creation.
	* StopControllerInput() must be called when this object is destroyed.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "InputVR")
	void OnFoundControllers();
	virtual void OnFoundControllers_Implementation();

	/**
	* Automatically called when VR controllers are tracked.
	* ReceiveControllerInput() must have been called during this object's creation.
	* StopControllerInput() must be called when this object is destroyed.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "InputVR")
	void OnControllerTracked(bool bIsRight);
	virtual void OnControllerTracked_Implementation(bool bIsRight);

	/**
	* Automatically called when VR controllers are lost.
	* ReceiveControllerInput() must have been called during this object's creation.
	* StopControllerInput() must be called when this object is destroyed.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "InputVR")
	void OnControllerLost(bool bIsRight);
	virtual void OnControllerLost_Implementation(bool bIsRight);

	/**
	* Automatically called when a button(s) is pressed on a VR controller.
	* For Oculus controllers: X (bottom) and Y (top) are on the left, and B (top) and A (bottom) are on the right.
	* ReceiveControllerInput() must have been called during this object's creation.
	* StopControllerInput() must be called when this object is destroyed.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "InputVR")
	void OnButtonPressed(bool X, bool Y, bool B, bool A);
	virtual void OnButtonPressed_Implementation(bool X, bool Y, bool B, bool A);

	/**
	* Automatically called when a button(s) is held down on a VR controller.
	* For Oculus controllers: X (bottom) and Y (top) are on the left, and B (top) and A (bottom) are on the right.
	* ReceiveControllerInput() must have been called during this object's creation.
	* StopControllerInput() must be called when this object is destroyed.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "InputVR")
	void OnButtonHeld(bool X, bool Y, bool B, bool A);
	virtual void OnButtonHeld_Implementation(bool X, bool Y, bool B, bool A);

	/**
	* Automatically called when a button(s) is released on a VR controller.
	* For Oculus controllers: X (bottom) and Y (top) are on the left, and B (top) and A (bottom) are on the right.
	* ReceiveControllerInput() must have been called during this object's creation.
	* StopControllerInput() must be called when this object is destroyed.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "InputVR")
	void OnButtonReleased(bool X, bool Y, bool B, bool A);
	virtual void OnButtonReleased_Implementation(bool X, bool Y, bool B, bool A);

	/**
	* Automatically called when a trigger(s) is pressed on a VR controller.
	* ReceiveControllerInput() must have been called during this object's creation.
	* StopControllerInput() must be called when this object is destroyed.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "InputVR")
	void OnTriggerPressed(bool Left, float LeftAnalog, bool Right, float RightAnalog);
	virtual void OnTriggerPressed_Implementation(bool Left, float LeftAnalog, bool Right, float RightAnalog);

	/**
	* Automatically called when a trigger(s) is held down on a VR controller.
	* ReceiveControllerInput() must have been called during this object's creation.
	* StopControllerInput() must be called when this object is destroyed.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "InputVR")
	void OnTriggerHeld(bool Left, float LeftAnalog, bool Right, float RightAnalog);
	virtual void OnTriggerHeld_Implementation(bool Left, float LeftAnalog, bool Right, float RightAnalog);

	/**
	* Automatically called when a trigger(s) is released on a VR controller.
	* ReceiveControllerInput() must have been called during this object's creation.
	* StopControllerInput() must be called when this object is destroyed.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "InputVR")
	void OnTriggerReleased(bool Left, float LeftAnalog, bool Right, float RightAnalog);
	virtual void OnTriggerReleased_Implementation(bool Left, float LeftAnalog, bool Right, float RightAnalog);

	/**
	* Automatically called when a shoulder(s) is pressed on a VR controller.
	* ReceiveControllerInput() must have been called during this object's creation.
	* StopControllerInput() must be called when this object is destroyed.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "InputVR")
	void OnShoulderPressed(bool Left, float LeftAnalog, bool Right, float RightAnalog);
	virtual void OnShoulderPressed_Implementation(bool Left, float LeftAnalog, bool Right, float RightAnalog);

	/**
	* Automatically called when a shoulder(s) is held down on a VR controller.
	* ReceiveControllerInput() must have been called during this object's creation.
	* StopControllerInput() must be called when this object is destroyed.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "InputVR")
	void OnShoulderHeld(bool Left, float LeftAnalog, bool Right, float RightAnalog);
	virtual void OnShoulderHeld_Implementation(bool Left, float LeftAnalog, bool Right, float RightAnalog);

	/**
	* Automatically called when a shoulder(s) is released on a VR controller.
	* ReceiveControllerInput() must have been called during this object's creation.
	* StopControllerInput() must be called when this object is destroyed.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "InputVR")
	void OnShoulderReleased(bool Left, float LeftAnalog, bool Right, float RightAnalog);
	virtual void OnShoulderReleased_Implementation(bool Left, float LeftAnalog, bool Right, float RightAnalog);

	/**
	* Automatically called when the left joystick is moved or pressed on a VR controller.
	* ReceiveControllerInput() must have been called during this object's creation.
	* StopControllerInput() must be called when this object is destroyed.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "InputVR")
	void OnLeftJoystickMoved(FVector2D Direction, float Magnitude, bool bIsPressed);
	virtual void OnLeftJoystickMoved_Implementation(FVector2D Direction, float Magnitude, bool bIsPressed);

	/**
	* Automatically called when the right joystick is moved or pressed on a VR controller.
	* ReceiveControllerInput() must have been called during this object's creation.
	* StopControllerInput() must be called when this object is destroyed.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "InputVR")
	void OnRightJoystickMoved(FVector2D Direction, float Magnitude, bool bIsPressed);
	virtual void OnRightJoystickMoved_Implementation(FVector2D Direction, float Magnitude, bool bIsPressed);

	/**
	* Automatically called when a special button is pressed on a VR controller.
	* On Oculus controllers: the Options button is on the left and the Meta button is on the right.
	* ReceiveControllerInput() must have been called during this object's creation.
	* StopControllerInput() must be called when this object is destroyed.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "InputVR")
	void OnSpecialButtonPressed(bool bIsRight);
	virtual void OnSpecialButtonPressed_Implementation(bool bIsRight);

	/**
	* Automatically called when a special button is held down on a VR controller.
	* On Oculus controllers: the Options button is on the left and the Meta button is on the right.
	* ReceiveControllerInput() must have been called during this object's creation.
	* StopControllerInput() must be called when this object is destroyed.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "InputVR")
	void OnSpecialButtonHeld(bool bIsRight);
	virtual void OnSpecialButtonHeld_Implementation(bool bIsRight);

	/**
	* Automatically called when a special button is released on a VR controller.
	* On Oculus controllers: the Options button is on the left and the Meta button is on the right.
	* ReceiveControllerInput() must have been called during this object's creation.
	* StopControllerInput() must be called when this object is destroyed.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "InputVR")
	void OnSpecialButtonReleased(bool bIsRight);
	virtual void OnSpecialButtonReleased_Implementation(bool bIsRight);
};
