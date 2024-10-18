// Dragons rule ok

#include <TDGameInstance.h>
#include "SlateComps/SLivesWidget.h"
#include "SlateComps/SContextMenuSquareWidget.h"
#include "TDPlayerHUD.h"

ATDPlayerHUD::ATDPlayerHUD() {
	
}

void ATDPlayerHUD::BeginPlay() {
	Super::BeginPlay();

	NewFont = FStyleDefaults::GetFontInfo(); // HOLY SHIT
	NewFont.Size = 48;

	LivesPtr = &Cast<UTDGameInstance>(GetGameInstance())->Lives;
	TDUIResources = Cast<UTDGameInstance>(GetGameInstance())->GetSlateGameResources();

	if (LivesPtr != nullptr) {
		GEngine->GameViewport->AddViewportWidgetContent(
			SAssignNew(LivesWidgetPtr, SLivesWidget)
			.font(NewFont)
			.livesPtr(LivesPtr)
		);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Lives pointer failed"));
	}

	if (TDUIResources.IsValid()) {
		GEngine->GameViewport->AddViewportWidgetContent(
			SAssignNew(BuildContextMenuPtr, SBuilderMenuWidget)
			.tdUIResources(TDUIResources)
		);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("UIResources invalid"));
	}

	if (BuildContextMenuPtr.IsValid()) {
		BuildContextMenuPtr->GridPanelSquareArray[2][2]->SetImageBrushWithName("fireball_new_Brush");

		for (size_t i = 0; i < BuildContextMenuPtr->GridPanelSquareArray.Num(); i++) {
			for (size_t j = 0; j < BuildContextMenuPtr->GridPanelSquareArray[i].Num(); j++) {
				BuildContextMenuPtr->GridPanelSquareArray[i][j]->OnClicked.BindUObject(this, &ATDPlayerHUD::ReceivedButtonInput);
			}
		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Menu pointer invalid"));
	}
}

TObjectPtr<ATowerDefenceThingPlayerController> ATDPlayerHUD::GetPlayerOwner() {
	return Cast<ATowerDefenceThingPlayerController>(PlayerOwner);
}

void ATDPlayerHUD::ReceivedButtonInput(ESquareFunctionType type, int32 id) {
	GetPlayerOwner()->ConsumeHUDButtonInput(type, id);
}
