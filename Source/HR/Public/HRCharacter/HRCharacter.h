// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HRCharacter.generated.h"

UCLASS()
class HR_API AHRCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere)
	class UHRLockViewComponent* LockViewComp;

	UPROPERTY(VisibleAnywhere)
	class UHRInteractionComponent* InteractionComp;

	bool isLockView;
	AActor* ActorLockTo;
public:
	class APlayerController* ThisPlayerController;

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
