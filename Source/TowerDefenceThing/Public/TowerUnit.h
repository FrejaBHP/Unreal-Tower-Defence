// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TowerUnit.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTowerUnit : public UInterface {
	GENERATED_BODY()
};

class TOWERDEFENCETHING_API ITowerUnit {
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool TrySetTarget(AActor* target) = 0;
	virtual void OnHitEnemy(TWeakObjectPtr<AActor> enemy) = 0;
};