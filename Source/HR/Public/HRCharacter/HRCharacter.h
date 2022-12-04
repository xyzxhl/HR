// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HRCharacter/HRCharacterBase.h"
#include "HRCharacter.generated.h"

class UHRSaveGame;

UCLASS()
class HR_API AHRCharacter : public AHRCharacterBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UHRLockViewComponent* LockViewComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interact")
	class UHRInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	class UHRExtraAttributeSet* ExtraAttributeSet;

public:

	AHRCharacter();

	// 仅在cpp可编辑
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UAbilitySystemComponent* OwnerComp, float NewValue);

	// 仅在cpp可编辑
	UFUNCTION()
	void OnStaminaChanged(AActor* InstigatorActor, UAbilitySystemComponent* OwnerComp, float NewValue);

	// 仅在cpp可编辑
	UFUNCTION()
	void OnManaChanged(AActor* InstigatorActor, UAbilitySystemComponent* OwnerComp, float NewValue);

	// 仅在cpp可编辑
	UFUNCTION()
	void Die();

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnRight(float Value);

	void LookUp(float Value);

public:
	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	void SaveCharacter(UHRSaveGame* SaveObject);
	void LoadCharacter(UHRSaveGame* LoadObject);
};
