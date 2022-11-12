// Fill out your copyright notice in the Description page of Project Settings.


#include "HRAbility/HRStaminaRecovery.h"
#include "HRAbility/HRExtraAttributeSet.h"

UHRStaminaRecovery::UHRStaminaRecovery()
{
	StaminaRecoveryRateDef.AttributeToCapture = UHRExtraAttributeSet::GetStaminaRecoveryRateAttribute();
	StaminaRecoveryRateDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	StaminaRecoveryRateDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(StaminaRecoveryRateDef);
}

float UHRStaminaRecovery::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float StaminaRecovery = 0.f;
	GetCapturedAttributeMagnitude(StaminaRecoveryRateDef, Spec, EvaluationParameters, StaminaRecovery);

	StaminaRecovery *= 0.05f;

    return StaminaRecovery;
}
