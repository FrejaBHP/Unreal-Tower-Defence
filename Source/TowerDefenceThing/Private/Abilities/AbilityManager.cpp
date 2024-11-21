// Dragons rule ok


#include "Abilities/AbilityManager.h"
#include "Abilities/ABasicFireball.h"

AbilityManager::AbilityManager() {

}

TUniquePtr<TDAbility> AbilityManager::GetAbilityFromHandle(EAbilityHandle aHandle) {
	switch (aHandle) {
		case EAbilityHandle::BasicFireball:
			return MakeUnique<ABasicFireball>();
			break;

		default:
			return MakeUnique<ABasicFireball>();
			break;
	}
}

TUniquePtr<TDAbility> AbilityManager::GiveAbilityFromHandle(EAbilityHandle aHandle, USceneComponent* aComponent) {
	return GetAbilityFromHandle(aHandle);
}

AbilityManager::~AbilityManager() {

}
