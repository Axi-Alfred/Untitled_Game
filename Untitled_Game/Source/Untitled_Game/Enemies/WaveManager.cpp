// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"
#include "Kismet/GameplayStatics.h"

void AWaveManager::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> FoundManagers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AObjectiveManager::StaticClass(), FoundManagers);
	
	if (FoundManagers.Num() > 0)
	{
		ObjectiveManager = Cast<AObjectiveManager>(FoundManagers[0]);
	}
	
	StartWave();
}

void AWaveManager::StartWave()
{
	// Detta kommer behöva ändras tror jag (just nu blir logiken att vi börjar slåss i "zon B/zon 2"
	if (ObjectiveManager)
	{
		ObjectiveManager->SetObjectiveIndex(CurrentZone);	
	}
	
	SpawnPortals();
}

void AWaveManager::SpawnPortals()
{
	ActivePortals = 0;
	
	TArray<AActor*> CurrentZonePoints;
	
	switch (CurrentZone)
	{
	case 0: CurrentZonePoints = ZoneAPoints; break;
	case 1: CurrentZonePoints = ZoneBPoints; break;
	case 2: CurrentZonePoints = ZoneCPoints; break;
	case 3: CurrentZonePoints = ZoneDPoints; break;
	default: break;
	}
	
	//kopierar spawnpoint för att sedan kunna ta bort dem spawnpoints som används
	TArray<AActor*> AvailableSpawnPoints = CurrentZonePoints;
	
	for (int i = 0; i < PortalsPerWave; i++)
	{
		if (AvailableSpawnPoints.Num() == 0) break;
		
		int Index = FMath::RandRange(0, AvailableSpawnPoints.Num() - 1);
		AActor* SpawnPoint = AvailableSpawnPoints[Index];
		
		//ta bort använda spawnpoints (förhindrar att portaler kan spawnas på samma ställe)
		AvailableSpawnPoints.RemoveAt(Index);
		
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
	
	UE_LOG(LogTemp, Warning, TEXT("Destroyed Portal, remaining active portals: %d"), ActivePortals);
	
	if (ActivePortals == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Wave cleared!"));
		ShowPortalsCleared();
		
		CurrentZone++;
		if (CurrentZone > 3)
		{
			CurrentZone = 0;
		}
		
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
