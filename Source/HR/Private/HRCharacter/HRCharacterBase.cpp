// Fill out your copyright notice in the Description page of Project Settings.


#include "HRCharacter/HRCharacterBase.h"
#include "HRAbility/HRAbilitySystemComponent.h"
#include "HRAbility/HRAttributeSet.h"
#include "HRAbility/HRGameplayAbility.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AHRCharacterBase::AHRCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseSpeed = 250.0f;
	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;

	AbilitySystemComp = CreateDefaultSubobject<UHRAbilitySystemComponent>(TEXT("AbilitySystem"));
	AbilitySystemComp->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<UHRAttributeSet>(TEXT("AttributeSet"));
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

void AHRCharacterBase::OnRep_Controller()
{
	Super::OnRep_Controller();

	if (AbilitySystemComp)
	{
		AbilitySystemComp->RefreshAbilityActorInfo();
	}
}

void AHRCharacterBase::Die()
{
}
