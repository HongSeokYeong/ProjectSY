// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SYDataAsset_StartUpDataBase.generated.h"

class USYGameplayAbility;
class USYAbilitySystemComponent;
/**
 *
 */
UCLASS()
class PROJECTSY_API USYDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(TObjectPtr<USYAbilitySystemComponent> InASCToGive, int32 ApplyLevel = 1);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<USYGameplayAbility>> ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<USYGameplayAbility>> ReactiveAbilities;

	void GrantAbilities(const TArray<TSubclassOf<USYGameplayAbility>>& InAbilitiesToGive, TObjectPtr<USYAbilitySystemComponent> InASCToGive, int32 ApplyLevel = 1);
};
