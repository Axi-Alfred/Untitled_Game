
#pragma once

#include "CoreMinimal.h"
#include "ObjectiveManager.h"
#include "GameFramework/Actor.h"
#include "WaveManager.generated.h"

UCLASS()
class UNTITLED_GAME_API AWaveManager : public AActor
{
	GENERATED_BODY()
	
public:	
	virtual void BeginPlay() override;
	
	// Portal-klass som spawnas under waves
	UPROPERTY(EditAnywhere, Category="Wave")
	TSubclassOf<AActor> PortalClass;
	
	// Hur många portaler ska komma per wave
	UPROPERTY(EditAnywhere, Category="Wave")
	int32 PortalsPerWave = 3;
	
	// Spawnpoints för varje zon
	UPROPERTY(EditAnywhere, Category="Zones")
	TArray<AActor*> ZoneAPoints;
	
	UPROPERTY(EditAnywhere, Category="Zones")
	TArray<AActor*> ZoneBPoints;
	
	UPROPERTY(EditAnywhere, Category="Zones")
	TArray<AActor*> ZoneCPoints;
	
	UPROPERTY(EditAnywhere, Category="Zones")
	TArray<AActor*> ZoneDPoints;
	
	// Variabel för att hålla koll på hur många fiender kvar innan wave avlsutas
	UPROPERTY(BlueprintReadOnly)
	int32 EnemiesAlive = 0;
	
	UPROPERTY(BlueprintReadOnly)
	int32 CurrentWave = 1;
	
	UPROPERTY(BlueprintReadOnly)
	float TimeUntilNextWave = 0.f;
	
	// Hur många fiender ska portaler spawna
	UPROPERTY(BlueprintReadOnly)
	int32 EnemiesPerPortal;
	
	//Hur många fiender ska portaler spawna från start
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Wave")
	int32 BaseEnemiesPerPortal = 1;
	
	//Väntetid mellan waves
	UPROPERTY(EditAnywhere, Category="Wave")
	float TimeBetweenWaves = 30.f;
	
	UFUNCTION(BlueprintCallable)
	void AddAliveEnemy(AActor* Enemy);
	
	UFUNCTION(BlueprintCallable)
	void EnemyDied(AActor* DestroyedActor);
	
	// Event för UI feedback (PLACEHOLDER JUST NU)
	UFUNCTION(BlueprintImplementableEvent)
	void ShowEnemiesCleared();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnWaveStarted(int32 WaveNumber);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnCountdownUpdated(int32 TimeLeft);
	
	FTimerHandle WaveTimerHandle;
	FTimerHandle CountdownTimerHandle;
	
	void UpdateCountdown();
	
private:
	
	// index för vilken zon som är under attack
	// 0 = A, 1 = B, 2 = C, 3 = D
	int32 CurrentZone = 0;
	
	// Referens till ObjectiveManager för att kunna byta objective vid nya waves.
	UPROPERTY()
	AObjectiveManager* ObjectiveManager;
	
	void StartWave();
	void SpawnPortals();
};
