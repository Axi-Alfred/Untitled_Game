// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	
	// Vart kan portaler spawnas
	UPROPERTY(EditAnywhere, Category="Portal")
	TArray<AActor*> PortalSpawnPoints;
	
	// Hur många portaler ska komma per wave
	UPROPERTY(EditAnywhere, Category="Portal")
	int PortalsPerWave = 3;
	
private:
	int ActivePortals = 0;
	
	void StartWave();
	void SpawnPortals();

public:	
	void OnPortalDestroyed();

};
