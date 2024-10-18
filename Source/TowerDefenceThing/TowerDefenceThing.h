// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "FTDUIResources.h"
#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTowerDefenceThing, Log, All);

class TowerDefenceThing : public FDefaultGameModuleImpl {

public:
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Called when GameModule is loaded, load any resources game may need here
	virtual void StartupModule() override;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Called when GameModule is unloaded, before shutdown, unload resources/cleanup here
	virtual void ShutdownModule() override;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Give a handle to TDUIResources to anyone who asks
	TSharedPtr<FSlateGameResources> GetSlateGameResources();

protected:
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Data Structure and Interface for maintaining SlateGameResources on Game to Game basis
	FTDUIResources TDUIResources;
};
