// Fill out your copyright notice in the Description page of Project Settings.

#include "SGameModeBase.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "SHealthComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Actor.h"

ASGameModeBase::ASGameModeBase()
{
	TimeBetweenWaves = 2.0f;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1.0f;
}

void ASGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CheckWaveState();
	CheckAnyPlayerAlive();
}

void ASGameModeBase::SpawnBotTimerElapsed()
{
	SpawnNewBot();

	NrOfBotsSpawned--;

	if(NrOfBotsSpawned <= 0)
	{
		EndWave();
	}

}

void ASGameModeBase::StartWave()
{
	WaveCount++;

	NrOfBotsSpawned = 2 * WaveCount;

	GetWorldTimerManager().SetTimer(TimerHandle_BotSpawner, this, &ASGameModeBase::SpawnBotTimerElapsed, 1.0f, true, 0.0f);
}

void ASGameModeBase::EndWave()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_BotSpawner);

	PrepareForNextWave();
}

void ASGameModeBase::PrepareForNextWave()
{
	GetWorldTimerManager().SetTimer(TimerHandle_NextWaveStart, this, &ASGameModeBase::StartWave, TimeBetweenWaves, false);

}

void ASGameModeBase::CheckWaveState()
{
	bool bIsPreparingForWave = GetWorldTimerManager().IsTimerActive(TimerHandle_NextWaveStart);

	if(NrOfBotsSpawned > 0 || bIsPreparingForWave)return;

	bool bIsAnyBotAlive = false;

	for(FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	{
		APawn* TestPawn = It->Get();

		if(TestPawn == nullptr || TestPawn->IsPlayerControlled()) continue;

		USHealthComponent* HealthComp = Cast<USHealthComponent>(TestPawn->GetComponentByClass(USHealthComponent::StaticClass()));
		if(HealthComp && HealthComp->GetHealth() > 0.0f)
		{
			bIsAnyBotAlive = true;
			break;
		}
	}

	if(!bIsAnyBotAlive)
	{
		PrepareForNextWave();
	}
}

void ASGameModeBase::CheckAnyPlayerAlive()
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if(PC && PC->GetPawn())
		{
			APawn* MyPawn = PC->GetPawn();
			USHealthComponent* HealthComp = Cast<USHealthComponent>(MyPawn->GetComponentByClass(USHealthComponent::StaticClass()));

			if (ensure(HealthComp) && HealthComp->GetHealth() > 0.0f) return;

		}
	}

	GameOver();
}

void ASGameModeBase::GameOver()
{
	EndWave();

	UE_LOG(LogTemp, Log, TEXT("Gameover "))

}

void ASGameModeBase::StartPlay()
{
	Super::StartPlay();

	PrepareForNextWave();
}


