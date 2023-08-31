#include "LevelAudioActor.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ALevelAudioActor::ALevelAudioActor()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	AudioSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("AudioSceneComponent"));
	SetRootComponent(AudioSceneComponent);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->bIsUISound = false;
	AudioComponent->bAutoActivate = true;
}

void ALevelAudioActor::BeginPlay()
{
	Super::BeginPlay();

	NumberOfAudios = AudioChoices.Num();

	if (AudioChoices.IsValidIndex(AudioCounter) && AudioChoices[AudioCounter] != nullptr)
	{
		AudioComponent->SetSound(AudioChoices[AudioCounter]);
		AudioComponent->Play();
	}
}

void ALevelAudioActor::ChangeSound()
{	
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

