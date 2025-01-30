// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SYBaseCharacter.h"
#include "SYEnemyCharacter.generated.h"

class USYEnemyCombatComponent;
class USYEnemyUIComponent;
class UWidgetComponent;
class UBoxComponent;

/**
 * 
 */
UCLASS()
class PROJECTSY_API ASYEnemyCharacter : public ASYBaseCharacter
{
	GENERATED_BODY()
	
public:
	ASYEnemyCharacter();

	virtual TObjectPtr<USYPawnCombatComponent> GetPawnCombatComponent() const override;

	virtual TObjectPtr<USYPawnUIComponent> GetPawnUIComponent() const override;

	virtual TObjectPtr<USYEnemyUIComponent> GetEnemyUIComponent	() const override;

protected:
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<USYEnemyCombatComponent> EnemyCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<UBoxComponent> LeftHandCollisionBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	FName LeftHandCollisionBoxAttachBoneName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	FName RightHandCollisionBoxAttachBoneName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<UBoxComponent> RightHandCollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<USYEnemyUIComponent> EnemyUIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UWidgetComponent> EnemyHealthWidgetComponent;

	UFUNCTION()
	virtual void OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	void InitEnemyStartUpData();

public:
	FORCEINLINE TObjectPtr<USYEnemyCombatComponent> GetEnemyCombatComponent() const {return EnemyCombatComponent;}
	FORCEINLINE TObjectPtr<UBoxComponent> GetLeftHandCollisionBox() const {return LeftHandCollisionBox;}
	FORCEINLINE TObjectPtr<UBoxComponent> GetRightHandCollisionBox() const {return RightHandCollisionBox;}
};
