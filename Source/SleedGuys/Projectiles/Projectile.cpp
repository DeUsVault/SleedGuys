// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "SleedGuys/Character/SleedCharacter.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	SetRootComponent(ProjectileMesh);

	OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	OverlapSphere->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->InitialSpeed = InitMoveSpeed;
	ProjectileMovementComponent->MaxSpeed = MaxMoveSpeed;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	OverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnSphereOverlap);
	//ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

}

void AProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	float Speed = this->GetVelocity().Size();
	if (Speed <= MinVelocityTrigger)
	{
		// disable overlap events if speed is too low
		OverlapSphere->OnComponentBeginOverlap.RemoveDynamic(this, &AProjectile::OnSphereOverlap);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(Speed));
		return;
	}

	if (OtherActor)
	{
		ASleedCharacter* HittedCharacter = Cast<ASleedCharacter>(OtherActor);
		if (HittedCharacter)
		{
			FVector impactPoint = GetActorLocation();
			FVector forceDirection = HittedCharacter->GetActorLocation() - impactPoint;
			forceDirection.Normalize();

			FVector LaunchPower = FVector(forceDirection.X * ForcePower, forceDirection.Y * ForcePower, 0.f);

			HittedCharacter->ChangeAirFrictionAndLunch(LaunchPower);

			// disable overlap events, we want the projectile to interact only one time
			OverlapSphere->OnComponentBeginOverlap.RemoveDynamic(this, &AProjectile::OnSphereOverlap);
		}
	}
}

