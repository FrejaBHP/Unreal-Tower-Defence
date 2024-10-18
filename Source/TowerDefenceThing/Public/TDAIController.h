// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include <SplinePath.h>
#include "Enemies/EnemyBasePawn.h"
#include "TDAIController.generated.h"

UCLASS()
class TOWERDEFENCETHING_API ATDAIController : public AAIController {
	GENERATED_BODY()

public:
	ATDAIController();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	ASplinePath* SplinePath = nullptr;

	UPROPERTY()
	AEnemyBasePawn* PossBasePawn = nullptr;

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	void TDPassedPoint(uint8 pointIndex);
	void TDMoveToSplinePoint(uint8 index);
	void TDUpdateGoalsForPoint(uint8 index);

	uint8 lastSplinePoint = 0;
	float distanceGoal = 0.f;
};
