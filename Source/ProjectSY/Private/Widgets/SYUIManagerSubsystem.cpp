// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SYUIManagerSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Widgets/SYWidgetBase.h"

void USYUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &USYUIManagerSubsystem::OnPreLoadMap);
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

void USYUIManagerSubsystem::OnPreLoadMap(const FString& MapName)
{
	WidgetClear();
}

USYWidgetBase* USYUIManagerSubsystem::OpenWidget(FName WidgetName)
{
	if (TObjectPtr<USYWidgetBase>* FoundWidget = CreatedWidgets.Find(WidgetName))
	{
		(*FoundWidget)->SetVisibility(ESlateVisibility::Visible);

		return *FoundWidget;
	}

	if (TSubclassOf<USYWidgetBase>* WidgetClassPtr = WidgetClassMap.Find(WidgetName))
	{
		if (*WidgetClassPtr)
		{
			USYWidgetBase* WidgetInstance = CreateWidget<USYWidgetBase>(GetWorld(), *WidgetClassPtr);

			if (WidgetInstance)
			{
				WidgetInstance->AddToViewport();
				WidgetInstance->SetVisibility(ESlateVisibility::Visible);

				CreatedWidgets.Add(WidgetName, WidgetInstance);

				return WidgetInstance;
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] WidgetName is not valid"), *WidgetName.ToString());

		return nullptr;
	}

	return nullptr;
}

USYWidgetBase* USYUIManagerSubsystem::OpenWidgetByClass(TSubclassOf<USYWidgetBase> WidgetClass)
{
	if (!IsValid(WidgetClass))
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] WidgetClass is not valid"), *WidgetClass->GetFName().ToString());
		return nullptr;
	}

	UBlueprintGeneratedClass* BPClass = Cast<UBlueprintGeneratedClass>(WidgetClass);

	if (TObjectPtr<USYWidgetBase>* FoundWidget = CreatedWidgets.Find(FName(BPClass->ClassGeneratedBy->GetName())))
	{
		(*FoundWidget)->ShowWidget();
		return *FoundWidget;
	}
	else
	{
		USYWidgetBase* WidgetInstance = CreateWidget<USYWidgetBase>(GetWorld(), WidgetClass);

		if (WidgetInstance)
		{
			WidgetInstance->AddToViewport();
			WidgetInstance->ShowWidget();
			CreatedWidgets.Add(WidgetClass->ClassGeneratedBy->GetFName(), WidgetInstance);

			return WidgetInstance;
		}
	}

	return nullptr;
}

void USYUIManagerSubsystem::CloseWidget(FName WidgetName)
{
	if (TObjectPtr<USYWidgetBase>* WidgetInstancePtr = CreatedWidgets.Find(WidgetName))
	{
		(*WidgetInstancePtr)->HideWidget();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] Widget is not opened"), *WidgetName.ToString());
	}
}

USYWidgetBase* USYUIManagerSubsystem::GetWidget(FName WidgetName)
{
	if (TObjectPtr<USYWidgetBase>* FoundWidget = CreatedWidgets.Find(WidgetName))
	{
		(*FoundWidget)->SetVisibility(ESlateVisibility::Visible);
		return *FoundWidget;
	}
	else
	{
		return nullptr;
	}
}

USYWidgetBase* USYUIManagerSubsystem::GetWidgetByClass(TSubclassOf<USYWidgetBase> WidgetClass)
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
