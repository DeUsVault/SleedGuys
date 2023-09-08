#include "AudioParent.h"

AAudioParent::AAudioParent()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAudioParent::BeginPlay()
{
	Super::BeginPlay();	
}

