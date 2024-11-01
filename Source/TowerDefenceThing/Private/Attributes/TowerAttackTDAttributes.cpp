// Dragons rule ok


#include "Attributes/TowerAttackTDAttributes.h"

TowerAttackTDAttributes::TowerAttackTDAttributes() {
	MinDamage = MakeUnique<TDAttribute>();
	MaxDamage = MakeUnique<TDAttribute>();
	Targets = MakeUnique<TDAttribute>();
	SplashRadius = MakeUnique<TDAttribute>();
	SplashPercentage = MakeUnique<TDAttribute>();
}

TowerAttackTDAttributes::~TowerAttackTDAttributes() {

}
