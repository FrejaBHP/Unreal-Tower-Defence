// Dragons rule ok


#include "Abilities/TDAbilityAreaOfEffect.h"

// Sets default values
ATDAbilityAreaOfEffect::ATDAbilityAreaOfEffect() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!OverlapComponent) {
		OverlapComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Overlap"));
		RootComponent = OverlapComponent;
		OverlapComponent->SetMobility(EComponentMobility::Stationary);
		OverlapComponent->SetCollisionProfileName(FName("TowerTargeting"));
	}
}

// Called when the game starts or when spawned
void ATDAbilityAreaOfEffect::BeginPlay() {
	Super::BeginPlay();
	
}

// Called every frame
void ATDAbilityAreaOfEffect::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}
