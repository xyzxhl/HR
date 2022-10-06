// Fill out your copyright notice in the Description page of Project Settings.


#include "HRAbility/HRAttributeSet.h"

UHRAttributeSet::UHRAttributeSet()
    : Health(100.0f)
	, MaxHealth(100.0f)
	, AttackPower(1.0f)
    , DefensePower(1.0f)
	, MoveSpeed(1.0f)
    , ActionSpeed(1.0f)
	, AttackSpeed(1.0f)
{
}

void UHRAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UHRAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHRAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHRAttributeSet, AttackPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHRAttributeSet, DefensePower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHRAttributeSet, MoveSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHRAttributeSet, ActionSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHRAttributeSet, AttackSpeed, COND_None, REPNOTIFY_Always);
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
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHRAttributeSet, ActionSpeed, OldValue);
}

void UHRAttributeSet::OnRep_AttackSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHRAttributeSet, AttackSpeed, OldValue);
}