// Dragons rule ok

#pragma once

#include "CoreMinimal.h"

class TOWERDEFENCETHING_API TDAttribute {
public:
	TDAttribute() :
		BaseValue { 0.f },
		CurrentValue { 0.f },
		MinValue { 0.f },
		MaxValue { 0.f },
		IgnoresMinMax { true }
	{}

	TDAttribute(float defaultValue) :
		BaseValue { defaultValue },
		CurrentValue { defaultValue },
		MinValue { 0.f },
		MaxValue { 0.f },
		IgnoresMinMax { true }
	{}

	TDAttribute(float defaultValue, float defaultMin, float defaultMax) :
		BaseValue { defaultValue },
		CurrentValue { defaultValue },
		MinValue { defaultMin },
		MaxValue { defaultMax },
		IgnoresMinMax { false }
	{}

	~TDAttribute();

	float GetBaseValue() const;
	float GetCurrentValue() const;
	float GetMinValue() const;
	float GetMaxValue() const;

	void SetBaseValue(float newBase);
	void SetCurrentValue(float newCurrent);
	void SetMinValue(float newMin);
	void SetMaxValue(float newMax);

	void Init(float base);
	void InitMinMax(float base, float min, float max);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	float BaseValue;

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	float CurrentValue;

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	float MinValue;

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	float MaxValue;

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	bool IgnoresMinMax;
};
