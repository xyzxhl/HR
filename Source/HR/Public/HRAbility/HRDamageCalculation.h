/////// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "HRDamageCalculation.generated.h"

/**
 * 
 */
UCLASS()
class HR_API UHRDamageCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:
	UHRDamageCalculation();
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

};
