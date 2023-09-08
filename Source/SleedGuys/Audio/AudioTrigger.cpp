#include "AudioTrigger.h"
#include "LevelAudioActor.h"

AAudioTrigger::AAudioTrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	AudioSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("AudioSceneComponent"));
	SetRootComponent(AudioSceneComponent);
}

void AAudioTrigger::BeginPlay()
{
	Super::BeginPlay();
}

void AAudioTrigger::ChangeSoundTrigger()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("broadcast"));

	if (LevelAudioActor)
	{
		LevelAudioActor->ChangeSound();
	}
}
