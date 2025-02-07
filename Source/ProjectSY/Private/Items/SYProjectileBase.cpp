// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/SYProjectileBase.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "SYFunctionLibrary.h"
#include "SYGameplayTags.h"
#include "AbilitySystemBlueprintLibrary.h"

// Sets default values
ASYProjectileBase::ASYProjectileBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ProjectileCollisionBox"));
	SetRootComponent(ProjectileCollisionBox);

	ProjectileCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	ProjectileCollisionBox->OnComponentHit.AddUniqueDynamic(this, &ASYProjectileBase::OnProjectileHit);
	ProjectileCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ASYProjectileBase::OnProjectileBeginOverlap);

	ProjectileNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileNiagaraComponent"));
	ProjectileNiagaraComponent->SetupAttachment(GetRootComponent());

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	ProjectileMovementComp->InitialSpeed = 700.0f;
	ProjectileMovementComp->MaxSpeed = 900.0f;
	ProjectileMovementComp->Velocity = FVector(1.0f, 0.0f, 0.0f);
	ProjectileMovementComp->ProjectileGravityScale = 0.0f;

	InitialLifeSpan = 4.0f;
}

// Called when the game starts or when spawned
void ASYProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	if (ProjectileDamagePolicy == EProjectileDamagePolicy::OnBeginOverlap)
	{
		ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	}
}

void ASYProjectileBase::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	BP_OnSpawnProjectileHitFX(Hit.ImpactPoint);

	APawn* HitPawn = Cast<APawn>(OtherActor);

	if (!HitPawn || !USYFunctionLibrary::IsTargetPawnHostile(GetInstigator(), HitPawn))
	{
		Destroy();
		return;
	}

	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = USYFunctionLibrary::NativeDoesActorHaveTag(HitPawn, FGameplayTag::RequestGameplayTag(FName("Player.Status.Blocking")));

	if (bIsPlayerBlocking)
	{
		bIsValidBlock = USYFunctionLibrary::IsValidBlock(this, HitPawn);
	}

	FGameplayEventData Data;
	Data.Instigator = this;
	Data.Target = HitPawn;

	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitPawn,
			FGameplayTag::RequestGameplayTag(FName("Player.Event.SuccessfulBlock")),
			Data
		);
	}
	else
	{
		HandleApplyProjectileDamage(HitPawn, Data);
	}

	Destroy();
}

void ASYProjectileBase::OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlappedActors.Contains(OtherActor))
	{
		return;
	}

	OverlappedActors.AddUnique(OtherActor);

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		FGameplayEventData Data;
		Data.Instigator = GetInstigator();
		Data.Target = HitPawn;

		if (USYFunctionLibrary::IsTargetPawnHostile(GetInstigator(), HitPawn))
		{
			HandleApplyProjectileDamage(HitPawn, Data);
		}
	}
}

void ASYProjectileBase::HandleApplyProjectileDamage(APawn* InHitPawn, const FGameplayEventData& InPayload)
{
	checkf(ProjectileDamageEffectSpecHandle.IsValid(), TEXT("Forgot to assign a valid spec handle to the projectile : %s"), *GetActorNameOrLabel());
	const bool bWasApplied = USYFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(GetInstigator(), InHitPawn, ProjectileDamageEffectSpecHandle);

	if (bWasApplied)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			InHitPawn,
			FGameplayTag::RequestGameplayTag(FName("Shared.Event.HitReact")),
			InPayload
		);
	}
}
