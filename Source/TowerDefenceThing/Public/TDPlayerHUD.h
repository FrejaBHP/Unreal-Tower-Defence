// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SlateComps/SquareWidgetData.h"
#include "Slate/SlateGameResources.h"
#include "SlateComps/SBuilderMenuWidget.h"
#include "../TowerDefenceThingPlayerController.h"
#include "TDPlayerHUD.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FBuildCommandSignature, int);

UCLASS()
class TOWERDEFENCETHING_API ATDPlayerHUD : public AHUD {
	GENERATED_BODY()

public:
	ATDPlayerHUD();
	void ReceivedButtonInput(ESquareFunctionType, int32);

	//UPROPERTY()
	FBuildCommandSignature BuildCommandDelegate;

	const FSlateFontInfo fontinfo = FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Medium.ttf"), 36);
	FSlateFontInfo NewFont;

	TSharedPtr<SWidget> LivesWidgetPtr;
	TSharedPtr<SBuilderMenuWidget> BuildContextMenuPtr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TObjectPtr<ATowerDefenceThingPlayerController> GetPlayerOwner();
	TSharedPtr<FSlateGameResources> TDUIResources;

private:
	int32* LivesPtr = nullptr;
};
