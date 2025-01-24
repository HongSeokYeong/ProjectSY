// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SYPawnUIInterface.generated.h"

class USYPawnUIComponent;
class USYPlayerUIComponent;
class USYEnemyUIComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USYPawnUIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTSY_API ISYPawnUIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual TObjectPtr<USYPawnUIComponent> GetPawnUIComponent() const = 0;

	virtual TObjectPtr<USYPlayerUIComponent> GetPlayerUIComponent() const;

	virtual TObjectPtr<USYEnemyUIComponent> GetEnemyUIComponent() const;
};
