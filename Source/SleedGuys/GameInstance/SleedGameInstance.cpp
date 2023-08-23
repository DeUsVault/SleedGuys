#include "SleedGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SleedGuys/Save/SleedSaveGame.h"

void USleedGameInstance::Init()
{
	Super::Init();

	GameData = Cast<USleedSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlot, 0));

	if (!GameData)
	{
		// create a new game data
		GameData = Cast<USleedSaveGame>(UGameplayStatics::CreateSaveGameObject(USleedSaveGame::StaticClass()));

		GameData->PlayerLocation = FVector(0, 0, 0);

		UGameplayStatics::SaveGameToSlot(GameData, SaveSlot, 0);
	}
}

void USleedGameInstance::SaveGameData(FVector PlayerLocation, int32 TimeSpent, int32 Deaths, int32 Coins)
{	
	if (GameData)
	{
		GameData->PlayerLocation = PlayerLocation;
		GameData->TimeSpent = TimeSpent;
		GameData->Deaths = Deaths;
		GameData->Coins = Coins;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("JaJAJA"));
		UGameplayStatics::SaveGameToSlot(GameData, SaveSlot, 0);
	}
}

USleedSaveGame* USleedGameInstance::LoadGameData()
{
	if (GameData) return GameData;
	
	return nullptr;
}
