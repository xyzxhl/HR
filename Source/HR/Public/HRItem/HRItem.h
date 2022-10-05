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

	/** 类型 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	FPrimaryAssetType ItemType;

	/** 名字 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FText ItemName;

	/** 描述 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FText ItemDescription;

	/** 图标 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FSlateBrush ItemIcon;

	UFUNCTION(BlueprintCallable, Category = Item)
	FString GetIdentifierString() const;
};
