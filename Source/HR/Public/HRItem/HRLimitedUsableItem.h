// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HRItem/HRItem.h"
#include "HRLimitedUsableItem.generated.h"

UCLASS()
class HR_API UHRLimitedUsableItem : public UHRItem
{
	GENERATED_BODY()

public:
	UHRLimitedUsableItem();
	
	int32 MaxCount;
	int32 CurrentCount;

	TSubclassOf<class UHRGameplayAbility> GrantedAbility;

};
