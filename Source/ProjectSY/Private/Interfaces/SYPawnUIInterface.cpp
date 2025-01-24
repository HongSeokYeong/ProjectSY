// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/SYPawnUIInterface.h"

// Add default functionality here for any ISYPawnUIInterface functions that are not pure virtual.

TObjectPtr<USYPlayerUIComponent> ISYPawnUIInterface::GetPlayerUIComponent() const
{
	return TObjectPtr<USYPlayerUIComponent>();
}

TObjectPtr<USYEnemyUIComponent> ISYPawnUIInterface::GetEnemyUIComponent() const
{
	return nullptr;
}
