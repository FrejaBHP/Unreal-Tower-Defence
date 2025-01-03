// Dragons rule ok


#include "SlateComps/SBottomPanelsWidget.h"
#include "SlateOptMacros.h"
#include "TDPlayerHUD.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SBottomPanelsWidget::Construct(const FArguments& InArgs) {
	TDUIResources = InArgs._tdUIResources;

	FSlateFontInfo baseFont = FStyleDefaults::GetFontInfo();
	BigFont = baseFont;
	BigFont.Size = 14.f;

	NormalFont = baseFont;
	NormalFont.Size = 12.f;
	
	ChildSlot
	.HAlign(EHorizontalAlignment::HAlign_Center)
	.VAlign(EVerticalAlignment::VAlign_Bottom)
	[
		SNew(SBox)
		.MinDesiredWidth(1200)
		.MaxDesiredWidth(1800)
		.Content()
		[
			SNew(SHorizontalBox)
			// Left part of the lower HUD (unused)
			+ SHorizontalBox::Slot() .AutoWidth() //.HAlign(EHorizontalAlignment::HAlign_Left)
			[
				SNew(SBox)
				.MinDesiredWidth(308)
				.MaxDesiredWidth(308)
			]

			// Middle part of the lower HUD (selected unit panel)
			+ SHorizontalBox::Slot() .HAlign(EHorizontalAlignment::HAlign_Fill)
			[
				SNew(SBorder)
				.BorderImage(&BlackBrush)
				.Padding(4.f)
				.Content()
				[
					SNew(SBox)
					.Content()
					[
						// VBox responsible for ordering content
						SNew(SVerticalBox)
						// Contains name and type of unit
						+ SVerticalBox::Slot() .Padding(0.f, 10.f) .AutoHeight()
						[
							SNew(SVerticalBox)
							// Name of unit
							+ SVerticalBox::Slot() .Padding(0.f, 0.f, 0.f, 4.f) .HAlign(EHorizontalAlignment::HAlign_Center)
							[
								SNew(STextBlock)
								.Font(BigFont)
								.Text(this, &SBottomPanelsWidget::GetUnitName)
							]
						
							// Title(?) of unit
							+ SVerticalBox::Slot() .HAlign(EHorizontalAlignment::HAlign_Center)
							[
								SNew(STextBlock)
								.Font(NormalFont)
								.Text(this, &SBottomPanelsWidget::GetUnitType)
							]
						]
						// End of name and type

						// Contains everything else
						+ SVerticalBox::Slot()
						[
							// HBox for ordering stats, etc
							SNew(SHorizontalBox)
							// Unit stats
							+ SHorizontalBox::Slot() .Padding(8.f, 0.f) .FillWidth(1)
							[
								SNew(SVerticalBox)
								+ SVerticalBox::Slot()
								[
									SNew(SHorizontalBox)
									+ SHorizontalBox::Slot()
									[
										SNew(STextBlock)
										.Font(NormalFont)
										.Text(this, &SBottomPanelsWidget::GetUnitRangeStatType)
									]
									
									+ SHorizontalBox::Slot()
									[
										SNew(STextBlock)
										.Font(NormalFont)
										.Text(this, &SBottomPanelsWidget::GetUnitRangeStatValue)
									]
								]

								+ SVerticalBox::Slot()
								[
									SNew(SHorizontalBox)
									+ SHorizontalBox::Slot()
									[
										SNew(STextBlock)
										.Font(NormalFont)
										.Text(this, &SBottomPanelsWidget::GetUnitStat2Type)
									]
									
									+ SHorizontalBox::Slot()
									[
										SNew(STextBlock)
										.Font(NormalFont)
										.Text(this, &SBottomPanelsWidget::GetUnitStat2Value)
									]
								]

								+ SVerticalBox::Slot()
								[
									SNew(SHorizontalBox)
									+ SHorizontalBox::Slot()
									[
										SNew(STextBlock)
										.Font(NormalFont)
										.Text(this, &SBottomPanelsWidget::GetUnitStat3Type)
									]
									
									+ SHorizontalBox::Slot()
									[
										SNew(STextBlock)
										.Font(NormalFont)
										.Text(this, &SBottomPanelsWidget::GetUnitStat3Value)
									]
								]
							]

							// Not sure yet
							+ SHorizontalBox::Slot() .FillWidth(1)
							[
								SNew(SBox)
							]

							// Inventory?
							+ SHorizontalBox::Slot() .FillWidth(1)
							[
								SNew(SBox)
							]
						]
						// End of everything else
					]
				]
			]

			// Right part of the lower HUD, contains the Context Menu
			+ SHorizontalBox::Slot() .AutoWidth()
			[
				SAssignNew(ContextMenuPtr, SBuilderMenuWidget)
				.tdUIResources(TDUIResources)
			]
		]
	];
}

void SBottomPanelsWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) {
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
	
	if (HasAttachedUnit) {
		UpdateUnitStatsPanel();
	}
}

