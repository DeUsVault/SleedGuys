#include "BoundChecker.h"
#include "Components/BoxComponent.h"
#include "SleedGuys/Character/SleedCharacter.h"

ABoundChecker::ABoundChecker()
{
	PrimaryActorTick.bCanEverTick = false;

	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapBox->SetupAttachment(RootComponent);
	OverlapBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	OverlapBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void ABoundChecker::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		BindOverlap();
	}
}

void ABoundChecker::BindOverlap()
{
	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &ABoundChecker::OnBoxOverlap);
}

void ABoundChecker::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASleedCharacter* SleedCharacter = Cast<ASleedCharacter>(OtherActor);
	if (SleedCharacter)
	{
		SleedCharacter->initFallDeath();
	}
}

