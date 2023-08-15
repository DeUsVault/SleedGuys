// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleMeshOverlap.h"

AObstacleMeshOverlap::AObstacleMeshOverlap()
{
	OverlapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	OverlapMesh->SetupAttachment(ObstacleMesh);
	OverlapMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	OverlapMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	OverlapMesh->SetVisibility(false);
}

void AObstacleMeshOverlap::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		BindOverlap();
	}
}

void AObstacleMeshOverlap::BindOverlap()
{	
	OverlapMesh->OnComponentBeginOverlap.AddDynamic(this, &AObstacleMeshOverlap::OnMeshOverlap);
	OverlapMesh->OnComponentEndOverlap.AddDynamic(this, &AObstacleMeshOverlap::OnMeshEndOverlap);
}

void AObstacleMeshOverlap::OnMeshOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AObstacleMeshOverlap::OnMeshEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
