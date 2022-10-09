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
	if (TargetActor->GetClass()->IsChildOf(AHRCharacterBase::StaticClass())) {
		AHRCharacterBase* TargetCharacter = Cast<AHRCharacterBase>(TargetActor);

		if (Data.EvaluatedData.Attribute == GetHealthAttribute()) {
			SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

			if (GetHealth() < 0.1f) {
				TargetCharacter->Die();
			}
		}
		else if (Data.EvaluatedData.Attribute == GetMoveSpeedAttribute()) {
			SetMoveSpeed(FMath::Clamp(GetMoveSpeed(), 1.0f, 1.3f));

			TargetCharacter->GetCharacterMovement()->MaxWalkSpeed *= GetMoveSpeed();
		}
	}
}

void UHRAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UHRAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHRAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHRAttributeSet, AttackPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHRAttributeSet, DefensePower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHRAttributeSet, MoveSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHRAttributeSet, AbilitySpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHRAttributeSet, AttackSpeed, COND_None, REPNOTIFY_Always);
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

void UHRAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHRAttributeSet, Health, OldValue);
}

void UHRAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHRAttributeSet, MaxHealth, OldValue);
}

void UHRAttributeSet::OnRep_AttackPower(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHRAttributeSet, AttackPower, OldValue);
}

void UHRAttributeSet::OnRep_DefensePower(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHRAttributeSet, DefensePower, OldValue);
}

void UHRAttributeSet::OnRep_MoveSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHRAttributeSet, MoveSpeed, OldValue);
}

void UHRAttributeSet::OnRep_ActionSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHRAttributeSet, AbilitySpeed, OldValue);
}

void UHRAttributeSet::OnRep_AttackSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHRAttributeSet, AttackSpeed, OldValue);
}