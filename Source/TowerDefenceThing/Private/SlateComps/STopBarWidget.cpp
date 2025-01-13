// Dragons rule ok


#include "SlateComps/STopBarWidget.h"
#include "Widgets/Layout/SScaleBox.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void STopBarWidget::Construct(const FArguments& InArgs) {
	TDUIResources = InArgs._tdUIResources;
	Lives = InArgs._livesPtr;
	Remaining = InArgs._remainingPtr;
	WaveNumber = InArgs._waveNumberPtr;

	BackgroundBrush.DrawAs = ESlateBrushDrawType::Image;
	BlackBrush.DrawAs = ESlateBrushDrawType::RoundedBox;
	BlackBrush.OutlineSettings.Width = 2.f;

	FSlateFontInfo baseFont = FStyleDefaults::GetFontInfo();
	baseFont.Size = 18.f;

	if (TSharedPtr<FSlateGameResources> lockedResources = TDUIResources.Pin()) {
		BackgroundBrush = *lockedResources->GetBrush("ui_top_Brush");
		LivesBrush = *lockedResources->GetBrush("ui_lives_Brush");
		GoldBrush = *lockedResources->GetBrush("ui_gold_Brush");
	}
	else {
		BackgroundBrush = BlackBrush;
		LivesBrush = BlackBrush;
		GoldBrush = BlackBrush;
	}

	ChildSlot
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Top)
	[
		SNew(SBorder)
		.BorderImage(&BackgroundBrush)
		.Padding(10.f)
		.Content()
		[
			// Top bar container itself
			SNew(SHorizontalBox)

			// Game stats container
			+ SHorizontalBox::Slot() .FillWidth(1.f)
			[
				SNew(SHorizontalBox)
				// Lives Counter
				+ SHorizontalBox::Slot() .FillWidth(1.f) .HAlign(HAlign_Left)
				[
					SNew(SBorder)
					.BorderImage(&BlackBrush)
					.Padding(TextPadding * 2, TextPadding)
					.Content()
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot() .Padding(0.f, 0.f, 8.f, 0.f) .AutoWidth()
						[
							SNew(SImage)
							.Image(&LivesBrush)
							.DesiredSizeOverride(FVector2D { IconSize, IconSize })

						]

						+ SHorizontalBox::Slot() .AutoWidth() .VAlign(EVerticalAlignment::VAlign_Center)
						[
							SNew(STextBlock)
							.Font(baseFont)
							.Text(this, &STopBarWidget::GetLivesText)
						]
					]
				]

				// Wave Counter
				+ SHorizontalBox::Slot() .FillWidth(1.f) .HAlign(HAlign_Center) .VAlign(EVerticalAlignment::VAlign_Center)
				[
					SNew(SBorder)
					.BorderImage(&BlackBrush)
					.Padding(TextPadding * 2, TextPadding)
					.Content()
					[
						SNew(STextBlock)
						.Font(baseFont)
						.Text(this, &STopBarWidget::GetWaveNumberText)
					]
				]
				
				// Enemies Remaining Counter
				+ SHorizontalBox::Slot() .FillWidth(1.f) .HAlign(HAlign_Center) .VAlign(EVerticalAlignment::VAlign_Center)
				[
					SNew(SBorder)
					.BorderImage(&BlackBrush)
					.Padding(TextPadding * 2, TextPadding)
					.Content()
					[
						SNew(STextBlock)
						.Font(baseFont)
						.Text(this, &STopBarWidget::GetRemainingText)
					]
				]
			]
			// End of game stats container

			// Player stats container
			+ SHorizontalBox::Slot() .FillWidth(1.f)
			[
				SNew(SHorizontalBox)
				// Gold Counter
				+ SHorizontalBox::Slot() .AutoWidth() .HAlign(HAlign_Left) .VAlign(EVerticalAlignment::VAlign_Center)
				[
					SNew(SBorder)
					.BorderImage(&BlackBrush)
					.Padding(TextPadding * 2, TextPadding)
					.Content()
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot() .Padding(0.f, 0.f, 8.f, 0.f) .AutoWidth()
						[
							SNew(SImage)
							.Image(&GoldBrush)
							.DesiredSizeOverride(FVector2D { IconSize, IconSize })

						]

						+ SHorizontalBox::Slot() .AutoWidth() .VAlign(EVerticalAlignment::VAlign_Center)
						[
							SNew(STextBlock)
							.Font(baseFont)
							.Text(this, &STopBarWidget::GetGoldText)
						]
					]
				]
			]
			// End of player stats container
		]
	];
}

void STopBarWidget::SetGoldAmount(int gold) {
	Gold = gold;
	GetGoldText();
}

FText STopBarWidget::GetLivesText() const {
	return FText::Format(INVTEXT("{0}"), FText::AsNumber(*Lives));
}

FText STopBarWidget::GetRemainingText() const {
	return FText::Format(INVTEXT("Remaining: {0}"), FText::AsNumber(*Remaining));
}

FText STopBarWidget::GetWaveNumberText() const {
	return FText::Format(INVTEXT("Wave: {0}"), FText::AsNumber(*WaveNumber + 1));
}

FText STopBarWidget::GetGoldText() const {
	return FText::Format(INVTEXT("{0}"), FText::AsNumber(Gold));
}

STopBarWidget::~STopBarWidget() {
	TDUIResources.Reset();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
