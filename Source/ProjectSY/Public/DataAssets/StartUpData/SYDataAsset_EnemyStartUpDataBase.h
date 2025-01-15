// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/SYDataAsset_StartUpDataBase.h"
#include "SYDataAsset_EnemyStartUpDataBase.generated.h"

class USYEnemyGameplayAbility;

/**
 * 
 */
UCLASS()
class PROJECTSY_API USYDataAsset_EnemyStartUpDataBase : public USYDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(TObjectPtr<USYAbilitySystemComponent> InASCToGive, int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<USYEnemyGameplayAbility>> EnemyCombatAbilities;
};
