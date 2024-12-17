// Copyright Epic Games, Inc. All Rights Reserved.

#include "TowerDefenceThingPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

#include "TowerDefenceThingCharacter.h"
#include "TDPlayerHUD.h"


DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ATowerDefenceThingPlayerController::ATowerDefenceThingPlayerController() {
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void ATowerDefenceThingPlayerController::BeginPlay() {
	// Call the base class  
	Super::BeginPlay();

	SelectedPawnPtr = GetPawn();
}

void ATowerDefenceThingPlayerController::SetupInputComponent() {
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {
		Subsystem->AddMappingContext(CustomMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent)) {
		EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Started, this, &ATowerDefenceThingPlayerController::OnSelectInput);

		EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Started, this, &ATowerDefenceThingPlayerController::OnMoveInputStarted);
		EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Triggered, this, &ATowerDefenceThingPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Completed, this, &ATowerDefenceThingPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Canceled, this, &ATowerDefenceThingPlayerController::OnSetDestinationReleased);
	}
	else {
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATowerDefenceThingPlayerController::AddPlayerGold(int32 amount) {
	PlayerGold += amount;

	FGoldChangedDelegate.ExecuteIfBound(GetPlayerGold());
}

void ATowerDefenceThingPlayerController::RemovePlayerGold(int32 amount) {
	if ((PlayerGold - amount) < 0) {
		PlayerGold = 0;
	}
	else {
		PlayerGold -= amount;
	}

	FGoldChangedDelegate.ExecuteIfBound(GetPlayerGold());
}

int32 ATowerDefenceThingPlayerController::GetPlayerGold() const {
	return PlayerGold;
}

void ATowerDefenceThingPlayerController::OnSelectInput() {
	FHitResult Hit;
	bool bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, true, Hit);

	if (bHitSuccessful) {
		AActor* tempActor = Hit.GetActor();

		// If clicked actor implements IClickableUnit, grab it
		if (tempActor != nullptr && tempActor->Implements<UClickableUnit>()) {
			SelectedPawnPtr = Cast<APawn>(tempActor);
			HandleSelectedUnit();
		}
	}
	// If the landscape is clicked and currently selected unit isn't the player unit, select it
	else if (GetPawn() != SelectedPawnPtr) {
		SelectedPawnPtr = GetPawn();
		HandleSelectedUnit();
	}
}

// When unit is selected, update HUD to reflect it and show stats + abilities
void ATowerDefenceThingPlayerController::HandleSelectedUnit() {
	IClickableUnit* selectedUnit = Cast<IClickableUnit>(SelectedPawnPtr);
	EUnitType unitType = selectedUnit->GetUnitType();

	/*
	if (unitType == EUnitType::Tower) {
		UE_LOG(LogTemp, Warning, TEXT("Tower"));
	}
	else if (unitType == EUnitType::Enemy) {
		UE_LOG(LogTemp, Warning, TEXT("Enemy"));
	}
	else if (unitType == EUnitType::Player) {
		UE_LOG(LogTemp, Warning, TEXT("Player"));
	}
	*/

	GetAndConvertAbilitiesToSWD(selectedUnit, unitType);
}

void ATowerDefenceThingPlayerController::GetAndConvertAbilitiesToSWD(IClickableUnit* unit, EUnitType type) {
	auto& abilities = unit->GetAbilityComponent().Abilities;
	auto pHUD = GetHUD<ATDPlayerHUD>();

	for (size_t i = 0; i < 4; i++) {
		// MIDLERTIDIG LØSNING PÅ PLADS I HUD. ÆNDR SENERE TIL EN LIDT MERE SOFISTIKERET METODE
		if (i < abilities.Num()) {
			// MIDLERTIDIGT FIKS TIL FJENDERS ABILITIES
			if (type != EUnitType::Enemy && abilities[i]->AbilityCast == EAbilityCast::Active) {
				pHUD->OverrideSquareWidgetAbility(i, 2, abilities[i]);
			}
			else {
				pHUD->OverrideSquareWidgetAbility(i, 2, abilities[i]);
			}
		}
		else {
			pHUD->ResetSquareWidgetData(i, 2);
		}
	}
}

void ATowerDefenceThingPlayerController::OnMoveInputStarted() {
	StopMovement();
}

// Triggered every frame when the input is held down
void ATowerDefenceThingPlayerController::OnSetDestinationTriggered() {
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	// If we hit a surface, cache the location
	if (bHitSuccessful) {
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr) {
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void ATowerDefenceThingPlayerController::OnSetDestinationReleased() {
	// If it was a short press
	if (FollowTime <= ShortPressThreshold) {
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

// Called when an Ability is pressed in the HUD. Has access to the ability's handle for now (should be the ability itself later down the line)
void ATowerDefenceThingPlayerController::ConsumeHUDButtonInput(EAbilityHandle aHandle) {
	UTDAbilityComponent& abilityComp = Cast<IClickableUnit>(SelectedPawnPtr)->GetAbilityComponent(); // Pawn is only assigned if interface is implemented, so this is safe
	abilityComp.TryCastAbility(aHandle);

	//UE_LOG(LogTemp, Warning, TEXT("Received input, type: %s, id: %i"), *UEnum::GetValueAsString(type), (int)aHandle);
}

void ATowerDefenceThingPlayerController::BeginDestroy() {
	Super::BeginDestroy();
}
