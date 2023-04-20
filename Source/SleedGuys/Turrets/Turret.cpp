// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Components/BoxComponent.h"
#include "SleedGuys/Projectiles/Projectile.h"

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

	Fire(FVector::ZeroVector);
}

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATurret::Fire(const FVector& HitTarget)
{	
	if (ProjectileClass)
	{
		FVector Location = ProjectileSpawnPoint->GetComponentLocation();
		FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();

		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
		Projectile->SetOwner(this);
	}
}

