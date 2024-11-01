// Dragons rule ok

#pragma once

#include "Attributes/TDAttributeSet.h"
#include "CoreMinimal.h"

class TOWERDEFENCETHING_API TowerBaseTDAttributes : public TDAttributeSet {
public:
	TowerBaseTDAttributes();

	TUniquePtr<TDAttribute> Range = nullptr;
	TUniquePtr<TDAttribute> AttackRate = nullptr;

	~TowerBaseTDAttributes();
};
