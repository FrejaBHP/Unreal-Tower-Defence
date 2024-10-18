// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemies/EnemyBasePawn.h"
#include "BasicEnemy.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCETHING_API ABasicEnemy : public AEnemyBasePawn
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	ABasicEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
