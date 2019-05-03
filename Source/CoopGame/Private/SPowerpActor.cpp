// Fill out your copyright notice in the Description page of Project Settings.

#include "SPowerpActor.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "UnrealNetwork.h"


// Sets default values
ASPowerpActor::ASPowerpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PowerupInterval = 0.0f;
	TotalNrOfTicks = 0;

	bIsPowerupActive = false;

	SetReplicates(true);
}

void ASPowerpActor::ActivatePowerup(AActor* ActiveFor)
{
	OnActivated(ActiveFor);

	bIsPowerupActive = true;
	OnRep_PowerupActive();

	if(PowerupInterval > 0.0f)
	{
		GetWorldTimerManager().SetTimer(TimerHandle_PowerupTick, this, &ASPowerpActor::OnTickPowerup, PowerupInterval, true);

	}else
	{
		OnTickPowerup();
	}
}

void ASPowerpActor::OnTickPowerup()
{
	TicksProcessed++;

	OnPowerupTicked();

	if(TicksProcessed >= TotalNrOfTicks)
	{
		OnExpired();

		bIsPowerupActive = false;
		OnRep_PowerupActive();

		GetWorldTimerManager().ClearTimer(TimerHandle_PowerupTick);
	}
}

void ASPowerpActor::OnRep_PowerupActive()
{
	OnPowerupStateChanged(bIsPowerupActive);
}

void ASPowerpActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASPowerpActor, bIsPowerupActive);
}

