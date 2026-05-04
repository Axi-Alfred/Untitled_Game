
#include "ObjectiveManager.h"

AObjectiveManager::AObjectiveManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

AActor* AObjectiveManager::GetCurrentObjective() const
{
	if (Objectives.IsValidIndex(CurrentIndex))
	{
		return Objectives[CurrentIndex];
	}
	return nullptr;
}

void AObjectiveManager::SetObjectiveIndex(int32 Index)
{
	if (!Objectives.IsValidIndex(Index))
	{
		UE_LOG(LogTemp, Error, TEXT("invalid objective index: %d"), Index);
		return;
	}
	
	CurrentIndex = Index;
	
	UE_LOG(LogTemp, Warning, TEXT("NewObjective: %s"), *Objectives[CurrentIndex]->GetName());
}
