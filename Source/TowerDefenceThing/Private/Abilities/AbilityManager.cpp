// Dragons rule ok


#include "Abilities/AbilityManager.h"
#include "Abilities/ABasicFireball.h"

AbilityManager::AbilityManager() {

}

UTDAbility* AbilityManager::CreateAssignAbilityFromHandle(EAbilityHandle aHandle, USceneComponent* comp) {
	return GetAbilityFromHandle(aHandle, comp);
}

UTDAbility* AbilityManager::GetAbilityFromHandle(EAbilityHandle aHandle, USceneComponent* comp) {
	switch (aHandle) {
	case EAbilityHandle::BasicFireball:
		return NewObject<UABasicFireball>(comp, "Basic Fireball");
		break;

	default:
		return NewObject<UABasicFireball>(comp, "Error Fireball");
		break;
	}
}

AbilityManager::~AbilityManager() {

}
