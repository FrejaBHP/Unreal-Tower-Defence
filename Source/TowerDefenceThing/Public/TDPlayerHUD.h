// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Slate/SlateGameResources.h"

#include "Abilities/TDAbility.h"
#include "SlateComps/SAbilityTooltip.h"
#include "SlateComps/SBottomPanelsWidget.h"
#include "SlateComps/STopBarWidget.h"
#include "../TowerDefenceThingPlayerController.h"
#include "TDPlayerHUD.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FBuildCommandSignature, int);

UCLASS()
class TOWERDEFENCETHING_API ATDPlayerHUD : public AHUD {
	GENERATED_BODY()

public:
	ATDPlayerHUD();
	virtual void DrawHUD() override;

	FBuildCommandSignature BuildCommandDelegate;

	TSharedPtr<STopBarWidget> TopBarWidgetPtr;
	TSharedPtr<SBottomPanelsWidget> BottomPanelsWidgetPtr;

	virtual void BeginDestroy() override;

	void UpdateLives() const;
	void UpdateEnemiesRemaining() const;
	void UpdateWaveNumber() const;
	void UpdateGold(const int32 gold) const;

	void ReceivedButtonInput(EAbilityHandle aHandle);
	void ReceivedButtonEntered(UTDAbility* abilityPointer, const FGeometry& widgetGeometry);
	void ReceivedButtonLeft();

	void OverrideUnitInStatsPanel(int8 type, FText nameText, FText typeText, const float* stat1, const float* stat2, const float* stat3, const float* stat4) const;
	void ResetUnitInStatsPanel() const;
	void OverrideSquareWidgetAbility(int8 x, int8 y, UTDAbility* ability) const;
	void ResetSquareWidgetData(int8 x, int8 y) const;

	FVector2D AbsoluteToViewport(FVector2D& absolutePosition);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void CreateTopBarWidget();
	void CreateBottomPanelsWidget();
	void CreateAbilityTooltipWidget();

	TObjectPtr<ATowerDefenceThingPlayerController> GetPlayerOwner();
	TSharedPtr<FSlateGameResources> TDUIResources;

	TSharedPtr<SAbilityTooltip> AbilityTooltipWidget;
	bool IsAbilityTooltipActive { false };

private:
	int32* LivesPtr { nullptr };
	int32* WaveNumberPtr { nullptr };
	int32* RemainingPtr { nullptr };
};
