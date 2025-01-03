// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include <TDGameInstance.h>
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TDAbilityComponent.h"
#include "Attributes/TowerBaseTDAttributes.h"
#include "Attributes/TowerAttackTDAttributes.h"
#include "ClickableUnit.h"
#include "EnemyUnit.h"
#include "TowerUnit.h"
#include "TowerBasePawn.generated.h"

UENUM()
enum class ETowerTargetType : int8 {
	Unit,
	Point
};

UENUM()
enum class ETowerAttackType : int8 {
	Projectile,
	Instant
};

UCLASS(Abstract)
class TOWERDEFENCETHING_API ATowerBasePawn : public APawn, public IClickableUnit, public ITowerUnit {
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATowerBasePawn();

	EUnitType UnitType { EUnitType::Tower };
	FName Name;
	TUniquePtr<TowerBaseTDAttributes> BaseAttributeSet = nullptr;
	TUniquePtr<TowerAttackTDAttributes> AttackAttributeSet = nullptr;

	ETowerTargetType TargetType;
	ETowerAttackType AttackType;

	TWeakObjectPtr<AActor> TowerTarget;
	IEnemyUnit* TowerTargetInterface;

	bool HasTarget { false };
	float AttackTimer { 0.f };
	int EnemiesInRange { 0 };

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnSelect() override;
	virtual EUnitType GetUnitType() override;
	virtual FName GetUnitName() override;

	virtual bool TrySetTarget(AActor* target) override;
	virtual void OnHitEnemy(float damage, TWeakObjectPtr<AActor> enemy) override;
	virtual void ApplyTowerDamageToEnemy(float damage, IEnemyUnit* enemyInterface);
	virtual void OnSplashEnemies(TArray<AActor*> enemies) override;
	virtual void ApplyTowerSplashToEnemy(IEnemyUnit* enemyInterface);
	virtual float GetSplashRadius() override;
	const virtual float& GetRange() override;
	const virtual float& GetMinDamage() override;
	const virtual float& GetMaxDamage() override;
	const virtual float& GetAttackSpeed() override;

	virtual TWeakObjectPtr<AActor> GetTarget() override;
	virtual UTDAbilityComponent& GetAbilityComponent() override;
	//virtual TArray<UTDAbility*>& GetAbilities() override;
	
	void GetNewTarget();
	void TryAttackTarget();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep,const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere)
	UPaperSpriteComponent* SpriteComponent;

	UPROPERTY(VisibleAnywhere)
	UTDAbilityComponent* AbilityComponent;

	UPROPERTY()
	UPaperSprite* VisibleSprite = nullptr;

	UPROPERTY()
	TSoftObjectPtr<UPaperSprite> SpritePtr = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetTarget(AActor* target);
	virtual void AttackTarget();

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController);
};
