// Dragons rule ok

#include "TDAIController.h"
#include <TDGameInstance.h>

ATDAIController::ATDAIController() {
	bStartAILogicOnPossess = true;
}

void ATDAIController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);
	PossBasePawn = Cast<AEnemyBasePawn>(GetPawn());
	SplinePath = Cast<UTDGameInstance>(GetGameInstance())->EnemySplinePath;

	TDPassedPoint(0);
}

void ATDAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	float distance = PossBasePawn->PawnMovementComponent->DistanceTravelled;
	float inputKeyValue = SplinePath->SplineComponent->GetInputKeyValueAtDistanceAlongSpline(distance);
	uint8 flooredKeyValue = floor(inputKeyValue);

	if (flooredKeyValue > lastSplinePoint) { // If flooredKeyValue is higher, unit has passed goal point
		TDPassedPoint(flooredKeyValue);
	}

	/*
	GEngine->ClearOnScreenDebugMessages();
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Distance travelled: %f"), distance));
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Distance goal: %f"), distanceGoal));
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Input key value: %f"), inputKeyValue));
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Last spline point: %i"), lastSplinePoint));
	*/
}

void ATDAIController::TDPassedPoint(uint8 pointIndex) {
	int numOfPoints = SplinePath->SplineComponent->GetNumberOfSplinePoints();

	if (pointIndex < numOfPoints - 1) { // If not finished, continue
		PossBasePawn->PawnMovementComponent->DistanceTravelled = SplinePath->SplineComponent->GetDistanceAlongSplineAtSplinePoint(pointIndex);
		TDUpdateGoalsForPoint(pointIndex);
		TDMoveToSplinePoint(pointIndex + 1);
	}
	else { // If finished, loop
		PossBasePawn->PawnMovementComponent->DistanceTravelled = 0.f;
		
		FVector startDest = SplinePath->SplineComponent->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
		startDest.Z = PossBasePawn->GetActorLocation().Z;

		PossBasePawn->SetActorLocation(startDest);
		TDUpdateGoalsForPoint(0);
		TDMoveToSplinePoint(1);

		Cast<UTDGameInstance>(GetGameInstance())->Lives--;
	}
}

void ATDAIController::TDMoveToSplinePoint(uint8 index) {
	FVector goalPos = SplinePath->SplineComponent->GetLocationAtSplinePoint(index, ESplineCoordinateSpace::World);
	FVector currentPos = GetPawn()->GetActorLocation();
	goalPos.Z = currentPos.Z;

	FVector difference = goalPos - currentPos;
	//UE_LOG(LogTemp, Display, TEXT("Moving to %f, %f, %f"), goalPos.X, goalPos.Y, goalPos.Z);
	FVector normal = difference.GetSafeNormal();

	GetPawn()->AddMovementInput(normal);

	//UE_LOG(LogTemp, Display, TEXT("Moving in direction %f, %f, %f"), normal.X, normal.Y, normal.Z);
}

void ATDAIController::TDUpdateGoalsForPoint(uint8 index) {
	lastSplinePoint = index;
	distanceGoal = SplinePath->SplineComponent->GetDistanceAlongSplineAtSplinePoint(index + 1);
}

