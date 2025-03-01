// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SYWidgetBase.h"
#include "SYEnemyWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSY_API USYEnemyWidget : public USYWidgetBase
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent, meta = (AdvancedDisplay = "On Owning Player UI Component Initialized"))
	void BP_OnOwningEnemyInitialized(ASYBaseCharacter* OwningEnemy);

public:
	UFUNCTION(BlueprintCallable)
	void InitEnemyCreatedWidget(AActor* OwningEnemyActor);
};
