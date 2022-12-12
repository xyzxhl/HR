// Fill out your copyright notice in the Description page of Project Settings.


#include "HRAI/AICharacter/HREnemyCharacter.h"
#include "HRAbility/HRAttributeSet.h"
#include <AIModule/Classes/AIController.h>
#include <AIModule/Classes/BehaviorTree/BlackboardComponent.h>
#include <AIModule/Classes/Perception/PawnSensingComponent.h>
#include <DrawDebugHelpers.h>
#include "Miscellaneous/HRWorldUserWidget.h"
#include "BrainComponent.h"
#include <GameFramework/Character.h>
#include "Components/CapsuleComponent.h"
#include "GameplayEffectTypes.h"

AHREnemyCharacter::AHREnemyCharacter()
{
	/* 给敌人角色赋予AI控制器，属性集和玩家感知系统 */
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	AttributeSet = CreateDefaultSubobject<UHRAttributeSet>(TEXT("AttributeSet"));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}


void AHREnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	/* 创建血条组件 */
	if (ActiveHealthBar == nullptr)
	{
		ActiveHealthBar = CreateWidget<UHRWorldUserWidget>(GetWorld(), HealthBarWidgetClass);
		if (ActiveHealthBar)
		{
			ActiveHealthBar->ActorToAttach = this;
			ActiveHealthBar->AddToViewport();
		}
	}
}

void AHREnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	/* 给感知组件增加委托：一旦视野中发现敌人，则执行OnPawnSeen函数 */
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AHREnemyCharacter::OnPawnSeen);
}


void AHREnemyCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

// When the enemy pawns catch a player in the eyesight, set the TargetActor to it and try to attack.
/* 当敌人发现一个玩家，将行为树中的TargetActor设为他并尝试去攻击 */
void AHREnemyCharacter::OnPawnSeen(APawn* Pawn)
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if (ensure(AIController))
	{
		UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();

		BlackboardComponent->SetValueAsObject("TargetActor", Pawn);

		DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER SPOTTED", nullptr, FColor::White, 4.0f, true);
	}
}


void AHREnemyCharacter::OnHealthChanged(AActor* InstigatorActor, UAbilitySystemComponent* OwnerComp, float NewValue)
{
	// If health is lower than zero, trigger die event.
	if (NewValue <= 0.f)
	{
		Die();
	}
}


void AHREnemyCharacter::Die()
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if (ensure(AIController))
	{
		// Stop behavior tree
		AIController->GetBrainComponent()->StopLogic("Killed");

	}

	// Ragdoll
	GetMesh()->SetCollisionProfileName("Ragdoll");
	GetMesh()->SetAllBodiesSimulatePhysics(true);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->DisableMovement();

	// Clean up
	SetLifeSpan(5.0f);
}


