// Dragons rule ok


#include "SlateComps/SSelectionWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSelectionWidget::Construct(const FArguments& InArgs) {
	OutlineBrush.DrawAs = ESlateBrushDrawType::RoundedBox;
	OutlineBrush.OutlineSettings.Width = 4.f;
	OutlineBrush.OutlineSettings.RoundingType = ESlateBrushRoundingType::HalfHeightRadius;

	ChildSlot
	[
		SNew(SBorder)
		.BorderImage(&OutlineBrush)
		.Content()
		[
			SNew(SBox)
		]
	];
}

void SSelectionWidget::SetColourRed() {
	OutlineBrush.OutlineSettings.Color = FLinearColor::Red;
}

void SSelectionWidget::SetColourGreen() {
	OutlineBrush.OutlineSettings.Color = FLinearColor::Green;
}

SSelectionWidget::~SSelectionWidget() {
	
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
