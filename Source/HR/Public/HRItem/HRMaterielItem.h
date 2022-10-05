// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HRItem/HRItem.h"
#include "HRMaterielItem.generated.h"

/**
 * 
 */
UCLASS()
class HR_API UHRMaterielItem : public UHRItem
{
	GENERATED_BODY()

public:
	UHRMaterielItem();

	TArray<TSubclassOf<class UHRGameplayAbility>> GrantedAbility;

};
