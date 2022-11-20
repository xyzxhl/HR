// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayAbilitySpec.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "AbilitySystemInterface.h"
#include "HRAbility/HRAbilitySystemComponent.h"
#include "HRAbility/HRGameplayAbility.h"
#include <GameplayEffectTypes.h>
#include "HRCharacterBase.generated.h"


/**
 * 角色基类
 * 挂载了ASC
 * 提供了加载、卸载、调用GA的函数
 * 声明了函数Die，会在生命值低于0时调用
 */
UCLASS()
class HR_API AHRCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
    class UHRAbilitySystemComponent* AbilitySystemComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	float BaseSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TMap<FString, FGameplayAbilitySpecHandle> AbilityHandles;

public:
	// Sets default values for this character's properties
	AHRCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
	virtual void PossessedBy(AController* NewController) override;

	/** 添加能力 */
	UFUNCTION(BlueprintCallable, Category = "AbilitySystem")
	bool AddAbility(TSubclassOf<UGameplayAbility> GameplayAbility, FString Name);

	/** 确认能力是否存在 */
	UFUNCTION(BlueprintCallable, Category = "AbilitySystem")
	bool FindAbility(FString Name);

	/** 使用能力 */
	UFUNCTION(BlueprintCallable, Category = "AbilitySystem")
	bool UseAbility(FString Name);

	/** 删除能力 */
	UFUNCTION(BlueprintCallable, Category = "AbilitySystem")
	bool DeleteAbility(FString Name);
};
