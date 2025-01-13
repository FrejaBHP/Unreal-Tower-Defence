// Dragons rule ok


#include "SlateComps/SBottomPanelsWidget.h"
#include "SlateOptMacros.h"
#include "TDPlayerHUD.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SBottomPanelsWidget::Construct(const FArguments& InArgs) {
	TDUIResources = InArgs._tdUIResources;

	FSlateFontInfo baseFont = FStyleDefaults::GetFontInfo();
	BigFont = baseFont;
	BigFont.Size = 15.f;

	NormalFont = baseFont;
	NormalFont.Size = 13.f;

	NumberFormatting.MaximumFractionalDigits = 1;
	
	ChildSlot
	.HAlign(HAlign_Center)
	.VAlign(VAlign_Bottom)
	[
		SNew(SBox)
		.MinDesiredWidth(1280)
		.MaxDesiredWidth(1920)
		.Content()
		[
			SNew(SHorizontalBox)
			// Left part of the lower HUD (unused)
			+ SHorizontalBox::Slot() .AutoWidth()
			[
				SNew(SBox)
				.MinDesiredWidth(308)
				.MaxDesiredWidth(308)
			]

			// Middle part of the lower HUD (selected unit panel)
			+ SHorizontalBox::Slot() .HAlign(HAlign_Fill)
			[
				SNew(SBorder)
				.BorderImage(&BlackBrush)
				.Padding(4.f)
				.OnMouseButtonDown(this, &SBottomPanelsWidget::IgnoreMouseInput)
				.OnMouseDoubleClick(this, &SBottomPanelsWidget::IgnoreMouseInput)
				.Content()
				[
					// VBox responsible for ordering content
					SNew(SVerticalBox)
					// Contains name and type of unit
					+ SVerticalBox::Slot() .Padding(0.f, 10.f) .AutoHeight()
					[
						SNew(SVerticalBox)
						// Name of unit
						+ SVerticalBox::Slot() .Padding(0.f, 0.f, 0.f, 4.f) .HAlign(HAlign_Center)
						[
							SNew(STextBlock)
							.Font(BigFont)
							.Text(this, &SBottomPanelsWidget::GetUnitName)
						]
						
						// Title(?) of unit
						+ SVerticalBox::Slot() .HAlign(HAlign_Center)
						[
							SNew(STextBlock)
							.Font(NormalFont)
							.Text(this, &SBottomPanelsWidget::GetUnitType)
						]
					]
					// End of name and type

					// Contains everything else
					+ SVerticalBox::Slot() .AutoHeight()
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
								+ SHorizontalBox::Slot() .Padding(0.f, 0.f, 6.f, 0.f) .AutoWidth()
								[
									SNew(SImage)
									.Image(&BUnitRangeStatType)
									.DesiredSizeOverride(FVector2D { StatIconSize, StatIconSize })
								]
									
								+ SHorizontalBox::Slot() .VAlign(VAlign_Center)
								[
									SNew(STextBlock)
									.Font(NormalFont)
									.Text(this, &SBottomPanelsWidget::GetUnitRangeStatValue)
								]
							]

							+ SVerticalBox::Slot() 
							[
								SNew(SHorizontalBox)
								+ SHorizontalBox::Slot() .Padding(0.f, 0.f, 6.f, 0.f) .AutoWidth()
								[
									SNew(SImage)
									.Image(&BUnitStat2Type)
									.DesiredSizeOverride(FVector2D { StatIconSize, StatIconSize })
								]
									
								+ SHorizontalBox::Slot() .VAlign(VAlign_Center)
								[
									SNew(STextBlock)
									.Font(NormalFont)
									.Text(this, &SBottomPanelsWidget::GetUnitStat2Value)
								]
							]

							+ SVerticalBox::Slot()
							[
								SNew(SHorizontalBox)
								+ SHorizontalBox::Slot() .Padding(0.f, 0.f, 6.f, 0.f) .AutoWidth()
								[
									SNew(SImage)
									.Image(&BUnitStat3Type)
									.DesiredSizeOverride(FVector2D { StatIconSize, StatIconSize })
								]
									
								+ SHorizontalBox::Slot() .VAlign(VAlign_Center)
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

			// Right part of the lower HUD, contains the Context Menu
			+ SHorizontalBox::Slot() .AutoWidth()
			[
				SAssignNew(ContextMenuPtr, SBuilderMenuWidget)
				.tdUIResources(TDUIResources)
			]
		]
	];

	ResetUnitStatsPanel();
}

// Since we're only ticking for one unit per player, performance here isn't a massive concern
// UpdateUnitStatsPanel() Updates the shown values of the unit's stats every frame by dereferencing the issued pointers
void SBottomPanelsWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) {
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
	
	if (HasAttachedUnit) {
		UpdateUnitStatsPanel();
	}
}

