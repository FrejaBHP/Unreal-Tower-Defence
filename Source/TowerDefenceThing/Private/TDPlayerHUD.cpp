// Dragons rule ok

#include "TDPlayerHUD.h"

#include "Widgets/Layout/SConstraintCanvas.h"
#include "Widgets/SCanvas.h"

#include "AbilityEnums.h"
#include "SlateComps/SContextMenuSquareWidget.h"
#include <TDGameInstance.h>


ATDPlayerHUD::ATDPlayerHUD() {
	
}

void ATDPlayerHUD::BeginPlay() {
	Super::BeginPlay();

	BigFont = FStyleDefaults::GetFontInfo(); // HOLY SHIT
	BigFont.Size = 48;

	LivesPtr = &Cast<UTDGameInstance>(GetGameInstance())->Lives;
	TDUIResources = Cast<UTDGameInstance>(GetGameInstance())->GetSlateGameResources();

	CreateLivesWidget();
	CreateGoldWidget();
	CreateContextMenuWidget();
	CreateAbilityTooltipWidget();

	GetPlayerOwner()->FGoldChangedDelegate.BindUObject(this, &ATDPlayerHUD::UpdateGoldWidget);
}

void ATDPlayerHUD::DrawHUD() {
	Super::DrawHUD();
}

TObjectPtr<ATowerDefenceThingPlayerController> ATDPlayerHUD::GetPlayerOwner() {
	return Cast<ATowerDefenceThingPlayerController>(PlayerOwner);
}

void ATDPlayerHUD::UpdateLivesWidget() const {
	LivesWidgetPtr->UpdateLivesCounter();
}

void ATDPlayerHUD::UpdateGoldWidget(const int32 gold) const {
	GoldWidgetPtr->SetGoldCount(gold);
}

void ATDPlayerHUD::ReceivedButtonInput(EAbilityHandle aHandle) {
	GetPlayerOwner()->ConsumeHUDButtonInput(aHandle);
}

