// Fill out your copyright notice in the Description page of Project Settings.


#include "RopeSwing.h"
#include "SleedGuys/Character/SleedCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "CableComponent.h"


ARopeSwing::ARopeSwing()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);
	SetRootComponent(BaseMesh);

	AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	AreaSphere->SetupAttachment(RootComponent);
	AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RopeSwingWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupWidget"));
	RopeSwingWidget->SetupAttachment(RootComponent);
}

void ARopeSwing::BeginPlay()
{
	Super::BeginPlay();

	// enable collision and response for player's version on server only
	if (HasAuthority())
	{
		AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		AreaSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		AreaSphere->OnComponentBeginOverlap.AddDynamic(this, &ARopeSwing::OnSphereOverlap);
		AreaSphere->OnComponentEndOverlap.AddDynamic(this, &ARopeSwing::OnSphereEndOverlap);
	}

	if (RopeSwingWidget)
	{
		RopeSwingWidget->SetVisibility(false);
	}
}

void ARopeSwing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARopeSwing::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASleedCharacter* SleedCharacter = Cast<ASleedCharacter>(OtherActor);
	if (SleedCharacter)
	{	
		SleedCharacter->SetOverlappingRopeSwing(this);
	}
}

void ARopeSwing::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ASleedCharacter* SleedCharacter = Cast<ASleedCharacter>(OtherActor);
	if (SleedCharacter)
	{
		SleedCharacter->SetOverlappingRopeSwing(nullptr);
	}
}

void ARopeSwing::ShowPickupWidget(bool bShowWidget)
{
	if (RopeSwingWidget)
	{
		RopeSwingWidget->SetVisibility(bShowWidget);
	}
}
