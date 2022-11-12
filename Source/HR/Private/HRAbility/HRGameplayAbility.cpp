// Fill out your copyright notice in the Description page of Project Settings.

#include "HRAbility/HRGameplayAbility.h"
#include "HRAbility/HRAttributeSet.h"
#include "HRAbility/HRExtraAttributeSet.h"
#include "HRCharacter/HRCharacter.h"

UHRGameplayAbility::UHRGameplayAbility()
    : StaminaChange(0.0f)
    , ManaChange(0.0f)
    , Damage(0.0f)
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

bool UHRGameplayAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
    AActor* Owner = ActorInfo->OwnerActor.Get();
    if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags)) {
        if (Owner->GetClass()->IsChildOf(AHRCharacter::StaticClass())) {
            AHRCharacter* HRCharacter = Cast<AHRCharacter>(Owner);
            if (HRCharacter->ExtraAttributeSet->GetStamina() + StaminaChange >= 0.0
                && HRCharacter->ExtraAttributeSet->GetMana() + ManaChange >= 0.0) {
                return true;
            }
        }
    }
    return false;
}

void UHRGameplayAbility::PreActivate(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData)
{
    Super::PreActivate(Handle, ActorInfo, ActivationInfo, OnGameplayAbilityEndedDelegate, TriggerEventData);
    AActor* Owner = ActorInfo->OwnerActor.Get();
    if (Owner->GetClass()->IsChildOf(AHRCharacter::StaticClass())) {
        AHRCharacter* HRCharacter = Cast<AHRCharacter>(Owner);
        HRCharacter->ExtraAttributeSet->SetDamage(Damage);
    }
}

void UHRGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    AActor* Owner = ActorInfo->OwnerActor.Get();
    if (Owner->GetClass()->IsChildOf(AHRCharacter::StaticClass())) {
        AHRCharacter* HRCharacter = Cast<AHRCharacter>(Owner);
        HRCharacter->ExtraAttributeSet->SetDamage(0.0f);
    }

    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
