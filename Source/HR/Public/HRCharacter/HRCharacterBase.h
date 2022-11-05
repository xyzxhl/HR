// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayAbilitySpec.h"
#include "AbilitySystemInterface.h"
#include "HRCharacterBase.generated.h"

UCLASS()
class HR_API AHRCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
    class UHRAbilitySystemComponent* AbilitySystemComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	class UHRAttributeSet* AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	float BaseSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TMap<FString, FGameplayAbilitySpecHandle> AbilityHandles;

public:
	// Sets default values for this character's properties
	AHRCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "AbilitySystem")
	void Die();

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
