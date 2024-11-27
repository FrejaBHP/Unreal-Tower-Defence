// Dragons rule ok


#include "Components/TDAbilityComponent.h"

// Sets default values for this component's properties
UTDAbilityComponent::UTDAbilityComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTDAbilityComponent::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void UTDAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// 
void UTDAbilityComponent::AddAbility(EAbilityHandle aHandle) {
	UTDAbility* newAbility = Cast<UTDGameInstance>(GetWorld()->GetGameInstance())->AManager->CreateAssignAbilityFromHandle(aHandle, this);
	
	newAbility->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
	newAbility->SetMobility(EComponentMobility::Stationary);
	newAbility->RegisterComponent();

	Abilities.Add(newAbility);
}
