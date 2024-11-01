// Dragons rule ok


#include "Attributes/TDAttribute.h"

float TDAttribute::GetBaseValue() const {
	return BaseValue;
}

float TDAttribute::GetCurrentValue() const {
	return CurrentValue;
}

float TDAttribute::GetMinValue() const {
	return MinValue;
}

float TDAttribute::GetMaxValue() const {
	return MaxValue;
}

void TDAttribute::SetBaseValue(float newBase) {
	BaseValue = newBase;
}

void TDAttribute::SetCurrentValue(float newCurrent) {
	CurrentValue = newCurrent;
}

void TDAttribute::SetMinValue(float newMin) {
	MinValue = newMin;
}

void TDAttribute::SetMaxValue(float newMax) {
	MaxValue = newMax;
}

void TDAttribute::Init(float base) {
	BaseValue = base;
	CurrentValue = base;
	IgnoresMinMax = true;
}

void TDAttribute::InitMinMax(float base, float min, float max) {
	BaseValue = base;
	CurrentValue = base;
	MinValue = min;
	MaxValue = max;
	IgnoresMinMax = false;
}

TDAttribute::~TDAttribute() {

}
