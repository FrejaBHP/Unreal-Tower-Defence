// Dragons rule ok


#include "AttributeSets/TowerAttackAttributes.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffect.h"

void UTowerAttackAttributes::OnRep_MinDamage(const FGameplayAttributeData& oldMinDamage) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTowerAttackAttributes, MinDamage, oldMinDamage);
}

void UTowerAttackAttributes::OnRep_MaxDamage(const FGameplayAttributeData& oldMaxDamage) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTowerAttackAttributes, MaxDamage, oldMaxDamage);
}

void UTowerAttackAttributes::OnRep_MaxTargets(const FGameplayAttributeData& oldMaxTargets) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTowerAttackAttributes, MaxTargets, oldMaxTargets);
}

void UTowerAttackAttributes::OnRep_SplashRadius(const FGameplayAttributeData& oldSplashRadius) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTowerAttackAttributes, SplashRadius, oldSplashRadius);
}

void UTowerAttackAttributes::OnRep_SplashPercentage(const FGameplayAttributeData& oldSplashPercentage) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTowerAttackAttributes, SplashPercentage, oldSplashPercentage);
}

void UTowerAttackAttributes::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UTowerAttackAttributes, MinDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTowerAttackAttributes, MaxDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTowerAttackAttributes, MaxTargets, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTowerAttackAttributes, SplashRadius, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTowerAttackAttributes, SplashPercentage, COND_None, REPNOTIFY_Always);
}