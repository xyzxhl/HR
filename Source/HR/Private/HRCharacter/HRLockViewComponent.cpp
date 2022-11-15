// Fill out your copyright notice in the Description page of Project Settings.


#include "HRCharacter/HRLockViewComponent.h"
#include "Kismet\GameplayStatics.h"
#include "Kismet\KismetMathLibrary.h"
#include "HRAI/AICharacter/HREnemyCharacter.h"


static TAutoConsoleVariable<bool> CVarDrawDebugger(TEXT("hr.DrawDebugger"), false, TEXT("�Ƿ���ʾ���Թ���"), ECVF_Cheat);

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


UHRLockViewComponent::UHRLockViewComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	ActorLockTo = nullptr;
	bIsLockView = false;
	bSetControllerPitch = false;

	MaxDistanceToActor = 3000.0f;
}


void UHRLockViewComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<APawn>(GetOwner());

	CurrentCamera = UGameplayStatics::GetPlayerController(this, 0)->PlayerCameraManager;
	CurrentCamera->ViewPitchMax = 30.0f;
}


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
	bool bDrawDebug = CVarDrawDebugger.GetValueOnGameThread();

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
			if (bDrawDebug)
			{
				DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.0f, 0, 2.0f);
			}
			if (HitActor->GetClass()->IsChildOf(AHREnemyCharacter::StaticClass()))
			{

				if (bDrawDebug)
				{
					DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, LineColor, false, 2.0f);
				}

				return HitActor;
			}
		}
	}

	return nullptr;
}