// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/SYBaseAnimInstance.h"
#include "SYFunctionLibrary.h"

bool USYBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return USYFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
	}

	return false;
}
