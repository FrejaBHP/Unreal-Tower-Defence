// Copyright Epic Games, Inc. All Rights Reserved.

#include "TowerDefenceThingCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

ATowerDefenceThingCharacter::ATowerDefenceThingCharacter() {
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0., 640., 0.);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1400.f;
	CameraBoom->SetWorldRotation(FRotator(-55., 0., 0.));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	if (!AbilityComponent) {
		AbilityComponent = CreateDefaultSubobject<UTDAbilityComponent>(TEXT("Abilities"));
		AbilityComponent->SetupAttachment(RootComponent);
		AbilityComponent->SetMobility(EComponentMobility::Movable);
	}

	Name = FName("Builder");
}

void ATowerDefenceThingCharacter::Tick(float DeltaSeconds) {
    Super::Tick(DeltaSeconds);
}

void ATowerDefenceThingCharacter::OnSelect() {

}

void ATowerDefenceThingCharacter::OnDeselect() {

}

EUnitType ATowerDefenceThingCharacter::GetUnitType() {
	return UnitType;
}

FName ATowerDefenceThingCharacter::GetUnitName() {
	return Name;
}

UTDAbilityComponent& ATowerDefenceThingCharacter::GetAbilityComponent() {
	return *AbilityComponent;
}
