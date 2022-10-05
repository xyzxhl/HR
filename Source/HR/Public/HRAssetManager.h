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

	/** ��Ʒ���� */
	/** ֱ�Ӵ���GA(����)*/
	static const FPrimaryAssetType	UnlimitedUsableItemType;
	static const FPrimaryAssetType	LimitedUsableItemType;
	/** ��GA*/
	static const FPrimaryAssetType	ReadOnlyItemType;
	/** ֱ�Ӵ���GA(����) �� ����һЩGA(����)*/
	static const FPrimaryAssetType	MaterielItemType;

	static UHRAssetManager& Get();

	class UHRItem* ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning = true);
};
