
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
	
	TimeUntilNextWave = TimeBetweenWaves;
		
	//Countdown mellan waves
	GetWorld()->GetTimerManager().SetTimer(
		CountdownTimerHandle,
		this,
		&AWaveManager::UpdateCountdown,
		1.0f,
		true);
	
	//Wave-Timer innan första waven också så att Sequence hinner köras och spelarna får en liten head-start
	GetWorld()->GetTimerManager().SetTimer(
		WaveTimerHandle,
		this,
		&AWaveManager::StartWave,
		TimeBetweenWaves,
		false);
}

void AWaveManager::StartWave()
{
	isCurrentWaveEmpowered = ShouldEmpowerNextWave;
	
	EnemiesAlive = 0;
	
	OnWaveStarted(CurrentWave);
	
	UE_LOG(LogTemp, Warning, TEXT("Wave started! Current wave: %d"), CurrentWave);
	
	//Öka antal fiender per wave
	EnemiesPerPortal = BaseEnemiesPerPortal + CurrentWave - 1;
	
	SpawnPortals();
	
	// Sätter tillbaka bool så att inte alla waves blir empowered
	ShouldEmpowerNextWave = false;
	isCurrentWaveEmpowered = false;
}

void AWaveManager::SpawnPortals()
{
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
	
	int32 PortalAmount = PortalsPerWave;
	
	if (ShouldEmpowerNextWave)
	{
		// Om nästa wave ska vara "flooded" så aktiverar vi alla möjliga portaler.
		PortalAmount = AvailableSpawnPoints.Num();
		
		UE_LOG(LogTemp, Warning, TEXT("EMPOWERED WAVE INCOMING!!!!"))
	}
	
	for (int32 i = 0; i < PortalAmount; i++)
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
		}
	}
}

void AWaveManager::AddAliveEnemy(AActor* Enemy)
{
	if (!Enemy) return;
	
	//Höj EnemiesAlive variabel
	EnemiesAlive++;
	
	//När enemy dör -> anropa EnemyDied()
	Enemy->OnDestroyed.AddDynamic(this, &AWaveManager::EnemyDied);
}

void AWaveManager::EnemyDied(AActor* DestroyedActor)
{
	EnemiesAlive--;
	TotalEnemiesKilled++;
	
	UE_LOG(LogTemp, Warning, TEXT("Enemy died, Enemies left: %d"), EnemiesAlive);
	
	if (EnemiesAlive <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Wave cleared!"));
		
		OnWaveEnded();
		ShowEnemiesCleared();
		
		CurrentWave++;
		
		//Loopar nuvarande zon mellan de 4 som existerar för nu
		CurrentZone++;
		if (CurrentZone > 3)
		{
			CurrentZone = 0;
		}
		
		TimeUntilNextWave = TimeBetweenWaves;
		
		//Countdown mellan waves
		GetWorld()->GetTimerManager().SetTimer(
			CountdownTimerHandle,
			this,
			&AWaveManager::UpdateCountdown,
			1.0f,
			true);
		
		//Starta nästa wave om "TimeBetweenWaves" sekunder
		GetWorld()->GetTimerManager().SetTimer(
			WaveTimerHandle,
			this,
			&AWaveManager::StartWave,
			TimeBetweenWaves,
			false);
	}
}

void AWaveManager::UpdateCountdown()
{
	TimeUntilNextWave--;
	
	if (TimeUntilNextWave == 10.0f)
	{
		// Synka det nuvarande objectivet med rätt zon som fiender spawnas i.
		if (ObjectiveManager)
		{
			ObjectiveManager->SetObjectiveIndex(CurrentZone);	
		}
	}
	
	OnCountdownUpdated(FMath::CeilToInt(TimeUntilNextWave));
	
	if (TimeUntilNextWave <= 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
	}
}

void AWaveManager::EmpowerNextWave()
{
	ShouldEmpowerNextWave = true;
	
	UE_LOG(LogTemp, Warning, TEXT("next wave will be flooded!"))
}
