// Fill out your copyright notice in the Description page of Project Settings.


#include "HRCreature/HRCreaturePawn.h"

// Sets default values
AHRCreaturePawn::AHRCreaturePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHRCreaturePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHRCreaturePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHRCreaturePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

