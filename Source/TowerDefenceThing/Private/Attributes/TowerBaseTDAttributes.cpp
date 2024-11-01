// Dragons rule ok


#include "Attributes/TowerBaseTDAttributes.h"

TowerBaseTDAttributes::TowerBaseTDAttributes() {
	Range = MakeUnique<TDAttribute>();
	AttackRate = MakeUnique<TDAttribute>();
}

TowerBaseTDAttributes::~TowerBaseTDAttributes() {

}
