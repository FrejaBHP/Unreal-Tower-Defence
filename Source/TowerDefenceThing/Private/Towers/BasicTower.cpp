// Dragons rule ok


#include "Towers/BasicTower.h"

// Sets default values
ABasicTower::ABasicTower() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABasicTower::BeginPlay() {
	Super::BeginPlay();
	
}

// Called every frame
void ABasicTower::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasicTower::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

