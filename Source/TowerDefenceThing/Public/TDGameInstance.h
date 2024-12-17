// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/ObjectLibrary.h"
#include "PaperSprite.h"
#include "PaperFlipbook.h"

#include "Abilities/AbilityManager.h"
#include "EnemySpawner.h"
#include "FTDUIResources.h"
#include "SplinePath.h"
#include "WaveManager.h"
#include "TDGameInstance.generated.h"

UCLASS()
class TOWERDEFENCETHING_API UTDGameInstance : public UGameInstance {
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	virtual void Shutdown() override;

	UPROPERTY()
	TObjectPtr<ASplinePath> EnemySplinePath { nullptr };

	UPROPERTY()
	TObjectPtr<AEnemySpawner> EnemySpawner { nullptr };

	UPROPERTY()
	int32 Lives;

	UPROPERTY()
	int32 WaveNumber { -1 };

	UPROPERTY()
	int32 RemainingEnemiesOnMap { 0 };

	FRandomStream RandStream;

	TUniquePtr<AbilityManager> AManager { nullptr };
	TUniquePtr<WaveManager> WavesManager { nullptr };

	void DeductFromLivesCounter(int);
	void DecrementEnemiesOnMap();
	void AwardBountyToPlayer(int player, int32 bounty);

	UPaperSprite* GetSpriteByName(FString spriteName);
	UPaperFlipbook* GetFlipbookByName(FString flipbookName);

	TSharedPtr<FSlateGameResources> GetSlateGameResources();
	

protected:
	UObjectLibrary* SpriteLib { nullptr };
	UObjectLibrary* FlipbookLib { nullptr };

	TMap<FName, UPaperSprite*> SpriteMap;
	TMap<FName, UPaperFlipbook*> FlipbookMap;

	FTDUIResources TDUIResources;

	void InitWaveManager() const;
	void SetNewWave();
	void StartSpawnWave();
	void StartWaveTimer();

private:
	UTDGameInstance();
	
	void CatalogueSprites();
	void CatalogueFlipbooks();
};
