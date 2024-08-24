
// Name
// Creator

// REQUIREMENT: MyEditorUtilityWidget.h

#if WITH_EDITOR

// Include this heading to use the class
#include "Boilerplate/MyEditorUtilityWidget.h"


// CONSTRUCTORS

// Object initializer constructor.
UMyEditorUtilityWidget::UMyEditorUtilityWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

// New constructors here


// UNREAL FUNCTIONS

// Called when the widget is created.
void UMyEditorUtilityWidget::NativeConstruct()
{
	// Calls the base class's function.
	Super::NativeConstruct();
}

// Called every frame while this widget is active.
void UMyEditorUtilityWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	// Calls the base class's function.
	Super::NativeTick(MyGeometry, InDeltaTime);
}

// Called when the widget is destroyed.
void UMyEditorUtilityWidget::NativeDestruct()
{
	// Calls the base class's function.
	Super::NativeDestruct();
}


// FUNCTIONS

// New functions here

#endif
