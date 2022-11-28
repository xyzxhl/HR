#include "HRGameModeBase.h"
#include "HRAI/AICharacter/HREnemyCharacter.h"
#include <EngineUtils.h>
#include <AIModule/Classes/EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h>
#include <AIModule/Classes/EnvironmentQuery/EnvQueryManager.h>
#include <AIModule/Classes/EnvironmentQuery/EnvQueryTypes.h>
#include <GameFramework/GameModeBase.h>
#include "HRAbility/HRAbilitySystemComponent.h"
#include <DrawDebugHelpers.h>
#include <Kismet/GameplayStatics.h>
#include "HRState/HRSaveGame.h"
#include "HRCharacter/HRCharacter.h"
#include "HRGameInstance.h"




AHRGameModeBase::AHRGameModeBase()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/HRCharacter/BP_HRCharacter"));
	if (ensure(PlayerPawnBPClass.Class))
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// Enemy spawn interval.
	BasicEnemySpawnTimerInterval = 2.0f;
	UHRGameInstance* GI =Cast<UHRGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GI)
	{
		if (!GI->SlotName.IsEmpty())
		{
			SlotName = GI->SlotName;
		}
		else
		{
			SlotName = "Save01";
		}
	}
	else
	{
		SlotName = "Save01";
	}
}

void AHRGameModeBase::StartPlay()
{
	Super::StartPlay();

	// Continuous timer to spawn in more bots.
	// Actual amount of bots and whether its allowed to spawn logic later in the chain...
	GetWorldTimerManager().SetTimer(TimerHandle_BasicSpawnbots, this, &AHRGameModeBase::BasicSpawnBotTimerElapsed, BasicEnemySpawnTimerInterval, true);
}

void AHRGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

	AHRCharacter* Cha = Cast<AHRCharacter>(NewPlayer->GetPawn());

	if (ensure(Cha))
	{
		Cha->SetActorTransform(CurrentSaveGame->Transform);
	}
}

void AHRGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName,Options,ErrorMessage);

	LoadSaveGame();
}

void AHRGameModeBase::BasicSpawnBotTimerElapsed()
{
	int32 NumofAliveBots = 0;
	for (TActorIterator<AHREnemyCharacter> It(GetWorld()); It; ++It)
	{
		AHREnemyCharacter* Bot = *It;
		UHRAbilitySystemComponent* ASC = Cast<UHRAbilitySystemComponent>(Bot->GetAbilitySystemComponent());
		if (ensure(ASC))
		{
			NumofAliveBots++;
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Found %i enemys"), NumofAliveBots);

	float MaxBotCount = 5.0f;
	if (DifficultyCurve)
	{
		MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}

	if (NumofAliveBots >= MaxBotCount)
	{
		UE_LOG(LogTemp, Log, TEXT("At maximum bot capacity. Skipping bot spawn."));
		return;
	}

	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);
	if (ensure(QueryInstance))
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &AHRGameModeBase::OnQueryCompleted);
	}
}

void AHRGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn bot EQS query failed!"));
		return;
	}

	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

	if (Locations.IsValidIndex(0))
	{
		GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator);

		// Track all the used spawn locations
		DrawDebugSphere(GetWorld(), Locations[0], 50.0f, 20, FColor::Blue, false, 60.0f);
	}
}


void AHRGameModeBase::DamageAll()
{
	for (TActorIterator<AHREnemyCharacter> It(GetWorld()); It; ++It)
	{
		AHREnemyCharacter* Bot = *It;
		UHRAbilitySystemComponent* ASC = Cast<UHRAbilitySystemComponent>(Bot->GetAbilitySystemComponent());
		if (ensure(ASC))
		{
		}
	}
}


void AHRGameModeBase::WriteSaveGame()
{
	AHRCharacter* Cha = Cast<AHRCharacter>(UGameplayStatics::GetActorOfClass(this, AHRCharacter::StaticClass()));

	CurrentSaveGame->Transform = Cha->GetActorTransform();

	UGameplayStatics::SaveGameToSlot(CurrentSaveGame, SlotName, 0);
}

void AHRGameModeBase::LoadSaveGame()
{
	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		CurrentSaveGame = Cast<UHRSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
		if (CurrentSaveGame == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to load SaveGame Data."));
			return;
		}

		UE_LOG(LogTemp, Log, TEXT("Loaded SaveGame Data."));
	}
	else
	{
		CurrentSaveGame = Cast<UHRSaveGame>(UGameplayStatics::CreateSaveGameObject(UHRSaveGame::StaticClass()));
		UE_LOG(LogTemp, Log, TEXT("Created New Savegame Data."))
	}
}

