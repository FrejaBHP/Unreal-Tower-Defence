// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SlateComps/SquareWidgetData.h"
#include "Input/IMC_TD_Def.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "TowerDefenceThingPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class ATowerDefenceThingPlayerController : public APlayerController {
	GENERATED_BODY()

public:
	ATowerDefenceThingPlayerController();
	virtual void BeginDestroy() override;

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	UPROPERTY(EditAnywhere, Category = Input)
	UIMC_TD_Def* CustomMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LeftClickAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* RightClickAction;

	void ConsumeHUDButtonInput(ESquareFunctionType, int32);

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();

private:
	FVector CachedDestination;

	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed
};


