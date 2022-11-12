// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "HRAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class HR_API UHRAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UHRAttributeSet();
	/** 属性修改前调用 */
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	/** 应用GE属性修改后调用 */
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	/** 生命值 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UHRAttributeSet, Health);

	/** 最大生命值 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UHRAttributeSet, MaxHealth);

	/** 伤害系数，计算优先度最低，无ui */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Damage")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UHRAttributeSet, AttackPower);

	/** 伤害减免系数，计算优先度最低，无ui */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Damage")
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UHRAttributeSet, DefensePower);

	/** 移动速度，无ui */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Speed")
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(UHRAttributeSet, MoveSpeed);

	/** 影响涉及动作的GA，无ui */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Speed")
	FGameplayAttributeData AbilitySpeed;
	ATTRIBUTE_ACCESSORS(UHRAttributeSet, AbilitySpeed);

	/** 影响基础攻击和其派生的速度，无ui */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Speed")
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(UHRAttributeSet, AttackSpeed);

	/** 临时值，用于伤害计算，在GA中对这个值进行修改 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Damage")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UHRAttributeSet, Damage);

protected:
	/** 用于处理最大值变化，百分比缩放当前值 */
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);

};
