// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SYTypes/SYEnumTypes.h"
#include "SYSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSY_API USYSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	ESYGameDifficulty SavedCurrentGameDifficulty;
};
