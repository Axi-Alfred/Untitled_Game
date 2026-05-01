
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
	
	// väntetid mellan waves
	UPROPERTY(EditAnywhere, Category="Wave")
	float CooldownPhaseTime = 30.f;
	
	// Spawnpoints för varje zon
	UPROPERTY(EditAnywhere, Category="Zones")
	TArray<AActor*> ZoneAPoints;
	
	UPROPERTY(EditAnywhere, Category="Zones")
	TArray<AActor*> ZoneBPoints;
	
	UPROPERTY(EditAnywhere, Category="Zones")
	TArray<AActor*> ZoneCPoints;
	
	UPROPERTY(EditAnywhere, Category="Zones")
	TArray<AActor*> ZoneDPoints;

	// Kallas av portaler när dem förstörs
	UFUNCTION(BlueprintCallable, Category="Wave")
	void OnPortalDestroyed();
	
	// Event för UI feedback (PLACEHOLDER JUST NU)
	UFUNCTION(BlueprintImplementableEvent, Category="Wave")
	void ShowPortalsCleared();
	
private:
	
	// Antal portaler som lever
	int32 ActivePortals = 0;
	
	// index för vilken zon som är under attack
	// 0 = A, 1 = B, 2 = C, 3 = D
	int32 CurrentZone = 0;
	
	// Referens till ObjectiveManager för att kunna byta objective vid nya waves.
	UPROPERTY()
	AObjectiveManager* ObjectiveManager;
	
	void StartWave();
	void SpawnPortals();
};
