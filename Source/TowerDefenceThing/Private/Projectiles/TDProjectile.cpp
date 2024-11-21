// Dragons rule ok


#include "Projectiles/TDProjectile.h"
#include "EnemyUnit.h"
#include "TDGameInstance.h"

// Sets default values
ATDProjectile::ATDProjectile() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!CollisionComponent) {
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
		RootComponent = CollisionComponent;
		CollisionComponent->SetNotifyRigidBodyCollision(true);
		CollisionComponent->InitSphereRadius(10.f);
		CollisionComponent->SetCollisionProfileName(FName("Projectile"));
		CollisionComponent->OnComponentHit.AddDynamic(this, &ATDProjectile::OnHit);
	}

	if (!SplashComponent) {
		SplashComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Splash"));
		SplashComponent->SetupAttachment(CollisionComponent);
		SplashComponent->SetNotifyRigidBodyCollision(true);
		//SplashComponent->InitSphereRadius(10.f);
		SplashComponent->SetCollisionProfileName(FName("Projectile"));
		//SplashComponent->OnComponentHit.AddDynamic(this, &ATDProjectile::OnHit);
	}
	
	if (!FlipbookComponent) {
		FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Visible Flipbook"));
		FlipbookComponent->SetupAttachment(CollisionComponent);
		FlipbookComponent->SetCollisionProfileName(FName("NoCollision"));
		FlipbookComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	if (!ProjMovementComponent) {
		// Use this component to drive this projectile's movement.
		ProjMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
		ProjMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjMovementComponent->ProjectileGravityScale = 0.0f;
	}
}

// Called when the game starts or when spawned
void ATDProjectile::BeginPlay() {
	Super::BeginPlay();

	// Lav potentielt om med constructionhelper, se om det virker nu hvor den anden fejl er fjernet
	FlipbookComponent->SetFlipbook(Cast<UTDGameInstance>(GetGameInstance())->GetFlipbookByName(*FlipbookName));

	ProjMovementComponent->InitialSpeed = Speed;
	ProjMovementComponent->MaxSpeed = Speed;
	SplashComponent->SetSphereRadius(SplashRadius);
}

// Called every frame
void ATDProjectile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (Target.IsValid()) {
		ProjMovementComponent->Velocity = (Target->GetActorLocation() - GetActorLocation()).GetSafeNormal() * Speed;

		// Modificeret logik fra bRotationFollowsVelocity, så projektilet vinkles endnu en 90 grader. Får det til ikke at pege op
		FRotator DesiredRotation = ProjMovementComponent->Velocity.Rotation();
		DesiredRotation.Pitch -= 90.;
		ProjMovementComponent->UpdatedComponent->SetWorldRotation(DesiredRotation);
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

	if (SplashRadius != 0.f) {
		TArray<AActor*> overlappingActors;
		SplashComponent->GetOverlappingActors(overlappingActors);

		int32 index;
		overlappingActors.Find(Target.Get(), index);
		if (index != INDEX_NONE) {
			overlappingActors.RemoveAt(index);
		}

		ProjectileSplashDelegate.Execute(overlappingActors);
	}

	if (RemainingChains > 0) {
		RemainingChains--;
	}
	else {
		Destroy();
	}
}

