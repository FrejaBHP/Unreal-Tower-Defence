// Dragons rule ok


#include "SlateComps/SSelectionWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSelectionWidget::Construct(const FArguments& InArgs) {
	GreenBrush.DrawAs = ESlateBrushDrawType::RoundedBox;
	GreenBrush.OutlineSettings.Width = 5.f;
	GreenBrush.OutlineSettings.Color = FLinearColor::Red;
	GreenBrush.OutlineSettings.RoundingType = ESlateBrushRoundingType::HalfHeightRadius;

	ChildSlot
	[
		SNew(SBorder)
		.BorderImage(&GreenBrush)
		.Content()
		[
			SAssignNew(SelectionBox, SBox)
		]
	];
}

void SSelectionWidget::SetSelectionRadius(float newRadius) {
	if (newRadius > 0.f) {
		SelectionRadius = newRadius;
	}
	else {
		SelectionRadius = 0.f;
	}
	ApplyRadius();
}

void SSelectionWidget::ApplyRadius() const {
	SelectionBox->SetMinDesiredWidth(SelectionRadius);
	SelectionBox->SetMinDesiredHeight(SelectionRadius);
	SelectionBox->SetMaxDesiredWidth(SelectionRadius);
	SelectionBox->SetMaxDesiredHeight(SelectionRadius);
}

SSelectionWidget::~SSelectionWidget() {
	SelectionBox.Reset();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
