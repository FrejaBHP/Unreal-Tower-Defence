// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "Abilities/TDAbility.h"
#include "AbilityEnums.h"
#include "Components/SceneComponent.h"

class TOWERDEFENCETHING_API AbilityManager {
public:
	AbilityManager();
	~AbilityManager();

	UTDAbility* CreateAssignAbilityFromHandle(EAbilityHandle aHandle, USceneComponent* comp);

protected:
	UTDAbility* GetAbilityFromHandle(EAbilityHandle aHandle, USceneComponent* comp);
};
