// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "HRDamegeCalculation.generated.h"

/**
 * 
 */
UCLASS()
class HR_API UHRDamegeCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:
	UHRDamegeCalculation();
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

};
