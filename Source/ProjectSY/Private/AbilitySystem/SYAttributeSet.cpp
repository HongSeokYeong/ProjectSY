// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SYAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "SYFunctionLibrary.h"
#include "SYGameplayTags.h"
#include "Interfaces/SYPawnUIInterface.h"
#include "Components/UI/SYPawnUIComponent.h"
#include "Components/UI/SYPlayerUIComponent.h"

#include "SYDebugHelper.h"

USYAttributeSet::USYAttributeSet()
{
	InitCurrentHealth(1.0f);
	InitMaxHealth(1.0f);
	InitCurrentRage(1.0f);
	InitMaxRage(1.0f);
	InitAttackPower(1.0f);
	InitDefensePower(1.0f);
}

void USYAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<ISYPawnUIInterface>(Data.Target.GetAvatarActor());
	}

	checkf(CachedPawnUIInterface.IsValid(), TEXT("%s didn't implement IPawnUIInterface"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	USYPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();

	checkf(PawnUIComponent, TEXT("Couldn't extrac a PawnUIComponent from %s"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.0f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);

		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
	}

	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float NewCurrentRage = FMath::Clamp(GetCurrentRage(), 0.0f, GetMaxRage());

		SetCurrentRage(NewCurrentRage);

		if (GetCurrentRage() == GetMaxRage())
		{
			USYFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), SYGameplayTags::Player_Status_Rage_Full);
		}
		else if(GetCurrentRage() == 0.0f)
		{ 
			USYFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), SYGameplayTags::Player_Status_Rage_None);
		}
		else
		{
			USYFunctionLibrary::RemoveGameplayTagFromActorIfFound(Data.Target.GetAvatarActor(), SYGameplayTags::Player_Status_Rage_Full);
			USYFunctionLibrary::RemoveGameplayTagFromActorIfFound(Data.Target.GetAvatarActor(), SYGameplayTags::Player_Status_Rage_None);
		}

		if (USYPlayerUIComponent* PlayerUIComponent = CachedPawnUIInterface->GetPlayerUIComponent())
		{
			PlayerUIComponent->OnCurrentRageChanged.Broadcast(GetCurrentRage() / GetMaxRage());
		}
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float DamageDone = GetDamageTaken();

		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.0f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);

		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());

		if (GetCurrentHealth() == 0.0f)
		{
			USYFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), SYGameplayTags::Shared_Status_Dead);
		}
	}
}
