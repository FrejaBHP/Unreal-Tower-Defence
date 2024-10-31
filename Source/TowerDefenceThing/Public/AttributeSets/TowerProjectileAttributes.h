// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "TowerProjectileAttributes.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class TOWERDEFENCETHING_API UTowerProjectileAttributes : public UAttributeSet {
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "Projectiles", ReplicatedUsing = OnRep_Speed)
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UTowerProjectileAttributes, Speed)

	UPROPERTY(BlueprintReadOnly, Category = "Projectiles", ReplicatedUsing = OnRep_Chains)
	FGameplayAttributeData Chains;
	ATTRIBUTE_ACCESSORS(UTowerProjectileAttributes, Chains)

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UFUNCTION()
	virtual void OnRep_Speed(const FGameplayAttributeData& oldSpeed);

	UFUNCTION()
	virtual void OnRep_Chains(const FGameplayAttributeData& oldChains);
};
