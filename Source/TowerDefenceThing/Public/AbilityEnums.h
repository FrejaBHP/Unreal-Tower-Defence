// Dragons rule ok

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class EAbilityCast : uint8 {
	Auto,
	Active,
	Triggered,
	Passive
};

UENUM()
enum class EAbilityType : uint8 {
	Projectile,
	Instant
};

UENUM()
enum class EAbilityTarget : uint8 {
	Friendly,
	Enemy,
	Self,
	All
};

UENUM()
enum class EAbilityHandle : uint8 {
	NONE,
	BasicFireball
};

class TOWERDEFENCETHING_API AbilityEnums {
public:
	AbilityEnums();
	~AbilityEnums();
};
