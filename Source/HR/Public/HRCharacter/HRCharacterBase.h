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
 * ��ɫ����
 * ������ASC
 * �ṩ�˼��ء�ж�ء�����GA�ĺ���
 * �����˺���Die����������ֵ����0ʱ����
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

	/** ������� */
	UFUNCTION(BlueprintCallable, Category = "AbilitySystem")
	bool AddAbility(TSubclassOf<UGameplayAbility> GameplayAbility, FString Name);

	/** ȷ�������Ƿ���� */
	UFUNCTION(BlueprintCallable, Category = "AbilitySystem")
	bool FindAbility(FString Name);

	/** ʹ������ */
	UFUNCTION(BlueprintCallable, Category = "AbilitySystem")
	bool UseAbility(FString Name);

	/** ɾ������ */
	UFUNCTION(BlueprintCallable, Category = "AbilitySystem")
	bool DeleteAbility(FString Name);
};
