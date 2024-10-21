// Dragons rule ok

#pragma once

#include "SlateComps/SContextMenuSquareWidget.h"
#include "CoreMinimal.h"
#include "Slate/SlateGameResources.h"
#include "Widgets/SCompoundWidget.h"

class TOWERDEFENCETHING_API SBuilderMenuWidget : public SCompoundWidget {

public:
	SLATE_BEGIN_ARGS(SBuilderMenuWidget) :
		_tdUIResources()
	{}
	SLATE_ARGUMENT(TSharedPtr<FSlateGameResources>, tdUIResources)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	~SBuilderMenuWidget();

	TArray<TArray<TSharedPtr<SContextMenuSquareWidget>>> GridPanelSquareArray;
	FReply IgnoreMouseInput(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);

protected:
	TSharedPtr<SBorder> GridBorderPtr;
	TSharedPtr<SUniformGridPanel> GridPanelPtr;
	FSlateColorBrush brush = FSlateColorBrush(FLinearColor::Black);
	TSharedPtr<FSlateGameResources> tdUIResources;
};
