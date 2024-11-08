// Dragons rule ok


#include "Components/TowerProjectileComponent.h"

// Sets default values for this component's properties
UTowerProjectileComponent::UTowerProjectileComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	OwnerTower = Cast<ITowerUnit>(GetOwner());

	ProjectileAttributeSet = MakeUnique<TowerProjectileTDAttributes>();
}

// Called when the game starts
void UTowerProjectileComponent::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void UTowerProjectileComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTowerProjectileComponent::SpawnProjectile(TWeakObjectPtr<AActor> target) {
	UWorld* World = GetWorld();
	if (World) {
		ATDProjectile* newProjectile = World->SpawnActorDeferred<ATDProjectile>(ATDProjectile::StaticClass(), GetOwner()->GetActorTransform(), GetOwner());
		newProjectile->Speed = ProjectileAttributeSet->Speed->GetCurrentValue();
		newProjectile->RemainingChains = ProjectileAttributeSet->Chain->GetCurrentValue();
		newProjectile->SplashRadius = OwnerTower->GetSplashRadius();
		newProjectile->Target = target;
		newProjectile->ProjectileHitDelegate.BindUObject(this, &UTowerProjectileComponent::OnProjectileHitTarget);
		newProjectile->ProjectileSplashDelegate.BindUObject(this, &UTowerProjectileComponent::OnProjectileSplashTarget);

		newProjectile->FinishSpawning(GetOwner()->GetActorTransform());
	}
}

void UTowerProjectileComponent::OnProjectileHitTarget(ATDProjectile* projectile, TWeakObjectPtr<AActor> target) {
	OwnerTower->OnHitEnemy(target);
}

void UTowerProjectileComponent::OnProjectileSplashTarget(TArray<AActor*> splashedActors) {
	OwnerTower->ApplySplashToEnemies(splashedActors);
}
