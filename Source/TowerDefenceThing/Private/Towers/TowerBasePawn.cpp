// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers/TowerBasePawn.h"

// Sets default values
ATowerBasePawn::ATowerBasePawn() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisibleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	VisibleMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATowerBasePawn::BeginPlay() {
	Super::BeginPlay();
	
}

// Called every frame
void ATowerBasePawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATowerBasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
