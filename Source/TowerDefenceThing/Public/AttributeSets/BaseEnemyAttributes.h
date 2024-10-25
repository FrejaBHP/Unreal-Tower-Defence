// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "BaseEnemyAttributes.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCETHING_API UBaseEnemyAttributes : public UAttributeSet {
	GENERATED_BODY()

public:
	/** Sample "Health" Attribute, publicly accessible */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Health;
	
};
