// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TDProjectile.generated.h"

DECLARE_DELEGATE_TwoParams(FProjectileHitSignature, ATDProjectile*, TWeakObjectPtr<AActor>);
DECLARE_DELEGATE_OneParam(FProjectileSplashSignature, TArray<AActor*>);

UCLASS()
class TOWERDEFENCETHING_API ATDProjectile : public AActor {
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATDProjectile();

	FProjectileHitSignature ProjectileHitDelegate;
	FProjectileSplashSignature ProjectileSplashDelegate;
	void OnCollideWithTarget();

	float Speed;
	float RemainingChains;
	float SplashRadius;
	TWeakObjectPtr<AActor> Target;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SplashComponent;

	UPROPERTY(VisibleAnywhere)
	UPaperSpriteComponent* SpriteComponent;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjMovementComponent;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
