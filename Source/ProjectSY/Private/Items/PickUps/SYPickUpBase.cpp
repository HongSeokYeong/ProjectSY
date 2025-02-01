// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PickUps/SYPickUpBase.h"
#include "Components/SphereComponent.h"

// Sets default values
ASYPickUpBase::ASYPickUpBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PickUpCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickUpCollisionSphere"));
	SetRootComponent(PickUpCollisionSphere);

	PickUpCollisionSphere->InitSphereRadius(50.0f);
	PickUpCollisionSphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &ASYPickUpBase::OnPickUpCollisionSphereOverlap);
}

void ASYPickUpBase::OnPickUpCollisionSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

