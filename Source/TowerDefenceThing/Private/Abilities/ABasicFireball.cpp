// Dragons rule ok


#include "Abilities/ABasicFireball.h"

ABasicFireball::ABasicFireball() {
	AbilityName = "Basic Fireball";
	AbilityFlipbookName = "proj_fireball_Flip";
	AbilityCast = EAbilityCast::Active;
	AbilityType = EAbilityType::Projectile;
	AbilityTarget = EAbilityTarget::Enemy;

	Cost = 0.f;
	Range = 350.f;
	Cooldown = 2.5f;
	TriggerChance = 0.f;

	Radius = 0.f;
	Speed = 750.f;
	Damage = 10.f;
}

bool ABasicFireball::TryCastAbility() {
	if (IsReady()) {
		CastAbility();
		return true;
	}
	else {
		return false;
	}
}

// When checks go through, ability is triggered
void ABasicFireball::CastAbility() {
	ResetCooldownTimer();
}

ABasicFireball::~ABasicFireball() {

}
