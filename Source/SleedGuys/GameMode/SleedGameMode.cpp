#include "SleedGameMode.h"
#include "SleedGuys/Character/SleedCharacter.h"
#include "SleedGuys/PlayerController/SleedPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

void ASleedGameMode::PlayerEliminated(ASleedCharacter* ElimmedCharacter, ASleedPlayerController* VictimController)
{
	if (ElimmedCharacter)
	{
		ElimmedCharacter->Elim();
	}
}

void ASleedGameMode::RequestRespawn(ACharacter* ElimmedCharacter, AController* ElimmedController)
{
	if (ElimmedCharacter)
	{
		ElimmedCharacter->Reset();
		ElimmedCharacter->Destroy();
	}
	if (ElimmedController)
	{
		TArray<AActor*> PlayerStarts;
		UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStarts);
		int32 Selection = FMath::RandRange(0, PlayerStarts.Num() - 1);
		RestartPlayerAtPlayerStart(ElimmedController, PlayerStarts[Selection]);
	}
}
