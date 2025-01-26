// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/SYPawnCombatInterface.h"
#include "Interfaces/SYPawnUIInterface.h"
#include "SYBaseCharacter.generated.h"

class USYAbilitySystemComponent;
class USYAttributeSet;
class USYDataAsset_StartUpDataBase;
class UMotionWarpingComponent;

UCLASS()
class PROJECTSY_API ASYBaseCharacter : public ACharacter, public IAbilitySystemInterface, public ISYPawnCombatInterface, public ISYPawnUIInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASYBaseCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual TObjectPtr<USYPawnCombatComponent> GetPawnCombatComponent() const override;

	virtual TObjectPtr<USYPawnUIComponent> GetPawnUIComponent() const override;

	virtual TObjectPtr<USYEnemyUIComponent> GetEnemyUIComponent() const override;

protected:
	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	USYAbilitySystemComponent* SYAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	USYAttributeSet* SYAttributeSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MotionWarping")
	TObjectPtr<UMotionWarpingComponent> MotionWarpingComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<USYDataAsset_StartUpDataBase> CharacterStartUpData;

public:
	FORCEINLINE USYAbilitySystemComponent* GetSYAbilitySyhstemComponent() const { return SYAbilitySystemComponent; };

	FORCEINLINE USYAttributeSet* GetSYAttributeSet() const { return SYAttributeSet; };
};
