// Fill out your copyright notice in the Description page of Project Settings.


#include "HRCharacter/HRCharacter.h"
#include "HRCharacter/HRInteractionComponent.h"
#include "HRCharacter/HRLockViewComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet\GameplayStatics.h"
#include "Kismet\KismetMathLibrary.h"
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

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	InteractionComp = CreateDefaultSubobject<UHRInteractionComponent>(TEXT("InteractionComp"));

	LockViewComp = CreateDefaultSubobject<UHRLockViewComponent>(TEXT("LockViewComp"));
	isLockView = false;
	ActorLockTo = nullptr;
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
	if (!isLockView)
	{
		AddControllerYawInput(Value);
	}
}

void AHRCharacter::LookUp(float Value)
{
	if (!isLockView)
	{
		AddControllerPitchInput(Value);
	}
}

void AHRCharacter::LockViewToEnemy()
{
	if (isLockView)
	{
		isLockView = false;
		ActorLockTo = nullptr;
	} 
	else
	{
		ActorLockTo = LockViewComp->EnemyCheck();
		if (ActorLockTo)
		{
			isLockView = true;
		}
	}
}

// Called when the game starts or when spawned
void AHRCharacter::BeginPlay()
{
	Super::BeginPlay();

	ThisPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	ThisPlayerController->PlayerCameraManager->ViewPitchMax = 40;
}

// Called every frame
void AHRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isLockView && ActorLockTo)
	{
		FVector Location = GetActorLocation();
		FVector TargetLotion = ActorLockTo->GetActorLocation();
		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(Location, TargetLotion);
		FRotator SelfRotation = GetControlRotation();
		float tp = TargetRotation.Pitch, ty = TargetRotation.Yaw, sp = SelfRotation.Pitch, sy = SelfRotation.Yaw;
		float PitchRotation = (((tp > sp) ^ (abs(tp - sp) > 180.0f)) ? 1.0f : -1.0f) *
			(abs(tp - sp) > 180.0f ? 360.0f - abs(tp - sp) : abs(tp - sp));
		float YawRotation = (((ty > sy) ^ (abs(ty - sy) > 180.0f)) ? 1.0f : -1.0f) *
			(abs(ty - sy) > 180.0f ? 360.0f - abs(ty - sy) : abs(ty - sy));
		AddControllerPitchInput(-PitchRotation * DeltaTime);
		AddControllerYawInput(YawRotation * DeltaTime);
		UE_LOG(LogTemp, Warning, TEXT ("%f %f"),TargetRotation.Pitch , SelfRotation.Pitch);
	}
}

// Called to bind functionality to input
void AHRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, InteractionComp, &UHRInteractionComponent::PrimaryInteract);
	PlayerInputComponent->BindAction("EnemyCheck", IE_Pressed, this, &AHRCharacter::LockViewToEnemy);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AHRCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AHRCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &AHRCharacter::TurnRight);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &AHRCharacter::LookUp);
}

