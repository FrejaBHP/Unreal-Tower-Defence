// Dragons rule ok

#pragma once

#include "Attributes/TDAttributeSet.h"
#include "CoreMinimal.h"

class TOWERDEFENCETHING_API TowerAttackTDAttributes : public TDAttributeSet {
public:
	TowerAttackTDAttributes();

	TUniquePtr<TDAttribute> MinDamage = nullptr;
	TUniquePtr<TDAttribute> MaxDamage = nullptr;
	TUniquePtr<TDAttribute> Targets = nullptr;
	TUniquePtr<TDAttribute> SplashRadius = nullptr;
	TUniquePtr<TDAttribute> SplashPercentage = nullptr;

	~TowerAttackTDAttributes();
};
