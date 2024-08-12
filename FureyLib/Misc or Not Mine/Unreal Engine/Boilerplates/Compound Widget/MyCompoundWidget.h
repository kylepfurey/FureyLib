
// Name
// Creator

// REQUIREMENT: MyCompoundWidget.cpp

#pragma once
#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

// Include this heading to use the class
// #include "MyCompoundWidget.h"

/** Template Unreal compound widget script. */
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


	// CONSTRUCTORS AND DESTRUCTOR

	/** Default constructor. */
	SMyCompoundWidget();

	// New constructors here

	/** Destructor. */
	~SMyCompoundWidget();

	
	// UNREAL FUNCTIONS

	/** Constructs this widget with InArgs. */
	void Construct(const FArguments& InArgs);


	// FUNCTIONS

	// New functions here
};
