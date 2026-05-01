
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
	EnemiesAlive = 0;
	
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
			AActor* Portal = GetWorld()->SpawnActor<AActor>(
				PortalClass,
				SpawnPoint->GetActorLocation(),
				FRotator::ZeroRotator);
			
			if (Portal)
			{
				ActivePortals++;
				
				EnemiesAlive += EnemiesPerPortal;
			}
		}
	}
}

void AWaveManager::OnPortalDestroyed()
{
	ActivePortals--;
	
	if (ActivePortals == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("All portals finished spawning"));
	}
}

void AWaveManager::EnemyDied()
{
	EnemiesAlive --;
	
	UE_LOG(LogTemp, Warning, TEXT("Enemy died, Enemies left: %d"), EnemiesAlive);
	
	if (EnemiesAlive <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Wave cleared!"));
		
		ShowEnemiesCleared();
		
		//Loopar nuvarande zon mellan de 4 som existerar för nu
		CurrentZone++;
		if (CurrentZone > 3)
		{
			CurrentZone = 0;
		}
		
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle,
			this,
			&AWaveManager::StartWave,
			TimeBetweenWaves,
			false);
	}
}