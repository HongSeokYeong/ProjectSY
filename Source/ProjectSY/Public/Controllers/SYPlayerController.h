// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "SYPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSY_API ASYPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	ASYPlayerController();

	virtual FGenericTeamId GetGenericTeamId() const override;

private:
	FGenericTeamId PlayerTeamID;
	
};
