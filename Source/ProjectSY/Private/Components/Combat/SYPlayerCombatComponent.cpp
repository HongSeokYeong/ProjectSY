// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/SYPlayerCombatComponent.h"
#include "Items/Weapons/SYPlayerWeapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "SYGameplayTags.h"

#include "SYDebugHelper.h"

ASYPlayerWeapon* USYPlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<ASYPlayerWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

ASYPlayerWeapon* USYPlayerCombatComponent::GetPlayerCurrentEquippedWeapon() const
{
	return Cast<ASYPlayerWeapon>(GetCharacterCurrentEquippedWeapon());
}

float USYPlayerCombatComponent::GetPlayerCurrentEquipWeaponDamageAtLevel(float InLevel) const
{
	return GetPlayerCurrentEquippedWeapon()->PlayerWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

void USYPlayerCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}

	OverlappedActors.AddUnique(HitActor);

	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		FGameplayTag::RequestGameplayTag(FName("Shared.Event.MeleeHit")),
		Data
	);

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		FGameplayTag::RequestGameplayTag(FName("Player.Event.HitPause")),
		FGameplayEventData()
	);
}

void USYPlayerCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		FGameplayTag::RequestGameplayTag(FName("Player.Event.HitPause")),
		FGameplayEventData()
	);
}
