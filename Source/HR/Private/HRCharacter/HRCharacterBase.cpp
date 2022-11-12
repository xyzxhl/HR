// Fill out your copyright notice in the Description page of Project Settings.


#include "HRCharacter/HRCharacterBase.h"
#include "HRAbility/HRAttributeSet.h"

// Sets default values
AHRCharacterBase::AHRCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseSpeed = 250.0f;
	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;

	AbilitySystemComp = CreateDefaultSubobject<UHRAbilitySystemComponent>(TEXT("AbilitySystem"));
	AbilitySystemComp->SetIsReplicated(true);
}

UAbilitySystemComponent* AHRCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

void AHRCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComp)
	{
		AbilitySystemComp->InitAbilityActorInfo(this, this);
	}
}

bool AHRCharacterBase::AddAbility(TSubclassOf<UGameplayAbility> GameplayAbility, FString Name)
{
	FGameplayAbilitySpecHandle Handle = AbilitySystemComp->K2_GiveAbility(GameplayAbility);
	if (Handle.IsValid()) {
		AbilityHandles.Add(Name, Handle);
		return true;
	}
	else
		return false;
}

bool AHRCharacterBase::FindAbility(FString Name)
{
	return AbilityHandles.Contains(Name);
}

bool AHRCharacterBase::UseAbility(FString Name)
{
	FGameplayAbilitySpecHandle* Handle = AbilityHandles.Find(Name);
	if (Handle) {
		AbilitySystemComp->TryActivateAbility(*Handle);
		return true;
	}
	else
		return false;
}

bool AHRCharacterBase::DeleteAbility(FString Name)
{
	FGameplayAbilitySpecHandle* Handle = AbilityHandles.Find(Name);
	if (Handle) {
		AbilitySystemComp->ClearAbility(*Handle);
		AbilityHandles.Remove(Name);
		return true;
	}
	else
		return false;
}
