// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleDoubleOverlap.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SleedGuys/Character/SleedCharacter.h"

AObstacleDoubleOverlap::AObstacleDoubleOverlap()
{	
	SecondObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecondObstacleMesh"));
	SecondObstacleMesh->SetupAttachment(RootComponent);

	SecondOverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SecondOverlapBox"));
	SecondOverlapBox->SetupAttachment(SecondObstacleMesh);
	SecondOverlapBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SecondOverlapBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SecondOverlapBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void AObstacleDoubleOverlap::BeginPlay()
{
	Super::BeginPlay();

	BindOverlap();
}

void AObstacleDoubleOverlap::BindOverlap()
{
	Super::BindOverlap();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("second bind"));
	SecondOverlapBox->OnComponentBeginOverlap.AddDynamic(this, &AObstacleDoubleOverlap::OnSecondBoxOverlap);
}

void AObstacleDoubleOverlap::OnSecondBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("I second override"));

	HandleCharacterOverlap(OtherActor, SweepResult);
}

void AObstacleDoubleOverlap::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("I first override"));

	HandleCharacterOverlap(OtherActor, SweepResult);
}

void AObstacleDoubleOverlap::HandleCharacterOverlap(AActor* OtherActor, const FHitResult& SweepResult)
{	
	if (!HasAuthority()) return; // we want damage to apply on the server only and replicate on the client

	ASleedCharacter* SleedCharacter = Cast<ASleedCharacter>(OtherActor);
	if (SleedCharacter)
	{	
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("hit oneshot"));
		float OneshotDamageNeeded = SleedCharacter->GetHealth();
		UGameplayStatics::ApplyDamage(SleedCharacter, OneshotDamageNeeded, nullptr, this, UDamageType::StaticClass());
	}
}
