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
	float BaseHealth { 15.f };
	float WaveHealthModifier { 1.2f };

	float BaseBounty { 1.f };
	int WavesPerBountyIncrease { 4 };

	float SlowSpeed { 150.f };
	float DefaultSpeed { 200.f };
	float FastSpeed { 250.f };

	TArray<FString> ValidEnemyFlipbookNames;
};
