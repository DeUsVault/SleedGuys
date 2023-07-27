#include "ObstacleSphereOverlap.h"
#include "Components/SphereComponent.h"

AObstacleSphereOverlap::AObstacleSphereOverlap()
{
	AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	AreaSphere->SetupAttachment(ObstacleMesh);
	AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AObstacleSphereOverlap::BeginPlay()
{
	Super::BeginPlay();

	// enable collision and response for player's version on server only
	if (HasAuthority())
	{
		AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		AreaSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		AreaSphere->OnComponentBeginOverlap.AddDynamic(this, &AObstacleSphereOverlap::OnSphereOverlap);
		AreaSphere->OnComponentEndOverlap.AddDynamic(this, &AObstacleSphereOverlap::OnSphereEndOverlap);
	}	
}

void AObstacleSphereOverlap::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("start"));
}

void AObstacleSphereOverlap::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("end"));
}

