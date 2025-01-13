// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers/TowerBasePawn.h"

// Sets default values
ATowerBasePawn::ATowerBasePawn() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!BoxComponent) {
		BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
		RootComponent = BoxComponent;
		BoxComponent->InitBoxExtent(FVector(50., 50., 25.));
		BoxComponent->SetMobility(EComponentMobility::Stationary);
		BoxComponent->SetCollisionProfileName(FName("TDTower"));
	}
	
	if (!CapsuleComponent) {
		CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Overlap Range"));
		CapsuleComponent->SetupAttachment(BoxComponent);
		CapsuleComponent->SetMobility(EComponentMobility::Stationary);
		CapsuleComponent->SetCollisionProfileName(FName("TowerTargeting"));
		CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ATowerBasePawn::OnOverlapBegin);
		CapsuleComponent->OnComponentEndOverlap.AddDynamic(this, &ATowerBasePawn::OnOverlapEnd);
	}

	if (!SpriteComponent) {
		SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Visible Sprite"));
		SpriteComponent->SetupAttachment(BoxComponent);
		SpriteComponent->SetCastShadow(true);
		SpriteComponent->SetMobility(EComponentMobility::Stationary);

		FRotator rotator = { 0., 90., 0. };
		SpriteComponent->AddRelativeRotation(rotator.Quaternion());
	}

	if (!AbilityComponent) {
		AbilityComponent = CreateDefaultSubobject<UTDAbilityComponent>(TEXT("Abilities"));
		AbilityComponent->SetupAttachment(BoxComponent);
		AbilityComponent->SetMobility(EComponentMobility::Stationary);
	}

	if (!SelectionCircleWidgetComponent) {
		SelectionCircleWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Selection Circle"));
		SelectionCircleWidgetComponent->SetupAttachment(BoxComponent);
		SelectionCircleWidgetComponent->SetPivot(FVector2D{ 0.5, 0.5 });
		FRotator widgetRotator = { 90., 0., 0. };
		SelectionCircleWidgetComponent->AddRelativeRotation(widgetRotator.Quaternion());
		SelectionCircleWidgetComponent->SetCastShadow(false);

		SetSelectionCircleVisibility(false);
	}

	BaseAttributeSet = MakeUnique<TowerBaseTDAttributes>();
	AttackAttributeSet = MakeUnique<TowerAttackTDAttributes>();
}

// Called when the game starts or when spawned
void ATowerBasePawn::BeginPlay() {
	Super::BeginPlay();

	/*
	UPlayer* player = GetNetOwningPlayer();
	if (player) {
		FName name = player->GetFName();
		UE_LOG(LogTemp, Warning, TEXT("Tower owner: %s"), *name.ToString());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No player owner"));
	}
	*/

	SelectionCircleWidgetComponent->SetSlateWidget(
		SAssignNew(SelectionCircleWidgetPtr, SSelectionWidget)
	);

	if (BoxComponent && SelectionCircleWidgetPtr) {
		FVector extent = BoxComponent->Bounds.GetBox().GetSize();
		SelectionCircleWidgetPtr->SetColourGreen();

		SelectionCircleWidgetComponent->AddRelativeLocation(FVector(0., 0., 5. - extent.Z));
		SelectionCircleWidgetComponent->SetDrawSize(FVector2D(extent.X, extent.Y));
	}
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
	else if (EnemiesInRange > 0) {
		GetNewTarget();
	}
}

