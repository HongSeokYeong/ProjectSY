// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UI/SYEnemyUIComponent.h"
#include "Widgets/SYWidgetBase.h"

void USYEnemyUIComponent::RegisterEnemyDrawnWidget(USYWidgetBase* InWidgetToRegister)
{
	EnemyDrawnWidgets.Add(InWidgetToRegister);
}

void USYEnemyUIComponent::RemoveEnemyDrawnWidgetsIfAny()
{
	if (EnemyDrawnWidgets.IsEmpty())
	{
		return;
	}

	for (USYWidgetBase* DrawnWidget : EnemyDrawnWidgets)
	{
		if (DrawnWidget)
		{
			DrawnWidget->RemoveFromParent();
		}
	}

	EnemyDrawnWidgets.Empty();
}
