// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SYBaseCharacter.h"
#include "SYPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSY_API ASYPlayerCharacter : public ASYBaseCharacter
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

};
