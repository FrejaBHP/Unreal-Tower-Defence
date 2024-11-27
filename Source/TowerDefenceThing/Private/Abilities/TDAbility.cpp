// Dragons rule ok


#include "Abilities/TDAbility.h"
#include "Abilities/TDAbilityAreaOfEffect.h"

UTDAbility::UTDAbility() {
	PrimaryComponentTick.bCanEverTick = true;
	OwnerTower = Cast<ITowerUnit>(GetOwner());
}

void UTDAbility::BeginPlay() {
	Super::BeginPlay();
}

void UTDAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// Run checks on if the ability should be allowed to be cast
// Could be checking for a valid target or if the caster has the resources to cast it
bool UTDAbility::TryCastAbility() {
	return true;
}

// When checks go through, ability is triggered
void UTDAbility::CastAbility() {

}

// Gets the remaining cooldown
float UTDAbility::GetCooldownTimer() const {
	return CooldownTimer;
}

// Sets the remaining cooldown. If reduced below 0, sets 0
void UTDAbility::SetCooldownTimer(float newCDTimer) {
	if (0.f > newCDTimer) {
		CooldownTimer = 0.f;
	}
	else {
		CooldownTimer = newCDTimer;
	}
}

// Shortcut function that can be fed deltaTime directly
void UTDAbility::ReduceCooldownTimer(float reduction) {
	SetCooldownTimer(CooldownTimer - reduction);
}

void UTDAbility::ResetCooldownTimer() {
	CooldownTimer = Cooldown;
}

// Checks if remaining cooldown is 0 (since SetCooldownTimer ensures it can't be below 0)
bool UTDAbility::IsReady() const {
	if (CooldownTimer > 0.f) {
		return false;
	}
	else {
		return true;
	}
}

AActor* UTDAbility::GetClosestTarget() {
	AActor* closestActor = nullptr;

	if (OverlapComponent) {
		TArray<AActor*> overlappingActors;
		OverlapComponent->GetOverlappingActors(overlappingActors);

		// If more than one target, find the closest one
		if (overlappingActors.Num() > 1) {
			float closestDistance = 5000;

			for (size_t i = 0; i < overlappingActors.Num(); i++) {
				float dist = overlappingActors[i]->GetDistanceTo(GetOwner());

				if (dist < closestDistance) {
					closestDistance = dist;
					closestActor = overlappingActors[i];
				}
			}
		}
		// If only one target, can skip the calculations
		else {
			closestActor = overlappingActors[0];
		}
	}

	return closestActor;
}

void UTDAbility::SpawnProjectile(TWeakObjectPtr<AActor> target, FString projectileFlipbookName) {
	UWorld* World = GetWorld();
	if (World) {
		ATDProjectile* newProjectile = World->SpawnActorDeferred<ATDProjectile>(ATDProjectile::StaticClass(), GetOwner()->GetActorTransform(), GetOwner());
		newProjectile->FlipbookName = projectileFlipbookName;
		newProjectile->Damage = Damage;
		newProjectile->Speed = Speed;
		newProjectile->RemainingChains = 0.f;
		newProjectile->SplashRadius = Radius;
		newProjectile->Target = target;
		newProjectile->ProjectileHitDelegate.BindUObject(this, &UTDAbility::OnAbilityProjectileHitTarget);
		newProjectile->ProjectileSplashDelegate.BindUObject(this, &UTDAbility::OnAbilityProjectileSplashTarget);

		newProjectile->FinishSpawning(GetOwner()->GetActorTransform());
	}
}

void UTDAbility::OnAbilityProjectileHitTarget(ATDProjectile* projectile, TWeakObjectPtr<AActor> target) {
	OwnerTower->OnHitEnemy(projectile->Damage, target);
}

void UTDAbility::OnAbilityProjectileSplashTarget(TArray<AActor*> splashedActors) {
	OwnerTower->OnSplashEnemies(splashedActors);
}

void UTDAbility::OnOverlapBegin(UPrimitiveComponent* CapsComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	EnemiesInRange++;

	//UE_LOG(LogTemp, Warning, TEXT("Enemy entered, now %i in range"), EnemiesInRange);
}

void UTDAbility::OnOverlapEnd(UPrimitiveComponent* CapsComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	EnemiesInRange--;

	//UE_LOG(LogTemp, Warning, TEXT("Enemy left, now %i in range"), EnemiesInRange);
}
