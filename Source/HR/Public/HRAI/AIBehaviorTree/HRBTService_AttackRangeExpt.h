// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "HRBTService_AttackRangeExpt.generated.h"

/**
 *
 */
UCLASS()
class HR_API UHRBTService_AttackRangeExpt : public UBTService
{
	GENERATED_BODY()



protected:

	UPROPERTY(EditAnywhere,Category="Ability")
		float AttackDistance;

	UPROPERTY(EditAnywhere, Category = "KeySelector")
		FBlackboardKeySelector AttackRangeKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
