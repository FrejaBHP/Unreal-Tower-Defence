// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <GameplayTagContainer.h>
#include "ClickableUnit.h"
#include "TowerDefenceThingCharacter.generated.h"

UCLASS(Blueprintable)
class ATowerDefenceThingCharacter : public ACharacter, public IClickableUnit {
	GENERATED_BODY()

public:
	ATowerDefenceThingCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	virtual void OnSelect() override;
	virtual FGameplayTag GetUnitTypeTag() override;
	virtual bool HasGameplayTag(FGameplayTag) override;
	virtual FName GetUnitName() override;

	FName Name;

	UPROPERTY()
	FGameplayTagContainer GameplayTags;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
};

