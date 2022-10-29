// Fill out your copyright notice in the Description page of Project Settings.


#include "HRAI/AIBehaviorTree/HRBTTask_SpeedChange.h"
#include <AIModule/Classes/AIController.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <AIModule/Classes/BehaviorTree/BlackboardComponent.h>

EBTNodeResult::Type UHRBTTask_SpeedChange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBC = OwnerComp.GetBlackboardComponent();
	AAIController* AIC = OwnerComp.GetAIOwner();
	if (ensure(AIC))
	{
		APawn* AICharacter = Cast<APawn>(AIC->GetPawn());
		if (ensure(AICharacter))
		{
			UCharacterMovementComponent* CMC = Cast<UCharacterMovementComponent>(AICharacter->GetComponentByClass(MovementComp));
			if (ensure(CMC))
			{
				if (BBC->GetValueAsBool(SpeedKey.SelectedKeyName))
				{
					CMC->MaxWalkSpeed = 400;
					return EBTNodeResult::Succeeded;
				}
				else
				{
					CMC->MaxWalkSpeed = 800;
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}
