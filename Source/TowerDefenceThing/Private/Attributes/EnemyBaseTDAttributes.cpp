// Dragons rule ok


#include "Attributes/EnemyBaseTDAttributes.h"

EnemyBaseTDAttributes::EnemyBaseTDAttributes() {
	Health = MakeUnique<TDAttribute>();
	Speed = MakeUnique<TDAttribute>();
}

EnemyBaseTDAttributes::~EnemyBaseTDAttributes() {

}
