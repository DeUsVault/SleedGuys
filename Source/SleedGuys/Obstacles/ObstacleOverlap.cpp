// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleOverlap.h"
#include "Components/BoxComponent.h"

AObstacleOverlap::AObstacleOverlap()
{
	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapBox->SetupAttachment(ObstacleMesh);
	OverlapBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	OverlapBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void AObstacleOverlap::BindOverlap()
{
	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &AObstacleOverlap::OnBoxOverlap);
}

void AObstacleOverlap::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("I Do Overlap"));

	Destroy();
}