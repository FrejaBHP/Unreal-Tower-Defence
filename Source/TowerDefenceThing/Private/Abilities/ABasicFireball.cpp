// Dragons rule ok


#include "Abilities/ABasicFireball.h"

UABasicFireball::UABasicFireball() {
	PrimaryComponentTick.bCanEverTick = true;

	AbilityName = "Basic Fireball";

	AbilityHUDBrushName = "icon_fireball_Brush";
	AbilityFlipbookName = "proj_fireball_Flip";

	AbilityHandle = EAbilityHandle::BasicFireball;
	AbilityCast = EAbilityCast::Active;
	AbilityType = EAbilityType::Projectile;
	AbilityTarget = EAbilityTarget::Enemy;
	IsAutoCast = false;

	Cost = 0.f;
	Range = 350.f;
	Cooldown = 2.5f;
	TriggerChance = 0.f;

	Radius = 0.f;
	Speed = 750.f;
	Damage = 10.f;

	if (!OverlapComponent) {
		OverlapComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Fireball Range"));
		OverlapComponent->SetMobility(EComponentMobility::Stationary);
		OverlapComponent->SetCollisionProfileName(FName("TowerTargeting"));
		OverlapComponent->SetCapsuleSize(Range, Range + 100.f);
	}
}

void UABasicFireball::BeginPlay() {
	Super::BeginPlay();

	// Setting these in the constructor, especially with SetupAttachment(), causes the component to become orphaned at origin
	// Somehow, this solves that problem. Yay?
	if (OverlapComponent) {
		OverlapComponent->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
		OverlapComponent->RegisterComponent();
		OverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &UABasicFireball::OnOverlapBegin);
		OverlapComponent->OnComponentEndOverlap.AddDynamic(this, &UABasicFireball::OnOverlapEnd);
	}
}

void UABasicFireball::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsReady()) {
		ReduceCooldownTimer(DeltaTime);
	}
	else if (IsAutoCast) {
		TryCastAbility();
	}
}

bool UABasicFireball::TryCastAbility() {
	if (EnemiesInRange > 0) { // Has no cost at the moment, so can always be cast provided it isn't cooling down and targets exist
		CastAbility();
		return true;
	}
	else {
		return false;
	}
}

// When checks go through, ability is triggered
void UABasicFireball::CastAbility() {
	AActor* closestTarget = GetClosestTarget();
	if (closestTarget) {
		TWeakObjectPtr<AActor> twTarget = closestTarget;
		SpawnProjectile(twTarget, AbilityFlipbookName);
		ResetCooldownTimer();
	}
}

FText UABasicFireball::GetAbilityDescription() {
	return FText::Format(INVTEXT("Fires a fireball at the nearest enemy, dealing {0} damage."), Damage);
}
