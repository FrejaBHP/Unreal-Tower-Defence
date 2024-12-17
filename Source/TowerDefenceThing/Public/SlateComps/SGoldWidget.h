// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class TOWERDEFENCETHING_API SGoldWidget : public SCompoundWidget {
public:
	SLATE_BEGIN_ARGS(SGoldWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	void SetGoldCount(int32 gold);

private:
	int32 Gold;
	FText GetGoldCount() const;
};
