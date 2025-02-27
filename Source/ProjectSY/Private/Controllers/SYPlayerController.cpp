// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/SYPlayerController.h"
#include "Widgets/SYUIManagerSubsystem.h"
#include "AbilitySystem/SYAbilitySystemComponent.h"
#include "AbilitySystem/SYAttributeSet.h"
#include "Components/UI/SYPawnUIComponent.h"
#include "Components/UI/SYPlayerUIComponent.h"

ASYPlayerController::ASYPlayerController()
{
	PlayerTeamID = FGenericTeamId(0);
}

FGenericTeamId ASYPlayerController::GetGenericTeamId() const
{
	return PlayerTeamID;
}

void ASYPlayerController::OnPossess(APawn* aPawn)
{
	GetGameInstance()->GetSubsystem<USYUIManagerSubsystem>()->OpenWidget(FName("WBP_PlayerOverlay"));
	Super::OnPossess(aPawn);
}
