// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <AIModule/Classes/EnvironmentQuery/EnvQueryTypes.h>
#include "HRGameModeBase.generated.h"

class UEnvQuery;
class UCurveFloat;

/**
 *
 */
UCLASS()
class HR_API AHRGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AHRGameModeBase();

	virtual void StartPlay() override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "EnemySpawn")
		TSubclassOf<AActor> MinionClass;

	UPROPERTY(EditDefaultsOnly, Category = "EnemySpawn")
		UEnvQuery* SpawnBotQuery;

	UPROPERTY(EditDefaultsOnly, Category = "EnemySpawn")
		UCurveFloat* DifficultyCurve;

	UPROPERTY(EditDefaultsOnly, Category = "EnemySpawn")
		float BasicEnemySpawnTimerInterval;

	FTimerHandle TimerHandle_BasicSpawnbots;

	UFUNCTION()
		void BasicSpawnBotTimerElapsed();

	UFUNCTION()
		void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);
};
