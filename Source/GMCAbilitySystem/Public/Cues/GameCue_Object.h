// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "GameCue_Object.generated.h"

/**
* UObject, non instantiated: use it for stuff you want to happen once, no ticking here !
 */
UCLASS(Blueprintable,meta = (ShowWorldContextPin))
class GMCABILITYSYSTEM_API UGameCue_Object : public UObject
{
	GENERATED_UCLASS_BODY()
	virtual void HandleGameCue(AActor* TargetActor);

public:

	UFUNCTION(BlueprintImplementableEvent, Category = "GameCue", DisplayName = "HandleGameCue", meta=(ScriptName = "HandleGamCue"))
	void K2_HandleGameCue(AActor* TargetActor) const;

	
	/** Execute the cue on the target actor. Overridable in Blueprints. */
	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	bool ExecuteCue(AActor* TargetActor);
	

	/** Tag associated with this cue. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameCue")
	FGameplayTag CueTag;

	bool HasTag(FGameplayTag Tag);
};