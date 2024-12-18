// Dragons rule ok

#pragma once

#include "CoreMinimal.h"

class TOWERDEFENCETHING_API WaveManager {
public:
	WaveManager();
	~WaveManager();

	void GenerateWaves(int amount);

	class TDWave {
		friend WaveManager;

		public:
			int32 Amount;
			float Health;
			float Speed;
			float Bounty;
			FString FlipbookName;
			// Modifiers, eventually
			// Same with abilities

			TDWave(int32 amount, float health, float speed, float bounty, FString flipbook) : Amount(amount), Health(health), Speed(speed), Bounty(bounty), FlipbookName(flipbook) {}
	};

	TArray<WaveManager::TDWave> WaveArray;

private:
	const float BaseHealth { 15.f };
	const float WaveHealthModifier { 1.2f };

	const float BaseBounty { 1.f };
	const int WavesPerBountyIncrease { 4 };

	const float SlowSpeed { 150.f };
	const float DefaultSpeed { 200.f };
	const float FastSpeed { 250.f };

	TArray<FString> ValidEnemyFlipbookNames;
};
