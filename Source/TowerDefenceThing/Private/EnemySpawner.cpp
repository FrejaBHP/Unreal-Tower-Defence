// Dragons rule ok


#include "EnemySpawner.h"
#include "Enemies/BasicEnemy.h"

// Sets default values
AEnemySpawner::AEnemySpawner() {
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	SpawnVolume->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AEnemySpawner::SpawnEnemy() {
	ABasicEnemy* newBasicEnemy = GetWorld()->SpawnActor<ABasicEnemy>(GetActorLocation(), GetActorRotation());
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay() {
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	FTimerHandle TimerHandle1;

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemySpawner::SpawnEnemy, 1.f, false, 1.f);
	GetWorldTimerManager().SetTimer(TimerHandle1, this, &AEnemySpawner::SpawnEnemy, 1.f, false, 1.5f);
}

