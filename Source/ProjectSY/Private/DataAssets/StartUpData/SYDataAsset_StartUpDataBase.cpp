// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/SYDataAsset_StartUpDataBase.h"
#include "AbilitySystem/SYAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/SYGameplayAbility.h"

void USYDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(TObjectPtr<USYAbilitySystemComponent> InASCToGive, int32 ApplyLevel)
{
	check(InASCToGive);

	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);

	if (!StartUpGameplayEffect.IsEmpty())
	{
		for (const TSubclassOf< UGameplayEffect>& EffectClass : StartUpGameplayEffect)
		{
			if (!EffectClass)
			{
				continue;
			}

			UGameplayEffect* EffectCDO = EffectClass->GetDefaultObject<UGameplayEffect>();
			InASCToGive->ApplyGameplayEffectToSelf(
				EffectCDO,
				ApplyLevel,
				InASCToGive->MakeEffectContext()
				);
		}
	}
}

void USYDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<USYGameplayAbility>>& InAbilitiesToGive, TObjectPtr<USYAbilitySystemComponent> InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<USYGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability)
		{
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;

		InASCToGive->GiveAbility(AbilitySpec);
	}
}
