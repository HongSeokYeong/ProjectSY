// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/SYEnemyGA_Heal.h"
#include "AbilitySystem/SYAbilitySystemComponent.h"

void USYEnemyGA_Heal::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	checkf(GEHeal, TEXT("GEHeal is not Set"));

	ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, GEHeal.GetDefaultObject(), 1);
}

void USYEnemyGA_Heal::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
