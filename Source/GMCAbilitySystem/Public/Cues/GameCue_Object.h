// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

#include "UObject/Object.h"
#include "GameCue_Object.generated.h"


class UGMC_AbilitySystemComponent;
/**
* UObject, non instantiated: use it for stuff you want to happen once, no ticking here !
 */
UCLASS(Blueprintable,meta = (ShowWorldContextPin))
class GMCABILITYSYSTEM_API UGameCue_Object : public UObject
{
	GENERATED_UCLASS_BODY()
	virtual void HandleGameCue(AActor* TargetActor,float EffectDuration,UGMC_AbilitySystemComponent* ASC, int Effect_ID = -1);

public:

	UFUNCTION(BlueprintImplementableEvent, Category = "GameCue", DisplayName = "HandleGameCue", meta=(ScriptName = "HandleGameCue"))
	void K2_HandleGameCue(AActor* TargetActor,float EffectDuration,UGMC_AbilitySystemComponent* ASC); 

	UPROPERTY(BlueprintReadOnly, Category="GameCue")
	int EffectID = -1;

	UPROPERTY(BlueprintReadOnly, Category="GameCue")
	float Duration;

	UFUNCTION()
	void OnEffectChanged(int32 ChangedEffectID, bool bIsEffectActive);

	/** Execute the cue on the target actor. Overridable in Blueprints. */
	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	bool ExecuteCue(AActor* TargetActor, float EffectDuration);

	
	UFUNCTION(BlueprintNativeEvent,BlueprintPure)
	bool OnRemove();

	/** Tag associated with this cue. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameCue")
	FGameplayTag CueTag;

	bool HasTag(FGameplayTag Tag);
};