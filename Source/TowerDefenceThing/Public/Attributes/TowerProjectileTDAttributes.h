// Dragons rule ok

#pragma once

#include "Attributes/TDAttributeSet.h"
#include "CoreMinimal.h"

class TOWERDEFENCETHING_API TowerProjectileTDAttributes : public TDAttributeSet {
public:
	TowerProjectileTDAttributes();

	TUniquePtr<TDAttribute> Speed = nullptr;
	TUniquePtr<TDAttribute> Chain = nullptr;

	~TowerProjectileTDAttributes();
};
