// Dragons rule ok


#include "SlateComps/SEnemyHealthBar.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SEnemyHealthBar::Construct(const FArguments& InArgs) {
	ChildSlot
	[
		SNew(SBorder)
		.BorderImage(&BlackBrush)
		.Padding(3.f)
		.Content()
		[
			SAssignNew(ProgressBarPtr, SProgressBar)
			.Percent(1.f)
			.BarFillType(EProgressBarFillType::LeftToRight)
			.FillColorAndOpacity(FSlateColor(FLinearColor::Green))
		]
	];
}

void SEnemyHealthBar::SetMaxHealth(float maxHealth) {
	MaxHealth = maxHealth;
}

void SEnemyHealthBar::SetHealth(float health) {
	CurrentHealth = health;
	
	if (CurrentHealth < 0.f) {
		HealthRatio = 0.f;
	}
	else {
		HealthRatio = CurrentHealth / MaxHealth;
	}

	ProgressBarPtr->SetPercent(HealthRatio);
}

SEnemyHealthBar::~SEnemyHealthBar() {
	ProgressBarPtr.Reset();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION