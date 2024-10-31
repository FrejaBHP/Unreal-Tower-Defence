// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <PaperFlipbook.h>
#include <PaperFlipbookComponent.h>
#include <TDGameInstance.h>
#include "Components/CapsuleComponent.h"
#include "Components/TDEnemyMovementComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "AttributeSets/BaseEnemyAttributes.h"
#include <GameplayTagContainer.h>
#include "ClickableUnit.h"
#include "EnemyBasePawn.generated.h"

UCLASS(Abstract)
class TOWERDEFENCETHING_API AEnemyBasePawn : public APawn, public IAbilitySystemInterface, public IClickableUnit {
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyBasePawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnSelect() override;
	virtual FGameplayTag GetUnitTypeTag() override;
	virtual bool HasGameplayTag(FGameplayTag) override;
	virtual FName GetUnitName() override;

	FName Name;

	UPROPERTY()
	FGameplayTagContainer GameplayTags;

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* CapsuleComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	UPaperFlipbookComponent* FlipbookComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	UTDEnemyMovementComponent* PawnMovementComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly, Category = "Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;
	
	UPROPERTY()
	TSoftObjectPtr<UPaperFlipbook> FlipbookPtr = nullptr;

	UPROPERTY()
	UPaperFlipbook* VisibleFlipbook = nullptr;

	UPROPERTY(VisibleAnywhere)
	UBaseEnemyAttributes* BaseAttributes;

	virtual void PossessedBy(AController* NewController);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UBaseEnemyAttributes* GetBaseAttributes() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