void ATDPlayerHUD::ReceivedButtonEntered(UTDAbility* abilityPointer, const FGeometry& widgetPosition) {
	
	//==================================================================================================
	// Jeg giver simpelthen op																			
	// Det er nu tredje dag, og jeg kan stadig ikke forstå, hvorfor tingene opfører sig, som de gør.	
	// Uanset hvad jeg prøver eller slår op, finder jeg ingen løsning.									
	// Tooltip featuren må forblive ikke færdig, fordi jeg gider ikke mere.								
	// Nyd kirkegården af forsøg og logging. Suk.														
	//==================================================================================================

	/*
	FVector2D viewportPosition = AbsoluteToViewport(position);
	//UE_LOG(LogTemp, Warning, TEXT("Viewport cposition of button: %s"), *viewportPosition.ToString());

	FVector2D tooltipSize = ActiveTooltipWidget->GetTickSpaceGeometry().GetAbsoluteSize();
	FVector2D tooltipLSize = ActiveTooltipWidget->GetTickSpaceGeometry().GetLocalSize();
	FVector2D tooltipLASize = ActiveTooltipWidget->GetTickSpaceGeometry().LocalToAbsolute(tooltipLSize);
	FVector2D tooltipALSize = ActiveTooltipWidget->GetTickSpaceGeometry().AbsoluteToLocal(tooltipSize);
	UE_LOG(LogTemp, Warning, TEXT("Tooltip widget size: %s"), *tooltipSize.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Tooltip widget local size: %s"), *tooltipLSize.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Tooltip widget local to absolute size: %s"), *tooltipLASize.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Tooltip widget absolute to local size: %s"), *tooltipALSize.ToString());
	FVector2D vwpSize = vwpWidgetGeo.GetAbsoluteSize();

	// Cookie cutter workaround? Nope
	FVector2D tooltipLocalPos = vwpWidgetGeo.AbsoluteToLocal(ActiveTooltipWidget->GetTickSpaceGeometry().GetAbsolutePosition());
	FVector2D buttonMidLocalPos = vwpWidgetGeo.AbsoluteToLocal(position);
	FVector2D tooltipAbsolutePos = ActiveTooltipWidget->GetTickSpaceGeometry().GetAbsolutePosition();

	FVector2D offsetToOffset = -tooltipLocalPos;
	UE_LOG(LogTemp, Warning, TEXT("offsetOffset: %s"), *offsetToOffset.ToString());

	FVector2D ratio = tooltipALSize / vwpSize;
	FVector2D adjustedPosition = ratio * position;
	FVector2D testPosition = position + offsetToOffset - FVector2D(312, 96);
	FVector2D testOffset = vwpWidgetGeo.LocalToAbsolute(offsetToOffset + buttonMidLocalPos);

	UE_LOG(LogTemp, Warning, TEXT("Pos: %s"), *position.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Ratio: %s"), *ratio.ToString());
	UE_LOG(LogTemp, Warning, TEXT("adjustPos: %s"), *adjustedPosition.ToString());
	UE_LOG(LogTemp, Warning, TEXT("testPos: %s"), *testPosition.ToString());

	FVector2D tooltipLocalPos = vwpWidgetGeo.AbsoluteToLocal(ActiveTooltipWidget->GetTickSpaceGeometry().GetAbsolutePositionAtCoordinates(FVector2D::ZeroVector));
	FVector2D tooltipAbsolutePos = ActiveTooltipWidget->GetTickSpaceGeometry().GetAbsolutePosition();

	FVector2D TESTLOL = ActiveTooltipWidget->GetTickSpaceGeometry().AbsoluteToLocal(position);
	
	FVector2D realOffsetMaybe = position + tooltipRelativeOffset;
	FVector2D realOffsetMaybe = position + tooltipRelativeOffset - FVector2D(312, 72);

	UE_LOG(LogTemp, Warning, TEXT("Button mid pos: %s"), *position.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Tooltip local to button: %s"), *TESTLOL.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Tooltip slot child position: %s"), *ActiveTooltipWidget->ConstraintCanvasSlot->GetWidget()->GetTickSpaceGeometry().GetAbsolutePositionAtCoordinates(FVector2D::ZeroVector).ToString());
	UE_LOG(LogTemp, Warning, TEXT("offset: %s"), *realOffsetMaybe.ToString());

	UE_LOG(LogTemp, Warning, TEXT("CCanvas paint geometry: %s"), *ActiveTooltipWidget->GetContentWidget()->GetPaintSpaceGeometry().ToString());
	UE_LOG(LogTemp, Warning, TEXT("CCanvas slot alignment: %s"), *ActiveTooltipWidget->CanvasSlot->GetAlignment().ToString());
	UE_LOG(LogTemp, Warning, TEXT("CCanvas slot topleft offset: %s"), *ActiveTooltipWidget->ConstraintCanvasSlot->GetOffset().GetTopLeft().ToString());
	UE_LOG(LogTemp, Warning, TEXT("A to Local position of tooltip: %s"), *vwpWidgetGeo.AbsoluteToLocal(ActiveTooltipWidget->GetTickSpaceGeometry().GetAbsolutePosition()).ToString());
	UE_LOG(LogTemp, Warning, TEXT("Absolute position of tooltip: %s"), *ActiveTooltipWidget->GetTickSpaceGeometry().GetAbsolutePosition().ToString());
	UE_LOG(LogTemp, Warning, TEXT("Tooltip paint geometry: %s"), *ActiveTooltipWidget->GetPaintSpaceGeometry().ToString());
	UE_LOG(LogTemp, Warning, TEXT("Centre position of tooltip: %s"), *ActiveTooltipWidget->GetPaintSpaceGeometry().GetAbsolutePositionAtCoordinates(FVector2D(0.5f, 0.5f)).ToString());
	UE_LOG(LogTemp, Warning, TEXT("Desired size of tooltip: %s"), *ActiveTooltipWidget->GetDesiredSize().ToString());
	*/

	if (!IsAbilityTooltipActive) {
		AbilityTooltipWidget->SetTooltipAbility(abilityPointer);

		// Should force widget to rearrange/resize to account for variance in description size
		AbilityTooltipWidget->MarkPrepassAsDirty();
		AbilityTooltipWidget->SlatePrepass();

		// This whole solution with offsetting is far from perfect and doesn't work as it should, but I'm leaving it as is
		const FGeometry& vwpWidgetGeo = GEngine->GameViewport->GetGameViewportWidget()->GetTickSpaceGeometry();
		const FVector2D position = widgetPosition.GetAbsolutePositionAtCoordinates(FVector2D(0.5f, 0.5f));
		
		// Always returns a positive offset from its origin out of viewport bounds, since the widget itself insists on existing outside of it
		const FVector2D tooltipRelativeOffset = vwpWidgetGeo.LocalToAbsolute(AbilityTooltipWidget->GetTickSpaceGeometry().GetLocalPositionAtCoordinates(FVector2D::ZeroVector));

		const FVector2D realOffsetMaybe = position + tooltipRelativeOffset - FVector2D(600, 72);
		AbilityTooltipWidget->ConstraintCanvasSlot->SetOffset(realOffsetMaybe);

		AbilityTooltipWidget->SetVisibility(EVisibility::HitTestInvisible);
		IsAbilityTooltipActive = true;
	}
}

