// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyUnit.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyUnit : public UInterface {
	GENERATED_BODY()
};

class TOWERDEFENCETHING_API IEnemyUnit {
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual float GetCurrentHealth() = 0;
	virtual void TakeDamage(float damage) = 0;
};
