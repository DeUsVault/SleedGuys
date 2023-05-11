// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleMeshOverlap.h"

AObstacleMeshOverlap::AObstacleMeshOverlap()
{
	ObstacleMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ObstacleMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ObstacleMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(ObstacleMesh);
}

void AObstacleMeshOverlap::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("here"));

	BindOverlap();
}

void AObstacleMeshOverlap::BindOverlap()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("there"));
	ObstacleMesh->OnComponentBeginOverlap.AddDynamic(this, &AObstacleMeshOverlap::OnBoxOverlap);
}

void AObstacleMeshOverlap::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Mesh Overlap"));

	//Destroy();
}
