// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCommit.h"

// Sets default values
ATestCommit::ATestCommit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));
	RootComponent = MeshComp;

}

// Called when the game starts or when spawned
void ATestCommit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestCommit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

