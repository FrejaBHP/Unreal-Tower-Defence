// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Notifications/SProgressBar.h"
#include "Widgets/SCompoundWidget.h"


class TOWERDEFENCETHING_API SEnemyHealthBar : public SCompoundWidget {
public:
	SLATE_BEGIN_ARGS(SEnemyHealthBar)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	~SEnemyHealthBar();
	
	void SetMaxHealth(float health);
	void SetHealth(float health);

protected:
	TSharedPtr<SProgressBar> ProgressBarPtr;
	FSlateColorBrush brush = FSlateColorBrush(FLinearColor::Black);

	float CurrentHealth { 0.f };
	float MaxHealth { 0.f };
	float HealthRatio { 1.f };
};
