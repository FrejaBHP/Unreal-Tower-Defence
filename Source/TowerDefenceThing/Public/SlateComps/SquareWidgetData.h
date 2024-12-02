// Dragons rule ok

#pragma once

#include "CoreMinimal.h"
#include "AbilityEnums.h"

UENUM()
enum class ESquareFunctionType : int8 {
	None,
	Build,
	Cast
};

class TOWERDEFENCETHING_API SquareWidgetData {
public:
	ESquareFunctionType FunctionType { ESquareFunctionType::None };
	EAbilityHandle AbilityHandle { EAbilityHandle::NONE };
	FName BrushName { "empty_Brush" };

	SquareWidgetData() = default;

	SquareWidgetData(ESquareFunctionType type, EAbilityHandle aHandle, FName brushName) :
		FunctionType{ type },
		AbilityHandle { aHandle },
		BrushName { brushName }
	{}

	~SquareWidgetData();
};
