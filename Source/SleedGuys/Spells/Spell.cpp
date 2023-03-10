// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell.h"
#include "Components/SphereComponent.h"

ASpell::ASpell()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	OverlapSphere->SetupAttachment(RootComponent);
	OverlapSphere->SetSphereRadius(SpellSphereRadius);
	OverlapSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	OverlapSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void ASpell::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		// we delay the overlap binding because, if it spawns and we are already overlapping it, then pickup is destroyed before it's other functionalities are implemented
		GetWorldTimerManager().SetTimer(
			BindSpellTimer,
			this,
			&ASpell::BindSpellTimerFinished,
			BindSpellTime
		);
	}
}

void ASpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpell::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void ASpell::BindSpellTimerFinished()
{
	OverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &ASpell::OnSphereOverlap);
}

void ASpell::setSpellCaster(AActor* Caster)
{
	SpellCaster = Caster;
}
