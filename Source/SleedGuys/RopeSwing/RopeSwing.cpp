// Fill out your copyright notice in the Description page of Project Settings.


#include "RopeSwing.h"
#include "SleedGuys/Character/SleedCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "CableComponent.h"
#include "Net/UnrealNetwork.h"


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
}

void ARopeSwing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARopeSwing::SpawnCable(ASleedCharacter* Character)
{
	Cable = NewObject<UCableComponent>(this);
	if (Cable && Character)
	{
		Cable->RegisterComponent();
		Cable->SetIsReplicated(true);

		FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, false);
		Cable->AttachToComponent(RootComponent, AttachmentRules, NAME_None);

		if (Character)
		{
			Cable->SetAttachEndToComponent(Character->GetMesh(), FName("RightHandSocket"));

			FVector CharacterLocation = Character->GetActorLocation();
			FVector RopeSwingLocation = GetActorLocation();

			float Distance = FVector::Dist(CharacterLocation, RopeSwingLocation);
			Cable->CableLength = Distance;
		}
	}

	if (Character)
	{
		Character->bIsRoping = true;
	}
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
		//SleedCharacter->SetOverlappingRopeSwing(nullptr);
	}
}

void ARopeSwing::ShowPickupWidget(bool bShowWidget)
{
	if (RopeSwingWidget)
	{
		RopeSwingWidget->SetVisibility(bShowWidget);
	}
}
