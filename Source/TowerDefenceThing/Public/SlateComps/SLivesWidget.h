// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class TOWERDEFENCETHING_API SLivesWidget : public SCompoundWidget {

public:
	SLATE_BEGIN_ARGS(SLivesWidget) :
		_livesPtr(nullptr),
		_font()
	{}
	SLATE_ARGUMENT(int32*, livesPtr)
	SLATE_ARGUMENT(FSlateFontInfo, font)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	~SLivesWidget();
	

protected:
	int32* livesPtr = nullptr;
	FSlateFontInfo font;
};
