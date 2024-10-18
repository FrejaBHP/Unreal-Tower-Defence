// Dragons rule ok

#pragma once


#include "SlateComps/SquareWidgetData.h"
#include "Slate/SlateGameResources.h"
#include "FTDUIResources.h"
#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

DECLARE_DELEGATE_TwoParams(FClickedSignature, ESquareFunctionType, int32);

class TOWERDEFENCETHING_API SContextMenuSquareWidget : public SCompoundWidget {

public:
	SLATE_BEGIN_ARGS(SContextMenuSquareWidget) :
		_tdUIResources()
	{}
	SLATE_ARGUMENT(TSharedPtr<FSlateGameResources>, tdUIResources)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	FReply OnMouseButtonDoubleClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	void SetImageBrushWithName(FName newBrushName);
	void SetSWData(SquareWidgetData newSWData);

	SquareWidgetData* SWData;
	FClickedSignature OnClicked;
	bool IsClickable = true;

protected:
	const FSlateBrush* GetImageBrushFromName(FName newBrushName) const;
	TSharedPtr<FSlateGameResources> tdUIResources;
	FSlateBrush imageBrush;
};
