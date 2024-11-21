// Dragons rule ok

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class EAbilityCast : int8 {
	Active,
	Triggered,
	Passive
};

UENUM()
enum class EAbilityType : int8 {
	Projectile,
	Instant
};

UENUM()
enum class EAbilityTarget : int8 {
	Friendly,
	Enemy,
	Self,
	All
};

UENUM()
enum class EAbilityHandle : int8 {
	BasicFireball
};

class TOWERDEFENCETHING_API AbilityEnums {
public:
	AbilityEnums();
	~AbilityEnums();
};
