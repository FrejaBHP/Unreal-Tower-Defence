// Dragons rule ok


#include "Towers/TowerManager.h"
#include "Towers/BasicTower.h"

TowerManager::TowerManager() {

}

AActor* TowerManager::CreateTowerFromHandle(ETowerHandle tHandle) {
	return GetTowerFromHandle(tHandle);
}

AActor* TowerManager::GetTowerFromHandle(ETowerHandle tHandle) {
	switch (tHandle) {
		case ETowerHandle::BasicTower:
			return NewObject<ABasicTower>();
			break;

		default:
			return NewObject<ABasicTower>();
			break;
	}
}

TowerManager::~TowerManager() {

}
