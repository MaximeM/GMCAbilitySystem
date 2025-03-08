// Fill out your copyright notice in the Description page of Project Settings.


#include "Cues/GameCue_Actor.h"


/**
* An Instantiated Actor with a tate and ticks if you want
 */
// Sets default values
AGameCue_Actor::AGameCue_Actor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGameCue_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGameCue_Actor::Destroyed()
{
	Super::Destroyed();
}

void AGameCue_Actor::HandleGameCue(AActor* TargetActor)
{
	if (IsValid(TargetActor))
	{
		K2_HandleGameCue(TargetActor);
		ExecuteCue(TargetActor);
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("NO TARGET FOR CUE"))
	}
}

bool AGameCue_Actor::ExecuteCue_Implementation(AActor* TargetActor)
{

	UE_LOG(LogTemp, Error, TEXT("CUE EXECUTING"));

	return false;

}


// Called every frame
void AGameCue_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

