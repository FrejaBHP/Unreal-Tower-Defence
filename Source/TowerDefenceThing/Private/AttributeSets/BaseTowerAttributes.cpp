// Dragons rule ok


#include "AttributeSets/BaseTowerAttributes.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffect.h"

void UBaseTowerAttributes::OnRep_AttackRate(const FGameplayAttributeData& oldAttackRate) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseTowerAttributes, AttackRate, oldAttackRate);
}

void UBaseTowerAttributes::OnRep_Range(const FGameplayAttributeData& oldRange) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseTowerAttributes, Range, oldRange);
}

void UBaseTowerAttributes::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UBaseTowerAttributes, AttackRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseTowerAttributes, Range, COND_None, REPNOTIFY_Always);
}