// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Slate/SlateGameResources.h"

#include "SlateComps/SBuilderMenuWidget.h"
#include "SlateComps/SquareWidgetData.h"
#include "../TowerDefenceThingPlayerController.h"
#include "TDPlayerHUD.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FBuildCommandSignature, int);

UCLASS()
class TOWERDEFENCETHING_API ATDPlayerHUD : public AHUD {
	GENERATED_BODY()

public:
	ATDPlayerHUD();

	//UPROPERTY()
	FBuildCommandSignature BuildCommandDelegate;

	const FSlateFontInfo fontinfo = FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Medium.ttf"), 36);
	FSlateFontInfo BigFont;

	TSharedPtr<SWidget> LivesWidgetPtr;
	TSharedPtr<SBuilderMenuWidget> BuildContextMenuPtr;

	virtual void BeginDestroy() override;
	void ReceivedButtonInput(ESquareFunctionType, EAbilityHandle);
	void ResetSquareWidgetData(int8 x, int8 y) const;
	void OverrideSquareWidgetData(int8 x, int8 y, SquareWidgetData swd) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void CreateLivesWidget();
	void CreateContextMenuWidget();

	TObjectPtr<ATowerDefenceThingPlayerController> GetPlayerOwner();
	TSharedPtr<FSlateGameResources> TDUIResources;

private:
	int32* LivesPtr = nullptr;
};
