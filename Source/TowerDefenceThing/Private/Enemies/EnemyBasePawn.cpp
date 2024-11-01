// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyBasePawn.h"
#include "TDAIController.h"

// Sets default values
AEnemyBasePawn::AEnemyBasePawn() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	RootComponent = CapsuleComponent;
	CapsuleComponent->InitCapsuleSize(50.f, 75.0f);
	CapsuleComponent->SetCollisionProfileName(FName("TDUnit"));

	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Visible Flipbook"));
	FlipbookComponent->SetupAttachment(CapsuleComponent);
	FlipbookComponent->SetCastShadow(true);
	FlipbookComponent->SetCollisionProfileName(FName("NoCollision"));

	FRotator rotator = { 0., 90., 0. };
	FlipbookComponent->AddRelativeRotation(rotator.Quaternion());

	// Configure character movement
	PawnMovementComponent = CreateDefaultSubobject<UTDEnemyMovementComponent>(TEXT("Movement"));
	if (PawnMovementComponent != nullptr) {
		PawnMovementComponent->UpdatedComponent = RootComponent;
		PawnMovementComponent->bConstrainToPlane = true;
		PawnMovementComponent->SetPlaneConstraintNormal(FVector(0.f, 0.f, 1.f));
		PawnMovementComponent->SetPlaneConstraintOrigin(FVector(0.f, 0.f, 75.f));
		PawnMovementComponent->bSnapToPlaneAtStart = true;
	}

	BaseAttributeSet = MakeUnique<EnemyBaseTDAttributes>();

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

void AEnemyBasePawn::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);
	SetOwner(NewController);
}

void AEnemyBasePawn::OnSelect() {
	
}

EUnitType AEnemyBasePawn::GetUnitType() {
	return UnitType;
}

FName AEnemyBasePawn::GetUnitName() {
	return Name;
}
