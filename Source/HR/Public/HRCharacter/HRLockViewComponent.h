// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HRLockViewComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HR_API UHRLockViewComponent : public UActorComponent
{
	GENERATED_BODY()
	
protected:
	class AHRCharacter* OwnerCharacter;
	
	class APlayerCameraManager* CurrentCamera;

	AActor* ActorLockTo;

	void ResetCameraLocation(float DeltaTime);
	AActor* EnemyCheck();

public:
	bool isLockView;

public:	
	// Sets default values for this component's properties
	UHRLockViewComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
