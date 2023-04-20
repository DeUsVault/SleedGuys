// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

class UBoxComponent;

UCLASS()
class SLEEDGUYS_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	ATurret();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* ProjectileSpawnPoint;

};
