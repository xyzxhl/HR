// Fill out your copyright notice in the Description page of Project Settings.


#include "HRAbility/HRExtraAttributeSet.h"
#include "HRCharacter/HRCharacter.h"

UHRExtraAttributeSet::UHRExtraAttributeSet()
    : Stamina(100.0f)
	, MaxStamina(100.0f)
	, StaminaRecoveryRate(40.0f)
    , Mana(0.0f)
    , MaxMana(100.0f)
	, ManaRecoveryRate(1.0f)
    , InitialMana(0.0f)
{
}

void UHRExtraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxStaminaAttribute())
	{
		AdjustAttributeForMaxChange(Stamina, MaxStamina, NewValue, GetStaminaAttribute());
	}
	else if (Attribute == GetMaxManaAttribute())
	{
		AdjustAttributeForMaxChange(Mana, MaxMana, NewValue, GetManaAttribute());
	}
}

void UHRExtraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	AActor* TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
	if (TargetActor->GetClass()->IsChildOf(AHRCharacter::StaticClass())) {
		AHRCharacter* TargetCharacter = Cast<AHRCharacter>(TargetActor);

		if (Data.EvaluatedData.Attribute == GetStaminaAttribute()) {
			SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));

		}
		else if (Data.EvaluatedData.Attribute == GetManaAttribute()) {
			SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));

		}
	}
}

void UHRExtraAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}