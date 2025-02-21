// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/SYEnemyGameplayAbility.h"
#include "SYEnemyGA_Heal.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSY_API USYEnemyGA_Heal : public USYEnemyGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> GEHeal;
};
