// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SYPawnExtensionComponentBase.h"
#include "GameplayTagContainer.h"
#include "SYPawnCombatComponent.generated.h"

class ASYWeaponBase;

UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	CurrentEquippedWeapon,
	LeftHand,
	RightHand
};

/**
 *
 */
UCLASS()
class PROJECTSY_API USYPawnCombatComponent : public USYPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "SY|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, ASYWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false);

	UFUNCTION(BlueprintCallable, Category = "SY|Combat")
	ASYWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SY|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	UFUNCTION(BlueprintCallable, Category = "SY|Combat")
	ASYWeaponBase* GetCharacterCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "SY|Combat")
	void ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);

	virtual void OnHitTargetActor(AActor* HitActor);
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor);

protected:
	TArray<AActor*> OverlappedActors;

private:
	TMap<FGameplayTag, TObjectPtr<ASYWeaponBase>> CharacterCarriedWeaponMap;
};
