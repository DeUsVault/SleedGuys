// Fill out your copyright notice in the Description page of Project Settings.

#include "ObstacleSlide.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "SleedGuys/Character/SleedCharacter.h"

AObstacleSlide::AObstacleSlide()
{
	IceVisual = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara Effect"));
	IceVisual->SetupAttachment(RootComponent);
}

void AObstacleSlide::BeginPlay()
{
	Super::BeginPlay();
}

void AObstacleSlide::OnMeshOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("slide start"));
	ASleedCharacter* SleedCharacter = Cast<ASleedCharacter>(OtherActor);
	if (SleedCharacter)
	{	
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("1"));
		SleedCharacter->setIsSliding(true);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("2"));
	}
}

void AObstacleSlide::OnMeshEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("slide end"));
	ASleedCharacter* SleedCharacter = Cast<ASleedCharacter>(OtherActor);
	if (SleedCharacter)
	{
		SleedCharacter->setIsSliding(false);
	}
}