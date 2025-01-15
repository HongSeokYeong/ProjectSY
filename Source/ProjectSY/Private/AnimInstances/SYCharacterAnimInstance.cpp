// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/SYCharacterAnimInstance.h"
#include "Characters/SYBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void USYCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<ASYBaseCharacter>(TryGetPawnOwner());

	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void USYCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();

	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.0f;
}
