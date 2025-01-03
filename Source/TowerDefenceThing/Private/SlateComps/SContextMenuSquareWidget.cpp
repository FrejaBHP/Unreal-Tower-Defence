// Dragons rule ok


#include "SlateComps/SContextMenuSquareWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SContextMenuSquareWidget::Construct(const FArguments& InArgs) {
	tdUIResources = InArgs._tdUIResources;
	imageBrush.DrawAs = ESlateBrushDrawType::Image;

	SetImageBrushWithName("empty_Brush");
	
	ChildSlot
	[
		SNew(SBox)
		.HeightOverride(72)
		.WidthOverride(72)
		[
			SAssignNew(ProgressBarPtr, SProgressBar)
			.Percent(0.f)
			.BackgroundImage(&imageBrush)
			.BarFillType(EProgressBarFillType::BottomToTop)
			.FillColorAndOpacity(FSlateColor(FLinearColor(0.5f, 0.5f, 0.5f, 0.5f)))
		]
	];
}

void SContextMenuSquareWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) {
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
	if (BoundAbility) {
		UpdateCooldown();
	}
}

void SContextMenuSquareWidget::OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) {
	if (OnEntered.IsBound() && BoundAbility) {
		OnEntered.Execute(BoundAbility, GetTickSpaceGeometry());
	}
}

FReply SContextMenuSquareWidget::OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) {
	if (BoundAbility) {
		FVector2D mouseMovePos = MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());
	}

	return FReply::Handled();
}

void SContextMenuSquareWidget::OnMouseLeave(const FPointerEvent& MouseEvent) {
	if (OnEntered.IsBound() && BoundAbility) {
		OnLeft.Execute();
	}
}

FReply SContextMenuSquareWidget::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) {
	if (OnClicked.IsBound() && IsClickable) {
		OnClicked.Execute(CurrentAbilityHandle);
	}
	return FReply::Handled();
}

FReply SContextMenuSquareWidget::OnMouseButtonDoubleClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) {
	if (OnClicked.IsBound() && IsClickable) {
		OnClicked.Execute(CurrentAbilityHandle);
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

void SContextMenuSquareWidget::UpdateCooldown() {
	if (BoundAbility->IsReady()) {
		CooldownRatio = 0.f;
	}
	else {
		CooldownRatio = BoundAbility->GetCooldownTimer() / BoundAbility->Cooldown;
	}

	ProgressBarPtr->SetPercent(CooldownRatio);
}

// Updates bound ability pointer and sets up necessary data like if it should be able to be clicked, the icon, etc
void SContextMenuSquareWidget::SetBoundAbility(UTDAbility* ability) {
	BoundAbility = ability;

	if (BoundAbility) {
		CurrentAbilityHandle = BoundAbility->AbilityHandle;
		CurrentAbilityBrushName = BoundAbility->AbilityHUDBrushName;
		IsClickable = ((BoundAbility->AbilityCast == EAbilityCast::Active) ? true : false);
	}
	// If ability pointer is null, set up the widget as "empty"
	else {
		CurrentAbilityHandle = EAbilityHandle::NONE;
		CurrentAbilityBrushName = "empty_Brush";
		IsClickable = false;
		ProgressBarPtr->SetPercent(0.f);
	}

	SetImageBrushWithName(CurrentAbilityBrushName);
}

SContextMenuSquareWidget::~SContextMenuSquareWidget() {
	tdUIResources.Reset();

	//UE_LOG(LogTemp, Warning, TEXT("Square Widget resources unloaded"));
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
