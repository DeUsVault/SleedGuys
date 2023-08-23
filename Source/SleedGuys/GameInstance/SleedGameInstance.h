#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SleedGameInstance.generated.h"

class USleedSaveGame;

/**
 * 
 */
UCLASS()
class SLEEDGUYS_API USleedGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	void Init() override;

	FString SaveSlot = "DefaultSlot";

	UPROPERTY()
	USleedSaveGame* GameData;

	void SaveGameData(FVector PlayerLocation, int32 TimeSpent, int32 Deaths, int32 Coins);
	USleedSaveGame* LoadGameData();
	
};
