// Dragons rule ok


#include "SlateComps/SContextMenuSquareWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SContextMenuSquareWidget::Construct(const FArguments& InArgs) {
	SWData = MakeUnique<SquareWidgetData>();

	tdUIResources = InArgs._tdUIResources;
	imageBrush.DrawAs = ESlateBrushDrawType::Image;

	SetImageBrushWithName(SWData->BrushName);
	
	ChildSlot
	[
		SNew(SBox)
			.HeightOverride(96)
			.WidthOverride(96)
			[
				SNew(SImage)
				.Image(&imageBrush)
			]
	];
}

FReply SContextMenuSquareWidget::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) {
	if (OnClicked.IsBound() && IsClickable) {
		OnClicked.Execute(SWData->FunctionType, SWData->FunctionID);
	}
	return FReply::Handled();
}

FReply SContextMenuSquareWidget::OnMouseButtonDoubleClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) {
	if (OnClicked.IsBound() && IsClickable) {
		OnClicked.Execute(SWData->FunctionType, SWData->FunctionID);
	}
	return FReply::Handled();
}

const FSlateBrush* SContextMenuSquareWidget::GetImageBrushFromName(FName newBrushName) const {
	if (TSharedPtr<FSlateGameResources> lockedResources = tdUIResources.Pin()) {
		return lockedResources->GetBrush(newBrushName);
	}
	else {
		return &imageBrush; // ruh roh
	}
}

void SContextMenuSquareWidget::SetImageBrushWithName(FName newBrushName) {
	imageBrush = *GetImageBrushFromName(newBrushName);
}

void SContextMenuSquareWidget::SetSWData(const SquareWidgetData& newSWData) {
	SWData->FunctionType = newSWData.FunctionType;
	SWData->FunctionID = newSWData.FunctionID;
	SWData->BrushName = newSWData.BrushName;
	SWData->DesiredGridX = newSWData.DesiredGridX;
	SWData->DesiredGridY = newSWData.DesiredGridY;

	IsClickable = ((SWData->FunctionType == ESquareFunctionType::None) ? false : true);

	SetImageBrushWithName(SWData->BrushName);
}

SContextMenuSquareWidget::~SContextMenuSquareWidget() {
	tdUIResources.Reset();

	//UE_LOG(LogTemp, Warning, TEXT("Square Widget resources unloaded"));
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
