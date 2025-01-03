// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"

#include "Abilities/TDAbility.h"
#include "ClickableUnit.h"
#include "Input/IMC_TD_Def.h"
#include "TowerDefenceThingPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

DECLARE_DELEGATE_OneParam(FGoldChangedSignature, int32 const);

UCLASS()
class ATowerDefenceThingPlayerController : public APlayerController {
	GENERATED_BODY()

public:
	ATowerDefenceThingPlayerController();
	virtual void BeginDestroy() override;

	virtual void Tick(float DeltaTime) override;

	FGoldChangedSignature FGoldChangedDelegate;

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	// Set in editor
	UPROPERTY(EditAnywhere, Category = Input)
	UIMC_TD_Def* CustomMappingContext;

	// Set in editor
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LeftClickAction;

	// Set in editor
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* RightClickAction;

	void ConsumeHUDButtonInput(EAbilityHandle);

	void AddPlayerGold(int32 amount);
	void RemovePlayerGold(int32 amount);
	int32 GetPlayerGold() const;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	TSoftObjectPtr<APawn> SelectedPawnPtr = nullptr;
	//APawn* SelectedPawnPtr = nullptr;

	int32 PlayerGold { 0 };

	void HandleSelectedUnit();
	void SendUnitDataToHUD(IClickableUnit* unit, EUnitType type);

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

	/** Input handlers for SetDestination action. */
	void OnSelectInput();

	void OnMoveInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();

private:
	FVector CachedDestination;
	float FollowTime; // For how long it has been pressed

	bool HasSelectedPawn { false };
};


