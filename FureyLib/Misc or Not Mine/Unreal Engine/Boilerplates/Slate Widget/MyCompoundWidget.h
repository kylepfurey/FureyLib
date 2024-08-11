
// Name
// Creator

// REQUIREMENT: MyCompoundWidget.cpp

#pragma once
#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

// Include this heading to use the class
// #include "MyCompoundWidget.h"

/** Template Unreal slate widget script. */
class MYGAME_API SMyCompoundWidget : public SCompoundWidget
{
public:

	// ARGUMENTS

	// Slate arguments.
	SLATE_BEGIN_ARGS(SMyCompoundWidget)
	{
		// Arguments here.
	}
	SLATE_END_ARGS()


	// CONSTRUCTORS

	/** Default constructor. */
	SMyCompoundWidget();

	/** Constructs this widget with InArgs. */
	void Construct(const FArguments& InArgs);


	// FUNCTIONS

	// New functions here
};
