// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "Slate/SlateGameResources.h"
#include "Widgets/Layout/SConstraintCanvas.h"
#include "Widgets/SCanvas.h"
#include "Widgets/SCompoundWidget.h"

#include "Abilities/TDAbility.h"


class TOWERDEFENCETHING_API SAbilityTooltip : public SCompoundWidget {
public:
	SLATE_BEGIN_ARGS(SAbilityTooltip) :
		_tdUIResources()
	{}
	SLATE_ARGUMENT(TWeakPtr<FSlateGameResources>, tdUIResources)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	~SAbilityTooltip();

	//SCanvas::FSlot* CanvasSlot;
	SConstraintCanvas::FSlot* ConstraintCanvasSlot;
	TSharedPtr<SBorder> TooltipBorder;

	void SetTooltipAbility(UTDAbility* tdAbility);
	void ApplyAbilityInfo();

private:
	const float IconSize { 28.f };
	TAttribute<bool> IsInteractiveWidget;

	TWeakPtr<FSlateGameResources> TDUIResources;

	FSlateColorBrush BackgroundBrush = FSlateColorBrush(FLinearColor(0.08f, 0.1f, 0.12f));
	FSlateBrush ManaCostBrush;
	FSlateBrush CooldownBrush;
	FSlateColor NameTextColour = FSlateColor(FLinearColor::White);
	FSlateColor SpecsTextColour = FSlateColor(FLinearColor(0.4f, 0.5f, 0.6f));
	FSlateColor DescriptionTextColour = FSlateColor(FLinearColor(0.7f, 0.8f, 0.9f));

	UTDAbility* Ability;

	FSlateFontInfo NameFont;
	FSlateFontInfo DescriptionFont;

	FText AbilityName;
	FText AbilityTarget;
	FText AbilityCastingType;
	FText AbilityCost;
	FText AbilityCooldown;
	FText AbilityDescription;

	FText GetAbilityName() const;
	FText GetAbilityTarget() const;
	FText GetAbilityCastingType() const;
	FText GetAbilityCost() const;
	FText GetAbilityCooldown() const;
	FText GetAbilityDescription() const;
};
