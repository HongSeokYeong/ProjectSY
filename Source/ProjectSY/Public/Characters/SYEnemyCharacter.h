// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SYBaseCharacter.h"
#include "SYEnemyCharacter.generated.h"

class USYEnemyCombatComponent;

/**
 * 
 */
UCLASS()
class PROJECTSY_API ASYEnemyCharacter : public ASYBaseCharacter
{
	GENERATED_BODY()
	
public:
	ASYEnemyCharacter();

protected:
	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<USYEnemyCombatComponent> EnemyCombatComponent;

private:
	void InitEnemyStartUpData();

public:
	FORCEINLINE TObjectPtr<USYEnemyCombatComponent> GetEnemyCombatComponent() const {return EnemyCombatComponent;}
};
