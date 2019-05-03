// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPowerpActor.generated.h"

UCLASS()
class COOPGAME_API ASPowerpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPowerpActor();


	UFUNCTION(BlueprintImplementableEvent, Category = "powerup")
	void OnActivated(AActor* ActiveFor);

	UFUNCTION(BlueprintImplementableEvent, Category = "powerup")
	void OnExpired();

	UFUNCTION(BlueprintImplementableEvent, Category = "powerup")
	void OnPowerupTicked();

	void ActivatePowerup(AActor* ActiveFor);

protected:

	UPROPERTY(EditDefaultsOnly, Category = "powerups")
	float PowerupInterval;

	UPROPERTY(EditDefaultsOnly, Category = "powerups")
	int32 TotalNrOfTicks;

	FTimerHandle TimerHandle_PowerupTick;

	UFUNCTION()
	void OnTickPowerup();

	int32 TicksProcessed;

	UPROPERTY(ReplicatedUsing = OnRep_PowerupActive)
	bool bIsPowerupActive;

	UFUNCTION()
	void OnRep_PowerupActive();

	UFUNCTION(BlueprintImplementableEvent, Category = "powerup")
	void OnPowerupStateChanged(bool bNewIsActive);
};
