#include "SaveEndActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SleedGuys/Character/SleedCharacter.h"
#include "SleedGuys/Save/SleedSaveGame.h"
#include "SleedGuys/GameInstance/SleedGameInstance.h"

ASaveEndActor::ASaveEndActor()
{
	PrimaryActorTick.bCanEverTick = false;

	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapBox->SetupAttachment(RootComponent);
	OverlapBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	OverlapBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void ASaveEndActor::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &ASaveEndActor::OnBoxOverlap);
	}
}

void ASaveEndActor::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASleedCharacter* SleedCharacter = Cast<ASleedCharacter>(OtherActor);
	if (SleedCharacter)
	{
		USleedSaveGame* SaveData = SleedCharacter->getDataForSave();
		if (SaveData)
		{	
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::FromInt(SaveData->TimeSpent));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::FromInt(SaveData->Deaths));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::FromInt(SaveData->Coins));

			USleedGameInstance* MyGameInstance = Cast<USleedGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
			if (MyGameInstance)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("YES"));
				MyGameInstance->SaveGameData(FVector::ZeroVector, SaveData->TimeSpent, SaveData->Deaths, SaveData->Coins);
			}
		}
	}
}

