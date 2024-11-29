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

void UTowerProjectileComponent::SpawnProjectile(float damage, TWeakObjectPtr<AActor> target, FString projectileFlipbookName) {
	UWorld* World = GetWorld();
	if (World) {
		ATDProjectile* newProjectile = World->SpawnActorDeferred<ATDProjectile>(ATDProjectile::StaticClass(), GetOwner()->GetActorTransform(), GetOwner());
		newProjectile->FlipbookName = projectileFlipbookName;
		newProjectile->Damage = damage;
		newProjectile->Speed = ProjectileAttributeSet->Speed->GetCurrentValue();
		newProjectile->RemainingChains = ProjectileAttributeSet->Chain->GetCurrentValue();
		newProjectile->SplashRadius = OwnerTower->GetSplashRadius();
		newProjectile->Target = target;
		newProjectile->ProjectileHitDelegate.BindUObject(this, &UTowerProjectileComponent::OnProjectileHitTarget);
		newProjectile->ProjectileSplashDelegate.BindUObject(this, &UTowerProjectileComponent::OnProjectileSplashTarget);
		newProjectile->ProjectileDestroyDelegate.BindUObject(this, &UTowerProjectileComponent::OnProjectileDestroyed);

		newProjectile->FinishSpawning(GetOwner()->GetActorTransform());
		ActiveProjectiles.Add(newProjectile);
	}
}

void UTowerProjectileComponent::ClearProjectiles() {
	if (!ActiveProjectiles.IsEmpty()) {
		for (size_t i = 0; i < ActiveProjectiles.Num(); i++) {
			ActiveProjectiles[i]->Destroy();
		}
		ActiveProjectiles.Empty();
	}
}

void UTowerProjectileComponent::OnProjectileHitTarget(ATDProjectile* projectile, TWeakObjectPtr<AActor> target) {
	OwnerTower->OnHitEnemy(projectile->Damage, target);
}

void UTowerProjectileComponent::OnProjectileSplashTarget(TArray<AActor*> splashedActors) {
	OwnerTower->OnSplashEnemies(splashedActors);
}

void UTowerProjectileComponent::OnProjectileDestroyed(ATDProjectile* projectile) {
	ActiveProjectiles.Remove(projectile);
}

void UTowerProjectileComponent::DestroyComponent(bool bPromoteChildren/*= false*/) {
	ClearProjectiles();
	Super::DestroyComponent(bPromoteChildren);
}