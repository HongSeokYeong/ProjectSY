// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SYUIManagerSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void USYUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void USYUIManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

bool USYUIManagerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (this->GetClass()->IsInBlueprint() && Super::ShouldCreateSubsystem(Outer))
	{
		return true;
	}

	return false;
}

void USYUIManagerSubsystem::OpenWidget(FName WidgetName)
{
	if (TObjectPtr<UUserWidget>* FoundWidget = CreatedWidgets.Find(WidgetName))
	{
		(*FoundWidget)->SetVisibility(ESlateVisibility::Visible);
		return;
	}

	if (TSubclassOf<UUserWidget>* WidgetClassPtr = WidgetClassMap.Find(WidgetName))
	{
		if (*WidgetClassPtr)
		{
			UUserWidget* WidgetInstance = CreateWidget<UUserWidget>(GetGameInstance()->GetWorld(), *WidgetClassPtr);

			if (WidgetInstance)
			{
				WidgetInstance->AddToViewport();
				WidgetInstance->SetVisibility(ESlateVisibility::Visible);
				CreatedWidgets.Add(WidgetName, WidgetInstance);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] WidgetName is not valid"), *WidgetName.ToString());
	}
}

void USYUIManagerSubsystem::OpenWidgetByClass(TSubclassOf<UUserWidget> WidgetClass)
{
	if (!IsValid(WidgetClass))
	{
		return;
	}

	// 생성되어있는 위젯이 있으면 찾아서 활성화
	if (TObjectPtr<UUserWidget>* FoundWidget = CreatedWidgets.Find(WidgetClass->GetFName()))
	{
		(*FoundWidget)->SetVisibility(ESlateVisibility::Visible);
		return;
	}
	else // 없으면 위젯 생성해서 캐싱하고 활성화
	{
		UUserWidget* WidgetInstance = CreateWidget<UUserWidget>(GetGameInstance()->GetWorld(), WidgetClass);

		if (WidgetInstance)
		{
			WidgetInstance->AddToViewport();
			WidgetInstance->SetVisibility(ESlateVisibility::Visible);
			CreatedWidgets.Add(WidgetClass->ClassGeneratedBy->GetFName(), WidgetInstance);
		}
	}
}

void USYUIManagerSubsystem::CloseWidget(FName WidgetName)
{
	if (TObjectPtr<UUserWidget>* WidgetInstancePtr = CreatedWidgets.Find(WidgetName))
	{
		(*WidgetInstancePtr)->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] Widget is not opened"), *WidgetName.ToString());
	}
}

UUserWidget* USYUIManagerSubsystem::GetWidget(FName WidgetName)
{
	if (TObjectPtr<UUserWidget>* FoundWidget = CreatedWidgets.Find(WidgetName))
	{
		(*FoundWidget)->SetVisibility(ESlateVisibility::Visible);
		return *FoundWidget;
	}
	else
	{
		return nullptr;
	}
}

UUserWidget* USYUIManagerSubsystem::GetWidgetByClass(TSubclassOf<UUserWidget> WidgetClass)
{
	if (!IsValid(WidgetClass))
	{
		return nullptr;
	}

	return GetWidget(WidgetClass->GetFName());
}

void USYUIManagerSubsystem::WidgetClear()
{
	CreatedWidgets.Empty();
}
