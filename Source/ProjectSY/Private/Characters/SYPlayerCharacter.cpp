// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SYPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/Input/SYDataAsset_InputConfig.h"
#include "Components/Input/SYPlayerInputComponent.h"
#include "SYGameplayTags.h"
#include "AbilitySystem/SYAbilitySystemComponent.h"
#include "DataAssets/StartUpData/SYDataAsset_PlayerStartUpData.h"
#include "Components/Combat/SYPlayerCombatComponent.h"
#include "Components/UI/SYPlayerUIComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

#include "SYDebugHelper.h"

ASYPlayerCharacter::ASYPlayerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 55.0f, 65.0f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

	PlayerCombatComponent = CreateDefaultSubobject<USYPlayerCombatComponent>(TEXT("SYPlayerCombatComponent"));

	PlayerUIComponent = CreateDefaultSubobject<USYPlayerUIComponent>(TEXT("SYPlayerUIComponent"));
}

TObjectPtr<USYPawnCombatComponent> ASYPlayerCharacter::GetPawnCombatComponent() const
{
	return PlayerCombatComponent;
}

TObjectPtr<USYPawnUIComponent> ASYPlayerCharacter::GetPawnUIComponent() const
{
	return PlayerUIComponent;
}

TObjectPtr<USYPlayerUIComponent> ASYPlayerCharacter::GetPlayerUIComponent() const
{
	return PlayerUIComponent;
}

void ASYPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!CharacterStartUpData.IsNull())
	{
		if (USYDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(SYAbilitySystemComponent);
		}
	}
}

void ASYPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset as input config"));

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(SubSystem);

	SubSystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	USYPlayerInputComponent* SYPlayerInputComponent = CastChecked<USYPlayerInputComponent>(PlayerInputComponent);

	SYPlayerInputComponent->BindNativeInputAction(InputConfigDataAsset, SYGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ASYPlayerCharacter::Input_Move);
	SYPlayerInputComponent->BindNativeInputAction(InputConfigDataAsset, SYGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ASYPlayerCharacter::Input_Look);

	SYPlayerInputComponent->BindNativeInputAction(InputConfigDataAsset, SYGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Triggered, this, &ASYPlayerCharacter::Input_SwitchTargetTriggered);
	SYPlayerInputComponent->BindNativeInputAction(InputConfigDataAsset, SYGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Completed, this, &ASYPlayerCharacter::Input_SwitchTargetCompleted);

	SYPlayerInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ASYPlayerCharacter::Input_AbilityInputPressed, &ASYPlayerCharacter::Input_AbilityInputReleased);
}

void ASYPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASYPlayerCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

	if (MovementVector.Y != 0.0f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);

		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	if (MovementVector.X != 0.0f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);

		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ASYPlayerCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.0f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}

	if (LookAxisVector.Y != 0.0f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASYPlayerCharacter::Input_SwitchTargetTriggered(const FInputActionValue& InputActionValue)
{
	SwitchDirection = InputActionValue.Get<FVector2D>();
}

void ASYPlayerCharacter::Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;
		
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		SwitchDirection.X > 0.0f ? SYGameplayTags::Player_Event_SwitchTarget_Right : SYGameplayTags::Player_Event_SwitchTarget_Left,
		Data
	);
}

void ASYPlayerCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	SYAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void ASYPlayerCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	SYAbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}
