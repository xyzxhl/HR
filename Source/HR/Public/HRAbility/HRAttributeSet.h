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
	/** �����޸�ǰ���� */
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	/** Ӧ��GE�����޸ĺ���� */
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	/** ����ֵ */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UHRAttributeSet, Health);

	/** �������ֵ */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UHRAttributeSet, MaxHealth);

	/** �˺�ϵ�����������ȶ���ͣ���ui */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Damage")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UHRAttributeSet, AttackPower);

	/** �˺�����ϵ�����������ȶ���ͣ���ui */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Damage")
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UHRAttributeSet, DefensePower);

	/** �ƶ��ٶȣ���ui */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Speed")
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(UHRAttributeSet, MoveSpeed);

	/** Ӱ���漰������GA����ui */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Speed")
	FGameplayAttributeData AbilitySpeed;
	ATTRIBUTE_ACCESSORS(UHRAttributeSet, AbilitySpeed);

	/** Ӱ��������������������ٶȣ���ui */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Speed")
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(UHRAttributeSet, AttackSpeed);

	/** ��ʱֵ�������˺����㣬��GA�ж����ֵ�����޸� */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Damage")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UHRAttributeSet, Damage);

protected:
	/** ���ڴ������ֵ�仯���ٷֱ����ŵ�ǰֵ */
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);

};
