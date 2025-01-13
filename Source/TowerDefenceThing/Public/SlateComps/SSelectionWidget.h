// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class TOWERDEFENCETHING_API SSelectionWidget : public SCompoundWidget {
public:
	SLATE_BEGIN_ARGS(SSelectionWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	void SetColourRed();
	void SetColourGreen();
	~SSelectionWidget();

private:
	FSlateColorBrush OutlineBrush = FSlateColorBrush(FLinearColor::Transparent);
};
