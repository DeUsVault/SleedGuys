// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

class UBoxComponent;
class AProjectile;
class AStaticMeshActor;

UCLASS()
class SLEEDGUYS_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	ATurret();
	virtual void Tick(float DeltaTime) override;

	void Fire();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditInstanceOnly)
	TArray<AStaticMeshActor*> PossibleTargets;

private:	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* ProjectileSpawnPoint;

	FTimerHandle FireRateTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Fire Events")
	float FireRate = 2.f;

	FVector ProjectileSpawnPointLocation;

};
