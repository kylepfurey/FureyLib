
// Name
// Creator

// REQUIREMENT: MyUserWidget.h

// Include this heading to use the class
#include "MyUserWidget.h"


// CONSTRUCTORS

// Object initializer constructor.
UMyUserWidget::UMyUserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

// New constructors here


// UNREAL FUNCTIONS

// Called when the widget is created.
void UMyUserWidget::NativeConstruct()
{
	// Calls the base class's function.
	Super::NativeConstruct();
}

// Called every frame while this widget is active.
void UMyUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	// Calls the base class's function.
	Super::NativeTick(MyGeometry, InDeltaTime);
}

// Called when the widget is destroyed.
void UMyUserWidget::NativeDestruct()
{
	// Calls the base class's function.
	Super::NativeDestruct();
}


// FUNCTIONS

// New functions here
