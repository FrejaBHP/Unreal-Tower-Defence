// Dragons rule ok


#include "SlateComps/SAbilityTooltip.h"
#include "AbilityEnums.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SAbilityTooltip::Construct(const FArguments& InArgs) {
	FSlateFontInfo baseFont = FStyleDefaults::GetFontInfo();
	NameFont = baseFont;
	NameFont.Size = 16.f;

	SetVisibility(EVisibility::Hidden);
	
	DescriptionFont = baseFont;
	DescriptionFont.Size = 14.f;

	ChildSlot
	[
		SNew(SConstraintCanvas)
		+ SConstraintCanvas::Slot() .AutoSize(true) .Alignment(FVector2D(0, 0)) .Expose(ConstraintCanvasSlot)
		[
			SAssignNew(TooltipBorder, SBorder)
			.BorderImage(&BackgroundBrush)
			.Padding(12.f)
			.Content()
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot() .Padding(0, 0, 0, 10) .AutoHeight()
				[
					SNew(STextBlock)
					.Font(NameFont)
					.ColorAndOpacity(NameTextColour)
					.Text(this, &SAbilityTooltip::GetAbilityName)
				]

				+ SVerticalBox::Slot()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot() .HAlign(HAlign_Left)
					[
						SNew(STextBlock)
						.Font(DescriptionFont)
						.ColorAndOpacity(SpecsTextColour)
						.Text(this, &SAbilityTooltip::GetAbilityTarget)
					]

					+ SHorizontalBox::Slot() .HAlign(HAlign_Right)
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot() .HAlign(HAlign_Right) .Padding(0, 0, 24, 0)
						[
							SNew(STextBlock)
							.Font(DescriptionFont)
							.ColorAndOpacity(SpecsTextColour)
							.Text(this, &SAbilityTooltip::GetAbilityCost)
						]

						+ SHorizontalBox::Slot() .HAlign(HAlign_Right)
						[
							SNew(STextBlock)
							.Font(DescriptionFont)
							.ColorAndOpacity(SpecsTextColour)
							.Text(this, &SAbilityTooltip::GetAbilityCooldown)
						]
					]
				]

				+ SVerticalBox::Slot()
				[
					SNew(STextBlock)
					.Font(DescriptionFont)
					.ColorAndOpacity(SpecsTextColour)
					.Text(this, &SAbilityTooltip::GetAbilityCastingType)
				]

				+ SVerticalBox::Slot() .Padding(0, 8, 0, 0) .AutoHeight()
				[
					SNew(STextBlock)
					.Font(DescriptionFont)
					.ColorAndOpacity(DescriptionTextColour)
					.WrapTextAt(400)
					.MinDesiredWidth(400)
					.Text(this, &SAbilityTooltip::GetAbilityDescription)
				]
			]
		]
	];
}

void SAbilityTooltip::SetTooltipAbility(UTDAbility* tdAbility) {
	Ability = tdAbility;
	ApplyAbilityInfo();
}

void SAbilityTooltip::ApplyAbilityInfo() {
	if (Ability) {
		AbilityName = FText::FromName(Ability->AbilityName);
		AbilityTarget = FText::Format(INVTEXT("Target: {0}"), FText::FromString(*UEnum::GetDisplayValueAsText(Ability->AbilityTarget).ToString()));
		AbilityCastingType = FText::Format(INVTEXT("Casting type: {0}"), FText::FromString(*UEnum::GetDisplayValueAsText(Ability->AbilityCast).ToString()));
		AbilityCost = FText::Format(INVTEXT("Cost: {0}"), FText::AsNumber(Ability->Cost));
		AbilityCooldown = FText::Format(INVTEXT("CD: {0}"), FText::AsNumber(Ability->Cooldown));
		AbilityDescription = Ability->GetAbilityDescription();
	}
}

FText SAbilityTooltip::GetAbilityName() const {
	return AbilityName;
}

FText SAbilityTooltip::GetAbilityTarget() const {
	return AbilityTarget;
}

FText SAbilityTooltip::GetAbilityCastingType() const {
	return AbilityCastingType;
}

FText SAbilityTooltip::GetAbilityCost() const {
	return AbilityCost;
}

FText SAbilityTooltip::GetAbilityCooldown() const {
	return AbilityCooldown;
}

FText SAbilityTooltip::GetAbilityDescription() const {
	return AbilityDescription;
}

SAbilityTooltip::~SAbilityTooltip() {
	TooltipBorder.Reset();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
