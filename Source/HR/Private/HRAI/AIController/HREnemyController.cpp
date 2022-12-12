// Fill out your copyright notice in the Description page of Project Settings.


#include "HRAI/AIController/HREnemyController.h"

void AHREnemyController::BeginPlay()
{
	Super::BeginPlay();

	// Run Behavior Tree.
	/* 运行行为树 */
	if (ensureMsgf(BehaviorTree,TEXT("Behavior Tree is nullptr! Please assign Behavior Tree to your AI Controller.")))
	{
		RunBehaviorTree(BehaviorTree);
	}
}