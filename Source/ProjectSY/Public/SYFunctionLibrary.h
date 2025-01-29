// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SYTypes/SYEnumTypes.h"
#include "SYFunctionLibrary.generated.h"

class USYAbilitySystemComponent;
class USYPawnCombatComponent;
struct FScalableFloat;

/**
 * 유틸 전역 함수 
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
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	static bool NativeDoesActorHaveTag(TObjectPtr<AActor> InActor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category = "SY|FunctionLibrary", meta = (DisplayName = "Does Actor Have tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, ESYConfirmType& OutConfirmType);

	static TObjectPtr<USYPawnCombatComponent> NativeGetPawnCombatComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "SY|FunctionLibrary", meta = (DisplayName = "GetPawnCombatComponentFromActor", ExpandEnumAsExecs = "OutValidType"))
	static USYPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* InActor, ESYValidType& OutValidType);

	UFUNCTION(BlueprintPure, Category = "SY|FunctionLibrary")
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);

	UFUNCTION(BlueprintPure, Category = "SY|FunctionLibrary", meta = (CompactNodeTitle = "Get Value At Level"))
	static float GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel = 1.0f);

	UFUNCTION(BlueprintPure, Category = "SY|FunctionLibrary")
	static FGameplayTag ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference);

	UFUNCTION(BlueprintPure, Category = "SY|FunctionLibrary")
	static bool IsValidBlock(AActor* InAttacker, AActor* InDefender);

	UFUNCTION(BlueprintCallable, Category = "SY|FunctionLibrary")
	static bool ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle);
};
