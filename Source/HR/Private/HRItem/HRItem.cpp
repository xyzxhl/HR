// Fill out your copyright notice in the Description page of Project Settings.


#include "HRItem/HRItem.h"

UHRItem::UHRItem()
{
}

FPrimaryAssetId UHRItem::GetPrimaryAssetId() const
{
    return FPrimaryAssetId(ItemType, GetFName());
}

FString UHRItem::GetIdentifierString() const
{
    return GetPrimaryAssetId().ToString();
}
