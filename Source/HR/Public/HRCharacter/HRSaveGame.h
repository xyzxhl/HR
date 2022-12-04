// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "HRSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class HR_API UHRSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FTransform PlayerTransform;
};
