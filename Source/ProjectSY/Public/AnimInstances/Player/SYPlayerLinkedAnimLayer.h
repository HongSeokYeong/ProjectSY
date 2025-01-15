// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/SYBaseAnimInstance.h"
#include "SYPlayerLinkedAnimLayer.generated.h"

class USYPlayerAnimInstance;

/**
 * 
 */
UCLASS()
class PROJECTSY_API USYPlayerLinkedAnimLayer : public USYBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	USYPlayerAnimInstance* GetPlayerAnimInstance() const;
};
