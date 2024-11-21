// Dragons rule ok


#include "Components/TDAbilityComponent.h"

// Sets default values for this component's properties
UTDAbilityComponent::UTDAbilityComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	OwnerTower = Cast<ITowerUnit>(GetOwner());
}

// Called when the game starts
void UTDAbilityComponent::BeginPlay() {
	Super::BeginPlay();
	
}

// Called every frame
void UTDAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (size_t i = 0; i < Abilities.Num(); i++) {
		if (!Abilities[i]->IsReady()) {
			Abilities[i]->ReduceCooldownTimer(DeltaTime);
		}
		else if (Abilities[i]->AbilityCast == EAbilityCast::Active && Abilities[i]->TryCastAbility()) {
			if (Abilities[i]->AbilityType == EAbilityType::Projectile) {
				if (OwnerTower->GetTarget().IsValid()) {
					SpawnProjectile(Abilities[i].Get(), OwnerTower->GetTarget(), Abilities[i]->AbilityFlipbookName);
				}
			}
		}
	}
}

// Skal skrives om til når jeg faktisk tilføjer abilities gennem Unique Pointers osv
// Bare et udkast for at få tingene til at give en smule mening
// Skulle også gerne være for specifikke abilities, og skal IKKE være en factoryfunktion
// Muligvis brug af dictionary/map til at koble ability + colshape

// Potentielt lav et bibliotek/liste ud af en klasse og lad andre klasser få en ny instans af en klasse ud fra et enum som fx EAbilityName::Fireball
void UTDAbilityComponent::AddAbility(EAbilityHandle aHandle) {
	TUniquePtr<TDAbility> newAbility = Cast<UTDGameInstance>(GetWorld()->GetGameInstance())->AManager->GiveAbilityFromHandle(EAbilityHandle::BasicFireball, this);
	
	if (newAbility->AbilityCast == EAbilityCast::Passive && newAbility->AbilityTarget != EAbilityTarget::Self) {
		UCapsuleComponent* auraOverlapComponent = NewObject<UCapsuleComponent>(this, UCapsuleComponent::StaticClass(), newAbility->AbilityName);
		auraOverlapComponent->SetupAttachment(this);
		auraOverlapComponent->SetMobility(EComponentMobility::Stationary);
		auraOverlapComponent->SetCapsuleSize(newAbility->Range, newAbility->Range + 100.f);
		auraOverlapComponent->RegisterComponent();

		AuraOverlapComponents.Add(auraOverlapComponent);
	}
	
	Abilities.Emplace(MoveTemp(newAbility));
}

void UTDAbilityComponent::DEBUGListAbilities() {
	for (size_t i = 0; i < Abilities.Num(); i++) {
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Abilities[i]->AbilityName.ToString());
	}
}

void UTDAbilityComponent::SpawnProjectile(TDAbility* ability, TWeakObjectPtr<AActor> target, FString projectileFlipbookName) {
	UWorld* World = GetWorld();
	if (World) {
		ATDProjectile* newProjectile = World->SpawnActorDeferred<ATDProjectile>(ATDProjectile::StaticClass(), GetOwner()->GetActorTransform(), GetOwner());
		newProjectile->FlipbookName = projectileFlipbookName;
		newProjectile->Damage = ability->Damage;
		newProjectile->Speed = ability->Speed;
		newProjectile->RemainingChains = 0.f;
		newProjectile->SplashRadius = ability->Radius;
		newProjectile->Target = target;
		newProjectile->ProjectileHitDelegate.BindUObject(this, &UTDAbilityComponent::OnAbilityProjectileHitTarget);
		newProjectile->ProjectileSplashDelegate.BindUObject(this, &UTDAbilityComponent::OnAbilityProjectileSplashTarget);

		newProjectile->FinishSpawning(GetOwner()->GetActorTransform());
	}
}

void UTDAbilityComponent::OnAbilityProjectileHitTarget(ATDProjectile* projectile, TWeakObjectPtr<AActor> target) {
	OwnerTower->OnHitEnemy(projectile->Damage, target);
}

void UTDAbilityComponent::OnAbilityProjectileSplashTarget(TArray<AActor*> splashedActors) {
	OwnerTower->OnSplashEnemies(splashedActors);
}
