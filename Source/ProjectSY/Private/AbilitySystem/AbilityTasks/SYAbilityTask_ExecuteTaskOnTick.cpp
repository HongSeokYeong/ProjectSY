// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/SYAbilityTask_ExecuteTaskOnTick.h"

USYAbilityTask_ExecuteTaskOnTick::USYAbilityTask_ExecuteTaskOnTick()
{
	bTickingTask = true;
}

USYAbilityTask_ExecuteTaskOnTick* USYAbilityTask_ExecuteTaskOnTick::ExecuteTaskOnTick(UGameplayAbility* OwningAbility)
{
	USYAbilityTask_ExecuteTaskOnTick* Node = NewAbilityTask<USYAbilityTask_ExecuteTaskOnTick>(OwningAbility);

	return Node;
}

void USYAbilityTask_ExecuteTaskOnTick::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnAbilityTaskTick.Broadcast(DeltaTime);
	}
	else
	{
		EndTask();
	}
}
