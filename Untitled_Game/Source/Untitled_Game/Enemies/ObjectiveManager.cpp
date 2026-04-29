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

void AObjectiveManager::SetObjectiveIndex(int Index)
{
	CurrentIndex = Index;
	
	if (Objectives.IsValidIndex(CurrentIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("NewObjective: %s"), *Objectives[CurrentIndex]->GetName());
	}
}
