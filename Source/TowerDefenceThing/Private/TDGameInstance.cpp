// Dragons rule ok


#include "TDGameInstance.h"
#include <Engine/StreamableManager.h>

UTDGameInstance::UTDGameInstance() {
	TDUIResources.Initialize();
	Lives = 50;
	CatalogueFlipbooks();
}

void UTDGameInstance::CatalogueFlipbooks() {
	FStreamableManager Streamable;

	BasicEnemyFlipbookPath = "/Game/Sprites/Flipbooks/Enemies/dg_humans32_0_Flip";
	
	UObject* loadedObject = Streamable.LoadSynchronous(BasicEnemyFlipbookPath.TryLoad());
	if (loadedObject != nullptr) {
		BasicEnemyFlipbookPtr = Cast<UPaperFlipbook>(loadedObject);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Graphic can not be loaded"));
	}
}

TSharedPtr<FSlateGameResources> UTDGameInstance::GetSlateGameResources() {
	/*Give caller a pointer to our FSlateGameResources*/
	/*Giving strong pointer, helps gurantee access to resources*/
	return TDUIResources.GetSlateGameResources();
}

void UTDGameInstance::LoadFlipbooksAsync() {
	
}

void UTDGameInstance::Shutdown() {
	TDUIResources.Shutdown();
	Super::Shutdown();
}
