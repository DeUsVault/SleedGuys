#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AudioParent.generated.h"

DECLARE_MULTICAST_DELEGATE(FSoundChangeDelegate)

UCLASS()
class SLEEDGUYS_API AAudioParent : public AActor
{
	GENERATED_BODY()
	
public:	
	AAudioParent();

	FSoundChangeDelegate SoundChange;

protected:
	virtual void BeginPlay() override;

};