// When a unit is selected, change the stat description text to match the type
void SBottomPanelsWidget::BindUnitStatsPanel(int8 type, FText nameText, FText typeText, const float* urs1, const float* urs2, const float* us2, const float* us3) {
	UnitTypeNum = type;

	switch (UnitTypeNum) {
		case 0: // If unit is a tower
			SetImageBrushWithName(BUnitRangeStatType, DamageBrushName);
			SetImageBrushWithName(BUnitStat2Type, ASpeedBrushName);
			SetImageBrushWithName(BUnitStat3Type, RangeBrushName);
			break;

		case 1: // If unit is an enemy
			SetImageBrushWithName(BUnitRangeStatType, HealthBrushName);
			SetImageBrushWithName(BUnitStat2Type, MSpeedBrushName);
			SetImageBrushWithName(BUnitStat3Type, FName(""));
			break;

		case 2: // If unit is a player
			SetImageBrushWithName(BUnitRangeStatType, FName(""));
			SetImageBrushWithName(BUnitStat2Type, FName(""));
			SetImageBrushWithName(BUnitStat3Type, FName(""));
			break;
	
		default: // Hopefully should never happen, but clears just in case
			SetImageBrushWithName(BUnitRangeStatType, FName(""));
			SetImageBrushWithName(BUnitStat2Type, FName(""));
			SetImageBrushWithName(BUnitStat3Type, FName(""));
			UE_LOG(LogTemp, Error, TEXT("Unknown unit type selected"));
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

// Resets textboxes and pointers for when a unit is no longer valid, to avoid dangling pointers and visual issues
void SBottomPanelsWidget::ResetUnitStatsPanel() {
	HasAttachedUnit = false;

	UnitRangeStat1 = nullptr;
	UnitRangeStat2 = nullptr;
	UnitStat2 = nullptr;
	UnitStat3 = nullptr;

	FUnitName = FText::GetEmpty();
	FUnitType = FText::GetEmpty();

	SetImageBrushWithName(BUnitRangeStatType, FName(""));
	SetImageBrushWithName(BUnitStat2Type, FName(""));
	SetImageBrushWithName(BUnitStat3Type, FName(""));
}

// Sets up mouse interaction with the Context Menu buttons
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

const FSlateBrush* SBottomPanelsWidget::GetImageBrushFromName(FName newBrushName) const {
	if (TSharedPtr<FSlateGameResources> lockedResources = TDUIResources.Pin()) {
		if (newBrushName != FName("")) {
			return lockedResources->GetBrush(newBrushName);
		}
		return lockedResources->GetBrush(FName("empty_Brush"));
	}
	else {
		return &BUnitRangeStatType;
	}
}

void SBottomPanelsWidget::SetImageBrushWithName(FSlateBrush& brush, FName newBrushName) {
	brush = *GetImageBrushFromName(newBrushName);
}

FReply SBottomPanelsWidget::IgnoreMouseInput(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) {
	return FReply::Handled();
}

FText SBottomPanelsWidget::GetUnitName() const {
	return FUnitName;
}

FText SBottomPanelsWidget::GetUnitType() const {
	return FUnitType;
}

FText SBottomPanelsWidget::GetUnitRangeStatValue() const {
	if (!UnitRangeStat1 || !UnitRangeStat2) {
		return FText::GetEmpty();
	}

	if (UnitTypeNum == 0) {
		return FText::Format(INVTEXT("{0} - {1}"), FText::AsNumber(*UnitRangeStat1, &NumberFormatting), FText::AsNumber(*UnitRangeStat2, &NumberFormatting));
	}
	return FText::Format(INVTEXT("{0} / {1}"), FText::AsNumber(*UnitRangeStat1, &NumberFormatting), FText::AsNumber(*UnitRangeStat2, &NumberFormatting));
}

FText SBottomPanelsWidget::GetUnitStat2Value() const {
	if (!UnitStat2) {
		return FText::GetEmpty();
	}
	return FText::Format(INVTEXT("{0}"), FText::AsNumber(*UnitStat2, &NumberFormatting));
}

FText SBottomPanelsWidget::GetUnitStat3Value() const {
	if (!UnitStat3) {
		return FText::GetEmpty();
	}
	return FText::Format(INVTEXT("{0}"), FText::AsNumber(*UnitStat3, &NumberFormatting));
}

SBottomPanelsWidget::~SBottomPanelsWidget() {
	ContextMenuPtr.Reset();
	TDUIResources.Reset();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
