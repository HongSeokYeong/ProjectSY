// Fill out your copyright notice in the Description page of Project Settings.


#include "SYGameInstance.h"
#include "MoviePlayer.h"

void USYGameInstance::Init()
{
	Super::Init();

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &USYGameInstance::OnPreLoadMap);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &USYGameInstance::OnDestinationWorldLoaded);
}

void USYGameInstance::OnPreLoadMap(const FString& MapName)
{
	GetSubsystem<USYUIManagerSubsystem>()->WidgetClear();
	FLoadingScreenAttributes LoadingScreenAttributes;
	LoadingScreenAttributes.bAutoCompleteWhenLoadingCompletes = true;
	LoadingScreenAttributes.MinimumLoadingScreenDisplayTime = 2.0f;
	LoadingScreenAttributes.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();

	GetMoviePlayer()->SetupLoadingScreen(LoadingScreenAttributes);
}

void USYGameInstance::OnDestinationWorldLoaded(UWorld* LoadedWorld)
{
	GetMoviePlayer()->StopMovie();
}

TSoftObjectPtr<UWorld> USYGameInstance::GetGameLevelByTag(FGameplayTag InTag) const
{
	for (const FSYGameLevelSet& GameLevelSet : GameLevelSets)
	{
		if (!GameLevelSet.IsValid())
		{
			continue;
		}

		if (GameLevelSet.LevelTag == InTag)
		{
			return GameLevelSet.Level;
		}
	}

	return TSoftObjectPtr<UWorld>();
}

USYUIManagerSubsystem* USYGameInstance::GetUIManagerSubsystem()
{
	return GetSubsystem<USYUIManagerSubsystem>();
}
