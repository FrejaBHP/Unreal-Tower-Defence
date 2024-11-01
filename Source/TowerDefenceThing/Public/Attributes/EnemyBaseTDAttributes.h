// Dragons rule ok

#pragma once

#include "Attributes/TDAttributeSet.h"
#include "CoreMinimal.h"

class TOWERDEFENCETHING_API EnemyBaseTDAttributes : public TDAttributeSet {

public:
	EnemyBaseTDAttributes();

	TUniquePtr<TDAttribute> Health = nullptr;
	TUniquePtr<TDAttribute> Speed = nullptr;

	~EnemyBaseTDAttributes();
};
