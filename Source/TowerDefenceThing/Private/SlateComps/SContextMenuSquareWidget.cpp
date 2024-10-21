// Dragons rule ok


#include "SlateComps/SContextMenuSquareWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SContextMenuSquareWidget::Construct(const FArguments& InArgs) {
	SWData = new SquareWidgetData();

	tdUIResources = InArgs._tdUIResources;
	imageBrush.DrawAs = ESlateBrushDrawType::Image;

	SetImageBrushWithName(SWData->brushName);
	
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
	return tdUIResources->GetBrush(newBrushName);
}

void SContextMenuSquareWidget::SetImageBrushWithName(FName newBrushName) {
	imageBrush = *GetImageBrushFromName(newBrushName);
}

void SContextMenuSquareWidget::SetSWData(SquareWidgetData newSWData) {
	SWData->FunctionType = newSWData.FunctionType;
	SWData->FunctionID = newSWData.FunctionID;
	SWData->brushName = newSWData.brushName;
	SWData->DesiredGridX = newSWData.DesiredGridX;
	SWData->DesiredGridY = newSWData.DesiredGridY;

	if (SWData->FunctionType == ESquareFunctionType::None) {
		IsClickable = false;
	}
	else {
		IsClickable = true;
	}

	SetImageBrushWithName(SWData->brushName);
}

SContextMenuSquareWidget::~SContextMenuSquareWidget() {
	tdUIResources.Reset();
	//free(SWData);
	//SWData = nullptr;

	UE_LOG(LogTemp, Warning, TEXT("Square Widget members unloaded"));
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
