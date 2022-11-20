// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HRCharacter/HRCharacterBase.h"
#include <GameplayEffectTypes.h>
#include "HREnemyCharacter.generated.h"

class UPawnSensingComponent;
class UHRWorldUserWidget;
class UUserWidget;
class UHRAttributeSet;

UCLASS()
class HR_API AHREnemyCharacter : public AHRCharacterBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UHRAttributeSet* AttributeSet;

public:
	AHREnemyCharacter();

protected:

	UHRWorldUserWidget* ActiveHealthBar;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName TimeToHit;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> HealthBarWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
	void Die();

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UAbilitySystemComponent* OwnerComp, float NewValue);

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	virtual void Tick(float DeltaSeconds) override;

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;
};
