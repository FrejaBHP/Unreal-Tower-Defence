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

	UTDGameInstance* instance = Cast<UTDGameInstance>(GetGameInstance());

	LivesPtr = &instance->Lives;
	WaveNumberPtr = &instance->WaveNumber;
	RemainingPtr = &instance->RemainingEnemiesOnMap;
	TDUIResources = instance->GetSlateGameResources();

	CreateTopBarWidget();
	CreateBottomPanelsWidget();
	CreateAbilityTooltipWidget();

	GetPlayerOwner()->FGoldChangedDelegate.BindUObject(this, &ATDPlayerHUD::UpdateGold);
}

void ATDPlayerHUD::DrawHUD() {
	Super::DrawHUD();
}

TObjectPtr<ATowerDefenceThingPlayerController> ATDPlayerHUD::GetPlayerOwner() {
	return Cast<ATowerDefenceThingPlayerController>(PlayerOwner);
}

void ATDPlayerHUD::UpdateLives() const {
	TopBarWidgetPtr->GetLivesText();
}

void ATDPlayerHUD::UpdateEnemiesRemaining() const {
	TopBarWidgetPtr->GetRemainingText();
}

void ATDPlayerHUD::UpdateWaveNumber() const {
	TopBarWidgetPtr->GetWaveNumberText();
}

void ATDPlayerHUD::UpdateGold(const int32 gold) const {
	TopBarWidgetPtr->SetGoldAmount(gold);
}

void ATDPlayerHUD::ReceivedButtonInput(EAbilityHandle aHandle) {
	GetPlayerOwner()->ConsumeHUDButtonInput(aHandle);
}

// When the mouse cursor enters the geometry of a Context Menu button widget
void ATDPlayerHUD::ReceivedButtonEntered(UTDAbility* abilityPointer, const FGeometry& widgetGeometry) {
	if (!IsAbilityTooltipActive) {
		AbilityTooltipWidget->SetTooltipAbility(abilityPointer);

		AbilityTooltipWidget->MarkPrepassAsDirty();
		AbilityTooltipWidget->SlatePrepass();

		const FVector2D widgetMiddleAbsolutePosition = widgetGeometry.GetAbsolutePositionAtCoordinates(FVector2D(0.5f, 0.f));

		// Parent widget, aka the player's game layer, is updated every tick, while the Tooltip widget is not.
		// This results in the parent always being in lockstep with viewport size, while Tooltip widget will always return the size from the last time it appeared
		// Therefore the parent widget's tick geometry is used instead to ensure accuracy
		const FVector2D widgetMiddleLocalPosition = AbilityTooltipWidget->GetParentWidget()->GetTickSpaceGeometry().AbsoluteToLocal(widgetMiddleAbsolutePosition);

		const FVector2D tooltipSize = AbilityTooltipWidget->TooltipBorder->GetDesiredSize();
		const FVector2D widgetSize = widgetGeometry.GetLocalSize();

		const FVector2D tooltipOffset { tooltipSize.X / 2, tooltipSize.Y + widgetSize.Y / 4 };
		const FVector2D finalOffset = widgetMiddleLocalPosition - tooltipOffset;

		AbilityTooltipWidget->ConstraintCanvasSlot->SetOffset(finalOffset);

		IsAbilityTooltipActive = true;
		AbilityTooltipWidget->SetVisibility(EVisibility::HitTestInvisible);
	}
}

// When the mouse cursor leaves the geometry of a Context Menu button widget
void ATDPlayerHUD::ReceivedButtonLeft() {
	if (IsAbilityTooltipActive) {
		IsAbilityTooltipActive = false;
		AbilityTooltipWidget->SetVisibility(EVisibility::Hidden);
	}
}

void ATDPlayerHUD::CreateTopBarWidget() {
	GEngine->GameViewport->AddViewportWidgetForPlayer(GetOwningPlayerController()->GetLocalPlayer(),
		SAssignNew(TopBarWidgetPtr, STopBarWidget)
			.tdUIResources(TDUIResources.ToWeakPtr())
			.livesPtr(LivesPtr)
			.remainingPtr(RemainingPtr)
			.waveNumberPtr(WaveNumberPtr)
		, 10);
}

void ATDPlayerHUD::CreateBottomPanelsWidget() {
	GEngine->GameViewport->AddViewportWidgetForPlayer(GetOwningPlayerController()->GetLocalPlayer(),
		SAssignNew(BottomPanelsWidgetPtr, SBottomPanelsWidget)
			.tdUIResources(TDUIResources.ToWeakPtr())
		, 10);

	BottomPanelsWidgetPtr->BindContextMenuWidget(this);
}

void ATDPlayerHUD::CreateAbilityTooltipWidget() {
	GEngine->GameViewport->AddViewportWidgetForPlayer(GetOwningPlayerController()->GetLocalPlayer(),
		SAssignNew(AbilityTooltipWidget, SAbilityTooltip)
	, 20);
}

void ATDPlayerHUD::OverrideUnitInStatsPanel(int8 type, FText nameText, FText typeText, const float* stat1, const float* stat2, const float* stat3, const float* stat4) const {
	BottomPanelsWidgetPtr->BindUnitStatsPanel(type, nameText, typeText, stat1, stat2, stat3, stat4);
}

void ATDPlayerHUD::ResetUnitInStatsPanel() const {
	BottomPanelsWidgetPtr->ResetUnitStatsPanel();
}

void ATDPlayerHUD::OverrideSquareWidgetAbility(int8 x, int8 y, UTDAbility* ability) const {
	BottomPanelsWidgetPtr->ContextMenuPtr->GridPanelSquareArray[x][y]->SetBoundAbility(ability);
}

void ATDPlayerHUD::ResetSquareWidgetData(int8 x, int8 y) const {
	BottomPanelsWidgetPtr->ContextMenuPtr->GridPanelSquareArray[x][y]->SetBoundAbility(nullptr);
}

FVector2D ATDPlayerHUD::AbsoluteToViewport(FVector2D& absolutePosition) {
	FIntPoint vwpSize = GEngine->GameViewport->Viewport->GetSizeXY();

	const FGeometry& vwpWidgetGeo = GEngine->GameViewport->GetGameViewportWidget()->GetTickSpaceGeometry();
	FVector2D vwpPosition = vwpWidgetGeo.AbsoluteToLocal(absolutePosition);

	return vwpPosition;
	//FVector2D pixelPosition = (vwpPosition / vwpWidgetGeo.GetLocalSize()) * FVector2D(vwpSize.X, vwpSize.Y);
}

void ATDPlayerHUD::BeginDestroy() {
	TopBarWidgetPtr.Reset();
	BottomPanelsWidgetPtr.Reset();
	AbilityTooltipWidget.Reset();

	TDUIResources.Reset();

	Super::BeginDestroy();
}
