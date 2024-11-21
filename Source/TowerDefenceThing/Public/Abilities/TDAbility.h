// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "AbilityEnums.h"

class TOWERDEFENCETHING_API TDAbility {
public:
	TDAbility();
	virtual ~TDAbility();

	FName AbilityName;
	FString AbilityFlipbookName;
	EAbilityCast AbilityCast;
	EAbilityType AbilityType;
	EAbilityTarget AbilityTarget;
	float Cost { 0.f };
	float Range { 0.f };
	float Cooldown { 0.f };
	float TriggerChance { 0.f };

	float Radius { 0.f };
	float Speed { 0.f };
	float Damage { 0.f };

	virtual bool TryCastAbility();
	virtual void CastAbility();

	float GetCooldownTimer() const;
	void SetCooldownTimer(float newCDTimer);
	void ReduceCooldownTimer(float reduction);
	void ResetCooldownTimer();
	bool IsReady() const;

protected:
	float CooldownTimer { 0.f };
};
