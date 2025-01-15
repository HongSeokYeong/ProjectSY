// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SYFunctionLibrary.generated.h"

class USYAbilitySystemComponent;

UENUM()
enum class ESYConfirmType : uint8
{
	Yes,
	No
};

/**
 *
 */
UCLASS()
class PROJECTSY_API USYFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	static TObjectPtr<USYAbilitySystemComponent> NativeGetSYASCFromActor(TObjectPtr<AActor> InActor);

	UFUNCTION(BlueprintCallable, Category = "SY|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "SY|FunctionLibrary")
	static void RemoveGameplayFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	static bool NativeDoesActorHaveTag(TObjectPtr<AActor> InActor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category = "SY|FunctionLibrary", meta = (DisplayName = "Does Actor Have tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, ESYConfirmType& OutConfirmType);
};
