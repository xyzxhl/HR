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
	virtual void OnRep_Controller() override;

	UFUNCTION()
	void Die();

	UFUNCTION(BlueprintCallable, Category = "AbilitySystem")
	void AddAbility(TSubclassOf<UGameplayAbility> GameplayAbility, FString Name);

	UFUNCTION(BlueprintCallable, Category = "AbilitySystem")
	void UseAbility(FString Name);
};
