// Dragons rule ok


#include "WaveManager.h"

WaveManager::WaveManager() {
	ValidEnemyFlipbookNames.Add("dg_humans32_0_Flip");
}

void WaveManager::GenerateWaves(int amount) {
	float totalHealthModifier = 1;
	float totalBounty = BaseBounty;

	for (size_t i = 0; i < amount; i++) {
		if (i != 0 && i % WavesPerBountyIncrease == 0) {
			totalBounty += 1;
		}

		WaveArray.Add(TDWave(10, BaseHealth * totalHealthModifier, DefaultSpeed, totalBounty, ValidEnemyFlipbookNames[0]));

		totalHealthModifier *= WaveHealthModifier;
	}
}

WaveManager::~WaveManager() {
	WaveArray.Empty();
	ValidEnemyFlipbookNames.Empty();
}
