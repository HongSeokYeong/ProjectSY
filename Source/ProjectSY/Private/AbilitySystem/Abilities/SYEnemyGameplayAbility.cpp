// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/SYEnemyGameplayAbility.h"
#include "Characters/SYEnemyCharacter.h"

ASYEnemyCharacter* USYEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
    if (!CachedEnemyCharacter.IsValid())
    {
        CachedEnemyCharacter = Cast<ASYEnemyCharacter>(CurrentActorInfo->AvatarActor);
    }

    return CachedEnemyCharacter.IsValid() ? CachedEnemyCharacter.Get() : nullptr;
}

USYEnemyCombatComponent* USYEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
    return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}
