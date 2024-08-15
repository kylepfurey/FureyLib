
// Name
// Creator

// REQUIREMENT: MyEditorUtilityWidget.cpp

#if WITH_EDITOR

#pragma once
#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "MyEditorUtilityWidget.generated.h"

// Include this heading to use the class
// #include "MyEditorUtilityWidget.h"

/** Template Unreal editor utility widget script. */
UCLASS(Blueprintable, BlueprintType)
class MYGAME_API UMyEditorUtilityWidget : public UUserWidget
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
	UMyEditorUtilityWidget(const FObjectInitializer& ObjectInitializer);

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

#endif
