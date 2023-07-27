// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "SleedGuys/Character/SleedCharacter.h"
#include "NiagaraComponent.h"

ACoin::ACoin()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	CoinVisual = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara Effect"));
	CoinVisual->SetupAttachment(RootComponent);
}

void ACoin::BeginPlay()
{
	Super::BeginPlay();	
}

void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACoin::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	ASleedCharacter* SleedCharacter = Cast<ASleedCharacter>(OtherActor);
	if (SleedCharacter)
	{
		SleedCharacter->AddGold(CoinValue);
	}

	Destroy();
}

