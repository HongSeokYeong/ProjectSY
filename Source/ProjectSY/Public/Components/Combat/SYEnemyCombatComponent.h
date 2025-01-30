// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/SYPawnCombatComponent.h"
#include "SYEnemyCombatComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSY_API USYEnemyCombatComponent : public USYPawnCombatComponent
{
	GENERATED_BODY()
	
public:
	virtual void OnHitTargetActor(AActor* HitActor) override;

protected:
	virtual void ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType);
};
