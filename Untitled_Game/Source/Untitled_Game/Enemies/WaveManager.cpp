
#include "WaveManager.h"
#include "Kismet/GameplayStatics.h"

void AWaveManager::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> FoundObjectiveManagers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AObjectiveManager::StaticClass(), FoundObjectiveManagers);
	
	if (FoundObjectiveManagers.Num() > 0)
	{
		ObjectiveManager = Cast<AObjectiveManager>(FoundObjectiveManagers[0]);
	}
	
	StartWave();
}

void AWaveManager::StartWave()
{
	// Synka det nuvarande objectivet med rätt zon som fiender spawnas i.
	if (ObjectiveManager)
	{
		ObjectiveManager->SetObjectiveIndex(CurrentZone);	
	}
	
	SpawnPortals();
}

void AWaveManager::SpawnPortals()
{
	ActivePortals = 0;
	
	// Välj spawnpoints baserat på vilken zon som ska attackeras.
	const TArray<AActor*>* CurrentZonePoints = nullptr;
	
	switch (CurrentZone)
	{
	case 0: CurrentZonePoints = &ZoneAPoints; break;
	case 1: CurrentZonePoints = &ZoneBPoints; break;
	case 2: CurrentZonePoints = &ZoneCPoints; break;
	case 3: CurrentZonePoints = &ZoneDPoints; break;
	default: return;
	}
	
	//kopierar spawnpoints för att inte kunna återanvända dem som redan används
	TArray<AActor*> AvailableSpawnPoints = *CurrentZonePoints;
	
	for (int32 i = 0; i < PortalsPerWave; i++)
	{
		if (AvailableSpawnPoints.Num() <= 0) break;
		
		int32 Index = FMath::RandRange(0, AvailableSpawnPoints.Num() - 1);
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
	
	if (ActivePortals <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Wave cleared!"));
		ShowPortalsCleared();
		
		CurrentZone++;
		
		if (CurrentZone > 3)
		{
			CurrentZone = 0;
		}
		
		// väntetid mellan waves
		FTimerHandle WaveTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(
			WaveTimerHandle,
			this,
			&AWaveManager::StartWave,
			CooldownPhaseTime,
			false);
	}
}
