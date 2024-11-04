// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Projectiles/TDProjectile.h"
#include "Attributes/TowerProjectileTDAttributes.h"
#include "TowerUnit.h"
#include "TowerProjectileComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENCETHING_API UTowerProjectileComponent : public UActorComponent {
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTowerProjectileComponent();

	void SpawnProjectile(TWeakObjectPtr<AActor> target);
	void OnProjectileHitTarget(ATDProjectile* projectile, TWeakObjectPtr<AActor> target);

	ITowerUnit* OwnerTower;

	TUniquePtr<TowerProjectileTDAttributes> ProjectileAttributeSet = nullptr;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};