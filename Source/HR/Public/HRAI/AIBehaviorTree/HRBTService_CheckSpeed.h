// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include <Components/ActorComponent.h>
#include "HRBTService_CheckSpeed.generated.h"

class UActorComponent;
class UCharacterMovementComponent;
class UBlackboardComponent;
/**
 *
 */
UCLASS()
class HR_API UHRBTService_CheckSpeed : public UBTService
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "KeySelector")
		FBlackboardKeySelector SpeedCheckKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
