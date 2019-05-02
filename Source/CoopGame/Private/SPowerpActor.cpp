// Fill out your copyright notice in the Description page of Project Settings.

#include "SPowerpActor.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"


// Sets default values
ASPowerpActor::ASPowerpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PowerupInterval = 0.0f;
	TotalNrOfTicks = 0;
}

void ASPowerpActor::ActivatePowerup()
{
	if(PowerupInterval > 0.0f)
	{
		GetWorldTimerManager().SetTimer(TimerHandle_PowerupTick, this, &ASPowerpActor::OnTickPowerup, PowerupInterval, true, 0.0f);

	}else
	{
		OnTickPowerup();
	}
}

// Called when the game starts or when spawned
void ASPowerpActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASPowerpActor::OnTickPowerup()
{
	TicksProcessed++;

	OnPowerupTicked();

	if(TicksProcessed >= TotalNrOfTicks)
	{
		OnExpired();
		GetWorldTimerManager().ClearTimer(TimerHandle_PowerupTick);
	}
}

