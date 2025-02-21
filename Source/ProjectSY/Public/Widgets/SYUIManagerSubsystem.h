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
	 
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void OpenWidget(FName WidgetName);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void OpenWidgetByClass(TSubclassOf<UUserWidget> WidgetClass);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void CloseWidget(FName WidgetName);

	UFUNCTION(BlueprintCallable, Category = "UI")
	UUserWidget* GetWidget(FName WidgetName);

	UFUNCTION(BlueprintCallable, Category = "UI")
	UUserWidget* GetWidgetByClass(TSubclassOf<UUserWidget> WidgetClass);

	void WidgetClear();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TMap<FName, TSubclassOf<UUserWidget>> WidgetClassMap;

private:
	UPROPERTY()
	TMap<FName, TObjectPtr<UUserWidget>> CreatedWidgets;
};