void SBottomPanelsWidget::BindUnitStatsPanel(int8 type, FText nameText, FText typeText, const float* urs1, const float* urs2, const float* us2, const float* us3) {
	UnitTypeNum = type;

	switch (UnitTypeNum) {
		case 0: // If unit is a tower
			FUnitRangeStatType = FText::FromString(*DamageString);
			FUnitStat2Type = FText::FromString(*AttackSpeedString);
			FUnitStat3Type = FText::FromString(*RangeString);
			break;

		case 1: // If unit is an enemy
			FUnitRangeStatType = FText::FromString(*HealthString);
			FUnitStat2Type = FText::FromString(*MovementSpeedString);
			FUnitStat3Type = FText::GetEmpty();
			break;

		case 2: // If unit is a player
			FUnitRangeStatType = FText::GetEmpty();
			FUnitStat2Type = FText::GetEmpty();
			FUnitStat3Type = FText::GetEmpty();
			break;
	
		default: // Hopefully should never happen, but clears just in case
			FUnitRangeStatType = FText::GetEmpty();
			FUnitStat2Type = FText::GetEmpty();
			FUnitStat3Type = FText::GetEmpty();
			UE_LOG(LogTemp, Error, TEXT("fug"));
			break;
	}

	FUnitName = nameText;
	FUnitType = typeText;
	UnitRangeStat1 = urs1;
	UnitRangeStat2 = urs2;
	UnitStat2 = us2;
	UnitStat3 = us3;

	HasAttachedUnit = true;
}

// Responsible for updating the text used to display current, non-constant stats
void SBottomPanelsWidget::UpdateUnitStatsPanel() {
	if (UnitRangeStat1 && UnitRangeStat2) {
		GetUnitRangeStatValue();
	}

	if (UnitStat2) {
		GetUnitStat2Value();
	}

	if (UnitStat3) {
		GetUnitStat3Value();
	}
}

void SBottomPanelsWidget::ResetUnitStatsPanel() {
	HasAttachedUnit = false;

	UnitRangeStat1 = nullptr;
	UnitRangeStat2 = nullptr;
	UnitStat2 = nullptr;
	UnitStat3 = nullptr;

	FUnitName = FText::GetEmpty();
	FUnitType = FText::GetEmpty();
	FUnitRangeStatType = FText::GetEmpty();
	FUnitStat2Type = FText::GetEmpty();
	FUnitStat3Type = FText::GetEmpty();
}

void SBottomPanelsWidget::BindContextMenuWidget(AHUD* hud) const {
	if (ContextMenuPtr.IsValid()) {
		ATDPlayerHUD* playerHUD = Cast<ATDPlayerHUD>(hud);

		for (size_t i = 0; i < ContextMenuPtr->GridPanelSquareArray.Num(); i++) {
			for (size_t j = 0; j < ContextMenuPtr->GridPanelSquareArray[i].Num(); j++) {
				ContextMenuPtr->GridPanelSquareArray[i][j]->OnClicked.BindUObject(playerHUD, &ATDPlayerHUD::ReceivedButtonInput);
				ContextMenuPtr->GridPanelSquareArray[i][j]->OnEntered.BindUObject(playerHUD, &ATDPlayerHUD::ReceivedButtonEntered);
				ContextMenuPtr->GridPanelSquareArray[i][j]->OnLeft.BindUObject(playerHUD, &ATDPlayerHUD::ReceivedButtonLeft);
			}
		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Context Menu pointer invalid, buttons not bound"));
	}
}

FText SBottomPanelsWidget::GetUnitName() const {
	return FUnitName;
}

FText SBottomPanelsWidget::GetUnitType() const {
	return FUnitType;
}

FText SBottomPanelsWidget::GetUnitRangeStatType() const {
	return FUnitRangeStatType;
}

FText SBottomPanelsWidget::GetUnitStat2Type() const {
	return FUnitStat2Type;
}

FText SBottomPanelsWidget::GetUnitStat3Type() const {
	return FUnitStat3Type;
}

FText SBottomPanelsWidget::GetUnitRangeStatValue() const {
	if (!UnitRangeStat1 || !UnitRangeStat2) {
		return FText::GetEmpty();
	}

	if (UnitTypeNum == 0) {
		return FText::Format(INVTEXT("{0} - {1}"), FText::AsNumber(*UnitRangeStat1), FText::AsNumber(*UnitRangeStat2));
	}
	return FText::Format(INVTEXT("{0} / {1}"), FText::AsNumber(*UnitRangeStat1), FText::AsNumber(*UnitRangeStat2));
}

FText SBottomPanelsWidget::GetUnitStat2Value() const {
	if (!UnitStat2) {
		return FText::GetEmpty();
	}
	return FText::Format(INVTEXT("{0}"), FText::AsNumber(*UnitStat2));
}

FText SBottomPanelsWidget::GetUnitStat3Value() const {
	if (!UnitStat3) {
		return FText::GetEmpty();
	}
	return FText::Format(INVTEXT("{0}"), FText::AsNumber(*UnitStat3));
}

SBottomPanelsWidget::~SBottomPanelsWidget() {
	ContextMenuPtr.Reset();
	TDUIResources.Reset();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
