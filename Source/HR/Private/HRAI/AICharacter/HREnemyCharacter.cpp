// Fill out your copyright notice in the Description page of Project Settings.


#include "HRAI/AICharacter/HREnemyCharacter.h"
#include "HRAbility/HRAttributeSet.h"
#include <AIModule/Classes/AIController.h>
#include <AIModule/Classes/BehaviorTree/BlackboardComponent.h>
#include <AIModule/Classes/Perception/PawnSensingComponent.h>
#include <DrawDebugHelpers.h>

AHREnemyCharacter::AHREnemyCharacter()
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	AttributeSet = CreateDefaultSubobject<UHRAttributeSet>(TEXT("AttributeSet"));
}

void AHREnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AHREnemyCharacter::OnPawnSeen);
}


// When the enemy pawns catch a player in the eyesight, set the TargetActor to it and try to attack.
void AHREnemyCharacter::OnPawnSeen(APawn* Pawn)
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if (ensure(AIController))
	{
		UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();

		BlackboardComponent->SetValueAsObject("TargetActor", Pawn);

		DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER SPOTTED", nullptr, FColor::White, 4.0f, true);
	}
}
