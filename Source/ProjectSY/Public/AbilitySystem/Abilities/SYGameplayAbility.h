// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SYGameplayAbility.generated.h"

class USYPawnCombatComponent;
class USYAbilitySystemComponent;

UENUM(BlueprintType)
enum class ESYAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

/**
 * 
 */
UCLASS()
class PROJECTSY_API USYGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UPROPERTY(EditDefaultsOnly, Category = "SYAbility")
	ESYAbilityActivationPolicy AbilityActivationPolicy = ESYAbilityActivationPolicy::OnTriggered;

	UFUNCTION(BlueprintPure, Category = "SY|Ability")
	USYPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "SY|Ability")
	USYAbilitySystemComponent* GetSYAbilitySystemComponentFromActorInfo() const;
};
