// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SYTypes/SYEnumTypes.h"
#include "SYBaseGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSY_API ASYBaseGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASYBaseGameMode();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Settings")
	ESYGameDifficulty CurrentGameDifficulty;

public:
	FORCEINLINE ESYGameDifficulty GetCurrentGameDifficulty() const {return CurrentGameDifficulty;}
};
