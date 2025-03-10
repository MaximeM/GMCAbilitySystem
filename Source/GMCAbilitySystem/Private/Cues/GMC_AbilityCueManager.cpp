// Fill out your copyright notice in the Description page of Project Settings.


#include "Cues/GMC_AbilityCueManager.h"
#include "GameplayTagContainer.h"
#include "Cues/GameCue_Object.h"
#include "Engine/World.h"
#include "Animation/AnimMontage.h"
#include "Engine/ObjectLibrary.h"






UGMC_AbilityCueManager::UGMC_AbilityCueManager()
{
}

void UGMC_AbilityCueManager::OnInit()
{
	// Specify the path where game cues are located
	FString GameCuesPath = TEXT("/Game/GameCues");



		LoadGameCueObjectsFromPath(GameCuesPath);
		LoadGameCueActorsFromPath(GameCuesPath);

}



UClass* UGMC_AbilityCueManager::LoadCueReference(FGameplayTag Tag)
{
    // Try to find the tag in the GameCuesObjectCollection
    TSoftClassPtr<UGameCue_Object>* SoftClassPtr = GameCuesObjectCollection.Find(Tag);

    if (SoftClassPtr != nullptr)
    {
        // Load class from the GameCuesObjectCollection
        if (!SoftClassPtr->IsValid())
        {
            UE_LOG(LogTemp, Log, TEXT("Loading class for cue with tag: %s"), *Tag.ToString());
            SoftClassPtr->LoadSynchronous();  // Load the class synchronously
        }

        UClass* CueClass = SoftClassPtr->Get();
        if (CueClass != nullptr)
        {
            // Check if the class is derived from AGameCue_Actor
            if (CueClass->IsChildOf(AGameCue_Actor::StaticClass()))
            {
                UE_LOG(LogTemp, Log, TEXT("Loaded class is AGameCue_Actor for tag: %s"), *Tag.ToString());
                return AGameCue_Actor::StaticClass();  // Return AGameCue_Actor class
            }
            return CueClass;
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to load class for cue with tag: %s"), *Tag.ToString());
            return nullptr;
        }
    }

    // If not found in GameCuesObjectCollection, try GameCueActorCollection
    TSoftClassPtr<AGameCue_Actor>* ActorClassPtr = GameCueActorCollection.Find(Tag);

    if (ActorClassPtr != nullptr)
    {
        // Load class from the GameCueActorCollection
        if (!ActorClassPtr->IsValid())
        {
            UE_LOG(LogTemp, Log, TEXT("Loading actor class for cue with tag: %s"), *Tag.ToString());
            ActorClassPtr->LoadSynchronous();  // Load the class synchronously
        }

        UClass* ActorClass = ActorClassPtr->Get();
        if (ActorClass != nullptr)
        {
            UE_LOG(LogTemp, Log, TEXT("Loaded actor class for tag: %s"), *Tag.ToString());
            return ActorClass;  // Return the class directly
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to load actor class for cue with tag: %s"), *Tag.ToString());
            return nullptr;
        }
    }

    // If the tag is not found in either collection
    UE_LOG(LogTemp, Warning, TEXT("Cue class not found for tag: %s"), *Tag.ToString());
    return nullptr;
}