void ATDPlayerHUD::ReceivedButtonLeft() {
	AbilityTooltipWidget->SetVisibility(EVisibility::Collapsed);
	IsAbilityTooltipActive = false;
}

void ATDPlayerHUD::CreateLivesWidget() {
	if (LivesPtr != nullptr) {
		GEngine->GameViewport->AddViewportWidgetForPlayer(GetOwningPlayerController()->GetLocalPlayer(), 
			SAssignNew(LivesWidgetPtr, SLivesWidget)
			.Font(BigFont)
			.LivesPtr(LivesPtr)
		, 10);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Lives pointer failed, lives widget not created"));
	}
}

void ATDPlayerHUD::CreateGoldWidget() {
	GEngine->GameViewport->AddViewportWidgetForPlayer(GetOwningPlayerController()->GetLocalPlayer(),
		SAssignNew(GoldWidgetPtr, SGoldWidget)
		, 10);
}

void ATDPlayerHUD::CreateContextMenuWidget() {
	if (TDUIResources.IsValid()) {
		GEngine->GameViewport->AddViewportWidgetForPlayer(GetOwningPlayerController()->GetLocalPlayer(),
			SAssignNew(BuildContextMenuPtr, SBuilderMenuWidget)
			.tdUIResources(TDUIResources.ToWeakPtr())
		, 10);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("UIResources invalid, context menu widget not created"));
	}

	if (BuildContextMenuPtr.IsValid()) {
		for (size_t i = 0; i < BuildContextMenuPtr->GridPanelSquareArray.Num(); i++) {
			for (size_t j = 0; j < BuildContextMenuPtr->GridPanelSquareArray[i].Num(); j++) {
				BuildContextMenuPtr->GridPanelSquareArray[i][j]->OnClicked.BindUObject(this, &ATDPlayerHUD::ReceivedButtonInput);
				BuildContextMenuPtr->GridPanelSquareArray[i][j]->OnEntered.BindUObject(this, &ATDPlayerHUD::ReceivedButtonEntered);
				BuildContextMenuPtr->GridPanelSquareArray[i][j]->OnLeft.BindUObject(this, &ATDPlayerHUD::ReceivedButtonLeft);
			}
		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Menu pointer invalid, button widgets not created"));
	}
}

void ATDPlayerHUD::CreateAbilityTooltipWidget() {
	GEngine->GameViewport->AddViewportWidgetForPlayer(GetOwningPlayerController()->GetLocalPlayer(),
		SAssignNew(AbilityTooltipWidget, SAbilityTooltip)
	, 20);
}

void ATDPlayerHUD::OverrideSquareWidgetAbility(int8 x, int8 y, UTDAbility* ability) const {
	BuildContextMenuPtr->GridPanelSquareArray[x][y]->SetBoundAbility(ability);
}

void ATDPlayerHUD::ResetSquareWidgetData(int8 x, int8 y) const {
	BuildContextMenuPtr->GridPanelSquareArray[x][y]->SetBoundAbility(nullptr);
}

FVector2D ATDPlayerHUD::AbsoluteToViewport(FVector2D& absolutePosition) {
	FIntPoint vwpSize = GEngine->GameViewport->Viewport->GetSizeXY();

	const FGeometry& vwpWidgetGeo = GEngine->GameViewport->GetGameViewportWidget()->GetTickSpaceGeometry();
	FVector2D vwpPosition = vwpWidgetGeo.AbsoluteToLocal(absolutePosition);

	return vwpPosition;
	//FVector2D pixelPosition = (vwpPosition / vwpWidgetGeo.GetLocalSize()) * FVector2D(vwpSize.X, vwpSize.Y);
}

void ATDPlayerHUD::BeginDestroy() {
	TDUIResources.Reset();
	LivesWidgetPtr.Reset();
	GoldWidgetPtr.Reset();
	BuildContextMenuPtr.Reset();
	AbilityTooltipWidget.Reset();

	Super::BeginDestroy();
}
