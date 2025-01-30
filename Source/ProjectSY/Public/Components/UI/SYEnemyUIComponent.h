// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/SYPawnUIComponent.h"
#include "SYEnemyUIComponent.generated.h"

class USYWidgetBase;

/**
 * 
 */
UCLASS()
class PROJECTSY_API USYEnemyUIComponent : public USYPawnUIComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void RegisterEnemyDrawnWidget(USYWidgetBase* InWidgetToRegister);

	UFUNCTION(BlueprintCallable)
	void RemoveEnemyDrawnWidgetsIfAny();

private:
	TArray<USYWidgetBase*> EnemyDrawnWidgets;
};
