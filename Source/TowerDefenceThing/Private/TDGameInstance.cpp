// Dragons rule ok


#include "TDGameInstance.h"
#include "TDPlayerHUD.h"
#include "../TowerDefenceThingPlayerController.h"
#include <Engine/StreamableManager.h>

UTDGameInstance::UTDGameInstance() {
	TDUIResources.Initialize();
	RandStream.GenerateNewSeed();

	Lives = 50;

	SpriteLib = UObjectLibrary::CreateLibrary(UPaperSprite::StaticClass(), false, false);
	FlipbookLib = UObjectLibrary::CreateLibrary(UPaperFlipbook::StaticClass(), false, false);

	CatalogueSprites();
	CatalogueFlipbooks();

	AManager = MakeUnique<AbilityManager>();
	TManager = MakeUnique<TowerManager>();
	WavesManager = MakeUnique<WaveManager>();
}

void UTDGameInstance::Init() {
	Super::Init();

	InitWaveManager();

	FTimerHandle StartTimerHandle;
	GetTimerManager().SetTimer(StartTimerHandle, this, &UTDGameInstance::SetNewWave, 2.f, false, -1.f);
}

void UTDGameInstance::InitWaveManager() const {
	WavesManager->GenerateWaves(20);
}

void UTDGameInstance::SetNewWave() {
	WaveNumber++;
	StartSpawnWave();

	//UE_LOG(LogTemp, Warning, TEXT("Wave %i"), WaveNumber + 1);
}

void UTDGameInstance::StartSpawnWave() {
	if (IsValid(EnemySpawner)) {
		EnemySpawner->SpawnWave(WavesManager->WaveArray[WaveNumber]);
		RemainingEnemiesOnMap = WavesManager->WaveArray[WaveNumber].Amount;

		//UE_LOG(LogTemp, Warning, TEXT("Enemies remaining: %i"), RemainingEnemiesOnMap);

		// Should probably replace this part with a delegate/signal to avoid this call chain

		auto& players = GetLocalPlayers();
		for (size_t i = 0; i < players.Num(); i++) {
			APlayerController* pCon = players[i]->GetPlayerController(GetWorld());
			ATDPlayerHUD* playerHUD = pCon->GetHUD<ATDPlayerHUD>();

			playerHUD->UpdateWaveNumber();
			playerHUD->UpdateEnemiesRemaining();
		}
	}
}

void UTDGameInstance::DeductFromLivesCounter(int amount) {
	Lives -= amount;

	// Ditto

	auto& players = GetLocalPlayers();
	for (size_t i = 0; i < players.Num(); i++) {
		APlayerController* pCon = players[i]->GetPlayerController(GetWorld());
		ATDPlayerHUD* playerHUD = pCon->GetHUD<ATDPlayerHUD>();

		playerHUD->UpdateLives();
	}
}

void UTDGameInstance::DecrementEnemiesOnMap() {
	RemainingEnemiesOnMap--;
	//UE_LOG(LogTemp, Warning, TEXT("Enemies remaining: %i"), RemainingEnemiesOnMap);

	// Ditto

	auto& players = GetLocalPlayers();
	for (size_t i = 0; i < players.Num(); i++) {
		APlayerController* pCon = players[i]->GetPlayerController(GetWorld());
		ATDPlayerHUD* playerHUD = pCon->GetHUD<ATDPlayerHUD>();

		playerHUD->UpdateEnemiesRemaining();
	}

	if (RemainingEnemiesOnMap == 0 && WaveNumber < WavesManager->WaveArray.Num() - 1) {
		StartWaveTimer();
	}
}

void UTDGameInstance::AwardBountyToPlayer(int player, int32 bounty) {
	ULocalPlayer* localPlayer = GetLocalPlayerByIndex(player);
	ATowerDefenceThingPlayerController* localController = Cast<ATowerDefenceThingPlayerController>(localPlayer->GetPlayerController(GetWorld()));
	localController->AddPlayerGold(bounty);
}

void UTDGameInstance::StartWaveTimer() {
	UE_LOG(LogTemp, Warning, TEXT("Wave %d complete! New wave starts in 15 seconds"), WaveNumber + 1);

	FTimerHandle WaveTimerHandle;
	GetTimerManager().SetTimer(WaveTimerHandle, this, &UTDGameInstance::SetNewWave, 15.f, false, -1.f);
}

void UTDGameInstance::CatalogueSprites() {
	TArray<FString> paths;
	paths.Add("/Game/Sprites/Static/Enemies");
	paths.Add("/Game/Sprites/Static/Projectiles");
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
	paths.Add("/Game/Sprites/Flipbooks/Projectiles");
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
	return SpriteMap[FName(*spriteName)];
}

UPaperFlipbook* UTDGameInstance::GetFlipbookByName(FString flipbookName) {
	return FlipbookMap[FName(*flipbookName)];
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
