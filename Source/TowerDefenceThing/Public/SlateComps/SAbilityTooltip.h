// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "Abilities/TDAbility.h"
#include "Widgets/Layout/SConstraintCanvas.h"
#include "Widgets/SCanvas.h"
#include "Widgets/SCompoundWidget.h"

class TOWERDEFENCETHING_API SAbilityTooltip : public SCompoundWidget {
public:
	SLATE_BEGIN_ARGS(SAbilityTooltip)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	~SAbilityTooltip();

	//SCanvas::FSlot* CanvasSlot;
	SConstraintCanvas::FSlot* ConstraintCanvasSlot;

	void SetTooltipAbility(UTDAbility* tdAbility);
	void ApplyAbilityInfo();


protected:
	FSlateColorBrush BackgroundBrush = FSlateColorBrush(FLinearColor(0.08f, 0.1f, 0.12f));
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

private:
	TAttribute<bool> IsInteractiveWidget;
};
