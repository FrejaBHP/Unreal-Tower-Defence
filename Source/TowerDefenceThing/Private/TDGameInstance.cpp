// Dragons rule ok


#include "TDGameInstance.h"
#include <Engine/StreamableManager.h>

UTDGameInstance::UTDGameInstance() {
	TDUIResources.Initialize();
	Lives = 50;
	SpriteLib = UObjectLibrary::CreateLibrary(UPaperSprite::StaticClass(), false, false);
	FlipbookLib = UObjectLibrary::CreateLibrary(UPaperFlipbook::StaticClass(), false, false);

	CatalogueSprites();
	CatalogueFlipbooks();
}

void UTDGameInstance::Init() {
	Super::Init();
}

void UTDGameInstance::CatalogueSprites() {
	TArray<FString> paths;
	paths.Add("/Game/Sprites/Static/Enemies");
	paths.Add("/Game/Sprites/Static/Towers");

	SpriteLib->LoadAssetsFromPaths(paths);

	if (SpriteLib->IsLibraryFullyLoaded()) {
		SpriteLib->LoadAssetsFromAssetData();

		TArray<UPaperSprite*> sprites;
		SpriteLib->GetObjects(sprites);

		for (auto& sprite : sprites) {
			SpriteMap.Add(sprite->GetFName(), sprite);
		}
	}
}

void UTDGameInstance::CatalogueFlipbooks() {
	TArray<FString> paths;
	paths.Add("/Game/Sprites/Flipbooks/Enemies");
	//paths.Add("/Game/Sprites/Flipbooks/Towers");

	FlipbookLib->LoadAssetsFromPaths(paths);

	if (FlipbookLib->IsLibraryFullyLoaded()) {
		FlipbookLib->LoadAssetsFromAssetData();

		TArray<UPaperFlipbook*> flipbooks;
		FlipbookLib->GetObjects(flipbooks);

		for (auto& flipbook : flipbooks) {
			FlipbookMap.Add(flipbook->GetFName(), flipbook);
		}
	}
}

UPaperSprite* UTDGameInstance::GetSpriteByName(FString spriteName) {
	UPaperSprite* spritePtr = SpriteMap[FName(*spriteName)];

	return spritePtr;
}

UPaperFlipbook* UTDGameInstance::GetFlipbookByName(FString flipbookName) {
	UPaperFlipbook* flipbookPtr = FlipbookMap[FName(*flipbookName)];

	return flipbookPtr;
}

TSharedPtr<FSlateGameResources> UTDGameInstance::GetSlateGameResources() {
	/*Give caller a pointer to our FSlateGameResources*/
	/*Giving strong pointer, helps gurantee access to resources*/
	return TDUIResources.GetSlateGameResources();
}

void UTDGameInstance::Shutdown() {
	TDUIResources.Shutdown();
	SpriteMap.Empty();
	FlipbookMap.Empty();

	Super::Shutdown();
}
