// Fill out your copyright notice in the Description page of Project Settings.


#include "HRAbility/HRDamageCalculation.h"
#include "HRAbility/HRAttributeSet.h"
#include "HRAbility/HRExtraAttributeSet.h"
#include "AbilitySystemComponent.h"

struct HRDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Mana);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ManaRecoveryRate);

	HRDamageStatics()
	{
		//false说明：不使用属性快照，在GE将要应用时获取属性
		DEFINE_ATTRIBUTE_CAPTUREDEF(UHRAttributeSet, DefensePower, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UHRAttributeSet, Health, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UHRExtraAttributeSet, Mana, Source, false);

		//true说明：使用属性快照，在GE实例化时获取属性
		DEFINE_ATTRIBUTE_CAPTUREDEF(UHRAttributeSet, AttackPower, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UHRAttributeSet, Damage, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UHRExtraAttributeSet, ManaRecoveryRate, Source, true);
	}
};

static const HRDamageStatics& DamageStatics()
{
	static HRDamageStatics DamageStaticsObject;
	return DamageStaticsObject;
}

UHRDamageCalculation::UHRDamageCalculation()
{
	RelevantAttributesToCapture.Add(DamageStatics().DefensePowerDef);
	RelevantAttributesToCapture.Add(DamageStatics().AttackPowerDef);
	RelevantAttributesToCapture.Add(DamageStatics().DamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().HealthDef);
	RelevantAttributesToCapture.Add(DamageStatics().ManaDef);
	RelevantAttributesToCapture.Add(DamageStatics().ManaRecoveryRateDef);
}

void UHRDamageCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->GetAvatarActor_Direct() : nullptr;
	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor_Direct() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// 根据标签判断一些影响是否被使用
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float DefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DefensePowerDef, EvaluationParameters, DefensePower);

	float AttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().AttackPowerDef, EvaluationParameters, AttackPower);

	float Damage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DamageDef, EvaluationParameters, Damage);

	float ManaRecoveryRate = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ManaRecoveryRateDef, EvaluationParameters, ManaRecoveryRate);

	float DamageDone = Damage * AttackPower * DefensePower;
	float ManaRecovery = DamageDone * ManaRecoveryRate;
	if (DamageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().HealthProperty, EGameplayModOp::Additive, -DamageDone));
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().ManaProperty, EGameplayModOp::Additive, ManaRecovery));
	}
}
