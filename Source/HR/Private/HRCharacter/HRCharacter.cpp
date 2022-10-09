// Fill out your copyright notice in the Description page of Project Settings.

#include "HRCharacter/HRCharacter.h"
#include "HRCharacter/HRInteractionComponent.h"
#include "HRCharacter/HRLockViewComponent.h"
#include "HRAbility/HRExtraAttributeSet.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AHRCharacter::AHRCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 250.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.0f;
	CameraBoom->SocketOffset.Z = 100.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	InteractionComp = CreateDefaultSubobject<UHRInteractionComponent>(TEXT("InteractionComp"));

	LockViewComp = CreateDefaultSubobject<UHRLockViewComponent>(TEXT("LockViewComp"));
}

void AHRCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0, Rotation.Yaw, 0);
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AHRCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0, Rotation.Yaw, 0);
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AHRCharacter::TurnRight(float Value)
{
	if (!LockViewComp->bIsLockView)
	{
		AddControllerYawInput(Value);
	}
}

void AHRCharacter::LookUp(float Value)
{
	if (!LockViewComp->bIsLockView)
	{
		AddControllerPitchInput(Value);
	}
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

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, InteractionComp, &UHRInteractionComponent::PrimaryInteract);
	PlayerInputComponent->BindAction("EnemyCheck", IE_Pressed, LockViewComp, &UHRLockViewComponent::LockViewToActor);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AHRCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AHRCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &AHRCharacter::TurnRight);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &AHRCharacter::LookUp);
}

