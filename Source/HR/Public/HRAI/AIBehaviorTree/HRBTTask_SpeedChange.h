// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "HRBTTask_SpeedChange.generated.h"

class UCharacterMovementComponent;

UCLASS()
class HR_API UHRBTTask_SpeedChange : public UBTTaskNode
{
	GENERATED_BODY()

		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere,Category="KeySelector")
		FBlackboardKeySelector SpeedKey;
};
