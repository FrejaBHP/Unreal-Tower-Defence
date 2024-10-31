// Dragons rule ok

#include "AttributeSets/BaseEnemyAttributes.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffect.h"

void UBaseEnemyAttributes::OnRep_MaxHealth(const FGameplayAttributeData& oldMaxHealth) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseEnemyAttributes, MaxHealth, oldMaxHealth);
}

void UBaseEnemyAttributes::OnRep_Health(const FGameplayAttributeData& oldHealth) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseEnemyAttributes, Health, oldHealth);
}

void UBaseEnemyAttributes::OnRep_Speed(const FGameplayAttributeData& oldSpeed) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseEnemyAttributes, Speed, oldSpeed);
}

void UBaseEnemyAttributes::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UBaseEnemyAttributes, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseEnemyAttributes, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseEnemyAttributes, Speed, COND_None, REPNOTIFY_Always);
}

