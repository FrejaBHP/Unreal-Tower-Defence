// Dragons rule ok


#include "SlateComps/SLivesWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SLivesWidget::Construct(const FArguments& InArgs) {
	livesPtr = InArgs._livesPtr;
	font = InArgs._font;

	ChildSlot
	.HAlign(HAlign_Right)
	.VAlign(VAlign_Top)
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		[
			SNew(STextBlock)
			.Font(font)
			.ColorAndOpacity(FSlateColor(FLinearColor::Black))
			.Text_Lambda([this]()->FText { return FText::AsNumber(*livesPtr); })
		]
	];
}

SLivesWidget::~SLivesWidget() {
	//UE_LOG(LogTemp, Warning, TEXT("Lives Widget resources unloaded"));
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
