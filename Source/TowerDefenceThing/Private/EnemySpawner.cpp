// Dragons rule ok


#include "EnemySpawner.h"
#include "Enemies/BasicEnemy.h"
#include "TDGameInstance.h"

// Sets default values
AEnemySpawner::AEnemySpawner() {
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	SpawnVolume->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay() {
	Super::BeginPlay();

	Cast<UTDGameInstance>(GetGameInstance())->EnemySpawner = this;
}

void AEnemySpawner::SpawnWave(WaveManager::TDWave& wave) {
	EnemiesToSpawn = wave.Amount;

	TimerDelegate.BindUFunction(this, FName("SpawnEnemy"), wave.Health, wave.Speed, wave.Bounty, wave.FlipbookName);
	GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, 1.f, true, -1.f);
}

// Also needs support for spawning different enemy types
void AEnemySpawner::SpawnEnemy(float health, float speed, float bounty, FString flipbook) {
	UTDGameInstance* GI = Cast<UTDGameInstance>(GetGameInstance());

	if (EnemiesToSpawn != 0) {
		ABasicEnemy* newBasicEnemy = GetWorld()->SpawnActorDeferred<ABasicEnemy>(ABasicEnemy::StaticClass(), GetActorTransform(), this);
		newBasicEnemy->SetWaveStats(health, speed, (int32)bounty);
		newBasicEnemy->SetFlipbook(flipbook);
		newBasicEnemy->EnemyDeathDecrementDelegate.BindUObject(GI, &UTDGameInstance::DecrementEnemiesOnMap);
		newBasicEnemy->EnemyBountyDelegate.BindUObject(GI, &UTDGameInstance::AwardBountyToPlayer);
		newBasicEnemy->FinishSpawning(GetActorTransform());

		EnemiesToSpawn--;
	}

	if (EnemiesToSpawn == 0) {
		GetWorldTimerManager().PauseTimer(TimerHandle);
	}
}
