// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"

#include "AbilityEnums.h"
#include "Projectiles/TDProjectile.h"
#include "TowerUnit.h"
#include "TDAbility.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOWERDEFENCETHING_API UTDAbility : public USceneComponent {
	GENERATED_BODY()

public:
	UTDAbility();

	FName AbilityName;
	FString AbilityFlipbookName;
	EAbilityCast AbilityCast;
	EAbilityType AbilityType;
	EAbilityTarget AbilityTarget;
	float Cost { 0.f };
	float Range { 0.f };
	float Cooldown { 0.f };
	float TriggerChance { 0.f };

	float Radius { 0.f };
	float Speed { 0.f };
	float Damage { 0.f };

	int EnemiesInRange { 0 };
	ITowerUnit* OwnerTower;

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* OverlapComponent;

	virtual bool TryCastAbility();
	virtual void CastAbility();
	
	void SpawnProjectile(TWeakObjectPtr<AActor> target, FString projectileFlipbookName);
	void OnAbilityProjectileHitTarget(ATDProjectile* projectile, TWeakObjectPtr<AActor> target);
	void OnAbilityProjectileSplashTarget(TArray<AActor*> splashedActors);

	// Gets the closest target if there is an overlap component. Returns a nullptr if there are no overlaps
	AActor* GetClosestTarget();

	float GetCooldownTimer() const;
	void SetCooldownTimer(float newCDTimer);
	void ReduceCooldownTimer(float reduction);
	void ResetCooldownTimer();
	bool IsReady() const;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	float CooldownTimer { 0.f };

	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
