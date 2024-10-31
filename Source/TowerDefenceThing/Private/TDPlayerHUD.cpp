// Dragons rule ok

#include "TDPlayerHUD.h"
#include <TDGameInstance.h>
#include "SlateComps/SLivesWidget.h"
#include "SlateComps/SContextMenuSquareWidget.h"
#include "SlateComps/SquareWidgetData.h"

ATDPlayerHUD::ATDPlayerHUD() {
	
}

void ATDPlayerHUD::BeginPlay() {
	Super::BeginPlay();

	BigFont = FStyleDefaults::GetFontInfo(); // HOLY SHIT
	BigFont.Size = 48;

	LivesPtr = &Cast<UTDGameInstance>(GetGameInstance())->Lives;
	TDUIResources = Cast<UTDGameInstance>(GetGameInstance())->GetSlateGameResources();

	CreateLivesWidget();
	CreateContextMenuWidget();
}

TObjectPtr<ATowerDefenceThingPlayerController> ATDPlayerHUD::GetPlayerOwner() {
	return Cast<ATowerDefenceThingPlayerController>(PlayerOwner);
}

void ATDPlayerHUD::ReceivedButtonInput(ESquareFunctionType type, int32 id) {
	GetPlayerOwner()->ConsumeHUDButtonInput(type, id);
}

void ATDPlayerHUD::CreateLivesWidget() {
	if (LivesPtr != nullptr) {
		GEngine->GameViewport->AddViewportWidgetContent(
			SAssignNew(LivesWidgetPtr, SLivesWidget)
			.font(BigFont)
			.livesPtr(LivesPtr)
		);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Lives pointer failed, lives widget not created"));
	}
}

void ATDPlayerHUD::CreateContextMenuWidget() {
	if (TDUIResources.IsValid()) {
		GEngine->GameViewport->AddViewportWidgetContent(
			SAssignNew(BuildContextMenuPtr, SBuilderMenuWidget)
			.tdUIResources(TDUIResources.ToWeakPtr())
		);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("UIResources invalid, context menu widget not created"));
	}

	if (BuildContextMenuPtr.IsValid()) {
		for (size_t i = 0; i < BuildContextMenuPtr->GridPanelSquareArray.Num(); i++) {
			for (size_t j = 0; j < BuildContextMenuPtr->GridPanelSquareArray[i].Num(); j++) {
				BuildContextMenuPtr->GridPanelSquareArray[i][j]->OnClicked.BindUObject(this, &ATDPlayerHUD::ReceivedButtonInput);
			}
		}

		
		BuildContextMenuPtr->GridPanelSquareArray[0][2]->SetSWData(SquareWidgetData { ESquareFunctionType::None, 1, "icon_fireball_Brush", 0, 0 });
		BuildContextMenuPtr->GridPanelSquareArray[3][2]->SetSWData(SquareWidgetData { ESquareFunctionType::Build, 2, "icon_fireball_Brush", 0, 0 });
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Menu pointer invalid, button widgets not created"));
	}
}

void ATDPlayerHUD::BeginDestroy() {
	TDUIResources.Reset();
	LivesWidgetPtr.Reset();
	BuildContextMenuPtr.Reset();

	Super::BeginDestroy();
}
