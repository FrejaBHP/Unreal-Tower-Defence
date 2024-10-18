// Copyright Epic Games, Inc. All Rights Reserved.

#include "TowerDefenceThing.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, TowerDefenceThing, "TowerDefenceThing" );

DEFINE_LOG_CATEGORY(LogTowerDefenceThing)

void TowerDefenceThing::StartupModule() {
	//UE_LOG(LogTemp, Warning, TEXT("Module started"));

	/*Loads resources and registers them with Slate*/
	/*Do this before trying to use resources*/
	//TDUIResources.Initialize();

	/*TODO: Anything else game module might need to do on load*/
}

void TowerDefenceThing::ShutdownModule() {

	/*Unregister resources/styles with Slate, cleanup, free memory*/
	//TDUIResources.Shutdown();

	/*Cleanup/free any resources here*/
}

/*First defined here, no need to call parent*/
/*Give caller a pointer to our FSlateGameResources*/
TSharedPtr<FSlateGameResources> TowerDefenceThing::GetSlateGameResources() {
	/*Give caller a pointer to our FSlateGameResources*/
	/*Giving strong pointer, helps gurantee access to resources*/
	return TDUIResources.GetSlateGameResources();
}
