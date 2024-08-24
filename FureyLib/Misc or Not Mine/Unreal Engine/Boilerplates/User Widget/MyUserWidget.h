
// Name
// Creator

// REQUIREMENT: MyUserWidget.cpp

#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

// Include this heading to use the class
// #include "Boilerplate/MyUserWidget.h"

/** Template Unreal user widget script. */
UCLASS(Blueprintable, BlueprintType)
class MYGAME_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	// VARIABLES

	// New variables here


	// FUNCTIONS

	// New functions here

public:

	// VARIABLES

	// New variables here


	// CONSTRUCTORS

	/** Object initializer constructor. */
	UMyUserWidget(const FObjectInitializer& ObjectInitializer);

	// New constructors here


	// UNREAL FUNCTIONS

	/** Called when the widget is created. */
	virtual void NativeConstruct() override;

	/** Called every frame while this widget is active. */
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	/** Called when the widget is destroyed. */
	virtual void NativeDestruct() override;


	// FUNCTIONS

	// New functions here
};
