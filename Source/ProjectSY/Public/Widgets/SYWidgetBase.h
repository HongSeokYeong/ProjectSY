// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SYWidgetBase.generated.h"

/**
 *
 */
UCLASS()
class PROJECTSY_API USYWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

public:
	virtual void ShowWidget();

	UFUNCTION(BlueprintImplementableEvent, meta = (AdvancedDisplay = "On Owning Show UI Widget"))
	void BP_ShowWidget();

	UFUNCTION(BlueprintCallable)
	virtual void HideWidget();
};
