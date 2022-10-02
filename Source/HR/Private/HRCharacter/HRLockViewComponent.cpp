// Fill out your copyright notice in the Description page of Project Settings.


#include "HRCharacter/HRLockViewComponent.h"
#include "HRCharacter\HRCharacter.h"
#include "HRCreature/HREnemyPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet\GameplayStatics.h"
#include "Kismet\KismetMathLibrary.h"

// Sets default values for this component's properties
UHRLockViewComponent::UHRLockViewComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ActorLockTo = nullptr;
	isLockView = false;
}


// Called when the game starts
void UHRLockViewComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<AHRCharacter>(GetOwner());

	CurrentCamera = UGameplayStatics::GetPlayerController(this, 0)->PlayerCameraManager;
	CurrentCamera->ViewPitchMax = 30.0f;
}


// Called every frame
void UHRLockViewComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (isLockView)
	{
		if (ActorLockTo) {
			FVector Location = CurrentCamera->GetCameraLocation();
			FVector TargetLotion = ActorLockTo->GetActorLocation();

			FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(Location, TargetLotion);
			FRotator SelfRotation = OwnerCharacter->GetControlRotation();

			float tp = TargetRotation.Pitch, ty = TargetRotation.Yaw, sp = SelfRotation.Pitch, sy = SelfRotation.Yaw;

			if (tp > 30.0f) {
				if (OwnerCharacter->CameraBoom->SocketOffset.Z < 200.0f) OwnerCharacter->CameraBoom->SocketOffset.Z += 300.0f * DeltaTime;
				tp = 30.0f;
			}
			if (tp < 0.0f)
				ResetCameraLocation(DeltaTime);

			float PitchRotation = (((tp > sp) ^ (abs(tp - sp) > 180.0f)) ? 1.0f : -1.0f) *
				(abs(tp - sp) > 180.0f ? 360.0f - abs(tp - sp) : abs(tp - sp));
			float YawRotation = (((ty > sy) ^ (abs(ty - sy) > 180.0f)) ? 1.0f : -1.0f) *
				(abs(ty - sy) > 180.0f ? 360.0f - abs(ty - sy) : abs(ty - sy));

			OwnerCharacter->AddControllerPitchInput(-PitchRotation * DeltaTime * 10);
			OwnerCharacter->AddControllerYawInput(YawRotation * DeltaTime * 10);
		}
		else {
			ActorLockTo = EnemyCheck();
			if (!ActorLockTo)
			{
				isLockView = false;
			}
		}
	}
	else
		ResetCameraLocation(DeltaTime);
}

void UHRLockViewComponent::ResetCameraLocation(float DeltaTime)
{
	if (OwnerCharacter->CameraBoom->SocketOffset.Z > 0.1f)
		OwnerCharacter->CameraBoom->SocketOffset.Z -= 300.0f * DeltaTime;
	else
		OwnerCharacter->CameraBoom->SocketOffset.Z = 0.0f;
}

AActor* UHRLockViewComponent::EnemyCheck()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FVector EyeLocation;
	FRotator EyeRotation;
	OwnerCharacter->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * 5000);


	TArray<FHitResult> Hits;

	float Radius = 100.f;

	FCollisionShape Shape;
	Shape.SetSphere(Radius);

	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);

	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.0f, 0, 2.0f);
			if (HitActor->GetClass()->IsChildOf(AHREnemyPawn::StaticClass()))
			{
				DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, LineColor, false, 2.0f);
				return HitActor;
			}
		}
	}

	return nullptr;
}