// Fill out your copyright notice in the Description page of Project Settings.


#include "SYFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/SYAbilitySystemComponent.h"

TObjectPtr<USYAbilitySystemComponent> USYFunctionLibrary::NativeGetSYASCFromActor(TObjectPtr<AActor> InActor)
{
    check(InActor);

    return CastChecked<USYAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void USYFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
    USYAbilitySystemComponent* ASC = NativeGetSYASCFromActor(InActor);

    if (!ASC->HasMatchingGameplayTag(TagToAdd))
    {
        ASC->AddLooseGameplayTag(TagToAdd);
    }
}

void USYFunctionLibrary::RemoveGameplayFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
    USYAbilitySystemComponent* ASC = NativeGetSYASCFromActor(InActor);

    if (ASC->HasMatchingGameplayTag(TagToRemove))
    {
        ASC->RemoveLooseGameplayTag(TagToRemove);
    }
}

bool USYFunctionLibrary::NativeDoesActorHaveTag(TObjectPtr<AActor> InActor, FGameplayTag TagToCheck)
{
    USYAbilitySystemComponent* ASC = NativeGetSYASCFromActor(InActor);

    return ASC->HasMatchingGameplayTag(TagToCheck);
}

void USYFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, ESYConfirmType& OutConfirmType)
{
    OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? ESYConfirmType::Yes : ESYConfirmType::No;
}
