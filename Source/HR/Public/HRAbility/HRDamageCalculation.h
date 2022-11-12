/////// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "HRDamageCalculation.generated.h"

/**
 * 负责处理玩家对敌人造成的伤害
 * 计算伤害系数，伤害减免系数
 * 直接修改Target的生命值
 * 根据ManaRecoveryRate直接修改Source的Mana
 */
UCLASS()
class HR_API UHRDamageCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:
	UHRDamageCalculation();
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

};
