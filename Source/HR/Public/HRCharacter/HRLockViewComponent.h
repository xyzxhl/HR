// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HRLockViewComponent.generated.h"

/** 
 * 用于锁定目标，外部通过控制isLockView控制是否生效
 * 注意：组件BeginPlay函数中，控制了相机旋转范围
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HR_API UHRLockViewComponent : public UActorComponent
{
	GENERATED_BODY()
	
protected:
	/** 拥有者 */
	class APawn* OwnerCharacter;

	/** 拥有者的相机 */
	class APlayerCameraManager* CurrentCamera;

	/** 被锁定者 */
	AActor* ActorLockTo;

	/** 寻找可被锁定的HREnemyPawn */
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
