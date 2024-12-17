// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include <Components/BoxComponent.h>
#include "GameFramework/Actor.h"
#include "WaveManager.h"
#include "EnemySpawner.generated.h"

UCLASS()
class TOWERDEFENCETHING_API AEnemySpawner : public AActor {
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	void SpawnWave(WaveManager::TDWave& wave);

	UFUNCTION()
	void SpawnEnemy(float health, float speed, float bounty, FString flipbook);

	UPROPERTY()
	int32 EnemiesToSpawn { 0 };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* SpawnVolume;
};
