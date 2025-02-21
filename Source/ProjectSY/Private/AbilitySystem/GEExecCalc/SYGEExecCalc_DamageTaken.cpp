// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalc/SYGEExecCalc_DamageTaken.h"
#include "AbilitySystem/SYAttributeSet.h"
#include "SYGameplayTags.h"
#include "SYDebugHelper.h"
#include "Widgets/SYUIManagerSubsystem.h"

struct FSYDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FSYDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(USYAttributeSet, AttackPower, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(USYAttributeSet, DefensePower, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(USYAttributeSet, DamageTaken, Target, false)
	}
};

static const FSYDamageCapture& GetSYDamageCapture()
{
	static FSYDamageCapture SYDamageCapture;
	return SYDamageCapture;
}

USYGEExecCalc_DamageTaken::USYGEExecCalc_DamageTaken()
{
	RelevantAttributesToCapture.Add(GetSYDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetSYDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetSYDamageCapture().DamageTakenDef);
}

void USYGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetSYDamageCapture().AttackPowerDef, EvaluateParameters, SourceAttackPower);

	float BaseDamage = 0.0f;
	int32 UsedLightAttackComboCount = 0;
	int32 UsedHeavyAttackComboCount = 0;

	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Shared.SetByCaller.BaseDamage"))))
		{
			BaseDamage = TagMagnitude.Value;
		}

		if (TagMagnitude.Key.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Player.SetByCaller.AttackType.Light"))))
		{
			UsedLightAttackComboCount = TagMagnitude.Value;
		}

		if (TagMagnitude.Key.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Player.SetByCaller.AttackType.Heavy"))))
		{
			UsedHeavyAttackComboCount = TagMagnitude.Value;
		}
	}

	float TargetDefensePower = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetSYDamageCapture().DefensePowerDef, EvaluateParameters, TargetDefensePower);

	if (UsedLightAttackComboCount != 0)
	{
		const float DamageIncreasePercentLight = (UsedLightAttackComboCount - 1) * 0.05f + 1.0f;

		BaseDamage *= DamageIncreasePercentLight;
	}

	if (UsedHeavyAttackComboCount != 0)
	{
		const float DamageIncreasePercentHeavy = UsedHeavyAttackComboCount * 0.15f + 1.0f;

		BaseDamage *= DamageIncreasePercentHeavy;
	}

	const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefensePower;

	if (FinalDamageDone > 0.0f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetSYDamageCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamageDone
			)
		);
	}
}
