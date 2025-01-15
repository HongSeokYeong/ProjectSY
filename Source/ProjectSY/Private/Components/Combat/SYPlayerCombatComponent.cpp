// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/SYPlayerCombatComponent.h"
#include "Items/Weapons/SYPlayerWeapon.h"

ASYPlayerWeapon* USYPlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
    return Cast<ASYPlayerWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}
