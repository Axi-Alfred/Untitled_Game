
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
	
	// Hämta player 
	// NOTE: (MÅSTE UPPDATERAS OM VI KÖR CO-OP)
	PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	// Hämta manager
	TArray<AActor*> FoundManagers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AObjectiveManager::StaticClass(), FoundManagers);
	
	if (FoundManagers.Num() > 0)
	{
		ObjectiveManager = Cast<AObjectiveManager>(FoundManagers[0]);
	}
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UpdateTarget();
}

void AEnemyAIController::UpdateTarget()
{
	if (!GetPawn() || !PlayerActor || !ObjectiveManager) return;
	
	AActor* CurrentObjective = ObjectiveManager->GetCurrentObjective();
	if (!CurrentObjective) return;
	
	float DistanceToPlayer = FVector::Dist(
		GetPawn()->GetActorLocation(),
		PlayerActor->GetActorLocation());
	
	AActor* NewTarget = (DistanceToPlayer < DetectionRadius) ? PlayerActor : CurrentObjective;
	
	// uppdaterar blackboard och sätt ny target (player eller objective)
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
