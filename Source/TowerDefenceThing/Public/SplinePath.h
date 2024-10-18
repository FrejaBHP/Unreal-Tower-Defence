// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/SplineComponent.h>
#include "SplinePath.generated.h"

UCLASS()
class TOWERDEFENCETHING_API ASplinePath : public AActor {
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplinePath();

	UPROPERTY(EditAnywhere)
	USplineComponent* SplineComponent = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void SetupETDMap();

};
