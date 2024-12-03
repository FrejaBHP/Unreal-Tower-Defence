// Dragons rule ok

#pragma once


#include "CoreMinimal.h"
#include "Widgets/Notifications/SProgressBar.h"
#include "Widgets/SCompoundWidget.h"

#include "Abilities/TDAbility.h"
#include "AbilityEnums.h"
#include "FTDUIResources.h"
#include "Slate/SlateGameResources.h"


DECLARE_DELEGATE_OneParam(FClickedSignature, EAbilityHandle);

class TOWERDEFENCETHING_API SContextMenuSquareWidget : public SCompoundWidget {

public:
	SLATE_BEGIN_ARGS(SContextMenuSquareWidget) :
		_tdUIResources()
	{}
	SLATE_ARGUMENT(TWeakPtr<FSlateGameResources>, tdUIResources)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	~SContextMenuSquareWidget();
	FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	FReply OnMouseButtonDoubleClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	void SetImageBrushWithName(FName newBrushName);
	void SetBoundAbility(UTDAbility* ability);
	void UpdateCooldown();
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	FClickedSignature OnClicked;
	bool IsClickable = false;

protected:
	TSharedPtr<SProgressBar> ProgressBarPtr;
	TWeakPtr<FSlateGameResources> tdUIResources;
	FSlateBrush imageBrush;

	UTDAbility* BoundAbility = nullptr;
	FName CurrentAbilityBrushName;
	EAbilityHandle CurrentAbilityHandle;
	float CooldownRatio { 1.f };
	const FSlateBrush* GetImageBrushFromName(FName newBrushName) const;
};
