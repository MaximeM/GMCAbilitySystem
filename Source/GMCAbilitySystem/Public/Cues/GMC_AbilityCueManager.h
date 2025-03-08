// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameCue_Object.h"
#include "GameCue_Actor.h"
#include "AssetRegistry/AssetData.h"
#include "UObject/Object.h"
#include "AssetRegistry/AssetRegistryModule.h"

#include "GMC_AbilityCueManager.generated.h"

/**
 * 
 */
UCLASS()
class GMCABILITYSYSTEM_API UGMC_AbilityCueManager : public UDataAsset
{
	GENERATED_BODY()


	public:
	UGMC_AbilityCueManager();

	UFUNCTION()
	void OnInit();

	UPROPERTY(EditAnywhere)
	TArray<FGameplayTag> RegisteredGameCues;

	UFUNCTION(BlueprintCallable, Category = "GameCue")
	UClass* LoadCueReference(FGameplayTag Tag);


	void LoadGameCueObjectsFromPath(const FString& Path);
	void LoadGameCueActorsFromPath(const FString& Path);

private:
	

	UPROPERTY()
	TMap<FGameplayTag, TSoftClassPtr<UGameCue_Object>> GameCuesObjectCollection;
	TMap<FGameplayTag, TSoftClassPtr<AGameCue_Actor>> GameCueActorCollection;

};
