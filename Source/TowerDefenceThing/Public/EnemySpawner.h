// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "EnemySpawner.generated.h"

UCLASS()
class TOWERDEFENCETHING_API AEnemySpawner : public AActor {
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	UFUNCTION()
	void SpawnEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* SpawnVolume;
};
