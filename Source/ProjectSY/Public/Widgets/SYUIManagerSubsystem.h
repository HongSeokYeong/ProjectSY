// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "SYUIManagerSubsystem.generated.h"

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTSY_API USYUIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	virtual void OnPreLoadMap(const FString& MapName);

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	USYWidgetBase* OpenWidget(FName WidgetName);

	UFUNCTION(BlueprintCallable, Category = "UI")
	USYWidgetBase* OpenWidgetByClass(TSubclassOf<USYWidgetBase> WidgetClass);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void CloseWidget(FName WidgetName);

	UFUNCTION(BlueprintCallable, Category = "UI")
	USYWidgetBase* GetWidget(FName WidgetName);

	UFUNCTION(BlueprintCallable, Category = "UI")
	USYWidgetBase* GetWidgetByClass(TSubclassOf<USYWidgetBase> WidgetClass);

	void WidgetClear();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TMap<FName, TSubclassOf<USYWidgetBase>> WidgetClassMap;

	UPROPERTY()
	TMap<FName, TObjectPtr<USYWidgetBase>> CreatedWidgets;
};