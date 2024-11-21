// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Projectiles/TDProjectile.h"
#include "Abilities/TDAbility.h"
#include "Abilities/TDAbilityAura.h"
#include "AbilityEnums.h"
#include <TDGameInstance.h>
#include "TowerUnit.h"
#include "TDAbilityComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENCETHING_API UTDAbilityComponent : public USceneComponent {
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTDAbilityComponent();

	TArray<TUniquePtr<TDAbility>> Abilities;

	void AddAbility(EAbilityHandle aHandle);
	void DEBUGListAbilities();

	UPROPERTY()
	TArray<UCapsuleComponent*> AuraOverlapComponents;

	void SpawnProjectile(TDAbility* ability, TWeakObjectPtr<AActor> target, FString projectileFlipbookName);
	void OnAbilityProjectileHitTarget(ATDProjectile* projectile, TWeakObjectPtr<AActor> target);
	void OnAbilityProjectileSplashTarget(TArray<AActor*> splashedActors);

	ITowerUnit* OwnerTower;
	TWeakObjectPtr<AActor> TowerTarget;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
