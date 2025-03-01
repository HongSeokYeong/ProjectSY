// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SYEnemyWidget.h"
#include "Interfaces/SYPawnUIInterface.h"
#include "Characters/SYBaseCharacter.h"

void USYEnemyWidget::InitEnemyCreatedWidget(AActor* OwningEnemyActor)
{
	if (ASYBaseCharacter* Character = Cast<ASYBaseCharacter>(OwningEnemyActor))
	{
		BP_OnOwningEnemyInitialized(Character);
	}
	
	/*if (ISYPawnUIInterface* PawnUIInterface = Cast<ISYPawnUIInterface>(OwningEnemyActor))
	{
		USYEnemyUIComponent* EnemyUIComponent = PawnUIInterface->GetEnemyUIComponent();

		checkf(EnemyUIComponent, TEXT("Failed to extrac an EnemyUIComponent from %s"), *OwningEnemyActor->GetActorNameOrLabel());

		BP_OnOwningEnemyInitialized(EnemyUIComponent);
	}*/
}