// Dragons rule ok


#include "AttributeSets/TowerProjectileAttributes.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffect.h"

void UTowerProjectileAttributes::OnRep_Speed(const FGameplayAttributeData& oldSpeed) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTowerProjectileAttributes, Speed, oldSpeed);
}

void UTowerProjectileAttributes::OnRep_Chains(const FGameplayAttributeData& oldChains) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTowerProjectileAttributes, Chains, oldChains);
}

void UTowerProjectileAttributes::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UTowerProjectileAttributes, Speed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTowerProjectileAttributes, Chains, COND_None, REPNOTIFY_Always);
}
