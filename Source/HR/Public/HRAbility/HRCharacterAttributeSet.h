// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HRAbility/HRAttributeSet.h"
#include "HRCharacterAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class HR_API UHRCharacterAttributeSet : public UHRAttributeSet
{
	GENERATED_BODY()

public:
	UHRCharacterAttributeSet();
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource", ReplicatedUsing = OnRep_Stamina)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UHRCharacterAttributeSet, Stamina);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource", ReplicatedUsing = OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UHRCharacterAttributeSet, MaxStamina);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource", ReplicatedUsing = OnRep_StaminaRecoveryRate)
	FGameplayAttributeData StaminaRecoveryRate;
	ATTRIBUTE_ACCESSORS(UHRCharacterAttributeSet, StaminaRecoveryRate);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource", ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UHRCharacterAttributeSet, Mana);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource", ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UHRCharacterAttributeSet, MaxMana);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource", ReplicatedUsing = OnRep_ManaRecoveryRate)
	FGameplayAttributeData ManaRecoveryRate;
	ATTRIBUTE_ACCESSORS(UHRCharacterAttributeSet, ManaRecoveryRate);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resource", ReplicatedUsing = OnRep_InitialMana)
	FGameplayAttributeData InitialMana;
	ATTRIBUTE_ACCESSORS(UHRCharacterAttributeSet, InitialMana);

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
