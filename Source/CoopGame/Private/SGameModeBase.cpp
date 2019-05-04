// Fill out your copyright notice in the Description page of Project Settings.

#include "SGameModeBase.h"
#include "TimerManager.h"

ASGameModeBase::ASGameModeBase()
{
	TimeBetweenWaves = 2.0f;
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
	FTimerHandle TimerHandle_NextWaveStart;
	GetWorldTimerManager().SetTimer(TimerHandle_NextWaveStart, this, &ASGameModeBase::StartWave, TimeBetweenWaves, false);

}

void ASGameModeBase::StartPlay()
{
	Super::StartPlay();

	PrepareForNextWave();
}


