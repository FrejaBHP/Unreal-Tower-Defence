// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "Abilities/TDAbility.h"
#include "ABasicFireball.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOWERDEFENCETHING_API UABasicFireball : public UTDAbility {
	GENERATED_BODY()

public:
	UABasicFireball();

	virtual bool TryCastAbility() override;
	virtual void CastAbility() override;
	virtual FText GetAbilityDescription() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
