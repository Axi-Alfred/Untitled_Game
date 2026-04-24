// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveManager.h"

AObjectiveManager::AObjectiveManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

AActor* AObjectiveManager::GetCurrentObjective() const
{
	if (Objectives.IsValidIndex(CurrentIndex))
	{
		return Objectives[CurrentIndex];
	}
	return nullptr;
}

void AObjectiveManager::AdvanceObjective()
{
	// Här kommer koden där vilket objective som skall attackeras ligga. (for now gå bara till nästa objective)
	CurrentIndex++;
	
	if (Objectives.IsValidIndex(CurrentIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("NewObjective: %s"), *Objectives[CurrentIndex]->GetName());
	}
}
