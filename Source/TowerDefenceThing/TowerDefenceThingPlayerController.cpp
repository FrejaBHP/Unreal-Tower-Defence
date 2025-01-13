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

#include "EnemyUnit.h"
#include "TowerDefenceThingCharacter.h"
#include "TowerUnit.h"
#include <TDGameInstance.h>
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

void ATowerDefenceThingPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	//GEngine->ClearOnScreenDebugMessages();
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("Selected: %s"), (HasSelectedPawn ? TEXT("True") : TEXT("False"))));
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Purple, FString::Printf(TEXT("Valid pawn: %s"), (SelectedPawnPtr.IsValid() ? TEXT("True") : TEXT("False"))));

	if (HasSelectedPawn && !SelectedPawnPtr.IsValid()) {
		auto pHUD = GetHUD<ATDPlayerHUD>();
		pHUD->ResetUnitInStatsPanel();

		HasSelectedPawn = false;
		SelectedPawnPtr = nullptr;
	}
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

		EnhancedInputComponent->BindAction(EscKeyboardAction, ETriggerEvent::Started, this, &ATowerDefenceThingPlayerController::SwitchMode);
	}
	else {
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATowerDefenceThingPlayerController::SwitchMode() {
	IsInBuildMode = !IsInBuildMode;

	UE_LOG(LogTemp, Warning, TEXT("Builder Mode: %s"), (IsInBuildMode ? TEXT("On") : TEXT("Off")));
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
	if (!IsInBuildMode) {
		FHitResult Hit;
		bool bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, true, Hit);

		if (bHitSuccessful) {
			auto clickedLocation = Hit.ImpactPoint;
			FVector2D gridLocation = GetNearestCentrePointInWorldGrid(clickedLocation.X, clickedLocation.Y);

			AActor* tempActor = Hit.GetActor();

			// If clicked actor implements IClickableUnit, grab it
			if (tempActor != nullptr && tempActor->Implements<UClickableUnit>()) {
				TryDeselectLastUnit();

				SelectedPawnPtr = Cast<APawn>(tempActor);
				HasSelectedPawn = true;
				HandleSelectedUnit();
			}
		}
		// If the landscape is clicked, try and grab the builder unit instead
		else {
			TrySelectBuilder();
		}
	}
	else {
		FHitResult Hit;
		bool bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel2, true, Hit);

		if (bHitSuccessful) {
			AActor* staticActor = Hit.GetActor();

			// Hold lige øje med, om den kan forsøge at tage pladser på gitteret væk fra hvor man klikkede, fx et sted, hvor man ikke må bygge
			if (staticActor->ActorHasTag(FName("Buildable"))) {
				auto clickedNormal = Hit.ImpactNormal;

				if (clickedNormal.Z > 0.95) {
					double actorBoundingBoxHeight = staticActor->GetComponentsBoundingBox().GetSize().Z;
					double actorTranslation = staticActor->GetActorTransform().GetTranslation().Z;
					double staticActorHeight = actorBoundingBoxHeight + actorTranslation;

					auto clickedLocation = Hit.ImpactPoint;
					FVector2D gridLocation = GetNearestCentrePointInWorldGrid(clickedLocation.X, clickedLocation.Y);

					//UE_LOG(LogTemp, Warning, TEXT("Clicked Location: %s"), *clickedLocation.ToString());
					//UE_LOG(LogTemp, Warning, TEXT("Grid Location: %s"), *gridLocation.ToString());

					FHitResult TowerCheckHit(ForceInit);
					FVector start { gridLocation.X, gridLocation.Y, staticActorHeight + 0.5 };
					FVector end { gridLocation.X, gridLocation.Y, staticActorHeight + 75.};
					GetWorld()->LineTraceSingleByChannel(TowerCheckHit, start, end, ECollisionChannel::ECC_GameTraceChannel1);

					if (!TowerCheckHit.GetActor()) {
						TryPlaceBuilding(ETowerHandle::BasicTower, FVector { gridLocation.X, gridLocation.Y, staticActorHeight });
					}
				}
			}
		}
	}
}

