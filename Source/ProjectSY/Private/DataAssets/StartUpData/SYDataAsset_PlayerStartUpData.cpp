// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/SYDataAsset_PlayerStartUpData.h"
#include "AbilitySystem/Abilities/SYGameplayAbility.h"
#include "AbilitySystem/SYAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/SYPlayerGameplayAbility.h"

void USYDataAsset_PlayerStartUpData::GiveToAbilitySystemComponent(TObjectPtr<USYAbilitySystemComponent> InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	for (const FSYPlayerAbilitySet& AbilitySet : PlayerStartUpAbilitySets)
	{
		if (!AbilitySet.IsValid())
		{
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

		InASCToGive->GiveAbility(AbilitySpec);
	}
}
