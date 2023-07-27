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

	RandomFireRate = FMath::FRandRange(FireRateMin, FireRateMax);
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATurret::Fire, RandomFireRate, true);
}

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATurret::Fire()
{	
	// check if ProjectileClasses array has elements and pick one at random
	int32 ProjectilesNum = ProjectileClasses.Num();
	if (ProjectilesNum > 0)
	{	
		int32 ProjectileSelection = FMath::RandRange(0, ProjectilesNum - 1);
		if (ProjectileClasses[ProjectileSelection])
		{	
			// check if PossibleTargets array has elements and pick one at random
			int32 TargetsNum = PossibleTargets.Num();
			if (TargetsNum > 0)
			{
				int32 Selection = FMath::RandRange(0, TargetsNum - 1);
				if (PossibleTargets[Selection])
				{
					AActor* Actor = Cast<AActor>(PossibleTargets[Selection]);
					if (Actor)
					{
						FVector HitTarget = Actor->GetActorLocation();
						if (bUseRandomOffset)
						{
							FVector RandomOffsetVector = FVector(
								FMath::FRandRange(-RandomHitTargetOffset, RandomHitTargetOffset),
								FMath::FRandRange(-RandomHitTargetOffset, RandomHitTargetOffset),
								FMath::FRandRange(-RandomHitTargetOffset, RandomHitTargetOffset)
							);
							HitTarget += RandomOffsetVector;
						}

						// calculate the rotation our projectile should have, by taking into account the target's location/rotation
						FVector ToTarget = HitTarget - ProjectileSpawnPointLocation;
						FRotator TargetRotation = ToTarget.Rotation();

						if (ProjectileClasses[ProjectileSelection])
						{
							AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClasses[ProjectileSelection], ProjectileSpawnPointLocation, TargetRotation);
							Projectile->SetOwner(this);
						}
					}
				}
			}
		}
	}

	RandomFireRate = FMath::FRandRange(FireRateMin, FireRateMax);
}

