#include "HRGameModeBase.h"
#include "HRAI/AICharacter/HREnemyCharacter.h"
#include <EngineUtils.h>
#include <AIModule/Classes/EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h>
#include <AIModule/Classes/EnvironmentQuery/EnvQueryManager.h>
#include <AIModule/Classes/EnvironmentQuery/EnvQueryTypes.h>
#include <GameFramework/GameModeBase.h>
#include "HRAbility/HRAbilitySystemComponent.h"
#include <DrawDebugHelpers.h>
#include "HRCharacter/HRCharacter.h"
#include <Kismet/GameplayStatics.h>
#include "HRGameInstance.h"
#include "HRCharacter/HRSaveGame.h"




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
}

void AHRGameModeBase::StartPlay()
{
	Super::StartPlay();

	/* 设置循环定时器，用以生成敌人 */
	GetWorldTimerManager().SetTimer(TimerHandle_BasicSpawnbots, this, &AHRGameModeBase::BasicSpawnBotTimerElapsed, BasicEnemySpawnTimerInterval, true);
}


void AHRGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);


	/* 用存档中的内容初始化游戏数据。自动读取自动存档内容。若自动存档为空，则创建新存档。 */
	UHRGameInstance* GI = Cast<UHRGameInstance>(GetGameInstance());

	if (ensure(GI))
	{
		if (!(GI->SlotName.IsEmpty()))
		{
			SlotName = GI->SlotName;
		}
		else
		{
			SlotName = "Save01";
		}
	}

	LoadSaveGame();
}


void AHRGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

	/* 初始化新玩家 */
	AHRCharacter* HRChar = Cast<AHRCharacter>(NewPlayer->GetPawn());
	if (HRChar)
	{
		HRChar->LoadCharacter(CurrentSaveGame);
	}
}


void AHRGameModeBase::WriteSaveGame(FString NameofSlot)
{

	/* 没用的废物。本意是用这个来写存档，但一旦在蓝图中调用这个函数UE编辑器就会崩溃 */
	AHRCharacter* HRChar = Cast<AHRCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (HRChar)
	{
		HRChar->SaveCharacter(CurrentSaveGame);
	}

	UGameplayStatics::SaveGameToSlot(CurrentSaveGame, NameofSlot, 0);
}


void AHRGameModeBase::LoadSaveGame()
{

	/* 读取存档 */
	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		UE_LOG(LogTemp, Log, TEXT("Load game from slot."));
		CurrentSaveGame = Cast<UHRSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
	}
	/* 存档为空，开始新游戏 */
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Create new game."));
		CurrentSaveGame = Cast<UHRSaveGame>(UGameplayStatics::CreateSaveGameObject(UHRSaveGame::StaticClass()));
	}
}


void AHRGameModeBase::BasicSpawnBotTimerElapsed()
{
	/* 给当前世界中存活的敌人计数 */
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

	/* 用曲线给最大敌人数赋值，当存活敌人数量大于最大值则停止生成 */
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

	/* 敌人数量正确，开始运行EQS生成敌人 */
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

	/* 在玩家附近生成敌人，详见蓝图 */
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
	/* 后期开发可能用到的Debug道具 */
	for (TActorIterator<AHREnemyCharacter> It(GetWorld()); It; ++It)
	{
		AHREnemyCharacter* Bot = *It;
		UHRAbilitySystemComponent* ASC = Cast<UHRAbilitySystemComponent>(Bot->GetAbilitySystemComponent());
		if (ensure(ASC))
		{
		}
	}
}

