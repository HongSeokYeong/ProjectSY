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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsOverlapActorReset = false;

	UFUNCTION(BlueprintCallable, Category = "SY|Combat")
	ASYPlayerWeapon* GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const;

	UFUNCTION(BlueprintCallable, Category = "SY|Combat")
	ASYPlayerWeapon* GetPlayerCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "SY|Combat")
	float GetPlayerCurrentEquipWeaponDamageAtLevel(float InLevel) const;

	virtual void OnHitTargetActor(AActor* HitActor) override;
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor) override;
};
