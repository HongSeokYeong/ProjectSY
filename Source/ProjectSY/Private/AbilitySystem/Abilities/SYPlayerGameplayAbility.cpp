// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/SYPlayerGameplayAbility.h"
#include "Characters/SYPlayerCharacter.h"
#include "Controllers/SYPlayerController.h"

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
