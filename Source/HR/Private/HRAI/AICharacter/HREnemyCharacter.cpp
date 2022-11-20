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
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	AttributeSet = CreateDefaultSubobject<UHRAttributeSet>(TEXT("AttributeSet"));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}


void AHREnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

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

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AHREnemyCharacter::OnPawnSeen);

}


void AHREnemyCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

// When the enemy pawns catch a player in the eyesight, set the TargetActor to it and try to attack.
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