void UGMC_AbilityCueManager::LoadGameCueObjectsFromPath(const FString& Path)
{
	// Create an object library for UGameCue
	UObjectLibrary* ObjectLibrary = UObjectLibrary::CreateLibrary(UGameCue_Object::StaticClass(), true, GIsEditor && !IsRunningCommandlet());

	if (!ObjectLibrary)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create UObjectLibrary for GameCue"));
		return;
	}

	// Load the assets from the specified path into the object library
	ObjectLibrary->AddToRoot();  // Ensure it stays in memory while loading


	ObjectLibrary->LoadBlueprintAssetDataFromPaths({Path},true);
	TArray<FAssetData> CueData;
	ObjectLibrary->GetAssetDataList(CueData);
	for (const FAssetData& AssetData : CueData)
	{
		// Check if the asset is a Blueprint
		if (AssetData.GetClass() == UBlueprint::StaticClass())
		{
			// Load the blueprint object
			UBlueprint* LoadedBlueprint = Cast<UBlueprint>(AssetData.GetAsset());
			if (LoadedBlueprint && LoadedBlueprint->GeneratedClass)
			{
				// Check if the generated class is a subclass of UGameCue
				if (LoadedBlueprint->GeneratedClass->IsChildOf(UGameCue_Object::StaticClass()))
				{
					// Instantiate the GameCue class from the Blueprint
					UGameCue_Object* GameCue = NewObject<UGameCue_Object>(this, LoadedBlueprint->GeneratedClass);
					if (GameCue)
					{
						UE_LOG(LogTemp, Log, TEXT("Successfully loaded and instantiated: %s"), *LoadedBlueprint->GetName());
						GameCuesObjectCollection.Add(GameCue->CueTag, GameCue->GetClass());
					}
					else
					{
						UE_LOG(LogTemp, Error, TEXT("Failed to instantiate UGameCue from blueprint: %s"), *LoadedBlueprint->GetName());
					}
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Blueprint does not subclass UGameCue: %s"), *LoadedBlueprint->GetName());
				}
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to load blueprint or its generated class: %s"), *AssetData.AssetName.ToString());
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Loaded asset is not a Blueprint: %s"), *AssetData.AssetName.ToString());
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Loaded %d GameCues_Object."), GameCuesObjectCollection.Num());

	
		// Clean up
		ObjectLibrary->RemoveFromRoot();
	}

void UGMC_AbilityCueManager::LoadGameCueActorsFromPath(const FString& Path)
{
		// Create an object library for UGameCue
	UObjectLibrary* ObjectLibrary = UObjectLibrary::CreateLibrary(AGameCue_Actor::StaticClass(), true, GIsEditor && !IsRunningCommandlet());

	if (!ObjectLibrary)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create UObjectLibrary for GameCue"));
		return;
	}

	// Load the assets from the specified path into the object library
	ObjectLibrary->AddToRoot();  // Ensure it stays in memory while loading


	ObjectLibrary->LoadBlueprintAssetDataFromPaths({Path},true);
	TArray<FAssetData> CueData;
	ObjectLibrary->GetAssetDataList(CueData);
	for (const FAssetData& AssetData : CueData)
	{
		// Check if the asset is a Blueprint
		if (AssetData.GetClass() == UBlueprint::StaticClass())
		{
			// Load the blueprint object
			UBlueprint* LoadedBlueprint = Cast<UBlueprint>(AssetData.GetAsset());
			if (LoadedBlueprint && LoadedBlueprint->GeneratedClass)
			{
				// Check if the generated class is a subclass of UGameCue
				if (LoadedBlueprint->GeneratedClass->IsChildOf(AGameCue_Actor::StaticClass()))
				{
					// Instantiate the GameCue class from the Blueprint
					AGameCue_Actor* GameCue = NewObject<AGameCue_Actor>(this, LoadedBlueprint->GeneratedClass);
					if (GameCue)
					{
						UE_LOG(LogTemp, Log, TEXT("Successfully loaded and instantiated: %s"), *LoadedBlueprint->GetName());
						GameCueActorCollection.Add(GameCue->CueTag, GameCue->GetClass());
					}
					else
					{
						UE_LOG(LogTemp, Error, TEXT("Failed to instantiate UGameCue from blueprint: %s"), *LoadedBlueprint->GetName());
					}
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Blueprint does not subclass UGameCue: %s"), *LoadedBlueprint->GetName());
				}
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to load blueprint or its generated class: %s"), *AssetData.AssetName.ToString());
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Loaded asset is not a Blueprint: %s"), *AssetData.AssetName.ToString());
		}
	}

		UE_LOG(LogTemp, Log, TEXT("Loaded %d GameCues_Actor."), GameCueActorCollection.Num());

		
	
		// Clean up
		ObjectLibrary->RemoveFromRoot();
}

void UGMC_AbilityCueManager::OnEffectRemoved(int EffectID)
{
	int WasRemoved = ActiveEffects.Remove(EffectID);
	if (WasRemoved == -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Effect ID does not exists"));

		
	}
	//UE_LOG(LogTemp, Warning, TEXT("Effect ID: %d Removed"), EffectID);
}

void UGMC_AbilityCueManager::OnEffectAdded(int EffectID, UObject* Object)
{
	int WasAdded = ActiveEffects.AddUnique(EffectID);
	if (WasAdded == -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Effect ID already exists"));
	}
	//UE_LOG(LogTemp, Warning, TEXT("Effect ID: %d added"), EffectID);
}

