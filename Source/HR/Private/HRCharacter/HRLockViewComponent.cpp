// Fill out your copyright notice in the Description page of Project Settings.


#include "HRCharacter/HRLockViewComponent.h"
#include "HRCharacter\HREnemy.h"
#include "Kismet\GameplayStatics.h"
#include "Kismet\KismetMathLibrary.h"

void UHRLockViewComponent::LockViewToActor()
{
	if (bIsLockView) {
		bIsLockView = false;
		ActorLockTo = nullptr;
	}
	else {
		ActorLockTo = EnemyCheck();
		if (ActorLockTo) {
			bIsLockView = true;
		}
	}
	bSetControllerPitch = false;
}

// Sets default values for this component's properties
UHRLockViewComponent::UHRLockViewComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ActorLockTo = nullptr;
	bIsLockView = false;
	bSetControllerPitch = false;

	MaxDistanceToActor = 3000.0f;
}

// Called when the game starts
void UHRLockViewComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<APawn>(GetOwner());

	CurrentCamera = UGameplayStatics::GetPlayerController(this, 0)->PlayerCameraManager;
	CurrentCamera->ViewPitchMax = 30.0f;
}

// Called every frame
void UHRLockViewComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsLockView)
	{
		if (!ActorLockTo->IsValidLowLevelFast()) {
			LockViewToActor();
			return;
		}

		FVector ActorLocation = OwnerCharacter->GetActorLocation();
		FVector CameraLocation = CurrentCamera->GetCameraLocation();
		FVector TargetLotion = ActorLockTo->GetActorLocation();

		if ((ActorLocation - TargetLotion).Size() > MaxDistanceToActor) {
			LockViewToActor();
			return;
		}

		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(ActorLocation, TargetLotion);
		FRotator CameraTargetRotation = UKismetMathLibrary::FindLookAtRotation(CameraLocation, TargetLotion);
		FRotator SelfRotation = OwnerCharacter->GetControlRotation();

		float tp = CameraTargetRotation.Pitch, ty = TargetRotation.Yaw, sp = SelfRotation.Pitch, sy = SelfRotation.Yaw;

		//����Pitch��ת
		if (!bSetControllerPitch) {
			if (sp < 180.0f || sp > 350.0f) {
				OwnerCharacter->AddControllerPitchInput(DeltaTime * 180.0f);
			}
			else {
				FRotator ControllerPitch(350.0f, sy, 0);

				OwnerCharacter->Controller->SetControlRotation(ControllerPitch);

				bSetControllerPitch = true;
			}
		}
		else {
			CameraTargetRotation = FRotator(tp, 0, 0);
			FRotator DeltaRot(tp * DeltaTime * 8.0f, 0, 0);

			CurrentCamera->ProcessViewRotation(DeltaTime, CameraTargetRotation, DeltaRot);
		}

		//����Yaw��ת
		float YawRotation = (((ty > sy) ^ (abs(ty - sy) > 180.0f)) ? 1.0f : -1.0f) *
			(abs(ty - sy) > 180.0f ? 360.0f - abs(ty - sy) : abs(ty - sy));

		OwnerCharacter->AddControllerYawInput(YawRotation * DeltaTime * 8.0f);
	}
}

AActor* UHRLockViewComponent::EnemyCheck()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

	FVector EyeLocation;
	FRotator EyeRotation;
	OwnerCharacter->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * MaxDistanceToActor);

	TArray<FHitResult> Hits;

	float Radius = 300.0f;

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
			if (HitActor->GetClass()->IsChildOf(AHREnemy::StaticClass()))
			{
				DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, LineColor, false, 2.0f);
				return HitActor;
			}
		}
	}

	return nullptr;
}