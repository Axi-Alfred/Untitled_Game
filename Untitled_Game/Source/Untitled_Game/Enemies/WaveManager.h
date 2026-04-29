// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ObjectiveManager.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveManager.generated.h"

UCLASS()
class UNTITLED_GAME_API AWaveManager : public AActor
{
	GENERATED_BODY()
	
public:	
	virtual void BeginPlay() override;
	
	// Portal BP
	UPROPERTY(EditAnywhere, Category="Portal")
	TSubclassOf<AActor> PortalClass;
	
	// Hur många portaler ska komma per wave
	UPROPERTY(EditAnywhere, Category="Portal")
	int PortalsPerWave = 3;
	
	// Portaler för varje zon
	UPROPERTY(EditAnywhere, Category="Zones")
	TArray<AActor*> ZoneAPoints;
	
	UPROPERTY(EditAnywhere, Category="Zones")
	TArray<AActor*> ZoneBPoints;
	
	UPROPERTY(EditAnywhere, Category="Zones")
	TArray<AActor*> ZoneCPoints;
	
	UPROPERTY(EditAnywhere, Category="Zones")
	TArray<AActor*> ZoneDPoints;
	
private:
	int ActivePortals = 0;
	int CurrentZone = 0;
	
	AObjectiveManager* ObjectiveManager;
	
	void StartWave();
	void SpawnPortals();

public:	
	UFUNCTION(BlueprintCallable, Category="Portal")
	void OnPortalDestroyed();
	
	UFUNCTION(BlueprintImplementableEvent)
	void ShowPortalsCleared();

};
