// Dragons rule ok


#include "WaveManager.h"

WaveManager::WaveManager() {
	ValidEnemyFlipbookNames.Add("dg_humans32_0_Flip");
}

void WaveManager::GenerateWaves(int amount) {
	float totalHealthModifier = 1;
	for (size_t i = 0; i < amount; i++) {
		WaveArray.Add(TDWave(10, BaseHealth * totalHealthModifier, DefaultSpeed, ValidEnemyFlipbookNames[0]));

		totalHealthModifier *= WaveHealthModifier;
	}
}

WaveManager::~WaveManager() {
	WaveArray.Empty();
	ValidEnemyFlipbookNames.Empty();
}
