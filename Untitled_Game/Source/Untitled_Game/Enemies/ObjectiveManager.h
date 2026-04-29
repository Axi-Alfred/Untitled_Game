// Fill out your copyright notice in the Description page of Project Settings.

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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> Objectives;
	
	UPROPERTY(BlueprintReadOnly)
	int CurrentIndex = 0;
	
	AActor* GetCurrentObjective() const;
	
	void SetObjectiveIndex(int Index);
};
