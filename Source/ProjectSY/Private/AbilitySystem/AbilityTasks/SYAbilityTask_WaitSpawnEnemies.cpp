// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/SYAbilityTask_WaitSpawnEnemies.h"
#include "AbilitySystemComponent.h"
#include "Engine/AssetManager.h"
#include "NavigationSystem.h"
#include "Characters/SYEnemyCharacter.h"

USYAbilityTask_WaitSpawnEnemies* USYAbilityTask_WaitSpawnEnemies::WaitSpawnEnemies(UGameplayAbility* OwningAbility, FGameplayTag EventTag, TArray<TSoftClassPtr<ASYEnemyCharacter>> SoftEnemyClassToSpawnArray, int32 NumToSpawn, const FVector& SpawnOrigin, float RandomSpawnRadius)
{
    USYAbilityTask_WaitSpawnEnemies* Node = NewAbilityTask<USYAbilityTask_WaitSpawnEnemies>(OwningAbility);
    Node->CachedEventTag = EventTag;
    Node->CachedSoftEnemyClassToSpawnArray = SoftEnemyClassToSpawnArray;
    Node->CachedNumToSpawn = NumToSpawn;
    Node->CachedSpawnOrigin = SpawnOrigin;
    Node->CachedRandomSpawnRadius = RandomSpawnRadius;

    return Node;
}

void USYAbilityTask_WaitSpawnEnemies::Activate()
{
    Super::Activate();

    FGameplayEventMulticastDelegate& Delegate = AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedEventTag);

    DelegateHandle = Delegate.AddUObject(this, &USYAbilityTask_WaitSpawnEnemies::OnGameplayEventReceived);
}

void USYAbilityTask_WaitSpawnEnemies::OnDestroy(bool bInOwnerFinished)
{
    FGameplayEventMulticastDelegate& Delegate = AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedEventTag);
    
    Delegate.Remove(DelegateHandle);

    Super::OnDestroy(bInOwnerFinished);
}

void USYAbilityTask_WaitSpawnEnemies::OnGameplayEventReceived(const FGameplayEventData* InPayload)
{
    if (ensure(!CachedSoftEnemyClassToSpawnArray.IsEmpty()))
    {
        for (const TSoftClassPtr<ASYEnemyCharacter>& EnemyCharacter : CachedSoftEnemyClassToSpawnArray)
        {
            UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
                EnemyCharacter.ToSoftObjectPath(),
                FStreamableDelegate::CreateUObject(this, &USYAbilityTask_WaitSpawnEnemies::OnEnemyClassLoaded)
            );
        }
    }
    else
    {
        if (ShouldBroadcastAbilityTaskDelegates())
        {
            DidNotSpawn.Broadcast(TArray<ASYEnemyCharacter*>());
        }

        EndTask();
    }
}

void USYAbilityTask_WaitSpawnEnemies::OnEnemyClassLoaded()
{
    // UClass* LoadedClass = CachedSoftEnemyClassToSpawnArray.Get();
    UWorld* World = GetWorld();

    for (const TSoftClassPtr<ASYEnemyCharacter>& LoadedClass : CachedSoftEnemyClassToSpawnArray)
    {
        if (!LoadedClass.Get() || !World)
        {
            if (ShouldBroadcastAbilityTaskDelegates())
            {
                DidNotSpawn.Broadcast(TArray<ASYEnemyCharacter*>());
            }

            EndTask();
            return;
        }
    }

    TArray<ASYEnemyCharacter*> SpawnedEnemies;

    FActorSpawnParameters SpawnParam;
    SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    
    for (int32 i = 0; i < CachedNumToSpawn; i++)
    {
        FVector RandomLocation;
        UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this, CachedSpawnOrigin, RandomLocation, CachedRandomSpawnRadius);

        RandomLocation += FVector(0.0f, 0.0f, 150.0f);

        const FRotator SpawnFacingRotation = AbilitySystemComponent->GetAvatarActor()->GetActorForwardVector().ToOrientationRotator();

        for (const TSoftClassPtr<ASYEnemyCharacter>& LoadedClass : CachedSoftEnemyClassToSpawnArray)
        {
            ASYEnemyCharacter* SpawnedEnemy = World->SpawnActor<ASYEnemyCharacter>(LoadedClass.Get(), RandomLocation, SpawnFacingRotation, SpawnParam);

            if (SpawnedEnemy)
            {
                SpawnedEnemies.Add(SpawnedEnemy);
            }
        }
    }

    if (ShouldBroadcastAbilityTaskDelegates())
    {
        if (!SpawnedEnemies.IsEmpty())
        {
            OnSpawnFinished.Broadcast(SpawnedEnemies);
        }
        else
        {
            DidNotSpawn.Broadcast(TArray<ASYEnemyCharacter*>());
        }
    }

    EndTask();
}
