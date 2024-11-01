// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include <TDGameInstance.h>
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Attributes/TowerBaseTDAttributes.h"
#include "ClickableUnit.h"
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
class TOWERDEFENCETHING_API ATowerBasePawn : public APawn, public IClickableUnit {
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATowerBasePawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnSelect() override;
	virtual EUnitType GetUnitType() override;
	virtual FName GetUnitName() override;

	EUnitType UnitType { EUnitType::Tower };
	FName Name;
	TUniquePtr<TowerBaseTDAttributes> BaseAttributeSet = nullptr;

	ETowerTargetType TargetType;
	ETowerAttackType AttackType;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* CapsuleComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	UPaperSpriteComponent* SpriteComponent = nullptr;

	UPROPERTY()
	UPaperSprite* VisibleSprite = nullptr;

	UPROPERTY()
	TSoftObjectPtr<UPaperSprite> SpritePtr = nullptr;

	virtual void PossessedBy(AController* NewController);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
