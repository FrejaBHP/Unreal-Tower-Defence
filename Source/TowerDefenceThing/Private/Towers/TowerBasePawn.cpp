// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers/TowerBasePawn.h"

// Sets default values
ATowerBasePawn::ATowerBasePawn() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GameplayTags.AddTag(FGameplayTag::RequestGameplayTag(FName("UnitTags.Tower")));

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	RootComponent = BoxComponent;
	BoxComponent->InitBoxExtent(FVector(50., 50., 50.));
	BoxComponent->SetMobility(EComponentMobility::Stationary);
	BoxComponent->SetCollisionProfileName(FName("TDUnit"));

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Visible Sprite"));
	SpriteComponent->SetupAttachment(BoxComponent);
	SpriteComponent->SetCastShadow(true);
	SpriteComponent->SetMobility(EComponentMobility::Stationary);

	FRotator rotator = { 0., 90., 0. };
	SpriteComponent->AddRelativeRotation(rotator.Quaternion());

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System"));
	AbilitySystemComponent->SetIsReplicated(true);

	BaseAttributes = CreateDefaultSubobject<UBaseTowerAttributes>(TEXT("Base Attributes"));
}

// Called when the game starts or when spawned
void ATowerBasePawn::BeginPlay() {
	Super::BeginPlay();
	
}

// Called every frame
void ATowerBasePawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATowerBasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATowerBasePawn::OnSelect() {

}

FGameplayTag ATowerBasePawn::GetUnitTypeTag() {
	return FGameplayTag::RequestGameplayTag(FName("UnitTags.Tower"));
}

bool ATowerBasePawn::HasGameplayTag(FGameplayTag tag) {
	if (GameplayTags.HasTag(tag)) {
		return true;
	}
	else {
		return false;
	}
}

FName ATowerBasePawn::GetUnitName() {
	return Name;
}

UAbilitySystemComponent* ATowerBasePawn::GetAbilitySystemComponent() const {
	return AbilitySystemComponent;
}

UBaseTowerAttributes* ATowerBasePawn::GetBaseAttributes() const {
	return BaseAttributes;
}
