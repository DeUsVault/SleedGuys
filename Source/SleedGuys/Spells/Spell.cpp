// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

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

	SpellEffectComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("SpellEffectComponent"));
	SpellEffectComponent->SetupAttachment(RootComponent);
}

void ASpell::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
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
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Spell Timer Finished!"));

	TArray<AActor*> Result;
	GetOverlappingActors(Result);
	if(Result.Num() > 0)
	{
		for (auto Actor : Result)
		{
			if (Actor && Actor->ActorHasTag(FName("SleedCharacter")))
			{
				Actor->Destroy();
			}
		}
	}
	Destroy();
}

void ASpell::setSpellCaster(AActor* Caster)
{
	SpellCaster = Caster;
}
