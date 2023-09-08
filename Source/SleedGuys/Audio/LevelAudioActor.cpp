#include "LevelAudioActor.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ALevelAudioActor::ALevelAudioActor()
{
	PrimaryActorTick.bCanEverTick = false;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->bIsUISound = false;
	AudioComponent->bAutoActivate = true;
}

void ALevelAudioActor::BeginPlay()
{
	Super::BeginPlay();

	AudioComponent->SetVolumeMultiplier(CustomVolume);

	NumberOfAudios = AudioChoices.Num();

	if (AudioChoices.IsValidIndex(AudioCounter) && AudioChoices[AudioCounter] != nullptr)
	{
		AudioComponent->SetSound(AudioChoices[AudioCounter]);
		AudioComponent->Play();
	}
}

void ALevelAudioActor::ChangeSound()
{	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("receive broadcast"));
	AudioCounter++;
	if (AudioCounter >= NumberOfAudios)
	{
		AudioCounter = 0;
	}
	if (AudioChoices.IsValidIndex(AudioCounter) && AudioChoices[AudioCounter] != nullptr)
	{	
		AudioComponent->Stop();
		AudioComponent->SetSound(AudioChoices[AudioCounter]);
		AudioComponent->Play();
	}
	else if (AudioChoices.IsValidIndex(AudioCounter) && AudioChoices[AudioCounter] == nullptr)
	{
		AudioComponent->Stop();
	}
}

