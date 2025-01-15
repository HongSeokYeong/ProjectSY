// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/SYGameplayAbility.h"
#include "SYEnemyGameplayAbility.generated.h"

class ASYEnemyCharacter;
class USYEnemyCombatComponent;

/**
 * 
 */
UCLASS()
class PROJECTSY_API USYEnemyGameplayAbility : public USYGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "SY|Ability")
	ASYEnemyCharacter* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "SY|Ability")
	USYEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

private:
	TWeakObjectPtr<ASYEnemyCharacter> CachedEnemyCharacter;
};
