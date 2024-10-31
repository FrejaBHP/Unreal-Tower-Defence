// Dragons rule ok


#include "Towers/BasicTower.h"

// Sets default values
ABasicTower::ABasicTower() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackAttributes = CreateDefaultSubobject<UTowerAttackAttributes>(TEXT("Attack Attributes"));
	ProjectileAttributes = CreateDefaultSubobject<UTowerProjectileAttributes>(TEXT("Projectile Attributes"));

	Name = FName("Basic Tower");

	TargetType = ETowerTargetType::Unit;
	AttackType = ETowerAttackType::Projectile;

	BaseAttributes->InitRange(700.f);
	BaseAttributes->InitAttackRate(1.f);

	AttackAttributes->InitMinDamage(6.f);
	AttackAttributes->InitMaxDamage(8.f);
	AttackAttributes->InitMaxTargets(1.f);
	AttackAttributes->InitSplashRadius(0.f);
	AttackAttributes->InitSplashPercentage(0.f);

	ProjectileAttributes->InitChains(0.f);
	ProjectileAttributes->InitSpeed(2000.f);
}

// Called when the game starts or when spawned
void ABasicTower::BeginPlay() {
	Super::BeginPlay();
	
	SpritePtr = Cast<UTDGameInstance>(GetGameInstance())->GetSpriteByName("statue_archer_Sprite");

	if (SpritePtr != nullptr) {
		VisibleSprite = SpritePtr.Get();
		SpriteComponent->SetSprite(VisibleSprite);
	}
}

// Called every frame
void ABasicTower::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasicTower::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UTowerAttackAttributes* ABasicTower::GetAttackAttributes() const {
	return AttackAttributes;
}

UTowerProjectileAttributes* ABasicTower::GetProjectileAttributes() const {
	return ProjectileAttributes;
}

