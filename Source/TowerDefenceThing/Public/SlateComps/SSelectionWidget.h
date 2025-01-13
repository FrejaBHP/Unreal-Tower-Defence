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
	void SetSelectionRadius(float newRadius);
	~SSelectionWidget();

private:
	FSlateColorBrush GreenBrush = FSlateColorBrush(FLinearColor::Transparent);

	TSharedPtr<SBox> SelectionBox;

	float SelectionRadius { 32.f };
	void ApplyRadius() const;
};
