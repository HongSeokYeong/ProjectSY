// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/SYGameplayAbility.h"
#include "SYPlayerGameplayAbility.generated.h"

class ASYPlayerCharacter;
class ASYPlayerController;

/**
 * 
 */
UCLASS()
class PROJECTSY_API USYPlayerGameplayAbility : public USYGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "SY|Ability")
	ASYPlayerCharacter* GetPlayerCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "SY|Ability")
	ASYPlayerController* GetPlayerControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "SY|Ability")
	USYPlayerCombatComponent* GetPlayerCombatComponentFromActorInfo();

private:
	TWeakObjectPtr<ASYPlayerCharacter> CachedPlayerCharacter;
	TWeakObjectPtr<ASYPlayerController> CachedPlayerController;
	
};
