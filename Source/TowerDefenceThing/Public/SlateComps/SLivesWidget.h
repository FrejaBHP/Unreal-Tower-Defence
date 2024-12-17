// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class TOWERDEFENCETHING_API SLivesWidget : public SCompoundWidget {

public:
	SLATE_BEGIN_ARGS(SLivesWidget) :
		_LivesPtr(),
		_Font()
	{}
	SLATE_ARGUMENT(int32*, LivesPtr)
	SLATE_ARGUMENT(FSlateFontInfo, Font)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	~SLivesWidget();

	void UpdateLivesCounter();

private:
	int32* Lives;
	FSlateFontInfo Font;

	FText GetLivesCount() const;
};
