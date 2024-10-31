// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTags.h"
#include "ClickableUnit.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UClickableUnit : public UInterface {
	GENERATED_BODY()
};

/**
 * 
 */
class TOWERDEFENCETHING_API IClickableUnit {
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void OnSelect() = 0;
	virtual FGameplayTag GetUnitTypeTag() = 0;
	virtual bool HasGameplayTag(FGameplayTag) = 0;
	virtual FName GetUnitName() = 0;

};
