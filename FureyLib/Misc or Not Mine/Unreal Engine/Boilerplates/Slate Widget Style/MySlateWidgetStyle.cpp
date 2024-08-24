
// Name
// Creator

// REQUIREMENT: MySlateWidgetStyle.h

// Include this heading to use the struct
#include "Boilerplate/MySlateWidgetStyle.h"


// VARIABLES

// Slate style name.
const FName FMySlateStyle::TypeName(TEXT("FMySlateStyle"));


// CONSTRUCTORS AND DESTRUCTOR

// Default constructor.
FMySlateStyle::FMySlateStyle()
{

}

// Destructor.
FMySlateStyle::~FMySlateStyle()
{

}


// UNREAL FUNCTIONS

// Gets the default slate style.
const FMySlateStyle& FMySlateStyle::GetDefault()
{
	static FMySlateStyle Default;

	return Default;
}

// Gets the resources of this slate style.
void FMySlateStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them.
}


// FUNCTIONS

// New functions here
