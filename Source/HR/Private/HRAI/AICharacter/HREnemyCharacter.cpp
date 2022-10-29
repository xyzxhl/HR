// Fill out your copyright notice in the Description page of Project Settings.


#include "HRAI/AICharacter/HREnemyCharacter.h"
#include <AIModule/Classes/AIController.h>
#include <AIModule/Classes/BehaviorTree/BlackboardComponent.h>
#include <AIModule/Classes/Perception/PawnSensingComponent.h>
#include <DrawDebugHelpers.h>

AHREnemyCharacter::AHREnemyCharacter()
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");
}

void AHREnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AHREnemyCharacter::OnPawnSeen);
}

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
