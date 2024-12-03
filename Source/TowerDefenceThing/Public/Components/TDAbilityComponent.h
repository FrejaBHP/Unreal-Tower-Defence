// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Abilities/TDAbility.h"
#include "AbilityEnums.h"
#include <TDGameInstance.h>
#include "TDAbilityComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENCETHING_API UTDAbilityComponent : public USceneComponent {
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTDAbilityComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere)
	TArray<UTDAbility*> Abilities;

	void AddAbility(EAbilityHandle aHandle);
	void RemoveAbility(EAbilityHandle aHandle);
	bool TryCastAbility(EAbilityHandle aHandle);
	int32 GetAbilityIndex(EAbilityHandle aHandle) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
