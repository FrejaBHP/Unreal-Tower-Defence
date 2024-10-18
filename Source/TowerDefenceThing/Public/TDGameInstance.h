// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PaperFlipbook.h"
#include "SplinePath.h"
#include "FTDUIResources.h"
#include "TDGameInstance.generated.h"

UCLASS()
class TOWERDEFENCETHING_API UTDGameInstance : public UGameInstance {
	GENERATED_BODY()
	
public:
	TSharedPtr<FSlateGameResources> GetSlateGameResources();

	UPROPERTY()
	ASplinePath* EnemySplinePath = nullptr;

	UPROPERTY()
	UPaperFlipbook* BasicEnemyFlipbookPtr = nullptr;

	UPROPERTY()
	int32 Lives;

protected:
	FTDUIResources TDUIResources;

private:
	UTDGameInstance();
	void CatalogueFlipbooks();
	void LoadFlipbooksAsync();

	FSoftObjectPath BasicEnemyFlipbookPath;
};
