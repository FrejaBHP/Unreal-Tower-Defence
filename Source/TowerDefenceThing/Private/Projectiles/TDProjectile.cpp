// Dragons rule ok


#include "Projectiles/TDProjectile.h"
#include "EnemyUnit.h"
#include "TDGameInstance.h"

// Sets default values
ATDProjectile::ATDProjectile() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!SphereComponent) {
		SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
		RootComponent = SphereComponent;
		SphereComponent->SetNotifyRigidBodyCollision(true);
		SphereComponent->InitSphereRadius(10.f);
		SphereComponent->SetCollisionProfileName(FName("Projectile"));
		SphereComponent->OnComponentHit.AddDynamic(this, &ATDProjectile::OnHit);
	}
	
	if (!SpriteComponent) {
		SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Visible Sprite"));
		SpriteComponent->SetupAttachment(SphereComponent);
		SpriteComponent->SetCollisionProfileName(FName("NoCollision"));
		SpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	if (!ProjMovementComponent) {
		// Use this component to drive this projectile's movement.
		ProjMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
		ProjMovementComponent->SetUpdatedComponent(SphereComponent);
		ProjMovementComponent->bRotationFollowsVelocity = true;
		ProjMovementComponent->ProjectileGravityScale = 0.0f;
	}
}

// Called when the game starts or when spawned
void ATDProjectile::BeginPlay() {
	Super::BeginPlay();

	// Lav potentielt om med constructionhelper, se om det virker nu hvor den anden fejl er fjernet
	SpriteComponent->SetSprite(Cast<UTDGameInstance>(GetGameInstance())->GetSpriteByName("arrow_Sprite"));

	ProjMovementComponent->InitialSpeed = Speed;
	ProjMovementComponent->MaxSpeed = Speed;
}

// Called every frame
void ATDProjectile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (Target.IsValid()) {
		ProjMovementComponent->Velocity = (Target->GetActorLocation() - GetActorLocation()).GetSafeNormal() * Speed;
	}
	else {
		Destroy();
	}
}

void ATDProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	if (OtherActor == Target) {
		OnCollideWithTarget();
	}
}

void ATDProjectile::OnCollideWithTarget() {
	ProjectileHitDelegate.Execute(this, Target);

	if (RemainingChains > 0) {
		RemainingChains--;
	}
	else {
		Destroy();
	}
}

