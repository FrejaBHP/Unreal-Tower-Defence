// Dragons rule ok

#include "Components/TDEnemyMovementComponent.h"
#include "Enemies/EnemyBasePawn.h"
#include "TDAIController.h"

UTDEnemyMovementComponent::UTDEnemyMovementComponent() {
	NavAgentProps.bCanWalk = true;
}

void UTDEnemyMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	if (ShouldSkipUpdate(DeltaTime)) {
		return;
	}

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent) {
		return;
	}

	const AController* Controller = GetPawnOwner()->GetController();
	const AEnemyBasePawn* BasePawn = Cast<AEnemyBasePawn>(GetPawnOwner());

	const FVector inputVelocity = GetPendingInputVector() * BasePawn->GetBaseAttributes()->GetSpeed(); // Base speed later!
	if (!inputVelocity.IsZero()) {
		Velocity = inputVelocity;
	}

	ConsumeInputVector();

	FVector delta = Velocity * DeltaTime;
	if (!delta.IsNearlyZero(1e-6f)) {
		const FQuat Rotation = UpdatedComponent->GetComponentQuat();
		
		FHitResult hit(1.f);
		SafeMoveUpdatedComponent(delta, Rotation, true, hit);

		if (hit.IsValidBlockingHit()) {
			HandleImpact(hit, DeltaTime, delta);
			// Try to slide the remaining distance along the surface.
			SlideAlongSurface(delta, 1.f - hit.Time, hit.Normal, hit, true);
		}
	}
	
	DistanceTravelled += delta.Length();

	UpdateComponentVelocity();

}

void UTDEnemyMovementComponent::Test(FVector from, FVector to) {
	
}

