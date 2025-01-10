// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SYPlayerCharacter.h"
#include "SYDebugHelper.h"

void ASYPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	Debug::Print(TEXT("Working"));
}
