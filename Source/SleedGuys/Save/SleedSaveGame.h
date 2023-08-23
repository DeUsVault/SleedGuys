#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SleedSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SLEEDGUYS_API USleedSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FVector PlayerLocation;

	UPROPERTY()
	int32 TimeSpent;

	UPROPERTY()
	int32 Deaths;

	UPROPERTY()
	int32 Coins;
	
};
