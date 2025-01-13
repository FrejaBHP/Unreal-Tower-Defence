// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "Slate/SlateGameResources.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class TOWERDEFENCETHING_API STopBarWidget : public SCompoundWidget {
public:
	SLATE_BEGIN_ARGS(STopBarWidget) :
		_tdUIResources(),
		_livesPtr(nullptr),
		_remainingPtr(nullptr),
		_waveNumberPtr(nullptr)
	{}
	SLATE_ARGUMENT(TWeakPtr<FSlateGameResources>, tdUIResources)
	SLATE_ARGUMENT(int*, livesPtr)
	SLATE_ARGUMENT(int*, remainingPtr)
	SLATE_ARGUMENT(int*, waveNumberPtr)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	~STopBarWidget();

	void SetGoldAmount(int gold);

	FText GetLivesText() const;
	FText GetRemainingText() const;
	FText GetWaveNumberText() const;
	FText GetGoldText() const;

private:
	const float IconSize { 32.f };
	FSlateBrush LivesBrush;
	FSlateBrush GoldBrush;
	FSlateBrush BackgroundBrush;
	FSlateColorBrush BlackBrush = FSlateColorBrush(FLinearColor::Black);
	TWeakPtr<FSlateGameResources> TDUIResources;

	const float TextPadding { 8.f };
	int* Lives;
	int* Remaining;
	int* WaveNumber;
	int Gold;
};
