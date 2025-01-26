// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SYBaseCharacter.h"
#include "AbilitySystem/SYAbilitySystemComponent.h"
#include "AbilitySystem/SYAttributeSet.h"
#include "MotionWarpingComponent.h"

// Sets default values
ASYBaseCharacter::ASYBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	SYAbilitySystemComponent = CreateDefaultSubobject<USYAbilitySystemComponent>(TEXT("SYAbilitySystemComponent"));\

	SYAttributeSet = CreateDefaultSubobject<USYAttributeSet>(TEXT("SYAttributeSet"));

	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
}

UAbilitySystemComponent* ASYBaseCharacter::GetAbilitySystemComponent() const
{
	return SYAbilitySystemComponent;
}

TObjectPtr<USYPawnCombatComponent> ASYBaseCharacter::GetPawnCombatComponent() const
{
	return TObjectPtr<USYPawnCombatComponent>();
}

TObjectPtr<USYPawnUIComponent> ASYBaseCharacter::GetPawnUIComponent() const
{
	return TObjectPtr<USYPawnUIComponent>();
}

TObjectPtr<USYEnemyUIComponent> ASYBaseCharacter::GetEnemyUIComponent() const
{
	return TObjectPtr<USYEnemyUIComponent>();
}

void ASYBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (SYAbilitySystemComponent)
	{
		SYAbilitySystemComponent->InitAbilityActorInfo(this, this);

		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());
	}
}
