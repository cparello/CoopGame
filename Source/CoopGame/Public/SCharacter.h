// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SHealthComponent.h"
#include "SCharacter.generated.h"

UCLASS()
class COOPGAME_API ASCharacter : public ACharacter
{
GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void BeginCrouch();

	void EndCrouch();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USHealthComponent* HealthComponent;

	bool bWantsToZoom;

	UPROPERTY(EditDefaultsOnly, Category = "Player", meta = (ClampMin = 0.1, ClampMax = 100))
	float ZoomedInterpSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	float ZoomedFOV;

	float DefaultFOV;

	void BeginZoom();

	void EndZoom();

	UPROPERTY(Replicated)
	class ASWeapon* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<ASWeapon> StarterWeaponClass;

	UPROPERTY(VisibleDefaultsOnly, Category = "Player")
	FName WeaponAttachSocketName;

	UFUNCTION()
	void OnHealthChanged(USHealthComponent* OwningHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);


	
public:	
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Player")
	bool bDied;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual FVector GetPawnViewLocation() const override;

	UFUNCTION(BlueprintCallable, Category = "Player")
	void StartFire();

	UFUNCTION(BlueprintCallable, Category = "Player")
	void StopFire();
};
