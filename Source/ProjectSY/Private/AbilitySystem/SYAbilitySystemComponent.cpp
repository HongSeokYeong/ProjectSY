// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SYAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/SYPlayerGameplayAbility.h"
#include "SYDebugHelper.h"
#include "Abilities/GameplayAbility.h"

void USYAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	TryActivateAbilityByInputTag(InInputTag);
}

void USYAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid() || !InInputTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("InputTag.MustBeHeld"))))
	{
		return;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag) && AbilitySpec.IsActive())
		{
			CancelAbilityHandle(AbilitySpec.Handle);
		}
	}
}

void USYAbilitySystemComponent::GrantPlayerWeaponAbilities(const TArray<FSYPlayerAbilitySet>& InDefaultWeaponAbilities, const TArray<FSYPlayerSpecialAbilitySet>& InSpecialWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
	if (InDefaultWeaponAbilities.IsEmpty())
	{
		return;
	}

	for (const FSYPlayerAbilitySet& AbilitySet : InDefaultWeaponAbilities)
	{
		if (!AbilitySet.IsValid())
		{
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

		OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
	}

	for (const FSYPlayerSpecialAbilitySet& AbilitySet : InSpecialWeaponAbilities)
	{
		if (!AbilitySet.IsValid())
		{
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

		OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
	}
}

void USYAbilitySystemComponent::RemovedGrantedPlayerWeaponAbilities(UPARAM(ref)TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
{
	if (InSpecHandlesToRemove.IsEmpty())
	{
		return;
	}

	for (const FGameplayAbilitySpecHandle& SpecHandle : InSpecHandlesToRemove)
	{
		if (SpecHandle.IsValid())
		{
			ClearAbility(SpecHandle);
		}
	}

	InSpecHandlesToRemove.Empty();
}

bool USYAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate)
{
	check(AbilityTagToActivate.IsValid());

	TArray<FGameplayAbilitySpec*> FoundAbilitySpec;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityTagToActivate.GetSingleTagContainer(), FoundAbilitySpec, false);

	if (!FoundAbilitySpec.IsEmpty())
	{
		const int32 RandomAbilityIndex = FMath::RandRange(0, FoundAbilitySpec.Num() - 1);
		FGameplayAbilitySpec* SpecToActivate = FoundAbilitySpec[RandomAbilityIndex];

		check(SpecToActivate);

		if (!SpecToActivate->IsActive())
		{
			return TryActivateAbility(SpecToActivate->Handle);
		}
	}

	return false;
}

bool USYAbilitySystemComponent::TryActivateAbilityByInputTag(FGameplayTag AbilityTagToActivate)
{
	if (!AbilityTagToActivate.IsValid())
	{
		return false;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{

		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(AbilityTagToActivate))
		{
			continue;
		}

		if (AbilityTagToActivate.MatchesTag(FGameplayTag::RequestGameplayTag(FName("InputTag.Toggleable"))) && AbilitySpec.IsActive())
		{
			CancelAbilityHandle(AbilitySpec.Handle);
		}
		else
		{
			return TryActivateAbility(AbilitySpec.Handle);
		}
	}

	return false;
}
