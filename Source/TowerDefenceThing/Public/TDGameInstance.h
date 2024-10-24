// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PaperSprite.h"
#include "PaperFlipbook.h"
#include "SplinePath.h"
#include "Engine/ObjectLibrary.h"
#include "FTDUIResources.h"
#include "TDGameInstance.generated.h"

UCLASS()
class TOWERDEFENCETHING_API UTDGameInstance : public UGameInstance {
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	virtual void Shutdown() override;

	UPaperSprite* GetSpriteByName(FString spriteName);
	UPaperFlipbook* GetFlipbookByName(FString flipbookName);

	TSharedPtr<FSlateGameResources> GetSlateGameResources();

	UPROPERTY()
	ASplinePath* EnemySplinePath = nullptr;

	UPROPERTY()
	UPaperFlipbook* BasicEnemyFlipbookPtr = nullptr;

	UPROPERTY()
	int32 Lives;

protected:
	UObjectLibrary* SpriteLib{ nullptr };
	UObjectLibrary* FlipbookLib{ nullptr };

	TMap<FName, UPaperSprite*> SpriteMap;
	TMap<FName, UPaperFlipbook*> FlipbookMap;

	FTDUIResources TDUIResources;

private:
	UTDGameInstance();
	
	void CatalogueSprites();
	void CatalogueFlipbooks();

	FSoftObjectPath BasicEnemyFlipbookPath;
};
