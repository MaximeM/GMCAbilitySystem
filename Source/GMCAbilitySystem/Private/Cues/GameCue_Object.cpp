// Fill out your copyright notice in the Description page of Project Settings.


#include "Cues/GameCue_Object.h"
#include  "../Components/GMCAbilityComponent.h"



UGameCue_Object::UGameCue_Object(const FObjectInitializer& PCIP)
: Super(PCIP)
{
	

}
void UGameCue_Object::HandleGameCue(AActor* TargetActor,float EffectDuration, UGMC_AbilitySystemComponent* ASC, int Effect_ID)

{
	EffectID = Effect_ID;
	if (EffectID ==-1)
	{
		UE_LOG(LogTemp, Error, TEXT("NO Effect ID FOR QUEUE))"));

	}
	
	Duration = EffectDuration;
	if (IsValid(TargetActor))
	{
		K2_HandleGameCue(TargetActor, Duration,ASC);
		ExecuteCue(TargetActor, Duration);

		if (IsValid(ASC))
		{
			ASC->OnEffectChanged.AddDynamic(this, &UGameCue_Object::OnEffectChanged);
		}

		
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("NO TARGET FOR CUE"));
	}


	

	
	
}

void UGameCue_Object::OnEffectChanged(int32 ChangedEffectID, bool bIsEffectActive)
{
	if (ChangedEffectID == EffectID && !bIsEffectActive)
	{
		UE_LOG(LogTemp, Log, TEXT("WE SHOULD REMOVE"));
		OnRemove();

	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Not THis one"));

	}
	
}


bool UGameCue_Object::OnRemove_Implementation()
{
	MarkAsGarbage();
	return true;
}



bool UGameCue_Object::ExecuteCue_Implementation(AActor* TargetActor, float EffectDuration)
{

	Duration = EffectDuration;
	
	if (Duration > 0.0f)
	{
		FTimerHandle TimerHandle;

		// Use a lambda to call OnRemove
		TargetActor->GetWorld()->GetTimerManager().SetTimer(
			TimerHandle,
			[this]()
			{
				this->OnRemove();  // Call OnRemove directly within the lambda
			},
			Duration,
			false
		);
	}
	return true;

}

bool UGameCue_Object::HasTag(FGameplayTag Tag)
{
		return Tag == CueTag;
}
