// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SYPawnCombatInterface.generated.h"

class USYPawnCombatComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USYPawnCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTSY_API ISYPawnCombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual TObjectPtr<USYPawnCombatComponent> GetPawnCombatComponent() const = 0;
};
