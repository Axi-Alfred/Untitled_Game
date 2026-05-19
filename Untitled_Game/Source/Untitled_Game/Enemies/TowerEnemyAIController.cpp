#include "TowerEnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

void ATowerEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
	
	// Hämta manager
	TArray<AActor*> FoundManagers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AObjectiveManager::StaticClass(), FoundManagers);
	
	if (FoundManagers.Num() > 0)
	{
		ObjectiveManager = Cast<AObjectiveManager>(FoundManagers[0]);
	}
}

void ATowerEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UpdateTarget();
}

void ATowerEnemyAIController::UpdateTarget()
{
	if (!GetPawn() || !ObjectiveManager) return;
	
	AActor* CurrentObjective = ObjectiveManager->GetCurrentObjective();
	if (!CurrentObjective) return;
	
	// Sätt target till det Objective som är active
	AActor* NewTarget = CurrentObjective;
	
	// uppdaterar blackboard och sätt ny target
	if (UBlackboardComponent* BB = GetBlackboardComponent())
	{
		AActor* CurrentBBTarget = Cast<AActor>(BB->GetValueAsObject(TargetActorKey));
		
		if (CurrentBBTarget != NewTarget)
		{
			BB->SetValueAsObject(TargetActorKey, NewTarget);
			StopMovement();
		}
	}
}