// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Pawn.h"
#include <PaperFlipbook.h>
#include <PaperFlipbookComponent.h>
#include <TDGameInstance.h>

#include "Attributes/EnemyBaseTDAttributes.h"
#include "ClickableUnit.h"
#include "Components/TDEnemyMovementComponent.h"
#include "Components/TDAbilityComponent.h"
#include "Components/WidgetComponent.h"
#include "EnemyUnit.h"
#include "SlateComps/SEnemyHealthBar.h"
#include "EnemyBasePawn.generated.h"

DECLARE_DELEGATE(FEnemyDeathDecrementSignature);
DECLARE_DELEGATE_TwoParams(FEnemyBountySignature, int, int32);

UCLASS(Abstract)
class TOWERDEFENCETHING_API AEnemyBasePawn : public APawn, public IClickableUnit, public IEnemyUnit {
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyBasePawn();

	FEnemyDeathDecrementSignature EnemyDeathDecrementDelegate;
	FEnemyBountySignature EnemyBountyDelegate;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnSelect() override;
	virtual EUnitType GetUnitType() override;
	virtual FName GetUnitName() override;

	virtual float GetCurrentHealth() override;
	virtual void TakeDamage(int sourcePlayer, float damage) override;

	EUnitType UnitType { EUnitType::Enemy };
	FName Name;
	FString FlipbookName;
	float HealthMultiplier { 1.f };
	int32 Bounty { 0 };
	TUniquePtr<EnemyBaseTDAttributes> BaseAttributeSet = nullptr;

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere)
	UPaperFlipbookComponent* FlipbookComponent;

	UPROPERTY(VisibleAnywhere)
	UTDEnemyMovementComponent* PawnMovementComponent;

	UPROPERTY(VisibleAnywhere)
	UTDAbilityComponent* AbilityComponent;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* HealthBarWidgetComponent;

	TSharedPtr<SEnemyHealthBar> HealthBarWidgetPtr;
	
	UPROPERTY()
	TSoftObjectPtr<UPaperFlipbook> FlipbookPtr = nullptr;

	UPROPERTY()
	UPaperFlipbook* VisibleFlipbook = nullptr;

	virtual void PossessedBy(AController* NewController);
	virtual UTDAbilityComponent& GetAbilityComponent() override;

	void SetWaveStats(float baseHealth, float baseSpeed, int32 baseBounty);
	void SetFlipbook(FString flipbookName);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Die();
};
