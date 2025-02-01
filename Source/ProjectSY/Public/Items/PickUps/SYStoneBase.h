// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/PickUps/SYPickUpBase.h"
#include "AbilitySystem/SYAbilitySystemComponent.h"
#include "SYStoneBase.generated.h"

class UGameplayEffect;

/**
 *
 */
UCLASS()
class PROJECTSY_API ASYStoneBase : public ASYPickUpBase
{
	GENERATED_BODY()

public:
	void Consume(USYAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel);

protected:
	virtual void OnPickUpCollisionSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Stone Consumed"))
	void BP_OnStoneConsumed();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> StoneGameplayEffectClass;
};
