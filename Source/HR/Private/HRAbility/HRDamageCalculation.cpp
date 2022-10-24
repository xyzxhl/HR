// Fill out your copyright notice in the Description page of Project Settings.


#include "HRAbility/HRDamageCalculation.h"
#include "HRAbility/HRAttributeSet.h"
#include "HRAbility/HRExtraAttributeSet.h"
#include "AbilitySystemComponent.h"

struct HRDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower);

	HRDamageStatics()
	{
		//false说明：不使用属性快照，在GE将要应用时获取属性
		DEFINE_ATTRIBUTE_CAPTUREDEF(UHRAttributeSet, DefensePower, Target, false);

		//true说明：使用属性快照，在GE实例化时获取属性
		DEFINE_ATTRIBUTE_CAPTUREDEF(UHRAttributeSet, AttackPower, Source, true);


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
}

void UHRDamageCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();


}
