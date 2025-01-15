// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/SYDataAsset_StartUpDataBase.h"
#include "SYTypes/SYStructTypes.h"
#include "SYDataAsset_PlayerStartUpData.generated.h"



/**
 * 
 */
UCLASS()
class PROJECTSY_API USYDataAsset_PlayerStartUpData : public USYDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(TObjectPtr<USYAbilitySystemComponent> InASCToGive, int32 ApplyLevel = 1) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FSYPlayerAbilitySet> PlayerStartUpAbilitySets;
};
