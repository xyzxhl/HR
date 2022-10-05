// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HRItem.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class HR_API UHRItem : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UHRItem();

	/** ���� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	FPrimaryAssetType ItemType;

	/** ���� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FText ItemName;

	/** ���� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FText ItemDescription;

	/** ͼ�� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FSlateBrush ItemIcon;


};
