// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "HRExtraAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class HR_API UHRExtraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UHRExtraAttributeSet();
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource", ReplicatedUsing = OnRep_Stamina)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UHRExtraAttributeSet, Stamina);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource", ReplicatedUsing = OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UHRExtraAttributeSet, MaxStamina);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource", ReplicatedUsing = OnRep_StaminaRecoveryRate)
	FGameplayAttributeData StaminaRecoveryRate;
	ATTRIBUTE_ACCESSORS(UHRExtraAttributeSet, StaminaRecoveryRate);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource", ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UHRExtraAttributeSet, Mana);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource", ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UHRExtraAttributeSet, MaxMana);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource", ReplicatedUsing = OnRep_ManaRecoveryRate)
	FGameplayAttributeData ManaRecoveryRate;
	ATTRIBUTE_ACCESSORS(UHRExtraAttributeSet, ManaRecoveryRate);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource", ReplicatedUsing = OnRep_InitialMana)
	FGameplayAttributeData InitialMana;
	ATTRIBUTE_ACCESSORS(UHRExtraAttributeSet, InitialMana);

protected:
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);

	UFUNCTION()
	virtual void OnRep_Stamina(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_StaminaRecoveryRate(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxMana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_ManaRecoveryRate(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_InitialMana(const FGameplayAttributeData& OldValue);

};
