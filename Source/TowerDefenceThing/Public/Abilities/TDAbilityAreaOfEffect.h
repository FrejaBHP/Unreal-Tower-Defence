// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "TDAbilityAreaOfEffect.generated.h"

UCLASS()
class TOWERDEFENCETHING_API ATDAbilityAreaOfEffect : public AActor {
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATDAbilityAreaOfEffect();

	float Radius;

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* OverlapComponent = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
