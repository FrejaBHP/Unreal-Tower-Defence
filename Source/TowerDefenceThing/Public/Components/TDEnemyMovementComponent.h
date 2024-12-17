// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "TDEnemyMovementComponent.generated.h"


UCLASS()
class TOWERDEFENCETHING_API UTDEnemyMovementComponent : public UPawnMovementComponent {
	GENERATED_BODY()
	
public:
	UTDEnemyMovementComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	float MaxSpeed { 0.f };

	UPROPERTY()
	float BaseSpeed { 0.f };

	UPROPERTY()
	float DistanceTravelled { 0.f };
};
