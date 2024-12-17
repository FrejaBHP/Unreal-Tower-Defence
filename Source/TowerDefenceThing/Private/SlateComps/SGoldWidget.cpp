// Dragons rule ok


#include "SlateComps/SGoldWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SGoldWidget::Construct(const FArguments& InArgs) {
	FSlateFontInfo baseFont = FStyleDefaults::GetFontInfo();
	baseFont.Size = 48.f;
	
	ChildSlot
	.HAlign(HAlign_Left)
	.VAlign(VAlign_Top)
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		[
			SNew(STextBlock)
			.Font(baseFont)
			.ColorAndOpacity(FSlateColor(FLinearColor::Green))
			.Text(this, &SGoldWidget::GetGoldCount)
		]
	];
}

void SGoldWidget::SetGoldCount(int32 gold) {
	Gold = gold;
	GetGoldCount();
}

FText SGoldWidget::GetGoldCount() const {
	return FText::AsNumber(Gold);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
