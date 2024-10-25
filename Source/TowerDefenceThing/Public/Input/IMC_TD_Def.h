// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "IMC_TD_Def.generated.h"

UCLASS()
class TOWERDEFENCETHING_API UIMC_TD_Def : public UInputMappingContext {
	GENERATED_BODY()

public:
	UInputAction* InputLeftClick;
	UInputAction* InputRightClick;
};
