// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/SYGameplayAbility.h"
#include "AbilitySystem/SYAbilitySystemComponent.h"
#include "Components/Combat/SYPawnCombatComponent.h"

void USYGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (AbilityActivationPolicy == ESYAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void USYGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AbilityActivationPolicy == ESYAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

USYPawnCombatComponent* USYGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<USYPawnCombatComponent>();
}

USYAbilitySystemComponent* USYGameplayAbility::GetSYAbilitySystemComponentFromActorInfo() const
{
	return Cast<USYAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}
