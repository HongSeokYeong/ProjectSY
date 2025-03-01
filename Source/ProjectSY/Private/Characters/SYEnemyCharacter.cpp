// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SYEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/Combat/SYEnemyCombatComponent.h"
#include "Engine/AssetManager.h"
#include "DataAssets/StartUpData/SYDataAsset_EnemyStartUpDataBase.h"
#include "Components/UI/SYEnemyUIComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/SYWidgetBase.h"
#include "Components/BoxComponent.h"
#include "SYFunctionLibrary.h"
#include "GameMode/SYBaseGameMode.h"
#include "Widgets/SYEnemyWidget.h"

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

	LeftHandCollisionBox = CreateDefaultSubobject<UBoxComponent>("LeftHandCollisionBox");
	LeftHandCollisionBox->SetupAttachment(GetMesh());
	LeftHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftHandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ASYEnemyCharacter::OnBodyCollisionBoxBeginOverlap);

	RightHandCollisionBox = CreateDefaultSubobject<UBoxComponent>("RightHandCollisionBox");
	RightHandCollisionBox->SetupAttachment(GetMesh());
	RightHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightHandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ASYEnemyCharacter::OnBodyCollisionBoxBeginOverlap);
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

	if (USYEnemyWidget* HealthWidget = Cast<USYEnemyWidget>(EnemyHealthWidgetComponent->GetUserWidgetObject()))
	{
		HealthWidget->InitEnemyCreatedWidget(this);
	}
}

void ASYEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitEnemyStartUpData();
}

#if WITH_EDITOR
void ASYEnemyCharacter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ASYEnemyCharacter, LeftHandCollisionBoxAttachBoneName))
	{
		LeftHandCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, LeftHandCollisionBoxAttachBoneName);
	}

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ASYEnemyCharacter, RightHandCollisionBoxAttachBoneName))
	{
		RightHandCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, RightHandCollisionBoxAttachBoneName);
	}
}
#endif

void ASYEnemyCharacter::OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (USYFunctionLibrary::IsTargetPawnHostile(this, HitPawn))
		{
			EnemyCombatComponent->OnHitTargetActor(HitPawn);
		}
	}
}

void ASYEnemyCharacter::InitEnemyStartUpData()
{
	if (CharacterStartUpData.IsNull())
	{
		return;
	}

	int32 AbilityApplyLevel = 1;

	if (ASYBaseGameMode* BaseGameMode = GetWorld()->GetAuthGameMode<ASYBaseGameMode>())
	{
		switch (BaseGameMode->GetCurrentGameDifficulty())
		{
		case ESYGameDifficulty::Easy:
			AbilityApplyLevel = 1;
			break;
		case ESYGameDifficulty::Normal:
			AbilityApplyLevel = 2;
			break;
		case ESYGameDifficulty::Hard:
			AbilityApplyLevel = 3;
			break;
		case ESYGameDifficulty::VeryHard:
			AbilityApplyLevel = 4;
			break;
		default:
			break;
		}
	}

	// TODO 홍석영 : 매니저 클래스 UI매니저에 참고
	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this, AbilityApplyLevel]()
			{
				if (USYDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(SYAbilitySystemComponent, AbilityApplyLevel);
				}
			}
		)
	);
}
