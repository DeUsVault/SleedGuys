// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "Components/SphereComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"


APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	OverlapSphere->SetupAttachment(RootComponent);
	OverlapSphere->SetSphereRadius(150.f);
	OverlapSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	OverlapSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetupAttachment(OverlapSphere);
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APickup::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{ 
		// we delay the overlap binding because, if it spawns and we are already overlapping it, then pickup is destroyed before it's other functionalities are implemented
		GetWorldTimerManager().SetTimer(
			BindOverlapTimer,
			this,
			&APickup::BindOverlapTimerFinished,
			BindOverlapTime
		);
	}

	StartLocation = GetActorLocation();
}

void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bAllowMovement)
	{
		MoveOnAxis(DeltaTime);
	}
}

void APickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void APickup::BindOverlapTimerFinished()
{
	OverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnSphereOverlap);
}

void APickup::MoveOnAxis(float DeltaTime)
{
	CurrentLocation = GetActorLocation();

	float LocationX = CurrentLocation.X;
	float LocationY = CurrentLocation.Y;
	float LocationZ = CurrentLocation.Z;

	if (bMoveOnX) LocationX = LocationX + (Speed * DeltaTime);
	if (bMoveOnY) LocationY = LocationY + (Speed * DeltaTime);
	if (bMoveOnZ) LocationZ = LocationZ + (Speed * DeltaTime);

	CurrentLocation = FVector(LocationX, LocationY, LocationZ);
	SetActorLocation(CurrentLocation);

	float DistanceMoved = FVector::Dist(StartLocation, CurrentLocation);
	if (DistanceMoved >= Distance)
	{
		Speed = -Speed;
		StartLocation = CurrentLocation;
	}
}

void APickup::Destroyed()
{
	Super::Destroyed();

	if (PickupSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			PickupSound,
			GetActorLocation()
		);
	}
}

