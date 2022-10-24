// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HRCharacter/HRCharacterBase.h"
#include "HREnemyCharacter.generated.h"

class UPawnSensingComponent;

UCLASS()
class HR_API AHREnemyCharacter : public AHRCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHREnemyCharacter();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPawnSensingComponent* PawnSensingComp;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);
};
