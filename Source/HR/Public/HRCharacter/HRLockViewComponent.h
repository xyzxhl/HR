// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HRLockViewComponent.generated.h"

/** 
 * ��������Ŀ�꣬�ⲿͨ������isLockView�����Ƿ���Ч
 * ע�⣺���BeginPlay�����У������������ת��Χ
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HR_API UHRLockViewComponent : public UActorComponent
{
	GENERATED_BODY()
	
protected:
	/** ӵ���� */
	class APawn* OwnerCharacter;

	/** ӵ���ߵ���� */
	class APlayerCameraManager* CurrentCamera;

	/** �������� */
	AActor* ActorLockTo;

	/** Ѱ�ҿɱ�������HREnemyPawn */
	AActor* EnemyCheck();

	bool bSetControllerPitch;

public:
	bool bIsLockView;

	void LockViewToActor();

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
