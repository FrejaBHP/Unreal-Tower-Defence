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

	// Gets the starting value
	float GetBaseValue() const;
	// Gets the current value. Use this over the raw property unless you absolutely have to
	float GetCurrentValue() const;
	// Gets the minimum value. Use this over the raw property unless you absolutely have to
	float GetMinValue() const;
	// Gets the maximum value. Use this over the raw property unless you absolutely have to
	float GetMaxValue() const;

	// Sets the base value. Use this over the raw property unless you absolutely have to
	void SetBaseValue(float newBase);
	// Sets the current value. Use this over the raw property unless you absolutely have to
	void SetCurrentValue(float newCurrent);
	// Sets the minimum value. Use this over the raw property unless you absolutely have to
	void SetMinValue(float newMin);
	// Sets the maximum value. Use this over the raw property unless you absolutely have to
	void SetMaxValue(float newMax);

	void Init(float base);
	void InitMinMax(float base, float min, float max);

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	float BaseValue;

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	float CurrentValue;

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	float MinValue;

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	float MaxValue;

protected:
	

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	bool IgnoresMinMax;
};
