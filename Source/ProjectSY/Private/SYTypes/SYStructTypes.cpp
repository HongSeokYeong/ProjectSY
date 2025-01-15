// Fill out your copyright notice in the Description page of Project Settings.


#include "SYTypes/SYStructTypes.h"
#include "AbilitySystem/Abilities/SYPlayerGameplayAbility.h"

bool FSYPlayerAbilitySet::IsValid() const
{

	return InputTag.IsValid() && AbilityToGrant;
}
