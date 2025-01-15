// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/SYPawnCombatComponent.h"
#include "SYPlayerCombatComponent.generated.h"

class ASYPlayerWeapon;

/**
 * 
 */
UCLASS()
class PROJECTSY_API USYPlayerCombatComponent : public USYPawnCombatComponent
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable, Category = "SY|Combat")
	ASYPlayerWeapon* GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const;
};