// If currently selected unit isn't the player unit, select it
void ATowerDefenceThingPlayerController::TrySelectBuilder() {
	if (GetPawn() != SelectedPawnPtr || !HasSelectedPawn) {
		TryDeselectLastUnit();

		SelectedPawnPtr = GetPawn();
		HasSelectedPawn = true;
		HandleSelectedUnit();
	}
}

// When unit is selected, update HUD to reflect it and show stats + abilities
void ATowerDefenceThingPlayerController::HandleSelectedUnit() {
	IClickableUnit* selectedUnit = Cast<IClickableUnit>(SelectedPawnPtr.Get());
	EUnitType unitType = selectedUnit->GetUnitType();

	selectedUnit->OnSelect();

	SendUnitDataToHUD(selectedUnit, unitType);
}

void ATowerDefenceThingPlayerController::TryDeselectLastUnit() {
	if (SelectedPawnPtr.IsValid()) {
		IClickableUnit* selectedUnit = Cast<IClickableUnit>(SelectedPawnPtr.Get());
		selectedUnit->OnDeselect();
	}
}

void ATowerDefenceThingPlayerController::SendUnitDataToHUD(IClickableUnit* unit, EUnitType type) {
	auto pHUD = GetHUD<ATDPlayerHUD>();
	auto& abilities = unit->GetAbilityComponent().Abilities;
	FText ftName = FText::FromName(unit->GetUnitName());
	FText ftType = FText::FromString(*UEnum::GetDisplayValueAsText(unit->GetUnitType()).ToString());

	if (type == EUnitType::Tower) {
		ITowerUnit* towerUnit = Cast<ITowerUnit>(SelectedPawnPtr.Get());
		pHUD->OverrideUnitInStatsPanel(0, ftName, ftType, &towerUnit->GetMinDamage(), &towerUnit->GetMaxDamage(), &towerUnit->GetAttackSpeed(), &towerUnit->GetRange());
	}
	else if (type == EUnitType::Enemy) {
		IEnemyUnit* enemyUnit = Cast<IEnemyUnit>(SelectedPawnPtr.Get());
		pHUD->OverrideUnitInStatsPanel(1, ftName, ftType, &enemyUnit->GetCurrentHealth(), &enemyUnit->GetMaxHealth(), &enemyUnit->GetMovementSpeed(), nullptr);
	}
	else if (type == EUnitType::Player) {
		pHUD->OverrideUnitInStatsPanel(2, ftName, ftType, nullptr, nullptr, nullptr, nullptr);
	}

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
	UTDAbilityComponent& abilityComp = Cast<IClickableUnit>(SelectedPawnPtr.Get())->GetAbilityComponent(); // Pawn is only assigned if interface is implemented, so this is safe
	abilityComp.TryCastAbility(aHandle);

	//UE_LOG(LogTemp, Warning, TEXT("Received input, type: %s, id: %i"), *UEnum::GetValueAsString(type), (int)aHandle);
}

bool ATowerDefenceThingPlayerController::TryPlaceBuilding(ETowerHandle tHandle, FVector location) {
	// Implement checks here later for things such as cost
	PlaceBuilding(tHandle, location);
	return true;
}

void ATowerDefenceThingPlayerController::PlaceBuilding(ETowerHandle tHandle, FVector location) {
	AActor* newTower = Cast<UTDGameInstance>(GetWorld()->GetGameInstance())->TManager->CreateTowerFromHandle(tHandle);
	newTower = GetWorld()->SpawnActor(newTower->GetClass(), &location);
}

// Translates a given plane vector to the middle of the nearest grid square
// Has a slight inaccuracy when dealing with doubles exactly divisible by the grid size, eg 400,000, where the floor function more or less splits the result 50/50 to 3 or 4
FVector2D ATowerDefenceThingPlayerController::GetNearestCentrePointInWorldGrid(double worldX, double worldY) {
	const int gridSize = 100;

	const int timesGridX = floor(worldX / gridSize);
	const int timesGridY = floor(worldY / gridSize);

	const double gridX = StaticCast<double>((gridSize * timesGridX) + gridSize / 2);
	const double gridY = StaticCast<double>((gridSize * timesGridY) + gridSize / 2);

	FVector2D gridVector { gridX, gridY };

	return gridVector;
}

void ATowerDefenceThingPlayerController::BeginDestroy() {
	Super::BeginDestroy();
}
