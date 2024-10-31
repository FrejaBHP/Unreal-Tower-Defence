// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BaseTowerAttributes.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class TOWERDEFENCETHING_API UBaseTowerAttributes : public UAttributeSet {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Base", ReplicatedUsing = OnRep_AttackRate)
	FGameplayAttributeData AttackRate;
	ATTRIBUTE_ACCESSORS(UBaseTowerAttributes, AttackRate)

	UPROPERTY(BlueprintReadOnly, Category = "Range", ReplicatedUsing = OnRep_Range)
	FGameplayAttributeData Range;
	ATTRIBUTE_ACCESSORS(UBaseTowerAttributes, Range)

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UFUNCTION()
	virtual void OnRep_AttackRate(const FGameplayAttributeData& oldAttackRate);

	UFUNCTION()
	virtual void OnRep_Range(const FGameplayAttributeData& oldRange);
};
