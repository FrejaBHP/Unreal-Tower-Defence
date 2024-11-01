// Dragons rule ok


#include "Attributes/TowerProjectileTDAttributes.h"

TowerProjectileTDAttributes::TowerProjectileTDAttributes() {
	Speed = MakeUnique<TDAttribute>();
	Chain = MakeUnique<TDAttribute>();
}

TowerProjectileTDAttributes::~TowerProjectileTDAttributes() {

}
