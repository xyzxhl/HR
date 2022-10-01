// Fill out your copyright notice in the Description page of Project Settings.


#include "HRCharacter/HRCharacter.h"

// Sets default values
AHRCharacter::AHRCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHRCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

