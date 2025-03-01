// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Widgets/SYUIManagerSubsystem.h"
#include "AbilitySystem/SYAbilitySystemComponent.h"
#include "SYAttributeSet.generated.h"

class ISYPawnUIInterface;

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 *
 */
UCLASS()
class PROJECTSY_API USYAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	USYAttributeSet();

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(USYAttributeSet, CurrentHealth)

	UPROPERTY(BlueprintReadOnly, Category = "MaxHealth")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(USYAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "CurrentRage")
	FGameplayAttributeData CurrentRage;
	ATTRIBUTE_ACCESSORS(USYAttributeSet, CurrentRage)

	UPROPERTY(BlueprintReadOnly, Category = "MaxRage")
	FGameplayAttributeData MaxRage;
	ATTRIBUTE_ACCESSORS(USYAttributeSet, MaxRage)

	UPROPERTY(BlueprintReadOnly, Category = "AttackPower")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(USYAttributeSet, AttackPower)

	UPROPERTY(BlueprintReadOnly, Category = "DefensePower")
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(USYAttributeSet, DefensePower)

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(USYAttributeSet, DamageTaken);

private:
	TWeakInterfacePtr<ISYPawnUIInterface> CachedPawnUIInterface;
	TWeakObjectPtr<USYUIManagerSubsystem> CachedUIManager;
};
