// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/SYPlayerGameplayAbility.h"
#include "Characters/SYPlayerCharacter.h"
#include "Controllers/SYPlayerController.h"
#include "AbilitySystem/SYAbilitySystemComponent.h"
#include "SYGameplayTags.h"

ASYPlayerCharacter* USYPlayerGameplayAbility::GetPlayerCharacterFromActorInfo()
{
	if (!CachedPlayerCharacter.IsValid())
	{
		CachedPlayerCharacter = Cast<ASYPlayerCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedPlayerCharacter.IsValid() ? CachedPlayerCharacter.Get() : nullptr;

}

ASYPlayerController* USYPlayerGameplayAbility::GetPlayerControllerFromActorInfo()
{
	if (!CachedPlayerController.IsValid())
	{
		CachedPlayerController = Cast<ASYPlayerController>(CurrentActorInfo->PlayerController);
	}

	return CachedPlayerController.IsValid() ? CachedPlayerController.Get() : nullptr;
}

USYPlayerCombatComponent* USYPlayerGameplayAbility::GetPlayerCombatComponentFromActorInfo()
{
	return GetPlayerCharacterFromActorInfo()->GetPlayerCombatComponent();
}

USYPlayerUIComponent* USYPlayerGameplayAbility::GetPlayerUIComponentFromActorInfo()
{
	return GetPlayerCharacterFromActorInfo()->GetPlayerUIComponent();
}

FGameplayEffectSpecHandle USYPlayerGameplayAbility::MakePlayerDamageEffectSpeceHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount)
{
	check(EffectClass);

	FGameplayEffectContextHandle ContextHandle = GetSYAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle EffectSpecHandle = GetSYAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle
	);

	EffectSpecHandle.Data->SetSetByCallerMagnitude(
		FGameplayTag::RequestGameplayTag(FName("Shared.SetByCaller.BaseDamage")),
		InWeaponBaseDamage
	);

	if (InCurrentAttackTypeTag.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InUsedComboCount);
	}

	return EffectSpecHandle;
}

bool USYPlayerGameplayAbility::GetAbilityReaminingCooldownByTag(FGameplayTag InCooldownTag, float& TotalCooldownTime, float& RemainingCooldownTime)
{
	check(InCooldownTag.IsValid());

	FGameplayEffectQuery CooldownQuery = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(InCooldownTag.GetSingleTagContainer());

	TArray<TPair<float, float>> TimeRemainingAndDuration = GetAbilitySystemComponentFromActorInfo()->GetActiveEffectsTimeRemainingAndDuration(CooldownQuery);

	if (!TimeRemainingAndDuration.IsEmpty())
	{
		RemainingCooldownTime = TimeRemainingAndDuration[0].Key;
		TotalCooldownTime = TimeRemainingAndDuration[0].Value;
	}

	return RemainingCooldownTime > 0.0f;
}
