// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/SYEnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "SYGameplayTags.h"
#include "SYFunctionLibrary.h"

#include "SYDebugHelper.h"

void USYEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}

	OverlappedActors.AddUnique(HitActor);

	// TODO : Implement block check
	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = USYFunctionLibrary::NativeDoesActorHaveTag(HitActor, SYGameplayTags::Player_Status_Blocking);
	const bool bIsMyAttackUnblockable = USYFunctionLibrary::NativeDoesActorHaveTag(GetOwningPawn(), SYGameplayTags::Enemy_Status_Unbloackable);

	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		bIsValidBlock = USYFunctionLibrary::IsValidBlock(GetOwningPawn(), HitActor);
	}

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;

	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitActor,
			SYGameplayTags::Player_Event_SuccessfulBlock,
			EventData
		);
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			SYGameplayTags::Shared_Event_MeleeHit,
			EventData
		);
	}
}
