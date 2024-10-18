// Dragons rule ok

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class ESquareFunctionType : int8 {
	None,
	Build,
	Cast
};

class TOWERDEFENCETHING_API SquareWidgetData {

public:

	ESquareFunctionType FunctionType = ESquareFunctionType::None;
	int32 FunctionID = 0;
	FName brushName = "empty_Brush";
	int8 DesiredGridX = 0;
	int8 DesiredGridY = 0;

	SquareWidgetData();
	~SquareWidgetData();
};
