// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Slate/SlateGameResources.h"

#include "Abilities/TDAbility.h"
#include "SlateComps/SAbilityTooltip.h"
#include "SlateComps/SBuilderMenuWidget.h"
#include "SlateComps/SGoldWidget.h"
#include "SlateComps/SLivesWidget.h"
#include "../TowerDefenceThingPlayerController.h"
#include "TDPlayerHUD.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FBuildCommandSignature, int);

UCLASS()
class TOWERDEFENCETHING_API ATDPlayerHUD : public AHUD {
	GENERATED_BODY()

public:
	ATDPlayerHUD();
	virtual void DrawHUD() override;

	//UPROPERTY()
	FBuildCommandSignature BuildCommandDelegate;

	//const FSlateFontInfo fontinfo = FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Medium.ttf"), 36);
	FSlateFontInfo BigFont;

	TSharedPtr<SLivesWidget> LivesWidgetPtr;
	TSharedPtr<SGoldWidget> GoldWidgetPtr;
	TSharedPtr<SBuilderMenuWidget> BuildContextMenuPtr;

	virtual void BeginDestroy() override;

	void UpdateLivesWidget() const;
	void UpdateGoldWidget(const int32 gold) const;

	void ReceivedButtonInput(EAbilityHandle aHandle);
	void ReceivedButtonEntered(UTDAbility* abilityPointer, const FGeometry& widgetPosition);
	void ReceivedButtonLeft();
	void OverrideSquareWidgetAbility(int8 x, int8 y, UTDAbility* ability) const;
	void ResetSquareWidgetData(int8 x, int8 y) const;

	FVector2D AbsoluteToViewport(FVector2D& absolutePosition);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void CreateLivesWidget();
	void CreateGoldWidget();
	void CreateContextMenuWidget();
	void CreateAbilityTooltipWidget();

	TObjectPtr<ATowerDefenceThingPlayerController> GetPlayerOwner();
	TSharedPtr<FSlateGameResources> TDUIResources;

	TSharedPtr<SAbilityTooltip> AbilityTooltipWidget;
	bool IsAbilityTooltipActive { false };

private:
	int32* LivesPtr = nullptr;
};
