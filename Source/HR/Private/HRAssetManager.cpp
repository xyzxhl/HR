// Fill out your copyright notice in the Description page of Project Settings.


#include "HRAssetManager.h"
#include "HRItem/HRItem.h"
#include "AbilitySystemGlobals.h"

const FPrimaryAssetType	UHRAssetManager::UnlimitedUsableItemType = TEXT("UnlimitedUsable");
const FPrimaryAssetType	UHRAssetManager::LimitedUsableItemType = TEXT("LimitedUsable");
const FPrimaryAssetType	UHRAssetManager::ReadOnlyItemType = TEXT("ReadOnly");
const FPrimaryAssetType	UHRAssetManager::MaterielItemType = TEXT("Materiel");

UHRAssetManager::UHRAssetManager()
{
}

void UHRAssetManager::StartInitialLoading()
{
    Super::StartInitialLoading();

	UAbilitySystemGlobals::Get().InitGlobalData();
}

UHRAssetManager& UHRAssetManager::Get()
{
	UHRAssetManager* This = Cast<UHRAssetManager>(GEngine->AssetManager);

	if (This)
	{
		return *This;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid AssetManager in DefaultEngine.ini, must be RPGAssetManager!"));
		return *NewObject<UHRAssetManager>();
	}
}

UHRItem* UHRAssetManager::ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning)
{
    FSoftObjectPath ItemPath = GetPrimaryAssetPath(PrimaryAssetId);

	UHRItem* LoadedItem = Cast<UHRItem>(ItemPath.TryLoad());

	if (bLogWarning && LoadedItem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load item for identifier %s!"), *PrimaryAssetId.ToString());
	}

	return LoadedItem;
}
