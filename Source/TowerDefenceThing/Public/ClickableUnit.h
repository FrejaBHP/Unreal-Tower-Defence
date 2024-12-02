// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Abilities/TDAbility.h" // muligvis
#include "Components/TDAbilityComponent.h"
#include "ClickableUnit.generated.h"

UENUM()
enum class EUnitType : int8 {
	Enemy,
	Tower,
	Player
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UClickableUnit : public UInterface {
	GENERATED_BODY()
};

class TOWERDEFENCETHING_API IClickableUnit {
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void OnSelect() = 0;
	virtual EUnitType GetUnitType() = 0;
	virtual FName GetUnitName() = 0;
	virtual UTDAbilityComponent& GetAbilityComponent() = 0;
	//virtual TArray<UTDAbility*>& GetAbilities() = 0;
};
