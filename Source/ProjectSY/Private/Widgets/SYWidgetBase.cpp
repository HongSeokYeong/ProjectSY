// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SYWidgetBase.h"
#include "Interfaces/SYPawnUIInterface.h"

void USYWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ISYPawnUIInterface* PawnUIInterface = Cast<ISYPawnUIInterface>(GetOwningPlayerPawn()))
	{
		if (USYPlayerUIComponent* PlayerUIComponent = PawnUIInterface->GetPlayerUIComponent())
		{
			BP_OnOwningPlayerUIComponentInitialized(PlayerUIComponent);
		}
	}
}

void USYWidgetBase::InitEnemyCreatedWidget(AActor* OwningEnemyActor)
{
	if (ISYPawnUIInterface* PawnUIInterface = Cast<ISYPawnUIInterface>(OwningEnemyActor))
	{
		USYEnemyUIComponent* EnemyUIComponent = PawnUIInterface->GetEnemyUIComponent();

		checkf(EnemyUIComponent, TEXT("Failed to extrac an EnemyUIComponent from %s"), *OwningEnemyActor->GetActorNameOrLabel());

		BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
	}
}
