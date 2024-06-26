// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HRWorldUserWidget.generated.h"

class USizeBox;
/**
 *
 */
UCLASS()
class HR_API UHRWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		USizeBox* ParentSizeBox;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

	UPROPERTY(BlueprintReadOnly, Category = "UI")
		AActor* ActorToAttach;

	UPROPERTY(EditAnywhere, Category = "UI")
		FVector WorldOffset;
};
