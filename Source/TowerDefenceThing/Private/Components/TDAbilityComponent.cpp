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

// Gets the Ability Manager stored in the Game Instance, and returns a new component matching the EAbilityHandle argument
void UTDAbilityComponent::AddAbility(EAbilityHandle aHandle) {
	UTDAbility* newAbility = Cast<UTDGameInstance>(GetWorld()->GetGameInstance())->AManager->CreateAssignAbilityFromHandle(aHandle, this);
	
	newAbility->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
	newAbility->SetMobility(EComponentMobility::Stationary);
	newAbility->RegisterComponent();

	Abilities.Add(newAbility);
}

// Searches the ability TArray for an ability with a matching EAbilityHandle field, then deletes and cleans up the ability if it finds any
void UTDAbilityComponent::RemoveAbility(EAbilityHandle aHandle) {
	int32 index = Abilities.IndexOfByPredicate([&aHandle](const UTDAbility* ability) {
		return ability->AbilityHandle == aHandle;
	});

	if (index != INDEX_NONE) {
		Abilities[index]->DestroyAbility();
		Abilities.RemoveAt(index);
	}
}
