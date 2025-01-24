// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/SYPlayerController.h"

ASYPlayerController::ASYPlayerController()
{
	PlayerTeamID = FGenericTeamId(0);
}

FGenericTeamId ASYPlayerController::GetGenericTeamId() const
{
	return PlayerTeamID;
}
