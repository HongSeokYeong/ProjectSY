// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameplayTagContainer.h"
#include "Widgets/SYUIManagerSubsystem.h"

#include "SYGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FSYGameLevelSet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta = (Categories = "GameData.Level"))
	FGameplayTag LevelTag;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> Level;

	bool IsValid() const
	{
		return LevelTag.IsValid() && !Level.IsNull();
	}
};

/**
 *
 */
UCLASS()
class PROJECTSY_API USYGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	void Init() override;

protected	:
	virtual void OnPreLoadMap(const FString& MapName);
	virtual void OnDestinationWorldLoaded(UWorld* LoadedWorld );

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FSYGameLevelSet> GameLevelSets;

public:
	UFUNCTION(BlueprintPure, meta = (GameplayTagFilter = "GameData.Level"))
	TSoftObjectPtr<UWorld> GetGameLevelByTag(FGameplayTag InTag) const;

	UFUNCTION(BlueprintCallable, Category = "SubSystem")
	USYUIManagerSubsystem* GetUIManagerSubsystem();
};