void ATowerBasePawn::SetSelectionCircleVisibility(bool doVisible) {
	if (IsValid(SelectionCircleWidgetComponent)) {
		if (doVisible) {
			SelectionCircleWidgetComponent->SetVisibility(true);
		}
		else {
			SelectionCircleWidgetComponent->SetVisibility(false);
		}
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

void ATowerBasePawn::OnOverlapBegin(UPrimitiveComponent* CapsComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	EnemiesInRange++;

	//UE_LOG(LogTemp, Warning, TEXT("Enemy entered, now %i in range"), EnemiesInRange);
}

void ATowerBasePawn::OnOverlapEnd(UPrimitiveComponent* CapsComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	EnemiesInRange--;

	if (OtherActor == TowerTarget.Get()) {
		TowerTarget = nullptr;
	}

	//UE_LOG(LogTemp, Warning, TEXT("Enemy left, now %i in range"), EnemiesInRange);
}

void ATowerBasePawn::OnSelect() {
	SetSelectionCircleVisibility(true);
}

void ATowerBasePawn::OnDeselect() {
	SetSelectionCircleVisibility(false);
}

void ATowerBasePawn::GetNewTarget() {
	TArray<AActor*> actorArray;
	CapsuleComponent->GetOverlappingActors(actorArray);

	//UE_LOG(LogTemp, Warning, TEXT("Overlapping enemies: %i"), actorArray.Num());

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
		SetTarget(target);

		return true;
	}
	else {
		return false;
	}
}

void ATowerBasePawn::SetTarget(AActor* target) {
	//UE_LOG(LogTemp, Warning, TEXT("Target set"));
	TowerTarget = target;
	TowerTargetInterface = Cast<IEnemyUnit>(target);
}

void ATowerBasePawn::TryAttackTarget() {
	//UE_LOG(LogTemp, Warning, TEXT("Trying to attack target"));
	if (TowerTarget.IsValid() && TowerTargetInterface->GetCurrentHealth() > 0.f) {
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

void ATowerBasePawn::OnHitEnemy(float damage, TWeakObjectPtr<AActor> enemy) {
	IEnemyUnit* enemyInterface = Cast<IEnemyUnit>(enemy);
	ApplyTowerDamageToEnemy(damage, enemyInterface);
}

void ATowerBasePawn::ApplyTowerDamageToEnemy(float damage, IEnemyUnit* enemyInterface) {
	enemyInterface->TakeDamage(0, damage);
}

void ATowerBasePawn::OnSplashEnemies(TArray<AActor*> enemies) {
	for (size_t i = 0; i < enemies.Num(); i++) {
		IEnemyUnit* enemyInterface = Cast<IEnemyUnit>(enemies[i]);
		ApplyTowerSplashToEnemy(enemyInterface);
	}
}

void ATowerBasePawn::ApplyTowerSplashToEnemy(IEnemyUnit* enemyInterface) {
	float damage = Cast<UTDGameInstance>(GetGameInstance())->RandStream.FRandRange(AttackAttributeSet->MinDamage->GetCurrentValue(), AttackAttributeSet->MaxDamage->GetCurrentValue());
	damage *= AttackAttributeSet->SplashPercentage->GetCurrentValue();
	enemyInterface->TakeDamage(0, damage);
}

TWeakObjectPtr<AActor> ATowerBasePawn::GetTarget() {
	return TowerTarget;
}

UTDAbilityComponent& ATowerBasePawn::GetAbilityComponent() {
	return *AbilityComponent;
}

/*
TArray<UTDAbility*>& ATowerBasePawn::GetAbilities() {
	return AbilityComponent->Abilities;
}
*/


EUnitType ATowerBasePawn::GetUnitType() {
	return UnitType;
}

FName ATowerBasePawn::GetUnitName() {
	return Name;
}

float ATowerBasePawn::GetSplashRadius() {
	return AttackAttributeSet->SplashRadius->GetCurrentValue();
}

const float& ATowerBasePawn::GetRange() {
	return BaseAttributeSet->Range->CurrentValue;
}

const float& ATowerBasePawn::GetMinDamage() {
	return AttackAttributeSet->MinDamage->CurrentValue;
}

const float& ATowerBasePawn::GetMaxDamage() {
	return AttackAttributeSet->MaxDamage->CurrentValue;
}

const float& ATowerBasePawn::GetAttackSpeed() {
	return BaseAttributeSet->AttackRate->CurrentValue;
}

void ATowerBasePawn::Remove() {
	SelectionCircleWidgetPtr.Reset();

	SetActorTickEnabled(false);
	Destroy();
}
