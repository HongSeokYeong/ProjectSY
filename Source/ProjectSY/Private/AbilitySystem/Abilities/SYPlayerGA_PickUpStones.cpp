// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/SYPlayerGA_PickUpStones.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Characters/SYPlayerCharacter.h"
#include "Items/PickUps/SYStoneBase.h"
#include "Widgets/SYUIManagerSubsystem.h"
#include "Widgets/SYPlayerWidget.h"

void USYPlayerGA_PickUpStones::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	Cast<USYPlayerWidget>(GetUIManagerFromActorInfo()->GetWidget(FName("WBP_PlayerOverlay")))->OnStoneInteracted.Broadcast(true);
}

void USYPlayerGA_PickUpStones::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	Cast<USYPlayerWidget>(GetUIManagerFromActorInfo()->GetWidget(FName("WBP_PlayerOverlay")))->OnStoneInteracted.Broadcast(false);
}
void USYPlayerGA_PickUpStones::CollectStones()
{
	CollectedStones.Empty();
	
	TArray<FHitResult> TraceHits;

	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetPlayerCharacterFromActorInfo(),
		GetPlayerCharacterFromActorInfo()->GetActorLocation(),
		GetPlayerCharacterFromActorInfo()->GetActorLocation() + -GetPlayerCharacterFromActorInfo()->GetActorUpVector() * BoxTraceDistance,
		TraceBoxSize / 2.0f,
		(-GetPlayerCharacterFromActorInfo()->GetActorUpVector()).ToOrientationRotator(),
		StoneTraceChannel,
		false,
		TArray<AActor*>(),
		bDrawDebugShape ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		TraceHits,
		true
	);

	for (const FHitResult& TraceHit : TraceHits)
	{
		if (ASYStoneBase* FoundStone = Cast<ASYStoneBase>(TraceHit.GetActor()))
		{
			CollectedStones.AddUnique(FoundStone);
		}
	}

	if (CollectedStones.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
	}
}

void USYPlayerGA_PickUpStones::ConsumeStones()
{
	if (CollectedStones.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
		return;
	}

	for (ASYStoneBase* CollectedStone : CollectedStones)
	{
		if (CollectedStone)
		{
			CollectedStone->Consume(GetSYAbilitySystemComponentFromActorInfo(), GetAbilityLevel());
		}
	}
}
