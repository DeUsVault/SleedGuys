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

	ProjectileSpawnPointLocation = ProjectileSpawnPoint->GetComponentLocation();

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATurret::Fire, FireRate, true);
}

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATurret::Fire()
{	
	if (ProjectileClass)
	{	
		int32 TargetsNum = PossibleTargets.Num();

		if (TargetsNum > 0)
		{
			int32 Selection = FMath::RandRange(0, TargetsNum - 1);
			if (PossibleTargets[Selection])
			{
				AActor* Actor = Cast<AActor>(PossibleTargets[Selection]);
				if (Actor)
				{
					// calculate the rotation our projectile should have, by taking into account the target's location/rotation
					FVector HitTarget = Actor->GetActorLocation();
					FVector ToTarget = HitTarget - ProjectileSpawnPointLocation;
					FRotator TargetRotation = ToTarget.Rotation();

					if (ProjectileClass)
					{
						AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPointLocation, TargetRotation);
						Projectile->SetOwner(this);
					}
				}
			}
		}
	}
}

