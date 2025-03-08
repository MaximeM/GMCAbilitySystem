// Fill out your copyright notice in the Description page of Project Settings.


#include "Cues/GameCue_Object.h"


UGameCue_Object::UGameCue_Object(const FObjectInitializer& PCIP)
: Super(PCIP)
{

}
void UGameCue_Object::HandleGameCue(AActor* TargetActor)
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

bool UGameCue_Object::ExecuteCue_Implementation(AActor* TargetActor)
{

			UE_LOG(LogTemp, Error, TEXT("CUE EXECUTING"));

	return false;

}

bool UGameCue_Object::HasTag(FGameplayTag Tag)
{
		return Tag == CueTag;
}
