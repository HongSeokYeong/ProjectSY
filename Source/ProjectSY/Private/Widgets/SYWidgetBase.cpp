// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SYWidgetBase.h"
#include "Interfaces/SYPawnUIInterface.h"
#include "AbilitySystemInterface.h"


void USYWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	// 이 코드 playerwidget같은걸로 만들어서 빼야한다.
	if (ISYPawnUIInterface* PawnUIInterface = Cast<ISYPawnUIInterface>(GetOwningPlayerPawn()))
	{
		if (USYPlayerUIComponent* PlayerUIComponent = PawnUIInterface->GetPlayerUIComponent())
		{
			BP_OnOwningPlayerUIComponentInitialized(PlayerUIComponent);
		}
	}
}

void USYWidgetBase::ShowWidget()
{
	BP_ShowWidget();
	SetVisibility(ESlateVisibility::Visible);
}

void USYWidgetBase::HideWidget()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

// 이 코드 enemywidget같은걸로 만들어서 빼야한다.
void USYWidgetBase::InitEnemyCreatedWidget(AActor* OwningEnemyActor)
{
	if (ISYPawnUIInterface* PawnUIInterface = Cast<ISYPawnUIInterface>(OwningEnemyActor))
	{
		USYEnemyUIComponent* EnemyUIComponent = PawnUIInterface->GetEnemyUIComponent();

		checkf(EnemyUIComponent, TEXT("Failed to extrac an EnemyUIComponent from %s"), *OwningEnemyActor->GetActorNameOrLabel());

		BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
	}
}
