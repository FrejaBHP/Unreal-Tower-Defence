// Copyright Epic Games, Inc. All Rights Reserved.

#include "TowerDefenceThingPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "TowerDefenceThingCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "TDPlayerHUD.h"
#include "GameplayTags.h"
#include "Engine/LocalPlayer.h"

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
	else if (GetPawn() != SelectedPawnPtr) {
		SelectedPawnPtr = GetPawn();
		HandleSelectedUnit();
	}
}

void ATowerDefenceThingPlayerController::HandleSelectedUnit() {
	IClickableUnit* selectedUnit = Cast<IClickableUnit>(SelectedPawnPtr);
	FName unitTagName = selectedUnit->GetUnitTypeTag().GetTagName();

	if (unitTagName == FName("UnitTags.Tower")) {
		UE_LOG(LogTemp, Warning, TEXT("Tower"));
	}
	else if (unitTagName == FName("UnitTags.Enemy")) {
		UE_LOG(LogTemp, Warning, TEXT("Enemy"));
	}
	else if (unitTagName == FName("UnitTags.Player")) {
		UE_LOG(LogTemp, Warning, TEXT("Player"));
	}

	/*
	if (selectedUnit->HasGameplayTag(FGameplayTag::RequestGameplayTag(FName("UnitTags.Tower")))) {
		UE_LOG(LogTemp, Warning, TEXT("Tower"));
	}
	else if (selectedUnit->HasGameplayTag(FGameplayTag::RequestGameplayTag(FName("UnitTags.Enemy")))) {
		UE_LOG(LogTemp, Warning, TEXT("Enemy"));
	}
	else if (selectedUnit->HasGameplayTag(FGameplayTag::RequestGameplayTag(FName("UnitTags.Player")))) {
		UE_LOG(LogTemp, Warning, TEXT("Player"));
	}
	*/

	//GetHUD<ATDPlayerHUD>();
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

void ATowerDefenceThingPlayerController::ConsumeHUDButtonInput(ESquareFunctionType type, int32 id) {
	UE_LOG(LogTemp, Warning, TEXT("Received input, type: %s, id: %i"), *UEnum::GetValueAsString(type), id);
}

void ATowerDefenceThingPlayerController::BeginDestroy() {
	//CustomMappingContext->MarkAsGarbage();
	
	Super::BeginDestroy();
}
