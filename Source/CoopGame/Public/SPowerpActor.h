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
	void OnActivated();

	UFUNCTION(BlueprintImplementableEvent, Category = "powerup")
	void OnExpired();

	UFUNCTION(BlueprintImplementableEvent, Category = "powerup")
	void OnPowerupTicked();

	void ActivatePowerup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "powerups")
	float PowerupInterval;

	UPROPERTY(EditDefaultsOnly, Category = "powerups")
	int32 TotalNrOfTicks;

	FTimerHandle TimerHandle_PowerupTick;

	UFUNCTION()
	void OnTickPowerup();

	int32 TicksProcessed;
};
