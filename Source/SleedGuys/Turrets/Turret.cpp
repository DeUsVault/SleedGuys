// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Components/BoxComponent.h"

ATurret::ATurret()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	SetRootComponent(TurretMesh);

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxComp->SetupAttachment(TurretMesh);

	// create the projectile spawn point
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();	
}

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

