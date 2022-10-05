// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "HRAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class HR_API UHRAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	UHRAssetManager();
	virtual void StartInitialLoading() override;

	/** 物品类型 */
	/** 直接带有GA(主动)*/
	static const FPrimaryAssetType	UnlimitedUsableItemType;
	static const FPrimaryAssetType	LimitedUsableItemType;
	/** 无GA*/
	static const FPrimaryAssetType	ReadOnlyItemType;
	/** 直接带有GA(被动) 或 加载一些GA(主动)*/
	static const FPrimaryAssetType	MaterielItemType;

	static UHRAssetManager& Get();

	class UHRItem* ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning = true);
};
