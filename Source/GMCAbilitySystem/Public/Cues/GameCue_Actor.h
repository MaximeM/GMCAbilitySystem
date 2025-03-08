// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "GameCue_Actor.generated.h"

UCLASS(Blueprintable, meta = (ShowWorldContextPin), hidecategories = (Replication))
class GMCABILITYSYSTEM_API AGameCue_Actor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGameCue_Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Called on Destroy
	virtual void Destroyed() override;
	
	virtual void HandleGameCue(AActor* TargetActor);

public:


	UFUNCTION(BlueprintImplementableEvent, Category = "GameCue", DisplayName = "HandleGameCue", meta=(ScriptName = "HandleGamCue"))
	void K2_HandleGameCue(AActor* TargetActor) const;

	
	/** Execute the cue on the target actor. Overridable in Blueprints. */
	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	bool ExecuteCue(AActor* TargetActor);
	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/** Tag associated with this cue. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameCue")
	FGameplayTag CueTag;
	
};
