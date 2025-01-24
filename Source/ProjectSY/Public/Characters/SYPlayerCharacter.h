// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SYBaseCharacter.h"
#include "GameplayTagContainer.h"
#include "SYPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USYDataAsset_InputConfig;
class USYPlayerCombatComponent;
class USYPlayerUIComponent;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class PROJECTSY_API ASYPlayerCharacter : public ASYBaseCharacter
{
	GENERATED_BODY()

public:
	ASYPlayerCharacter();

	virtual TObjectPtr<USYPawnCombatComponent> GetPawnCombatComponent() const override;

	virtual TObjectPtr<USYPawnUIComponent> GetPawnUIComponent() const override;

	virtual TObjectPtr<USYPlayerUIComponent> GetPlayerUIComponent() const override;
	
protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;

private:
#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	USYPlayerCombatComponent* PlayerCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USYPlayerUIComponent> PlayerUIComponent;
#pragma endregion

	

#pragma region Inputs
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USYDataAsset_InputConfig> InputConfigDataAsset;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);

	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag);
#pragma endregion

public:
	FORCEINLINE USYPlayerCombatComponent* GetPlayerCombatComponent() const {return PlayerCombatComponent;}
};
