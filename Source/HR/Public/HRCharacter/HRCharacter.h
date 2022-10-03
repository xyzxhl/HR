// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "HRCharacter.generated.h"

UCLASS()
class HR_API AHRCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

protected:
	UPROPERTY(VisibleAnywhere)
	class UHRLockViewComponent* LockViewComp;

	UPROPERTY(VisibleAnywhere)
	class UHRInteractionComponent* InteractionComp;

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="CharacterBase")
    class UHRAbilitySystemComponent* AbilitySystemComp;

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

public:
	// Sets default values for this character's properties
	AHRCharacter();

protected:
	void MoveForward(float Value);
	void MoveRight(float Value);

	void TurnRight(float Value);
	void LookUp(float Value);

	void LockViewToEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
