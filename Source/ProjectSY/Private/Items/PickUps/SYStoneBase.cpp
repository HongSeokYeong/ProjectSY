// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PickUps/SYStoneBase.h"
#include "Characters/SYPlayerCharacter.h"
#include "AbilitySystem/SYAbilitySystemComponent.h"
#include "SYGameplayTags.h"

void ASYStoneBase::Consume(USYAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel)
{
	check(StoneGameplayEffectClass);
	
	UGameplayEffect* EffectCDO = StoneGameplayEffectClass->GetDefaultObject<UGameplayEffect>();

	AbilitySystemComponent->ApplyGameplayEffectToSelf(
		EffectCDO,
		ApplyLevel,
		AbilitySystemComponent->MakeEffectContext()
	);

	BP_OnStoneConsumed();
}

void ASYStoneBase::OnPickUpCollisionSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ASYPlayerCharacter* OverlappedPlayerCharacter = Cast<ASYPlayerCharacter>(OtherActor))
	{
		OverlappedPlayerCharacter->GetSYAbilitySystemComponent()->TryActivateAbilityByTag(SYGameplayTags::Player_Ability_PickUp_Stones);
	}
}