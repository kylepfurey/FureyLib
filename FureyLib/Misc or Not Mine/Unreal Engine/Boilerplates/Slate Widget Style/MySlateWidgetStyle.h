
// Name
// Creator

// REQUIREMENT: MySlateWidgetStyle.cpp

#pragma once
#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"
#include "MySlateWidgetStyle.generated.h"

// Include this heading to use the struct
// #include "Boilerplate/MySlateWidgetStyle.h"

/** Template Unreal slate widget style script. */
USTRUCT(BlueprintType)
struct MYGAME_API FMySlateStyle : public FSlateWidgetStyle
{
	GENERATED_BODY()

public:

	// VARIABLES

	/** This slate style's name. */
	static const FName TypeName;

	// New variables here


	// CONSTRUCTORS AND DESTRUCTOR

	/** Default constructor. */
	FMySlateStyle();

	// New constructors here

	/** Destructor. */
	virtual ~FMySlateStyle();


	// UNREAL FUNCTIONS

	/** Gets the default slate style. */
	static const FMySlateStyle& GetDefault();

	/** Gets the resources of this slate style. */
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;

	/** Returns the type name of this slate style. */
	virtual const FName GetTypeName() const override { return TypeName; };


	// FUNCTIONS

	// New functions here
};

/** Template Unreal slate widget style script. */
UCLASS(Blueprintable, BlueprintType, hidecategories = Object, MinimalAPI)
class UMySlateWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:

	// VARIABLES

	/** The actual data describing the widget appearance. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Appearance, meta = (ShowOnlyInnerProperties))
	FMySlateStyle WidgetStyle;

	// New variables here


	// UNREAL FUNCTIONS

	/** Returns the style of this slate widget. */
	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast<const struct FSlateWidgetStyle*>(&WidgetStyle);
	}


	// FUNCTIONS

	// New functions here
};
