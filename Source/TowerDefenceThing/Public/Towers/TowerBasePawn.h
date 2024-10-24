// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include <TDGameInstance.h>
#include "Components/BoxComponent.h"
#include "TowerBasePawn.generated.h"

UCLASS(Abstract)
class TOWERDEFENCETHING_API ATowerBasePawn : public APawn {
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATowerBasePawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	UPaperSpriteComponent* SpriteComponent = nullptr;

	UPROPERTY()
	UPaperSprite* VisibleSprite = nullptr;

	UPROPERTY()
	TSoftObjectPtr<UPaperSprite> SpritePtr = nullptr;

	/*
	UPROPERTY(VisibleAnywhere)
	UPaperFlipbookComponent* FlipbookComponent = nullptr;

	UPROPERTY()
	TSoftObjectPtr<UPaperFlipbook> FlipbookPtr = nullptr;

	UPROPERTY()
	UPaperFlipbook* VisibleFlipbook = nullptr;
	*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
