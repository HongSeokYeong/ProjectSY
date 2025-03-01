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

protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	USYPlayerCombatComponent* PlayerCombatComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USYDataAsset_InputConfig> InputConfigDataAsset;

	UPROPERTY()
	FVector2D SwitchDirection = FVector2D::ZeroVector;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);

	void Input_SwitchTargetTriggered(const FInputActionValue& InputActionValue);
	void Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue);

	void Input_PickUpStonesStarted(const FInputActionValue& InputActionValue);

	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag);

public:
	FORCEINLINE USYPlayerCombatComponent* GetPlayerCombatComponent() const {return PlayerCombatComponent;}

	UPROPERTY(BlueprintAssignable)
	FOnPercentChangedDelegate OnCurrentRageChanged;
};
