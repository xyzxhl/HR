// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "HRStaminaRecovery.generated.h"

/**
 * 负责捕获StaminaRecoveryRate的MMC
 */
UCLASS()
class HR_API UHRStaminaRecovery : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

	FGameplayEffectAttributeCaptureDefinition StaminaRecoveryRateDef;

public:
	UHRStaminaRecovery();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const;

};
