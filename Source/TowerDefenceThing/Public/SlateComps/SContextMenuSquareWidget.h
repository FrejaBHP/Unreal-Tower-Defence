// Dragons rule ok

#pragma once


#include "SlateComps/SquareWidgetData.h"
#include "Slate/SlateGameResources.h"
#include "FTDUIResources.h"
#include "AbilityEnums.h"
#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

DECLARE_DELEGATE_TwoParams(FClickedSignature, ESquareFunctionType, EAbilityHandle);

class TOWERDEFENCETHING_API SContextMenuSquareWidget : public SCompoundWidget {

public:
	SLATE_BEGIN_ARGS(SContextMenuSquareWidget) :
		_tdUIResources()
	{}
	SLATE_ARGUMENT(TWeakPtr<FSlateGameResources>, tdUIResources)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	~SContextMenuSquareWidget();
	FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	FReply OnMouseButtonDoubleClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	void SetImageBrushWithName(FName newBrushName);
	void SetSWData(const SquareWidgetData& newSWData);

	TUniquePtr<SquareWidgetData> SWData = nullptr;
	FClickedSignature OnClicked;
	bool IsClickable = false;

protected:
	const FSlateBrush* GetImageBrushFromName(FName newBrushName) const;
	TWeakPtr<FSlateGameResources> tdUIResources;
	FSlateBrush imageBrush;
};
