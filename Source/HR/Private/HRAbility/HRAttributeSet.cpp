// Fill out your copyright notice in the Description page of Project Settings.


#include "HRAbility/HRAttributeSet.h"
#include "HRCharacter/HRCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

UHRAttributeSet::UHRAttributeSet()
    : Health(100.0f)
	, MaxHealth(100.0f)
	, AttackPower(1.0f)
    , DefensePower(1.0f)
	, MoveSpeed(1.0f)
    , AbilitySpeed(1.0f)
	, AttackSpeed(1.0f)
{
}

void UHRAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
}

void UHRAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	AActor* TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
	if (TargetActor->GetClass()->IsChildOf(AHRCharacterBase::StaticClass())) 
	{
		AHRCharacterBase* TargetCharacter = Cast<AHRCharacterBase>(TargetActor);

		if (Data.EvaluatedData.Attribute == GetHealthAttribute()) 
		{
			SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

			OnHealthChanged.Broadcast(nullptr, TargetCharacter->GetAbilitySystemComponent(), GetHealth());
		}
		else if (Data.EvaluatedData.Attribute == GetMoveSpeedAttribute()) 
		{
			SetMoveSpeed(FMath::Clamp(GetMoveSpeed(), 1.0f, 1.3f));

			TargetCharacter->GetCharacterMovement()->MaxWalkSpeed = GetMoveSpeed() * TargetCharacter->BaseSpeed;
		}
	}
}

void UHRAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
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