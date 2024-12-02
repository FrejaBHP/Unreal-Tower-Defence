// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyBasePawn.h"
#include "TDAIController.h"

// Sets default values
AEnemyBasePawn::AEnemyBasePawn() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!CapsuleComponent) {
		CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
		RootComponent = CapsuleComponent;
		CapsuleComponent->InitCapsuleSize(25.f, 75.0f);
		CapsuleComponent->SetCollisionProfileName(FName("TDUnit"));
	}

	if (!FlipbookComponent) {
		FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Visible Flipbook"));
		FlipbookComponent->SetupAttachment(CapsuleComponent);
		FlipbookComponent->SetCastShadow(true);
		FlipbookComponent->SetCollisionProfileName(FName("NoCollision"));
		FRotator spriteRotator = { 0., 90., 0. };
		FlipbookComponent->AddRelativeRotation(spriteRotator.Quaternion());
	}

	// Configure character movement
	if (!PawnMovementComponent) {
		PawnMovementComponent = CreateDefaultSubobject<UTDEnemyMovementComponent>(TEXT("Movement"));
		PawnMovementComponent->UpdatedComponent = RootComponent;
		PawnMovementComponent->bConstrainToPlane = true;
		PawnMovementComponent->SetPlaneConstraintNormal(FVector(0.f, 0.f, 1.f));
		PawnMovementComponent->SetPlaneConstraintOrigin(FVector(0.f, 0.f, 75.f));
		PawnMovementComponent->bSnapToPlaneAtStart = true;
	}

	if (!AbilityComponent) {
		AbilityComponent = CreateDefaultSubobject<UTDAbilityComponent>(TEXT("Abilities"));
		AbilityComponent->SetupAttachment(RootComponent);
		AbilityComponent->SetMobility(EComponentMobility::Stationary);
	}
	
	if (!HealthBarWidgetComponent) {
		HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Bar"));
		HealthBarWidgetComponent->SetupAttachment(CapsuleComponent);
		HealthBarWidgetComponent->AddRelativeLocation(FVector(0.f, 0.f, 75.f));
		FRotator widgetRotator = { 0., 180., 0. };
		HealthBarWidgetComponent->AddRelativeRotation(widgetRotator.Quaternion());
		HealthBarWidgetComponent->SetDrawSize(FVector2D(75.f, 15.f));
		HealthBarWidgetComponent->SetCastShadow(false);
	}

	BaseAttributeSet = MakeUnique<EnemyBaseTDAttributes>();

	AIControllerClass = ATDAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AEnemyBasePawn::BeginPlay() {
	Super::BeginPlay();
	HealthBarWidgetComponent->SetSlateWidget(
		SAssignNew(HealthBarWidgetPtr, SEnemyHealthBar)
	);

	if (BaseAttributeSet->Health->GetMaxValue() != 0.f) {
		HealthBarWidgetPtr->SetMaxHealth(BaseAttributeSet->Health->GetMaxValue());
		HealthBarWidgetPtr->SetHealth(BaseAttributeSet->Health->GetCurrentValue());
	}
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

UTDAbilityComponent& AEnemyBasePawn::GetAbilityComponent() {
	return *AbilityComponent;
}

float AEnemyBasePawn::GetCurrentHealth() {
	return BaseAttributeSet->Health->GetCurrentValue();
}

void AEnemyBasePawn::TakeDamage(float damage) {
	// BASIC
	float newValue = BaseAttributeSet->Health->GetCurrentValue() - damage;
	BaseAttributeSet->Health->SetCurrentValue(newValue);
	HealthBarWidgetPtr->SetHealth(BaseAttributeSet->Health->GetCurrentValue());
	
	if (!(BaseAttributeSet->Health->GetCurrentValue() > 0.f)) {
		Die();
	}
}

void AEnemyBasePawn::Die() {
	HealthBarWidgetPtr.Reset();
	Destroy();
}
