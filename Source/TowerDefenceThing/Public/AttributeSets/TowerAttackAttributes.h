// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "TowerAttackAttributes.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class TOWERDEFENCETHING_API UTowerAttackAttributes : public UAttributeSet {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Attacks", ReplicatedUsing = OnRep_MinDamage)
	FGameplayAttributeData MinDamage;
	ATTRIBUTE_ACCESSORS(UTowerAttackAttributes, MinDamage)

	UPROPERTY(BlueprintReadOnly, Category = "Attacks", ReplicatedUsing = OnRep_MaxDamage)
	FGameplayAttributeData MaxDamage;
	ATTRIBUTE_ACCESSORS(UTowerAttackAttributes, MaxDamage)

	UPROPERTY(BlueprintReadOnly, Category = "Attacks", ReplicatedUsing = OnRep_MaxTargets)
	FGameplayAttributeData MaxTargets;
	ATTRIBUTE_ACCESSORS(UTowerAttackAttributes, MaxTargets)

	UPROPERTY(BlueprintReadOnly, Category = "Attacks", ReplicatedUsing = OnRep_SplashRadius)
	FGameplayAttributeData SplashRadius;
	ATTRIBUTE_ACCESSORS(UTowerAttackAttributes, SplashRadius)

	UPROPERTY(BlueprintReadOnly, Category = "Attacks", ReplicatedUsing = OnRep_SplashPercentage)
	FGameplayAttributeData SplashPercentage;
	ATTRIBUTE_ACCESSORS(UTowerAttackAttributes, SplashPercentage)

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UFUNCTION()
	virtual void OnRep_MinDamage(const FGameplayAttributeData& oldMinDamage);

	UFUNCTION()
	virtual void OnRep_MaxDamage(const FGameplayAttributeData& oldMaxDamage);

	UFUNCTION()
	virtual void OnRep_MaxTargets(const FGameplayAttributeData& oldMaxTargets);

	UFUNCTION()
	virtual void OnRep_SplashRadius(const FGameplayAttributeData& oldSplashRadius);

	UFUNCTION()
	virtual void OnRep_SplashPercentage(const FGameplayAttributeData& oldSplashPercentage);
};
