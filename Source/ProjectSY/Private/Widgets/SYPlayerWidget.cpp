// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SYPlayerWidget.h"
#include "Interfaces/SYPawnUIInterface.h"

void USYPlayerWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ASYBaseCharacter* Character = Cast<ASYBaseCharacter>(GetOwningPlayerPawn()))
	{
		BP_OnOwningPlayerInitialized(Character, this);

	}
}