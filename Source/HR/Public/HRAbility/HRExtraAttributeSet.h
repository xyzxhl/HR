// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HRAbility/HRAttributeSet.h"
#include "HRExtraAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class HR_API UHRExtraAttributeSet : public UHRAttributeSet
{
	GENERATED_BODY()

public:
	UHRExtraAttributeSet();
	/** 属性修改前调用 */
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	/** 应用GE属性修改后调用 */
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UHRExtraAttributeSet, Stamina);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UHRExtraAttributeSet, MaxStamina);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource")
	FGameplayAttributeData StaminaRecoveryRate;
	ATTRIBUTE_ACCESSORS(UHRExtraAttributeSet, StaminaRecoveryRate);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UHRExtraAttributeSet, Mana);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UHRExtraAttributeSet, MaxMana);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource")
	FGameplayAttributeData ManaRecoveryRate;
	ATTRIBUTE_ACCESSORS(UHRExtraAttributeSet, ManaRecoveryRate);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource")
	FGameplayAttributeData InitialMana;
	ATTRIBUTE_ACCESSORS(UHRExtraAttributeSet, InitialMana);
};
