// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "Towers/TowerBasePawn.h"
#include "BasicTower.generated.h"

UCLASS()
class TOWERDEFENCETHING_API ABasicTower : public ATowerBasePawn {
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasicTower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
