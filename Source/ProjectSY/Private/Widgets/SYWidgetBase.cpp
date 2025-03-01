// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SYWidgetBase.h"

void USYWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();
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
