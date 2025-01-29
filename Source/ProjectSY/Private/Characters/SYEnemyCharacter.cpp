// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SYEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/Combat/SYEnemyCombatComponent.h"
#include "Engine/AssetManager.h"
#include "DataAssets/StartUpData/SYDataAsset_EnemyStartUpDataBase.h"
#include "Components/UI/SYEnemyUIComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/SYWidgetBase.h"

ASYEnemyCharacter::ASYEnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 180.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.0f;

 	EnemyCombatComponent = CreateDefaultSubobject<USYEnemyCombatComponent>(TEXT("EnemyCombatComponent"));

	EnemyUIComponent = CreateDefaultSubobject<USYEnemyUIComponent>(TEXT("EnemyUIComponent"));

	EnemyHealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("EnemyHealthWidgetComponent"));
	EnemyHealthWidgetComponent->SetupAttachment(GetMesh());
}

TObjectPtr<USYPawnCombatComponent> ASYEnemyCharacter::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

TObjectPtr<USYPawnUIComponent> ASYEnemyCharacter::GetPawnUIComponent() const
{
	return EnemyUIComponent;
}

TObjectPtr<USYEnemyUIComponent> ASYEnemyCharacter::GetEnemyUIComponent() const
{
	return EnemyUIComponent;
}

void ASYEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (USYWidgetBase* HealthWidget = Cast<USYWidgetBase>(EnemyHealthWidgetComponent->GetUserWidgetObject()))
	{
		HealthWidget->InitEnemyCreatedWidget(this);
	}
}

void ASYEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitEnemyStartUpData();
}

void ASYEnemyCharacter::InitEnemyStartUpData()
{
	if (CharacterStartUpData.IsNull())
	{
		return;
	}

	// TODO 홍석영 : 매니저 클래스 UI매니저에 참고
	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this]()
			{
				if (USYDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(SYAbilitySystemComponent);
				}
			}
		)
	);
}
