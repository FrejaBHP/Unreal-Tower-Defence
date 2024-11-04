// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers/TowerBasePawn.h"

// Sets default values
ATowerBasePawn::ATowerBasePawn() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	RootComponent = BoxComponent;
	BoxComponent->InitBoxExtent(FVector(50., 50., 50.));
	BoxComponent->SetMobility(EComponentMobility::Stationary);
	BoxComponent->SetCollisionProfileName(FName("TDTower"));

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Overlap Range"));
	CapsuleComponent->SetupAttachment(BoxComponent);
	CapsuleComponent->SetMobility(EComponentMobility::Stationary);
	CapsuleComponent->SetCollisionProfileName(FName("TowerTargeting"));

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Visible Sprite"));
	SpriteComponent->SetupAttachment(BoxComponent);
	SpriteComponent->SetCastShadow(true);
	SpriteComponent->SetMobility(EComponentMobility::Stationary);

	FRotator rotator = { 0., 90., 0. };
	SpriteComponent->AddRelativeRotation(rotator.Quaternion());

	BaseAttributeSet = MakeUnique<TowerBaseTDAttributes>();
}

// Called when the game starts or when spawned
void ATowerBasePawn::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void ATowerBasePawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (AttackTimer > 0.f) {
		AttackTimer -= DeltaTime;
	}
	else if (TowerTarget != nullptr) {
		TryAttackTarget();
	}
	else {
		GetNewTarget();
	}
}

void ATowerBasePawn::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);
	SetOwner(NewController);
}

// Called to bind functionality to input
void ATowerBasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATowerBasePawn::OnSelect() {

}

EUnitType ATowerBasePawn::GetUnitType() {
	return UnitType;
}

FName ATowerBasePawn::GetUnitName() {
	return Name;
}

void ATowerBasePawn::GetNewTarget() {
	TArray<AActor*> actorArray;
	CapsuleComponent->GetOverlappingActors(actorArray);

	UE_LOG(LogTemp, Warning, TEXT("Overlapping enemies: %i"), actorArray.Num());

	if (actorArray.Num() > 0) {
		for (size_t i = 0; i < actorArray.Num(); i++) {
			if (TrySetTarget(actorArray[i])) {
				break;
			}
		}
	}
}

bool ATowerBasePawn::TrySetTarget(AActor* target) {
	if (target->Implements<UEnemyUnit>()) {
		float distanceToActor = GetHorizontalDistanceTo(target);
		UE_LOG(LogTemp, Warning, TEXT("Distance to target: %f"), distanceToActor);

		if (distanceToActor <= BaseAttributeSet->Range->GetCurrentValue()) {
			SetTarget(target);

			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

void ATowerBasePawn::SetTarget(AActor* target) {
	UE_LOG(LogTemp, Warning, TEXT("Target set"));
	TowerTarget = target;
	TowerTargetInterface = Cast<IEnemyUnit>(target);
}

void ATowerBasePawn::TryAttackTarget() {
	UE_LOG(LogTemp, Warning, TEXT("Trying to attack target"));
	if (TowerTarget.IsValid() && GetHorizontalDistanceTo(TowerTarget.Get()) <= BaseAttributeSet->Range->GetCurrentValue() && TowerTargetInterface->GetCurrentHealth() > 0.f) {
		AttackTarget();
	}
	else {
		TowerTarget.Reset();
		TowerTargetInterface = nullptr;
	}
}

void ATowerBasePawn::AttackTarget() {
	AttackTimer = BaseAttributeSet->AttackRate->GetCurrentValue();
}

void ATowerBasePawn::OnHitEnemy(TWeakObjectPtr<AActor> enemy) {

}