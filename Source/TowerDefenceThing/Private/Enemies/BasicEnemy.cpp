// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/BasicEnemy.h"

ABasicEnemy::ABasicEnemy() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Name = FName("Basic Enemy"); // Change this to be applied later from the Wave Manager
}

// Called when the game starts or when spawned
void ABasicEnemy::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void ABasicEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
