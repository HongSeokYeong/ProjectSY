// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SYWidgetBase.generated.h"

class USYPlayerUIComponent;

/**
 *
 */
UCLASS()
class PROJECTSY_API USYWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent, meta = (AdvancedDisplay = "On Owning Player UI Component Initialized"))
	void BP_OnOwningPlayerUIComponentInitialized(USYPlayerUIComponent* OwningPlayerUIComponent);

	UFUNCTION(BlueprintImplementableEvent, meta = (AdvancedDisplay = "On Owning Player UI Component Initialized"))
	void BP_OnOwningEnemyUIComponentInitialized(USYEnemyUIComponent* OwningEnemyUIComponent);

public:
	UFUNCTION(BlueprintCallable)
	void InitEnemyCreatedWidget(AActor* OwningEnemyActor);

	virtual void ShowWidget();

	UFUNCTION(BlueprintImplementableEvent, meta = (AdvancedDisplay = "On Owning Show UI Widget"))
	void BP_ShowWidget();

	UFUNCTION(BlueprintCallable)
	virtual void HideWidget();
};
