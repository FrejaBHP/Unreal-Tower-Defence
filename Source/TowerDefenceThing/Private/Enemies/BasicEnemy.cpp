// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/BasicEnemy.h"

ABasicEnemy::ABasicEnemy() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABasicEnemy::BeginPlay() {
	Super::BeginPlay();

	FlipbookPtr = Cast<UTDGameInstance>(GetGameInstance())->BasicEnemyFlipbookPtr;

	if (FlipbookPtr != nullptr) {
		VisibleFlipbook = FlipbookPtr.Get();
		FlipbookComponent->SetFlipbook(VisibleFlipbook);
	}
}

// Called every frame
void ABasicEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}
