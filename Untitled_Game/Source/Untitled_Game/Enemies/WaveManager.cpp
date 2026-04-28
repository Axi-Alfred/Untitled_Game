// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"

void AWaveManager::BeginPlay()
{
	Super::BeginPlay();
	
	StartWave();
}

void AWaveManager::StartWave()
{
	SpawnPortals();
}

void AWaveManager::SpawnPortals()
{
	ActivePortals = 0;
	
	for (int i = 0; i < PortalsPerWave; i++)
	{
		if (PortalSpawnPoints.Num() < 3) return;
		
		int Index = FMath::RandRange(0, PortalSpawnPoints.Num() - 1);
		AActor* SpawnPoint = PortalSpawnPoints[Index];
		
		if (SpawnPoint && PortalClass)
		{
			GetWorld()->SpawnActor<AActor>(
				PortalClass,
				SpawnPoint->GetActorLocation(),
				FRotator::ZeroRotator);
			
			ActivePortals++;
		}
	}
}

void AWaveManager::OnPortalDestroyed()
{
	ActivePortals--;
	
	UE_LOG(LogTemp, Warning, TEXT("Destroyed Portal, remaining active portals: &d"), ActivePortals);
	
	if (ActivePortals == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Wave cleared!"));
		
		// väntetid mellan waves
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle,
			this,
			&AWaveManager::StartWave,
			30.f,
			false);
	}
}
