// Fill out your copyright notice in the Description page of Project Settings.


#include "SYFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/SYAbilitySystemComponent.h"
#include "Interfaces/SYPawnCombatInterface.h"
#include "GenericTeamAgentInterface.h"
#include "Kismet/KismetMathLibrary.h"	
#include "SYGameplayTags.h"
#include "SYTypes/SYCountDownAction.h"
#include "SYGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/SYSaveGame.h"

TObjectPtr<USYAbilitySystemComponent> USYFunctionLibrary::NativeGetSYASCFromActor(TObjectPtr<AActor> InActor)
{
	check(InActor);

	return CastChecked<USYAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void USYFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	USYAbilitySystemComponent* ASC = NativeGetSYASCFromActor(InActor);

	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void USYFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	USYAbilitySystemComponent* ASC = NativeGetSYASCFromActor(InActor);

	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

bool USYFunctionLibrary::NativeDoesActorHaveTag(TObjectPtr<AActor> InActor, FGameplayTag TagToCheck)
{
	USYAbilitySystemComponent* ASC = NativeGetSYASCFromActor(InActor);

	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void USYFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, ESYConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? ESYConfirmType::Yes : ESYConfirmType::No;
}

TObjectPtr<USYPawnCombatComponent> USYFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);

	if (ISYPawnCombatInterface* PawnCombatInterface = Cast<ISYPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}
	return nullptr;
}

USYPawnCombatComponent* USYFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor, ESYValidType& OutValidType)
{
	USYPawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);

	OutValidType = CombatComponent ? ESYValidType::Valid : ESYValidType::InValid;

	return CombatComponent;
}

bool USYFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);

	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}

	return false;
}

float USYFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel)
{
	return InScalableFloat.GetValueAtLevel(InLevel);
}

FGameplayTag USYFunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference)
{
	check(InAttacker && InVictim);

	const FVector VictimForward = InVictim->GetActorForwardVector();
	const FVector VictimToAttackerNormalized = (InAttacker->GetActorLocation() - InVictim->GetActorLocation()).GetSafeNormal();

	const float FotResult = FVector::DotProduct(VictimForward, VictimToAttackerNormalized);

	OutAngleDifference = UKismetMathLibrary::DegAcos(FotResult);

	const FVector CrossResult = FVector::CrossProduct(VictimForward, VictimToAttackerNormalized);

	if (CrossResult.Z < 0.0f)
	{
		OutAngleDifference *= -1.0f;
	}

	if (OutAngleDifference >= -45.0f && OutAngleDifference <= 45.0f)
	{
		return FGameplayTag::RequestGameplayTag(FName("Shared.Status.HitReact.Front"));
	}
	else if (OutAngleDifference < -45.0f && OutAngleDifference >= -135.0f)
	{
		return FGameplayTag::RequestGameplayTag(FName("Shared.Status.HitReact.Left"));
	}
	else if (OutAngleDifference < -135.0f || OutAngleDifference > 135.0f)
	{
		return FGameplayTag::RequestGameplayTag(FName("Shared.Status.HitReact.Back"));
	}
	else if (OutAngleDifference > 45.0f && OutAngleDifference <= 135.0f)
	{
		return FGameplayTag::RequestGameplayTag(FName("Shared.Status.HitReact.Right"));
	}

	return FGameplayTag::RequestGameplayTag(FName("Shared.Status.HitReact.Front"));
}

bool USYFunctionLibrary::IsValidBlock(AActor* InAttacker, AActor* InDefender)
{
	check(InAttacker && InDefender);

	const float DotResult = FVector::DotProduct(InAttacker->GetActorForwardVector(), InDefender->GetActorForwardVector());

	return DotResult < 0.1f;
}

bool USYFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
	USYAbilitySystemComponent* SourceASC = NativeGetSYASCFromActor(InInstigator);
	USYAbilitySystemComponent* TargetASC = NativeGetSYASCFromActor(InTargetActor);

	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = SourceASC->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);

	return ActiveGameplayEffectHandle.WasSuccessfullyApplied();
}

void USYFunctionLibrary::CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval, float& OutRemainingTime, ESYCountDownActionInput CountDownInput, UPARAM(DisplayName = "Output")ESYCountDownActionOutput& CountDownOutput, FLatentActionInfo LatentInfo)
{
	UWorld* World = nullptr;

	if (GEngine)
	{
		World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	}

	if (!World)
	{
		return;
	}

	FLatentActionManager& LatentActionManager = World->GetLatentActionManager();

	FSYCountDownAction* FoundAction = LatentActionManager.FindExistingAction<FSYCountDownAction>(LatentInfo.CallbackTarget, LatentInfo.UUID);

	if (CountDownInput == ESYCountDownActionInput::Start)
	{
		if (!FoundAction)
		{
			LatentActionManager.AddNewAction(
				LatentInfo.CallbackTarget,
				LatentInfo.UUID,
				new FSYCountDownAction(TotalTime, UpdateInterval, OutRemainingTime, CountDownOutput, LatentInfo)
			);
		}
	}

	if (CountDownInput == ESYCountDownActionInput::Cancel)
	{
		if (FoundAction)
		{
			FoundAction->CancelAction();
		}
	}
}

USYGameInstance* USYFunctionLibrary::GetSYGameInstance(const UObject* WorldContextObject)
{
	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			return World->GetGameInstance<USYGameInstance>();
		}
	}

	return nullptr;
}

void USYFunctionLibrary::ToggleInputMode(const UObject* WorldContextObject, ESYInputMode InInputMode)
{
	APlayerController* PlayerController = nullptr;

	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			PlayerController = World->GetFirstPlayerController();
		}
	}

	if (!PlayerController)
	{
		return;
	}

	FInputModeGameOnly GameOnlyMode;

	FInputModeUIOnly UIOnlyMode;
	switch (InInputMode)
	{
	case ESYInputMode::GameOnly:
		PlayerController->SetInputMode(GameOnlyMode);
		PlayerController->bShowMouseCursor = false;
		break;
	case ESYInputMode::UIOnly:
		PlayerController->SetInputMode(UIOnlyMode);
		PlayerController->bShowMouseCursor = true;
		break;
	default:
		break;
	}
}

void USYFunctionLibrary::SaveCurrentGameDifficulty(ESYGameDifficulty InDifficultyToSave)
{
	USaveGame* SaveGameObject = UGameplayStatics::CreateSaveGameObject(USYSaveGame::StaticClass());

	if (USYSaveGame* SYSaveGameObject = Cast<USYSaveGame>(SaveGameObject))
	{
		SYSaveGameObject->SavedCurrentGameDifficulty = InDifficultyToSave;

		const bool bWasSaved = UGameplayStatics::SaveGameToSlot(SYSaveGameObject, FGameplayTag::RequestGameplayTag(FName("GameData.SaveGame.Slot.1")).ToString(), 0);
	}
}

bool USYFunctionLibrary::TryLoadSavedGameDifficulty(ESYGameDifficulty& OutSavedDifficulty)
{
	if (UGameplayStatics::DoesSaveGameExist(FGameplayTag::RequestGameplayTag(FName("GameData.SaveGame.Slot.1")).ToString(), 0))
	{
		USaveGame* SaveGameObject = UGameplayStatics::LoadGameFromSlot(FGameplayTag::RequestGameplayTag(FName("GameData.SaveGame.Slot.1")).ToString(), 0);

		if (USYSaveGame* SYSaveGameObject = Cast<USYSaveGame>(SaveGameObject))
		{
			OutSavedDifficulty = SYSaveGameObject->SavedCurrentGameDifficulty;

			return true;
		}
	}

	return false;
}
