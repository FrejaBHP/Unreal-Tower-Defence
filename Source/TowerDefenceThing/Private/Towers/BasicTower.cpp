// Dragons rule ok


#include "Towers/BasicTower.h"

// Sets default values
ABasicTower::ABasicTower() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileComponent = CreateDefaultSubobject<UTowerProjectileComponent>(TEXT("Projectile Component"));

	Name = FName("Basic Tower");

	TargetType = ETowerTargetType::Unit;
	AttackType = ETowerAttackType::Projectile;

	BaseAttributeSet->AttackRate->Init(1.f);
	BaseAttributeSet->Range->Init(350.f);

	AttackAttributeSet->MinDamage->Init(6.f);
	AttackAttributeSet->MaxDamage->Init(8.f);
	AttackAttributeSet->Targets->Init(1.f);
	AttackAttributeSet->SplashRadius->Init(0.f);
	AttackAttributeSet->SplashPercentage->Init(0.f);

	ProjectileComponent->ProjectileAttributeSet->Chain->Init(0.f); // Currently unimplemented, keep it at 0
	ProjectileComponent->ProjectileAttributeSet->Speed->Init(1000.f);
	ProjectileComponent->ProjectileFlipbookName = "arrow_Flip";

	CapsuleComponent->SetCapsuleSize(BaseAttributeSet->Range->GetBaseValue(), BaseAttributeSet->Range->GetBaseValue() + 100.f);
}

// Called when the game starts or when spawned
void ABasicTower::BeginPlay() {
	Super::BeginPlay();
	
	SpritePtr = Cast<UTDGameInstance>(GetGameInstance())->GetSpriteByName("statue_archer_Sprite");

	if (SpritePtr != nullptr) {
		VisibleSprite = SpritePtr.Get();
		SpriteComponent->SetSprite(VisibleSprite);
	}

	AbilityComponent->AddAbility(EAbilityHandle::BasicFireball);
	AbilityComponent->DEBUGListAbilities();
}

// Called every frame
void ABasicTower::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABasicTower::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABasicTower::AttackTarget() {
	Super::AttackTarget();
	const float damage = Cast<UTDGameInstance>(GetGameInstance())->RandStream.FRandRange(AttackAttributeSet->MinDamage->GetCurrentValue(), AttackAttributeSet->MaxDamage->GetCurrentValue());
	ProjectileComponent->SpawnProjectile(damage, TowerTarget, ProjectileComponent->ProjectileFlipbookName);
}

/*
void ABasicTower::OnHitEnemy(TWeakObjectPtr<AActor> enemy) {
	Super::OnHitEnemy(enemy);
}

void ATowerBasePawn::ApplyTowerDamageToEnemy(IEnemyUnit* enemyInterface) {
	Super::ApplyDamageToEnemy(enemyInterface);
}

void ABasicTower::OnSplashEnemies(TArray<AActor*> enemies) {
	Super::OnSplashEnemies(enemies);
}

void ATowerBasePawn::ApplyTowerSplashToEnemy(IEnemyUnit* enemyInterface) {
	Super::ApplySplashToEnemy(enemyInterface);
}
*/
