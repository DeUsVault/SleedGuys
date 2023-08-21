// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SleedGuys/Obstacles/Obstacle.h"
#include "SleedGuys/Enums/DamageTypes.h"
#include "MovingObstacleTurret.generated.h"

class USoundCue;

/**
 * 
 */
UCLASS()
class SLEEDGUYS_API AMovingObstacleTurret : public AObstacle
{
	GENERATED_BODY()
	
public:
	AMovingObstacleTurret();

	UFUNCTION(BlueprintCallable, Category = "Turret")
	void ActorOverlap(AActor* Actor);

protected:
	virtual void BeginPlay() override;

private:
	bool bCanApplyDamage = true;

	void ResetDamageCooldown();

	UPROPERTY(EditAnywhere)
	float DamagePerSecond = 5.f;

	UPROPERTY(EditAnywhere)
	float DamageCooldownDuration = 0.1f;

	FTimerHandle DamageCooldownTimerHandle;

	// hit sound
	UPROPERTY(EditAnywhere)
	USoundCue* HitSound;
};
