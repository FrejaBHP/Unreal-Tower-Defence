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
		CapsuleComponent->InitCapsuleSize(40.f, 75.0f);
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
		PawnMovementComponent->SetPlaneConstraintNormal(FVector(0., 0., 1.));
		PawnMovementComponent->SetPlaneConstraintOrigin(FVector(0., 0., 75.));
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
		HealthBarWidgetComponent->AddRelativeLocation(FVector(0., 0., 75.));
		FRotator widgetRotator = { 0., 180., 0. };
		HealthBarWidgetComponent->AddRelativeRotation(widgetRotator.Quaternion());
		HealthBarWidgetComponent->SetDrawSize(FVector2D(75., 15.));
		HealthBarWidgetComponent->SetCastShadow(false);
	}

	if (!SelectionCircleWidgetComponent) {
		SelectionCircleWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Selection Circle"));
		SelectionCircleWidgetComponent->SetupAttachment(CapsuleComponent);
		SelectionCircleWidgetComponent->SetPivot(FVector2D { 0.5, 0.5 });
		FRotator widgetRotator = { 90., 0., 0. };
		SelectionCircleWidgetComponent->AddRelativeRotation(widgetRotator.Quaternion());
		SelectionCircleWidgetComponent->SetCastShadow(false);

		SetSelectionCircleVisibility(false);
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

	SelectionCircleWidgetComponent->SetSlateWidget(
		SAssignNew(SelectionCircleWidgetPtr, SSelectionWidget)
	);

	if (CapsuleComponent && SelectionCircleWidgetPtr) {
		float radius;
		float halfHeight;
		CapsuleComponent->GetScaledCapsuleSize(radius, halfHeight);
		SelectionCircleWidgetPtr->SetColourRed();

		SelectionCircleWidgetComponent->AddRelativeLocation(FVector(0., 0., 10. - halfHeight));
		SelectionCircleWidgetComponent->SetDrawSize(FVector2D(radius * 2, radius * 2));
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

void AEnemyBasePawn::SetWaveStats(float baseHealth, float baseSpeed, int32 baseBounty) {
	Bounty = baseBounty;
	float effectiveHealth = baseHealth * HealthMultiplier;
	BaseAttributeSet->Health->InitMinMax(effectiveHealth, 0.f, effectiveHealth);
	BaseAttributeSet->Speed->InitMinMax(baseSpeed, 50.f, 400.f);
}

void AEnemyBasePawn::SetFlipbook(FString flipbookName) {
	FlipbookPtr = Cast<UTDGameInstance>(GetGameInstance())->GetFlipbookByName(flipbookName);

	if (FlipbookPtr) {
		VisibleFlipbook = FlipbookPtr.Get();
		FlipbookComponent->SetFlipbook(VisibleFlipbook);
	}
	else {
		FlipbookPtr = Cast<UTDGameInstance>(GetGameInstance())->GetFlipbookByName("dg_humans32_0_Flip");
		VisibleFlipbook = FlipbookPtr.Get();
		FlipbookComponent->SetFlipbook(VisibleFlipbook);
	}
}

void AEnemyBasePawn::OnSelect() {
	SetSelectionCircleVisibility(true);
}

void AEnemyBasePawn::OnDeselect() {
	SetSelectionCircleVisibility(false);
}

void AEnemyBasePawn::SetSelectionCircleVisibility(bool doVisible) {
	if (IsValid(SelectionCircleWidgetComponent)) {
		if (doVisible) {
			SelectionCircleWidgetComponent->SetVisibility(true);
		}
		else {
			SelectionCircleWidgetComponent->SetVisibility(false);
		}
	}
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

const float& AEnemyBasePawn::GetCurrentHealth() {
	return BaseAttributeSet->Health->CurrentValue;
}

const float& AEnemyBasePawn::GetMaxHealth() {
	return BaseAttributeSet->Health->MaxValue;
}

const float& AEnemyBasePawn::GetMovementSpeed() {
	return BaseAttributeSet->Speed->CurrentValue;
}

void AEnemyBasePawn::TakeDamage(int sourcePlayer, float damage) {
	// BASIC
	float newValue = BaseAttributeSet->Health->GetCurrentValue() - damage;
	BaseAttributeSet->Health->SetCurrentValue(newValue);
	HealthBarWidgetPtr->SetHealth(BaseAttributeSet->Health->GetCurrentValue());
	
	if (!(BaseAttributeSet->Health->GetCurrentValue() > 0.f)) {
		Die();
	}
}

void AEnemyBasePawn::Die() {
	if (EnemyBountyDelegate.IsBound()) {
		EnemyBountyDelegate.Execute(0, Bounty);
	}
	EnemyDeathDecrementDelegate.ExecuteIfBound();

	HealthBarWidgetPtr.Reset();
	SelectionCircleWidgetPtr.Reset();

	SetActorTickEnabled(false);
	Destroy();
}
