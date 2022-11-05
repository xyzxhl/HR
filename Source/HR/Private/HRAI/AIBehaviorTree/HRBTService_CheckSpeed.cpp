// Fill out your copyright notice in the Description page of Project Settings.


#include "HRAI/AIBehaviorTree/HRBTService_CheckSpeed.h"
#include <AIModule/Classes/AIController.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <AIModule/Classes/BehaviorTree/BlackboardComponent.h>
#include <GameFramework/Character.h>

void UHRBTService_CheckSpeed::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIC = OwnerComp.GetAIOwner();
	UBlackboardComponent* BBC = OwnerComp.GetBlackboardComponent();
	if (ensure(AIC))
	{
		ACharacter* AIPawn = AIC->GetCharacter();
		if (ensure(AIPawn))
		{
			UCharacterMovementComponent* CMC = Cast<UCharacterMovementComponent>(AIPawn->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
			bool bFast = CMC->MaxWalkSpeed == 800;
			BBC->SetValueAsBool(SpeedCheckKey.SelectedKeyName, bFast);
		}
	}
}
