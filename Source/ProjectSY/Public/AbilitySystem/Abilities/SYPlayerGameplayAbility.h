// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/SYGameplayAbility.h"
#include "Widgets/SYUIManagerSubsystem.h"
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

	UFUNCTION(BlueprintPure, Category = "SY|Ability")
	USYUIManagerSubsystem* GetUIManagerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "SY|Ability")
	FGameplayEffectSpecHandle MakePlayerDamageEffectSpeceHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount);

	UFUNCTION(BlueprintCallable, Category = "SY|Ability")
	bool GetAbilityReaminingCooldownByTag(FGameplayTag InCooldownTag, float& TotalCooldownTime, float& ReminingCooldownTime);

private:
	TWeakObjectPtr<ASYPlayerCharacter> CachedPlayerCharacter;
	TWeakObjectPtr<ASYPlayerController> CachedPlayerController;
	TWeakObjectPtr<USYUIManagerSubsystem> CachedUIManager;
	
};