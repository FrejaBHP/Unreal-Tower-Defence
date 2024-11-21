// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "Towers/TowerBasePawn.h"
#include "Components/TowerProjectileComponent.h"
#include "BasicTower.generated.h"

UCLASS()
class TOWERDEFENCETHING_API ABasicTower : public ATowerBasePawn {
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasicTower();

	//virtual void OnHitEnemy(TWeakObjectPtr<AActor> enemy) override;
	//virtual void ApplyTowerDamageToEnemy(IEnemyUnit* enemyInterface) override;
	//virtual void OnSplashEnemies(TArray<AActor*> enemies) override;
	//virtual void ApplyTowerSplashToEnemy(IEnemyUnit* enemyInterface) override;

	UTowerProjectileComponent* ProjectileComponent = nullptr;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void AttackTarget() override;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
