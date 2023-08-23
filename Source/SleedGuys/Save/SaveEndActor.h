#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SaveEndActor.generated.h"

class UBoxComponent;

UCLASS()
class SLEEDGUYS_API ASaveEndActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASaveEndActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UBoxComponent* OverlapBox;

	UFUNCTION()
	virtual void OnBoxOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

};
