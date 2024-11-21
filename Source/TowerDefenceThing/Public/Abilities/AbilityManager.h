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

	TUniquePtr<TDAbility> GiveAbilityFromHandle(EAbilityHandle aHandle, USceneComponent* aComponent);

protected:
	TUniquePtr<TDAbility> GetAbilityFromHandle(EAbilityHandle aHandle);
};
