// Fill out your copyright notice in the Description page of Project Settings.


#include "HRAI/AIBehaviorTree/HRBTService_AttackRangeExpt.h"
#include <AIModule/Classes/BehaviorTree/BlackboardComponent.h>
#include <AIModule/Classes/AIController.h>

void UHRBTService_AttackRangeExpt::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BBComp))
	{
		AActor* TargetActor = Cast<AActor>(BBComp->GetValueAsObject("TargetActor"));
		if (TargetActor)
		{
			AAIController* AIC = OwnerComp.GetAIOwner();

			if (ensure(AIC))
			{
				APawn* AIPawn = AIC->GetPawn();
				if (ensure(AIPawn))
				{
					float DistanceOfActor = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());
					bool bWithinAttackRange = DistanceOfActor < AttackDistance;

					bool bHasLineOfSight = false;
					if (bWithinAttackRange)
					{
						bHasLineOfSight = AIC->LineOfSightTo(TargetActor);
					}

					BBComp->SetValueAsBool(AttackRangeKey.SelectedKeyName, (bWithinAttackRange && bHasLineOfSight));
				}
			}
		}
	}
}
