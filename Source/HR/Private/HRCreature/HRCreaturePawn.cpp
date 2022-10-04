// Fill out your copyright notice in the Description page of Project Settings.


#include "HRCreature/HRCreaturePawn.h"
#include "HRAbility/HRAbilitySystemComponent.h"
#include "HRAbility/HRAttributeSet.h"
#include "HRAbility/HRGameplayAbility.h"

// Sets default values
AHRCreaturePawn::AHRCreaturePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComp = CreateDefaultSubobject<UHRAbilitySystemComponent>(TEXT("AbilitySystem"));
	AbilitySystemComp->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<UHRAttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* AHRCreaturePawn::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

void AHRCreaturePawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (AbilitySystemComp)
	{
		AbilitySystemComp->InitAbilityActorInfo(this, this);
	}
}

void AHRCreaturePawn::OnRep_Controller()
{
	Super::OnRep_Controller();

	if (AbilitySystemComp)
	{
		AbilitySystemComp->RefreshAbilityActorInfo();
	}
}

// Called when the game starts or when spawned
void AHRCreaturePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHRCreaturePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHRCreaturePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

