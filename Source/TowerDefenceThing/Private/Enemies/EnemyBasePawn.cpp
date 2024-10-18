// Fill out your copyright notice in the Description page of Project Settings.

#include "TDAIController.h"
#include "Enemies/EnemyBasePawn.h"

// Sets default values
AEnemyBasePawn::AEnemyBasePawn() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;
	CapsuleComponent->InitCapsuleSize(50.f, 75.0f);

	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipbookComponent"));
	FlipbookComponent->SetupAttachment(CapsuleComponent);
	FlipbookComponent->SetCastShadow(true);

	// Configure character movement
	PawnMovementComponent = CreateDefaultSubobject<UTDEnemyMovementComponent>(TEXT("PawnMovementComponent"));
	if (PawnMovementComponent != nullptr) {
		PawnMovementComponent->UpdatedComponent = RootComponent;
		PawnMovementComponent->bConstrainToPlane = true;
		PawnMovementComponent->SetPlaneConstraintNormal(FVector(0.f, 0.f, 1.f));
		PawnMovementComponent->SetPlaneConstraintOrigin(FVector(0.f, 0.f, 75.f));
		PawnMovementComponent->bSnapToPlaneAtStart = true;

		//UE_LOG(LogTemp, Display, TEXT("Max speed: %f"), PawnMovementComponent->GetMaxSpeed());
	}
	

	AIControllerClass = ATDAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AEnemyBasePawn::BeginPlay() {
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyBasePawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
