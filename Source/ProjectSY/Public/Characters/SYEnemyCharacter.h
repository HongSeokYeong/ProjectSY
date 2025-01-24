// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SYBaseCharacter.h"
#include "SYEnemyCharacter.generated.h"

class USYEnemyCombatComponent;
class USYEnemyUIComponent;
class UWidgetComponent;

/**
 * 
 */
UCLASS()
class PROJECTSY_API ASYEnemyCharacter : public ASYBaseCharacter
{
	GENERATED_BODY()
	
public:
	ASYEnemyCharacter();

	virtual TObjectPtr<USYPawnCombatComponent> GetPawnCombatComponent() const override;

	virtual TObjectPtr<USYPawnUIComponent> GetPawnUIComponent() const override;

	virtual TObjectPtr<USYEnemyUIComponent> GetEnemyUIComponent	() const override;

protected:
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<USYEnemyCombatComponent> EnemyCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<USYEnemyUIComponent> EnemyUIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UWidgetComponent> EnemyHealthWidgetComponent;

private:
	void InitEnemyStartUpData();

public:
	FORCEINLINE TObjectPtr<USYEnemyCombatComponent> GetEnemyCombatComponent() const {return EnemyCombatComponent;}
};
