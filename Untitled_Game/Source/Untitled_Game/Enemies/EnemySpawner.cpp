// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	StartWave();
}

void AEnemySpawner::StartWave()
{
	SpawnedCount = 0;
	
	GetWorld()->GetTimerManager().SetTimer(
		SpawnTimer, 
		this,
		&AEnemySpawner::SpawnEnemies,
		SpawnDelay,
		true);
}

void AEnemySpawner::SpawnEnemies()
{
	UE_LOG(LogTemp, Warning, TEXT("SpawnEnemies() called"));
	
	if (SpawnedCount >= EnemiesPerWave)
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimer);
		
		//Starta nästa wave
		FTimerHandle WaveHandle;
		GetWorld()->GetTimerManager().SetTimer(
			WaveHandle,
			this,
			&AEnemySpawner::StartWave,
			WaveDelay,
			false
		);
		
		return;
	}
	
	if (EnemyClass)
	{
		FVector SpawnLocation = GetActorLocation();
		
		if (SpawnPoints.Num() > 0)
		{
			int Index = FMath::RandRange(0, SpawnPoints.Num() - 1);
			AActor* SpawnPoint = SpawnPoints[Index];
			
			if (SpawnPoint)
			{
				SpawnLocation = SpawnPoint->GetActorLocation();
			}
		}
		
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
		GetWorld()->SpawnActor<APawn>(
			EnemyClass,
			SpawnLocation,
			FRotator::ZeroRotator,
			SpawnParams
		);
		
		SpawnedCount++;
	}
}

