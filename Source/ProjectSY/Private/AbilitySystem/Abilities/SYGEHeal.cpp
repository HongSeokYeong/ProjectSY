// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/SYGEHeal.h"
#include "AbilitySystem/SYAttributeSet.h"

USYGEHeal::USYGEHeal()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;

	FGameplayModifierInfo HealModifier;
	HealModifier.Attribute = USYAttributeSet::GetCurrentHealthAttribute();
	HealModifier.ModifierOp = EGameplayModOp::Additive;

	static ConstructorHelpers::FObjectFinder<UCurveTable> CurveTableFinder(
		TEXT("/Script/Engine.CurveTable'/Game/EnemyCharacter/FrostGiant/GameplayEffect/CT_FrostGiantStats.CT_FrostGiantStats'"));

	if (CurveTableFinder.Succeeded())
	{
		FScalableFloat ScalableValue;
		ScalableValue.Curve.CurveTable = CurveTableFinder.Object;
		ScalableValue.Curve.RowName = FName("FrostGiant.Heal");
		ScalableValue.Value = 1.0f;
		HealModifier.ModifierMagnitude = ScalableValue;
	}

	Modifiers.Add(HealModifier);
}
