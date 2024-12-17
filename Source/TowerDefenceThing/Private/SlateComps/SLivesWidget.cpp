// Dragons rule ok


#include "SlateComps/SLivesWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SLivesWidget::Construct(const FArguments& InArgs) {
	Lives = InArgs._LivesPtr;
	Font = InArgs._Font;

	ChildSlot
	.HAlign(HAlign_Right)
	.VAlign(VAlign_Top)
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		[
			SNew(STextBlock)
			.Font(Font)
			.ColorAndOpacity(FSlateColor(FLinearColor::Black))
			.Text(this, &SLivesWidget::GetLivesCount)
		]
	];
}

void SLivesWidget::UpdateLivesCounter() {
	GetLivesCount();
}

FText SLivesWidget::GetLivesCount() const {
	return FText::AsNumber(*Lives);
}

SLivesWidget::~SLivesWidget() {
	//UE_LOG(LogTemp, Warning, TEXT("Lives Widget resources unloaded"));
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
