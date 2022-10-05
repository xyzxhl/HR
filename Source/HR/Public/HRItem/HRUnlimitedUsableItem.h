// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HRItem/HRItem.h"
#include "HRUnlimitedUsableItem.generated.h"

/**
 * 
 */
UCLASS()
class HR_API UHRUnlimitedUsableItem : public UHRItem
{
	GENERATED_BODY()
	
public:
	UHRUnlimitedUsableItem();

	TSubclassOf<class UHRGameplayAbility> GrantedAbility;

};
