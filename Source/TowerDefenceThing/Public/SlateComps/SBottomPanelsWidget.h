// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "Slate/SlateGameResources.h"
#include "Widgets/SCompoundWidget.h"

#include "GameFramework/HUD.h"

#include "SlateComps/SBuilderMenuWidget.h"

/**
 * 
 */
class TOWERDEFENCETHING_API SBottomPanelsWidget : public SCompoundWidget {
public:
	SLATE_BEGIN_ARGS(SBottomPanelsWidget) :
		_tdUIResources()
	{}
	SLATE_ARGUMENT(TWeakPtr<FSlateGameResources>, tdUIResources)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
	~SBottomPanelsWidget();

	TSharedPtr<SBuilderMenuWidget> ContextMenuPtr;

	void BindContextMenuWidget(AHUD* hud) const;

	void BindUnitStatsPanel(int8 type, FText nameText, FText typeText, const float* urs1, const float* urs2, const float* us2, const float* us3);
	void UpdateUnitStatsPanel();
	void ResetUnitStatsPanel();

private:
	FSlateColor WhiteTextColour = FSlateColor(FLinearColor::White);
	FSlateFontInfo BigFont;
	FSlateFontInfo NormalFont;

	FSlateColorBrush BlackBrush = FSlateColorBrush(FLinearColor::Black);
	TWeakPtr<FSlateGameResources> TDUIResources;

	bool HasAttachedUnit { false };
	int8 UnitTypeNum;

	const FString DamageString = "Damage:";
	const FString RangeString = "Range:";
	const FString AttackSpeedString = "ASpeed:";

	const FString HealthString = "Health:";
	const FString MovementSpeedString = "MSpeed:";

	const float* UnitRangeStat1 { nullptr };
	const float* UnitRangeStat2 { nullptr };
	const float* UnitStat2 { nullptr };
	const float* UnitStat3 { nullptr };

	FText FUnitName;
	FText FUnitType;
	FText FUnitRangeStatType;
	FText FUnitStat2Type;
	FText FUnitStat3Type;

	FText FUnitRangeStat1;
	FText FUnitRangeStat2;
	FText FUnitStat2;
	FText FUnitStat3;

	FText GetUnitName() const;
	FText GetUnitType() const;
	FText GetUnitRangeStatType() const;
	FText GetUnitStat2Type() const;
	FText GetUnitStat3Type() const;
	FText GetUnitRangeStatValue() const;
	FText GetUnitStat2Value() const;
	FText GetUnitStat3Value() const;
};