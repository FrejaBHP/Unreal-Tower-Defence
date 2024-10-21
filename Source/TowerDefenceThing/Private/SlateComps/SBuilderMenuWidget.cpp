// Dragons rule ok


#include "SlateComps/SBuilderMenuWidget.h"
#include "SlateOptMacros.h"
#include <Widgets/Layout/SUniformGridPanel.h>

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SBuilderMenuWidget::Construct(const FArguments& InArgs) {
	tdUIResources = InArgs._tdUIResources;

	GridPanelSquareArray.SetNum(3);
	GridPanelSquareArray[0].SetNum(4);
	GridPanelSquareArray[1].SetNum(4);
	GridPanelSquareArray[2].SetNum(4);

	ChildSlot
	.HAlign(HAlign_Right)
	.VAlign(VAlign_Bottom)
	[
		SAssignNew(GridBorderPtr, SBorder)
		.BorderImage(&brush)
		.Padding(2.f)
		.OnMouseButtonDown(this, &SBuilderMenuWidget::IgnoreMouseInput)
		.OnMouseDoubleClick(this, &SBuilderMenuWidget::IgnoreMouseInput)
		.Content()
		[
			SAssignNew(GridPanelPtr, SUniformGridPanel)
			.SlotPadding(FMargin(2.0f))
				+ SUniformGridPanel::Slot(0, 0)
				[
					SAssignNew(GridPanelSquareArray[0][0], SContextMenuSquareWidget)
					.tdUIResources(tdUIResources)
				]
				
				+ SUniformGridPanel::Slot(1, 0)
				[
					SAssignNew(GridPanelSquareArray[0][1], SContextMenuSquareWidget)
					.tdUIResources(tdUIResources)
				]

				+ SUniformGridPanel::Slot(2, 0)
				[
					SAssignNew(GridPanelSquareArray[0][2], SContextMenuSquareWidget)
					.tdUIResources(tdUIResources)
				]

				+ SUniformGridPanel::Slot(3, 0)
				[
					SAssignNew(GridPanelSquareArray[0][3], SContextMenuSquareWidget)
					.tdUIResources(tdUIResources)
				]

				+ SUniformGridPanel::Slot(0, 1)
				[
					SAssignNew(GridPanelSquareArray[1][0], SContextMenuSquareWidget)
					.tdUIResources(tdUIResources)
				]

				+ SUniformGridPanel::Slot(1, 1)
				[
					SAssignNew(GridPanelSquareArray[1][1], SContextMenuSquareWidget)
					.tdUIResources(tdUIResources)
				]

				+ SUniformGridPanel::Slot(2, 1)
				[
					SAssignNew(GridPanelSquareArray[1][2], SContextMenuSquareWidget)
					.tdUIResources(tdUIResources)
				]

				+ SUniformGridPanel::Slot(3, 1)
				[
					SAssignNew(GridPanelSquareArray[1][3], SContextMenuSquareWidget)
					.tdUIResources(tdUIResources)
				]

				+ SUniformGridPanel::Slot(0, 2)
				[
					SAssignNew(GridPanelSquareArray[2][0], SContextMenuSquareWidget)
					.tdUIResources(tdUIResources)
				]

				+ SUniformGridPanel::Slot(1, 2)
				[
					SAssignNew(GridPanelSquareArray[2][1], SContextMenuSquareWidget)
					.tdUIResources(tdUIResources)
				]

				+ SUniformGridPanel::Slot(2, 2)
				[
					SAssignNew(GridPanelSquareArray[2][2], SContextMenuSquareWidget)
					.tdUIResources(tdUIResources)
				]

				+ SUniformGridPanel::Slot(3, 2)
				[
					SAssignNew(GridPanelSquareArray[2][3], SContextMenuSquareWidget)
					.tdUIResources(tdUIResources)
				]
		]
	];
}

FReply SBuilderMenuWidget::IgnoreMouseInput(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) {
	return FReply::Handled();
}

SBuilderMenuWidget::~SBuilderMenuWidget() {
	GridPanelSquareArray.Empty();
	tdUIResources.Reset();

	UE_LOG(LogTemp, Warning, TEXT("Context Menu Widget members unloaded"));
	//GridPanelPtr.Reset();
	//GridBorderPtr.Reset();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
