// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "Abilities/TDAbility.h"

class TOWERDEFENCETHING_API ABasicFireball : public TDAbility {
public:
	ABasicFireball();
	~ABasicFireball();

	virtual bool TryCastAbility() override;
	virtual void CastAbility() override;
};
