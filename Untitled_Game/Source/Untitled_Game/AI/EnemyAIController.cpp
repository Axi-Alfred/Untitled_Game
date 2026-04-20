// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
	
	// Hämta player (MÅSTE UPPDATERAS OM VI KÖR CO-OP)
	PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	// Hämta manager
	TArray<AActor*> FoundManagers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AObjectiveManager::StaticClass(), FoundManagers);
	
	if (FoundManagers.Num() > 0)
	{
		ObjectiveManager = Cast<AObjectiveManager>(FoundManagers[0]);
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Player: %s"), *GetNameSafe(PlayerActor));
	UE_LOG(LogTemp, Warning, TEXT("Manager: %s"), *GetNameSafe(ObjectiveManager));
	
	SetActorTickEnabled(true);
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UpdateTarget();
}

void AEnemyAIController::UpdateTarget()
{
	if (!GetPawn() || !PlayerActor) return;
	
	if (!ObjectiveManager)
	{
		TArray<AActor*> FoundManagers;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AObjectiveManager::StaticClass(), FoundManagers);
		
		if (FoundManagers.Num() > 0)
		{
			ObjectiveManager = Cast<AObjectiveManager>(FoundManagers[0]);
			UE_LOG(LogTemp, Warning, TEXT("Manager FOUND: %s"), *GetNameSafe(ObjectiveManager));
		}
	}
	
	if (!ObjectiveManager) return;
	
	AActor* CurrentObjective = ObjectiveManager->GetCurrentObjective();
	UE_LOG(LogTemp, Warning, TEXT("CurrentObjective: %s"), *GetNameSafe(CurrentObjective));
	if (!CurrentObjective) return;
	
	float Distance = FVector::Dist(
		GetPawn()->GetActorLocation(),
		PlayerActor->GetActorLocation());
	
	AActor* NewTarget = (Distance < DetectionRadius) ? PlayerActor : CurrentObjective;
	
	// hämta blackboard och sätt ny target för enemies
	if (UBlackboardComponent* BB = GetBlackboardComponent())
	{
		AActor* CurrentBBTarget = Cast<AActor>(BB->GetValueAsObject("TargetActor"));
		
		if (CurrentBBTarget != NewTarget)
		{
			BB->SetValueAsObject("TargetActor", NewTarget);
		}
	}
}
