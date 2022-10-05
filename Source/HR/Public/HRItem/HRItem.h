// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Styling/SlateBrush.h"
#include "HRAssetManager.h"
#include "HRItem.generated.h"

UCLASS(Abstract, BlueprintType)
class HR_API UHRItem : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UHRItem();
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

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

	UFUNCTION(BlueprintCallable, Category = Item)
	FString GetIdentifierString() const;
};
