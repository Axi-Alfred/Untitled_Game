// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class UNTITLED_GAME_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemySpawner();

protected:
	virtual void BeginPlay() override;
	
	// Vad spawnas
	UPROPERTY(EditAnywhere, Category = "Spawner")
	TSubclassOf<APawn> EnemyClass;

	// Hur många
	UPROPERTY(EditAnywhere, Category = "Spawner")
	int EnemiesPerWave = 5;
	
	// Hur länge mellan varje spawn
	UPROPERTY(EditAnywhere, Category = "Spawner")
	float SpawnDelay = 1.0f;

	// Hur länge mellan waves
	UPROPERTY(EditAnywhere, Category = "Spawner")
	float WaveDelay = 10.f;
	
	// Spawnpoints
	UPROPERTY(EditAnywhere, Category = "Spawner")
	TArray<AActor*> SpawnPoints;
	

private:
	int SpawnedCount = 0;
	
	void SpawnEnemies();
	void StartWave();
	
	FTimerHandle SpawnTimer;

};
