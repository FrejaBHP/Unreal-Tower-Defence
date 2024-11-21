// Dragons rule ok


#include "Abilities/TDAbility.h"
#include "Abilities/TDAbilityAreaOfEffect.h"

TDAbility::TDAbility() {

}

// Run checks on if the ability should be allowed to be cast
// Could be checking for a valid target or if the caster has the resources to cast it
bool TDAbility::TryCastAbility() {
	return true;
}

// When checks go through, ability is triggered
void TDAbility::CastAbility() {

}

// Gets the remaining cooldown
float TDAbility::GetCooldownTimer() const {
	return CooldownTimer;
}

// Sets the remaining cooldown. If reduced below 0, sets 0
void TDAbility::SetCooldownTimer(float newCDTimer) {
	if (0.f > newCDTimer) {
		CooldownTimer = 0.f;
	}
	else {
		CooldownTimer = newCDTimer;
	}
}

// Shortcut function that can be fed deltaTime directly
void TDAbility::ReduceCooldownTimer(float reduction) {
	SetCooldownTimer(CooldownTimer - reduction);
}

void TDAbility::ResetCooldownTimer() {
	CooldownTimer = Cooldown;
}

// Checks if remaining cooldown is 0 (since SetCooldownTimer ensures it can't be below 0)
bool TDAbility::IsReady() const {
	if (CooldownTimer > 0.f) {
		return false;
	}
	else {
		return true;
	}
}

TDAbility::~TDAbility() {

}
