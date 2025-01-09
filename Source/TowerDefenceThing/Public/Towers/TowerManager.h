// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
//#include "Towers/TowerBasePawn.h"
#include "TowerEnums.h"

class TOWERDEFENCETHING_API TowerManager {
public:
	TowerManager();
	~TowerManager();

	AActor* CreateTowerFromHandle(ETowerHandle tHandle);

protected:
	AActor* GetTowerFromHandle(ETowerHandle tHandle);
};
