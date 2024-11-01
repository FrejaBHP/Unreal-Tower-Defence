// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers/TowerBasePawn.h"

// Sets default values
ATowerBasePawn::ATowerBasePawn() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	RootComponent = BoxComponent;
	BoxComponent->InitBoxExtent(FVector(50., 50., 50.));
	BoxComponent->SetMobility(EComponentMobility::Stationary);
	BoxComponent->SetCollisionProfileName(FName("TDUnit"));

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Overlap Range"));
	CapsuleComponent->SetupAttachment(BoxComponent);
	CapsuleComponent->SetMobility(EComponentMobility::Stationary);
	CapsuleComponent->SetCollisionProfileName(FName("TowerTargeting"));

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Visible Sprite"));
	SpriteComponent->SetupAttachment(BoxComponent);
	SpriteComponent->SetCastShadow(true);
	SpriteComponent->SetMobility(EComponentMobility::Stationary);

	FRotator rotator = { 0., 90., 0. };
	SpriteComponent->AddRelativeRotation(rotator.Quaternion());

	BaseAttributeSet = MakeUnique<TowerBaseTDAttributes>();
}

// Called when the game starts or when spawned
void ATowerBasePawn::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void ATowerBasePawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ATowerBasePawn::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);
	SetOwner(NewController);
}

// Called to bind functionality to input
void ATowerBasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATowerBasePawn::OnSelect() {

}

EUnitType ATowerBasePawn::GetUnitType() {
	return UnitType;
}

FName ATowerBasePawn::GetUnitName() {
	return Name;
}
