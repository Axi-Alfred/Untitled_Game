
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectiveManager.generated.h"

UCLASS()
class UNTITLED_GAME_API AObjectiveManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AObjectiveManager();
	
	// Lista på alla objectives i leveln
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Objectives")
	TArray<AActor*> Objectives;
	
	// Nuvarande objective index, 
	// 0 = Zon A, 1 = Zon B, 2 = Zon C, 3 = Zon D.
	UPROPERTY(BlueprintReadOnly, Category="Objectives")
	int32 CurrentIndex = 0;
	
	// Returnerar nuvarande objective actor
	AActor* GetCurrentObjective() const;
	
	// Sätter vilket objective som är "under attack"
	void SetObjectiveIndex(int32 Index);
};
