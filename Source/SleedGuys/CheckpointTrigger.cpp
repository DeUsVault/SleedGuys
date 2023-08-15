#include "CheckpointTrigger.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "SleedGuys/Character/SleedCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/TextRenderComponent.h"

ACheckpointTrigger::ACheckpointTrigger()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	CheckpointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	SetRootComponent(CheckpointMesh);

	CheckpointTriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CheckpointTriggerSphere"));
	CheckpointTriggerSphere->SetupAttachment(RootComponent);
	CheckpointTriggerSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CheckpointTriggerSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CheckpointTriggerSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	CheckpointMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	CheckpointMovementComponent->InitialSpeed = 0.0f;
	CheckpointMovementComponent->MaxSpeed = 2000.0f;
	CheckpointMovementComponent->ProjectileGravityScale = 0.f;
	CheckpointMovementComponent->bRotationFollowsVelocity = false;

	Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));
	Text->SetupAttachment(RootComponent);
}

void ACheckpointTrigger::BeginPlay()
{
	Super::BeginPlay();	


	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimer(
			BindOverlapTimer,
			this,
			&ACheckpointTrigger::BindOverlapTimerFinished,
			BindOverlapTime
		);
	}
}

void ACheckpointTrigger::BindOverlapTimerFinished()
{
	CheckpointTriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &ACheckpointTrigger::OnSphereOverlap);

	GetWorldTimerManager().ClearTimer(BindOverlapTimer);
}

void ACheckpointTrigger::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		ASleedCharacter* SleedCharacter = Cast<ASleedCharacter>(OtherActor);
		if (SleedCharacter)
		{	
			// disable overlap events after first interaction
			CheckpointTriggerSphere->OnComponentBeginOverlap.RemoveDynamic(this, &ACheckpointTrigger::OnSphereOverlap);

			if (CheckpointMovementComponent)
			{	
				CheckpointMovementComponent->Velocity = FVector::ZeroVector;

				FVector NewVelocity = MoveDirection.GetSafeNormal() * DesiredSpeed;
				CheckpointMovementComponent->Velocity = NewVelocity;

				// destroy actor in DestroyTime seconds
				GetWorldTimerManager().SetTimer(
					DestroyTimer,
					this,
					&ACheckpointTrigger::BindDestroyTimerFinished,
					DestroyTime
				);
			}
		}
	}
}

void ACheckpointTrigger::GotHitted(ASleedCharacter* Character)
{
	if (CheckpointPlayerStart)
	{
		if (Character)
		{	
			Character->SetCheckpoint(CheckpointPlayerStart);
			Destroy();
		}
	}
}

void ACheckpointTrigger::BindDestroyTimerFinished()
{	
	GetWorldTimerManager().ClearTimer(DestroyTimer);
	Destroy();
}

void ACheckpointTrigger::Destroyed()
{
	if (DestructionEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			this,
			DestructionEffect,
			GetActorLocation()
		);
	}
}