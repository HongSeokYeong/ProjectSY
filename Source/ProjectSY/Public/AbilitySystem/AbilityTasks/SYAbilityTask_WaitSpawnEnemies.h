// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "SYAbilityTask_WaitSpawnEnemies.generated.h"

class ASYEnemyCharacter;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitSpawnEnemiesDelegate, const TArray<ASYEnemyCharacter*>&, SpawnedEnemies);

/**
 *
 */
UCLASS()
class PROJECTSY_API USYAbilityTask_WaitSpawnEnemies : public UAbilityTask
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "SY|AbilityTasks", meta = (DisplayName = "Wait Gameplay Event And Spawn Enemies", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true", NumToSpawn = "1", RandomSpawnRadius = "200"))
	static USYAbilityTask_WaitSpawnEnemies* WaitSpawnEnemies(UGameplayAbility* OwningAbility, FGameplayTag EventTag, TArray<TSoftClassPtr< ASYEnemyCharacter>> SoftEnemyClassToSpawnArray, int32 NumToSpawn, const FVector& SpawnOrigin, float RandomSpawnRadius);

	UPROPERTY(BlueprintAssignable)
	FWaitSpawnEnemiesDelegate OnSpawnFinished;

	UPROPERTY(BlueprintAssignable)
	FWaitSpawnEnemiesDelegate DidNotSpawn;

	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

private:
	FGameplayTag CachedEventTag;
	TArray<TSoftClassPtr<ASYEnemyCharacter>> CachedSoftEnemyClassToSpawnArray;
	int32 CachedNumToSpawn;
	FVector CachedSpawnOrigin;
	float CachedRandomSpawnRadius;
	FDelegateHandle DelegateHandle;

	void OnGameplayEventReceived(const FGameplayEventData* InPayload);
	void OnEnemyClassLoaded();
};
