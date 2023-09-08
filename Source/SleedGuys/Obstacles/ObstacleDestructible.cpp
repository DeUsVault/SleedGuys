// Fill out your copyright notice in the Description page of Project Settings.
#include "ObstacleDestructible.h"
#include "Components/SphereComponent.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "SleedGuys/Character/SleedCharacter.h"

AObstacleDestructible::AObstacleDestructible()
{	
	GeometryCollection = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("GeometryCollection"));
	GeometryCollection->SetupAttachment(RootComponent);
	GeometryCollection->SetGenerateOverlapEvents(true);
	GeometryCollection->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GeometryCollection->SetSimulatePhysics(false);

	AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	AreaSphere->SetupAttachment(GeometryCollection);
	AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AObstacleDestructible::BindOverlap()
{
	if (HasAuthority())
	{	
		AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		AreaSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		AreaSphere->OnComponentBeginOverlap.AddDynamic(this, &AObstacleDestructible::OnSphereOverlap);
	}
}

void AObstacleDestructible::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	ASleedCharacter* SleedCharacter = Cast<ASleedCharacter>(OtherActor);
	if (SleedCharacter)
	{	
		this->SetActorTickEnabled(false); // stop tick functionality
		ObstacleMesh->DestroyComponent();
		CreateFields(SweepResult.ImpactPoint);

		GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &AObstacleDestructible::HandleDestruction, DestroyTimer, false);
	}
}

void AObstacleDestructible::HandleDestruction()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("destruct overlap"));
	Destroy();
}
