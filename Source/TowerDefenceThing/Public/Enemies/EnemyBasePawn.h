// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <PaperFlipbook.h>
#include <PaperFlipbookComponent.h>
#include <TDGameInstance.h>
#include "Components/CapsuleComponent.h"
#include "Components/TDEnemyMovementComponent.h"
#include "Components/TDAbilityComponent.h"
#include "Components/WidgetComponent.h"
#include "Attributes/EnemyBaseTDAttributes.h"
#include "ClickableUnit.h"
#include "EnemyUnit.h"
#include "SlateComps/SEnemyHealthBar.h"
#include "EnemyBasePawn.generated.h"

UCLASS(Abstract)
class TOWERDEFENCETHING_API AEnemyBasePawn : public APawn, public IClickableUnit, public IEnemyUnit {
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyBasePawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnSelect() override;
	virtual EUnitType GetUnitType() override;
	virtual FName GetUnitName() override;

	virtual float GetCurrentHealth() override;
	virtual void TakeDamage(float damage) override;

	EUnitType UnitType { EUnitType::Enemy };
	FName Name;
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


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Die();
};
