// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AbilitySystemInterface.h"
#include "HRCreaturePawn.generated.h"

UCLASS()
class HR_API AHRCreaturePawn : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
    class UHRAbilitySystemComponent* AbilitySystemComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	class UHRAttributeSet* AttributeSet;

public:
	// Sets default values for this pawn's properties
	AHRCreaturePawn();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_Controller() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
